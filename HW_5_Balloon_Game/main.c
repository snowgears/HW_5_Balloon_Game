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

//TODO make this method utilize the system commands for clearing the screen
void clearscreen(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {

    printf("This is a 2D shooter game. You have 4 blasters, each on its respective edge of the board.\n");
    printf("Your goal is to shoot as many balloons (Q) as you can.\n");
    printf("Cats (M) will try to get to the balloons before you do. If a cat touches a balloon, they both dissapear.\n");
    printf("Once you shoot a cat, the game is over.\n");
    printf("\n");
    printf("CONTROLS:\n");
    printf("------------------------------------\n");
    printf("i - switch to top blaster.\n");
    printf("k - switch to bottom blaster.\n");
    printf("j - switch to left blaster.\n");
    printf("l - switch to right blaster.\n");
    printf("a,w,s,d - move selected blaster in a direction.\n");
    printf("SPACE_BAR - shoot from selected blaster.\n");
    printf("\n");
    printf("THE GAME WILL START WHEN YOU PRESS ENTER.\n");
    printf("\n");
    
    
    gameboard *pGameboard = SetupGameboard();
    
//    GamePiece *catPiece = (*pGameboard)[6][3];
//    ChangeGamePiece(catPiece, CAT, UP);
    GamePiece *balloonPiece = (*pGameboard)[13][7];
    ChangeGamePiece(balloonPiece, BALLOON, UP, FALSE);
    GamePiece *balloonPiece2 = (*pGameboard)[1][7];
    ChangeGamePiece(balloonPiece2, BALLOON, DOWN, FALSE);

    PrintGameboard(pGameboard);
    
    int selectedBlaster = UP;
    int c = getchar();
    GamePiece *pBlaster = GetBlaster(selectedBlaster, pGameboard);
    
    //user pressed enter
    if(c == '\n'){
        printf("GAME START.\n");
        for(;;){
            c = getchar();
            switch (c) {
                case 'i':
                    selectedBlaster = UP;
                    break;
                case 'k':
                    selectedBlaster = DOWN;
                    break;
                case 'j':
                    selectedBlaster = LEFT;
                    break;
                case 'l':
                    selectedBlaster = RIGHT;
                    break;
                case 'a':
                    pBlaster = GetBlaster(selectedBlaster, pGameboard);
                    MoveGamePiece(pBlaster, LEFT, pGameboard);
                    break;
                case 'w':
                    pBlaster = GetBlaster(selectedBlaster, pGameboard);
                    MoveGamePiece(pBlaster, UP, pGameboard);
                    break;
                case 's':
                    pBlaster = GetBlaster(selectedBlaster, pGameboard);
                    MoveGamePiece(pBlaster, DOWN, pGameboard);
                    break;
                case 'd':
                    pBlaster = GetBlaster(selectedBlaster, pGameboard);
                    MoveGamePiece(pBlaster, RIGHT, pGameboard);
                    break;
                case ' ':
                    pBlaster = GetBlaster(selectedBlaster, pGameboard);
                    ShootLaser(pBlaster, pGameboard);
                    break;
                default:
                    break;
            }
            
            IterateGameboard(pGameboard);
            clearscreen();
            PrintGameboard(pGameboard);
        }
    }

    RemoveGameboard(pGameboard);
}