#include "Food.h"


Food::Food()
{
    foodbucket = new objPosArrayList();
}

Food::~Food()
{
    delete foodbucket;
}


void Food::generateFood(objPosArrayList* blockOff)
{
    int x,y,k,size;
    int count = 0;
    int board[30][15] = {0}; //generate a vector set to check if the coordinates have been taken
    bool not_overlap = false;
    objPos tempplayer, tempfood;

    size = foodbucket->getSize(); //get the size list

    while(size>0) // clear all the food in bucket
    {
        foodbucket->removeHead();
        size--;
    }

    while(count < 3) //generate three common food
    {

        bool Flag = true;
        x = rand() % (30-2)+1;
        y = rand() % (15-2)+1;

        tempfood.setObjPos(x,y,'o');

        

        for(int k=0; k<blockOff->getSize();k++) //check if the food coordinate overlaps with the snake
        {
            blockOff->getElement(tempplayer,k);
            if(tempplayer.isPosEqual(&tempfood))
            {
                Flag =false;
                break;
            }
        }   

        
        if(Flag)
        {
            if(board[tempfood.x][tempfood.y] == 0 ) //if the coordnate hasn't been occupied
            {
                //add the coordinate and mark the corresponding vector
                foodbucket->insertTail(tempfood); 
                board[tempfood.x][tempfood.y]++; 
                count++;
            }
        }

    }

    while(count < 5) //generate two special food
    {

        bool Flag = 1;
        x = rand() % (30-2)+1;
        y = rand() % (15-2)+1;

        tempfood.setObjPos(x,y,'@');

        for(int k=0; k<blockOff->getSize();k++) //if the coordnate hasn't been occupied
        {
            blockOff->getElement(tempplayer,k); 
            if(tempplayer.isPosEqual(&tempfood))
            {
                Flag =0;
                break;
            }
        }   

        
        if(Flag)
        {
            if(board[tempfood.x][tempfood.y] == 0 )
            {
                //add the coordinate and mark the corresponding vector
                foodbucket->insertTail(tempfood);
                board[tempfood.x][tempfood.y]++;
                count++;
            }
        }

    }
    
}

objPosArrayList* Food::getFoodPos()
{
    return foodbucket;
}