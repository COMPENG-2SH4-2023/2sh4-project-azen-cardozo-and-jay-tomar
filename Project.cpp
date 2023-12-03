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

    //initalzied variables
    myGM = new GameMechs(30,15);
    myfood = new Food();
    myPlayer = new Player(myGM,myfood);


    //initialize food avoid player position
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    myfood->generateFood(tempPlayer);


    //update time
    srand(time(NULL));  



}

void GetInput(void)
{
    myGM->getInput();
}


void RunLogic(void)
{

    //move the snake
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();  
    myGM->clearInput();


    
    //get the player position and food position
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPos temphead;
    tempPlayer->getHeadElement(temphead);



    //if general food consumed
    if(myPlayer->checkFoodConsumption()==1)
    {
        //increase one score and add one lengthen
        myPlayer->increasePlayerLength();
        myfood->generateFood(tempPlayer);
        myGM->incrementScore();

    }

    else if(myPlayer->checkFoodConsumption()==2) //if special food consumed
    {
        //add 10 scores without increasing lengthen
        myfood->generateFood(tempPlayer);
        for(int i=0;i<10;i++) myGM->incrementScore();

    }

    //check if self collision happens
    if(myPlayer->checkSelfCollision())
    {
        myGM->setlostFlagTrue();
    }
    
}


void DrawScreen(void)
{
    MacUILib_clearScreen();  

    //local variables
    objPos bodypart,tempfoodpos;
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPosArrayList* tempfoodbucket = myfood->getFoodPos();


    //get the information of the head element
    objPos currHead;
    tempPlayer->getHeadElement(currHead);
    
    for(int i = 0;i < myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j< myGM->getBoardSizeX() ;j++)
        {

            for(int k=0; k<tempPlayer->getSize();k++) //get the body cooridnate
            {
                tempPlayer->getElement(bodypart,k);
                
                if(bodypart.x == j&&bodypart.y==i)
                {
                    break;
                }
            }

            for(int k=0; k<tempfoodbucket->getSize();k++) //get the food coordinate
            {
                tempfoodbucket->getElement(tempfoodpos,k);
                
                if(tempfoodpos.x == j&&tempfoodpos.y==i)
                {
                    break;
                }
            }

            if(j == bodypart.x && i == bodypart.y)
            {
                MacUILib_printf("%c",bodypart.symbol);
            }

            else if( j == tempfoodpos.x && i == tempfoodpos.y)
            {
                MacUILib_printf("%c",tempfoodpos.symbol);
            }

            else if( i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("#");
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    } 

    //display current info
    MacUILib_printf("Press \"space\" to exit\n");
    MacUILib_printf("Eat \"@\" to get 10 marks !\n");
    MacUILib_printf("Snake's Head: <%d,%d>\nScores: %d\n",currHead.x,currHead.y,myGM->getScore());
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(myGM ->getlostFlagStatus())
    {
        MacUILib_printf("Self Collision Happen !!!\n");
        MacUILib_printf("Final score: %d",myGM->getScore());
        MacUILib_uninit();
    }

    else{
        MacUILib_printf("Final score: %d",myGM->getScore());
        MacUILib_uninit();
    }

    delete myGM;
    delete myPlayer;
    delete myfood;
}
