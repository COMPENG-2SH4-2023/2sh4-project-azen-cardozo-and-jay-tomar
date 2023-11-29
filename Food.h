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
        objPosArrayList* foodbucket; //need to change


    public:
        //Constructor and Destructor
        Food(); //need to update
        ~Food();

        //getters
        void generateFood(objPosArrayList* blockOff); //need to upgrade
        objPosArrayList* getFoodPos(); //need to update

};

#endif