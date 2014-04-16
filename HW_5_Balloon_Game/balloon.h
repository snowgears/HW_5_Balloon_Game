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
#define NO_PIECE        8


////////////////////////
//  Type Definitions  //
////////////////////////

typedef struct{
    int type;
    int x;
    int y;
    int direction;
}GamePiece;

typedef GamePiece *gameboard[BOARD_SIZE][BOARD_SIZE];


///////////////////////
//     Functions     //
///////////////////////

GamePiece *CreateGamePiece(int type, int x, int y, int direction, gameboard *pGameboard);

GamePiece *SetGamePiece(int type, int x, int y, int direction, gameboard *pGameboard);

int PrintGameboard(gameboard *pGameboard);

int RemoveGameboard(gameboard *pGameboard);
