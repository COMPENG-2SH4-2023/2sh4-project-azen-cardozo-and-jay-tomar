#include "Player.h"


Player::Player(GameMechs* thisGMRef,Food* thisfood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,\
                      mainGameMechsRef->getBoardSizeY()/2,'*');

    
    //get foodinfo
    foodinfo = thisfood;
    
    
    //Set the inital playerPos
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    
    switch(mainGameMechsRef->getInput()) //modify the current moving direction
        {                      
            
            case 'w':
            case 'W':
                if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = UP;
                }
                break;
            
            case 's':
            case 'S':
                if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = DOWN;
                }
                break;
            
            case 'a':
            case 'A':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = LEFT;
                }
                break;
            
            case 'd':
            case 'D':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = RIGHT;
                }
                break;
            
            case ' ':
                mainGameMechsRef->setExitTrue();

            default:
                break;
        }

}

void Player::movePlayer()
{
    //Finite State Machine logic

    objPos currHead;
    playerPosList->getHeadElement(currHead);

    switch(myDir)//measuring the moving direction
    {
        case UP: //move up and wrap around from bottom
            currHead.y--;
            if(currHead.y<1)
            {
                currHead.y+=13;
            }
            break;
    
    
        case DOWN: //move down and wrap around from top
            currHead.y++;
            if(currHead.y>13)
            {
                currHead.y-=13;
            }
            break;
        
    
        case LEFT: //move left and wrap around from right
            currHead.x--;
            if(currHead.x<1)
            {
                currHead.x+=28;
            }
            break;

        case RIGHT: //move right and wrap around from left
            currHead.x++;
            if(currHead.x>28)
            {
                currHead.x-=28;
            }
            break;
    
    
        default:
            break;
    }

    
    //move the snake
    playerPosList->insertHead(currHead);
    playerPosList->removeTail();
    

}

int Player::checkFoodConsumption()
{
    int set;
    objPos currHead,foodpos;
    playerPosList->getHeadElement(currHead); //get the info of head element
    
    objPosArrayList* food = foodinfo->getFoodPos(); //get the info of food


    for(int i=0;i<food->getSize();i++)
    {
        food->getElement(foodpos,i);
        if(foodpos.isPosEqual(&currHead) &&foodpos.symbol=='o') //check if the general food is consumed
        {
            set = 1;
            break;
        }

        else if(foodpos.isPosEqual(&currHead) && foodpos.symbol=='@') //check if the special food is consumed
        {
            set = 2;
            break;
        }

        else //no food being consumed
        {
            set =0;
        }
    }
    

    return set;
}

void Player::increasePlayerLength()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    playerPosList->insertHead(currHead);
}


bool Player::checkSelfCollision()
{
    int k;
    objPos currHead,bodypart;
    playerPosList->getHeadElement(currHead);

    if(playerPosList->getSize()>1)  //make sure the player has been generated
    {
        for(k=2; k<playerPosList->getSize();k++) //check if the head element collided with the body
        {
            playerPosList->getElement(bodypart,k);

            if(bodypart.x == currHead.x && bodypart.y == currHead.y)
            {
                break;
            }
        }

        if(k != playerPosList->getSize()) //if collided
        {
            return true;
        }
        
    }

    return false;
}


