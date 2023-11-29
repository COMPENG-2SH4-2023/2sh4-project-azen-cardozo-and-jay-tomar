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
    int x,y,k;
    int count = 0;
    bool not_overlap = false;
    objPos tempplayer;
    objPos tempfood;

    int board[30][15] = {0};

    int size = foodbucket->getSize();
    while(size>0)
    {
        foodbucket->removeHead();
        size--;
    }

    while(count < 3)
    {

        bool Flag = 1;
        x = rand() % (30-2)+1;
        y = rand() % (15-2)+1;

        tempfood.setObjPos(x,y,'o');

        

        for(int k=0; k<blockOff->getSize();k++)
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
                foodbucket->insertTail(tempfood);
                board[tempfood.x][tempfood.y]++;
                count++;
            }
        }

    }

    while(count < 5)
    {

        bool Flag = 1;
        x = rand() % (30-2)+1;
        y = rand() % (15-2)+1;

        tempfood.setObjPos(x,y,'@');

        for(int k=0; k<blockOff->getSize();k++)
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