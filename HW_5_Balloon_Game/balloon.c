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
//            Creates a GamePiece structure                        //
//  Parameters:                                                    //
//            Type of GamePiece (type)                             //
//            Starting point on the board (x,y)                    //
//            Direction to move across board (direction)          //
//  Returns:                                                       //
//            Pointer to the balloon that was created              //
//                                                                 //
/////////////////////////////////////////////////////////////////////

GamePiece *CreateGamePiece(int type, int x, int y, int direction, gameboard *pGameboard){
    GamePiece *pGamePiece = NULL;
    pGamePiece = malloc(sizeof(GamePiece));
    
    pGamePiece->type = type;
    pGamePiece->x = x;
    pGamePiece->y = y;
    pGamePiece->direction = direction;
    
    (*pGameboard)[x][y] = pGamePiece;
    
    return pGamePiece;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Changes a game piece on the board                    //
//  Parameters:                                                    //
//            Type of GamePiece (type)                             //
//            Starting point on the board (x,y)                    //
//            Direction to move across board (direction)           //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            Pointer to the balloon that was created              //
//                                                                 //
/////////////////////////////////////////////////////////////////////

GamePiece *SetGamePiece(int type, int x, int y, int direction, gameboard *pGameboard){
    GamePiece *pGamePiece = (*pGameboard)[x][y];

    pGamePiece->type = type;
    pGamePiece->x = x;
    pGamePiece->y = y;
    pGamePiece->direction = direction;
    
    return pGamePiece;
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
    for (x=0; x < BOARD_SIZE; x++){
        for (y=0; y < BOARD_SIZE; y++){
            GamePiece *gp = (*pGameboard)[x][y];
            if(gp->type == BLASTER){
                printf(" > ");
            }
            else
                printf("   ");
        }
        printf("\n");
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Removes the gameboard and frees all elements         //
//  Parameters:                                                    //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int RemoveGameboard(gameboard *pGameboard){
    int x;
    int y;

    for (x=0; x < BOARD_SIZE; x++){
        for (y=0; y < BOARD_SIZE; y++){
            GamePiece *gp = (*pGameboard)[x][y];
            free(gp);
        }
    }
    
    free(pGameboard);
    
    return 0;
}



