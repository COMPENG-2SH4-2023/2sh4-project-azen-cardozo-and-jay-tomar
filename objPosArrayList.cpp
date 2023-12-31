#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;

}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeArray == sizeList) //check if the array has been full
    {
        return;
    }

    for(int i=sizeList ; i>0 ;i--)
    {
        aList[i].setObjPos(aList[i-1]);

    }

    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeArray == sizeList) //check if the array has been full
    {
        return;
    }

    aList[sizeList].setObjPos(thisPos);

    sizeList++;
}

void objPosArrayList::removeHead()
{
    if(sizeList == 0) // check if the list is empty
    {
        return;
    }   

    for(int i =0;i<sizeList-1;i++) //shift all the elements to the left
    {
        aList[i].setObjPos(aList[i+1]);
    }
    sizeList--;

}

void objPosArrayList::removeTail()
{
    if(sizeList ==0) // check if the list is empty
    {
        return;
    }

    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList ==0) // check if the list is empty
    {
        return;
    }

    returnPos.setObjPos(aList[0]);

}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(sizeList ==0) // check if the list is empty
    {
        return;
    }

    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(sizeList ==0) // check if the list is empty
    {
        return;
    }

    returnPos.setObjPos(aList[index]);

}