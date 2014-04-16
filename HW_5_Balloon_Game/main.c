//
//  main.c
//  HW_5_Balloon_Game
//
//  Created by Tanner Embry on 4/15/14.
//  Copyright (c) 2014 Tanner Embry. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "balloon.h"


//inline void clearscreen(){
//#if defined (__WIN32__)
//    system("cls");
//    return;
//#endif
//
//system("clear");
//}

//TODO make this work for windows also
void clearscreen(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {

    gameboard *pGameboard;
    pGameboard = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(GamePiece));
    
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y=0; y<BOARD_SIZE; y++){
            CreateGamePiece(NO_PIECE, x, y, DOWN, pGameboard);
        }
    }
    
    //make the 4 blasters
    GamePiece *topBlaster = SetGamePiece(BLASTER, BOARD_SIZE/2, 0, DOWN, pGameboard);
    GamePiece *bottomBlaster = SetGamePiece(BLASTER, BOARD_SIZE/2, BOARD_SIZE-1, UP, pGameboard);
    GamePiece *leftBlaster = SetGamePiece(BLASTER, 0, BOARD_SIZE/2, RIGHT, pGameboard);
    GamePiece *rightBlaster = SetGamePiece(BLASTER, BOARD_SIZE-1, BOARD_SIZE/2, RIGHT, pGameboard);

    
    PrintGameboard(pGameboard);
    
    
    RemoveGameboard(pGameboard);
}