#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "objPosArrayList.h"


class Food
{
    private:
        objPos foodPos;


    public:
        //Constructor and Destructor
        Food();
        ~Food();

        //getters
        void generateFood(objPosArrayList* blockOff); //need to upgrade
        void getFoodPos(objPos &returnPos);

};

#endif