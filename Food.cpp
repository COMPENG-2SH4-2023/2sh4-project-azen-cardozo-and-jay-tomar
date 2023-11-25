#include "Food.h"


Food::Food()
{
    foodPos.setObjPos(-1,-1,'o');
}


void Food::generateFood(objPosArrayList* blockOff)
{
    int x,y,k;
    bool breakloop = false;
    bool not_overlap = false;
    objPos tempBody;


    while(!breakloop)
    {
        x = rand() % (30-1)+1;
        y = rand() % (15-1)+1;
        foodPos.setObjPos(x,y,'o');

        for(k=0; k<blockOff->getSize();k++)
        {
            blockOff->getElement(tempBody,k);
            if(tempBody.isPosEqual(&foodPos))
            {
                break;
            }
        }
        
        if(k==blockOff->getSize())
        {
            not_overlap = true;
        }

        if(x != 29 && y != 14 && not_overlap)
        {
            breakloop = true;
        }

    }
    
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}