#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000



//global variables
GameMechs* myGM;
Player* myPlayer;
Food* myfood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();


    myGM = new GameMechs(30,15);
    myfood = new Food();
    myPlayer = new Player(myGM,myfood);

    
    
    

    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    myfood->generateFood(tempPlayer);


    srand(time(NULL));  



}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();  

    myGM->clearInput();


    
    //objPos tempPlayer;
    //myPlayer->getPlayerPos(tempPlayer);
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPos temphead;
    tempPlayer->getHeadElement(temphead);

    objPos tempfood;
    myfood->getFoodPos(tempfood);


    if(myPlayer->checkFoodConsumption())
    {
        myPlayer->increasePlayerLength();
        myfood->generateFood(tempPlayer);
        myGM->incrementScore();
        

    }
    
    if(myPlayer->checkSelfCollision())
    {
        myGM->setlostFlagTrue();
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    int k;
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPos bodypart;

    objPos tempfood;
    myfood->getFoodPos(tempfood);

    objPos currHead;
    tempPlayer->getHeadElement(currHead);
    

    
    for(int i = 0;i < myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j< myGM->getBoardSizeX() ;j++)
        {

            for(k=0; k<tempPlayer->getSize();k++)
            {
                tempPlayer->getElement(bodypart,k);
                
                if(bodypart.x == j&&bodypart.y==i)
                {
                    break;
                }
            }

            if(k != tempPlayer->getSize())
            {
                MacUILib_printf("%c",bodypart.symbol);
            }

            else if( i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("#");
            }
            else
            {

                if(i == tempfood.y && j == tempfood.x)
                {
                    MacUILib_printf("%c",tempfood.symbol);
                }

                else
                {
                    MacUILib_printf(" ");
                }
                
    
            }
        }
        MacUILib_printf("\n");
    } 
    MacUILib_printf("Player's Head: <%d,%d>\nScores: %d\n",currHead.x,currHead.y,myGM->getScore());
    MacUILib_printf("Food: %dx%d\n",tempfood.x,tempfood.y);
    if(myPlayer->checkSelfCollision())
    {
        MacUILib_printf("Self Collision Happen !!!\n");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
}
