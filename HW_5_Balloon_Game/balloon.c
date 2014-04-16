//
//  balloon.c
//  HW_5_Balloon_Game
//
//  Created by Tanner Embry on 4/15/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "balloon.h"


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a balloon structure                          //
//  Parameters:                                                    //
//            Starting point on the board (x,y)                    //
//            Direction to move accross board (direction)          //
//  Returns:                                                       //
//            Pointer to the balloon that was created              //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Balloon *CreateBalloon(int x, int y, int direction){
    Balloon *pBalloon = NULL;
    pBalloon = malloc(sizeof(Balloon));
    
    pBalloon->x = x;
    pBalloon->y = y;
    pBalloon->direction = direction;
    
    return pBalloon;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a cat structure                              //
//  Parameters:                                                    //
//            Starting point on the board (x,y)                    //
//  Returns:                                                       //
//            Pointer to the cat that was created                  //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Cat *CreateCat(int x, int y){
    Cat *pCat = NULL;
    pCat = malloc(sizeof(Cat));
    
    pCat->x = x;
    pCat->y = y;

    //TODO CALCULATE CLOSEST BALLOON HERE
    //WILL ALSO CALCULATE CLOSEST BALLOON EVERY SINGLE ITERATION
    
    return pCat;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a blaster structure                          //
//  Parameters:                                                    //
//            Edge to create the blaster on (side)                 //
//  Returns:                                                       //
//            Pointer to the blaster that was created              //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Blaster *CreateBlaster(int side){
    Blaster *pBlaster = NULL;
    pBlaster = malloc(sizeof(Blaster));
    
    int midPoint = BOARD_SIZE/2;
    
    if(side == UP){
        pBlaster->x = midPoint;
        pBlaster->y = 0;
        pBlaster->direction = DOWN;
    }
    else if(side == DOWN){
        pBlaster->x = midPoint;
        pBlaster->y = BOARD_SIZE-1;
        pBlaster->direction = UP;
    }
    else if(side == LEFT){
        pBlaster->x = 0;
        pBlaster->y = midPoint;
        pBlaster->direction = RIGHT;
    }
    else{
        pBlaster->x = BOARD_SIZE-1;
        pBlaster->y = midPoint;
        pBlaster->direction = LEFT;
    }

    return pBlaster;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates a laser structure                            //
//  Parameters:                                                    //
//            Starting point on the board (x,y)                    //
//            Direction to move accross board (direction)          //
//  Returns:                                                       //
//            Pointer to the laser that was created                //
//                                                                 //
/////////////////////////////////////////////////////////////////////

Laser *CreateLaser(int x, int y, int direction){
    Laser *pLaser = NULL;
    pLaser = malloc(sizeof(Laser));
    
    pLaser->x = x;
    pLaser->y = y;
    pLaser->direction = direction;
    
    return pLaser;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Prints the gameboard out to the console              //
//  Parameters:                                                    //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int PrintGameboard(gameboard *pGameboard){
    int x;
    int y;

    printf("\n");
    for (x=1; x < BOARD_SIZE; x++){
        for (y=1; y < BOARD_SIZE; y++){
            if((*pGameboard)[x][y] == BLASTER){
                printf(">");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}








