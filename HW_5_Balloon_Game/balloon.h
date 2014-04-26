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

#define UP              1
#define DOWN            2
#define LEFT            3
#define RIGHT           4

#define BLASTER         5
#define BALLOON         6
#define CAT             7
#define LASER           8
#define NO_PIECE        0

#define TRUE            9
#define FALSE           10


////////////////////////
//  Type Definitions  //
////////////////////////

typedef struct{
    int type;
    int y;
    int x;
    int direction;
    int moveInProgress;
}GamePiece;

typedef GamePiece *gameboard[BOARD_SIZE][BOARD_SIZE];


///////////////////////
//     Functions     //
///////////////////////

GamePiece *CreateGamePiece(int type, int x, int y, int direction, gameboard *pGameboard);

int ChangeGamePiece(GamePiece *pGamePiece, int type, int direction, int moveInProgress);

int MoveGamePiece(GamePiece *pGamePiece, int direction, gameboard *pGameboard);

int PrintGameboard(gameboard *pGameboard);

int RemoveGameboard(gameboard *pGameboard);

int StepTowardNearestBalloon(GamePiece *pGamePiece, gameboard *pGameboard);

int IterateGameboard(gameboard *pGameboard);

gameboard *SetupGameboard(void);

GamePiece *GetBlaster(int direction, gameboard *pGameboard);

int ShootLaser(GamePiece *pBlaster, gameboard *pGameboard);

int rand_mid(int low, int high);

int PlacePiecesRandomlyAtEdges(gameboard *pGameboard);
