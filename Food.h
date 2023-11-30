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
        objPosArrayList* foodbucket;


    public:
        //Constructor and Destructor
        Food(); 
        ~Food();

        
        void generateFood(objPosArrayList* blockOff); 
        objPosArrayList* getFoodPos(); 

};

#endif