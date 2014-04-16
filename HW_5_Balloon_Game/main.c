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
    pGameboard = calloc(BOARD_SIZE * BOARD_SIZE, sizeof(char));
    
    CreateBlaster(UP);
    CreateBlaster(DOWN);
    CreateBlaster(LEFT);
    CreateBlaster(RIGHT);
    
    PrintGameboard(pGameboard);
    
    
    free(pGameboard);
}