//
//  balloon.h
//  HW_5_Balloon_Game
//
//  Created by Tanner Embry on 4/15/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//


///////////////////////
//     Constants     //
///////////////////////

#define BOARD_SIZE      15

#define UP              0
#define DOWN            1
#define LEFT            2
#define RIGHT           3

#define BLASTER         4
#define BALLOON         5
#define CAT             6
#define LASER           7


////////////////////////
//  Type Definitions  //
////////////////////////

typedef int gameboard[BOARD_SIZE][BOARD_SIZE];

typedef struct{
    int x;
    int y;
    int direction;
}Balloon;

typedef struct{
    int x;
    int y;
    Balloon *closestBalloon;
}Cat;

typedef struct{
    int x;
    int y;
    int direction;
}Blaster;

typedef struct{
    int x;
    int y;
    int direction;
}Laser;


///////////////////////
//     Functions     //
///////////////////////

Blaster *CreateBlaster(int side);

int PrintGameboard(gameboard *pGameboard);