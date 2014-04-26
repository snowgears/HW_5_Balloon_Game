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
#include <math.h>


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Changes a game piece on the board                    //
//  Parameters:                                                    //
//            Pointer to the GamePiece to change (pGamePiece)      //
//            Type to change the piece to (type)                   //
//            Direction the new piece will move in (direction)     //
//            Update moveInProgress to TRUE/FALSE (moveInProgress) //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int ChangeGamePiece(GamePiece *pGamePiece, int type, int direction, int moveInProgress){

    pGamePiece->type = type;
    pGamePiece->direction = direction;
    pGamePiece->moveInProgress = moveInProgress;
    
    return 0;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Calculates a random number in a range                //
//  Parameters:                                                    //
//            Lower end of range (low)                             //
//            Upper end of range (high)                            //
//  Returns:                                                       //
//            The random number that was calculated                //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int rand_mid(int low, int high) {
    return low+rand()%(high-low+1);
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
                switch (gp->direction){
                    case UP:
                        printf(" ^ ");
                        break;
                    case DOWN:
                        printf(" v ");
                        break;
                    case LEFT:
                        printf(" < ");
                        break;
                    case RIGHT:
                        printf(" > ");
                        break;
                    default:
                        break;
                }
            }
            else if(gp->type == BALLOON){
                printf(" Q ");
            }
            else if(gp->type == CAT){
                printf(" M ");
            }
            else if(gp->type == LASER){
                if(gp->direction == LEFT || gp->direction == RIGHT){
                    printf(" - ");
                }
                else{
                    printf(" | ");
                }
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


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Checks if a pieces future location is valid          //
//  Parameters:                                                    //
//            Pointer to the piece to be checked (pGamePiece)      //
//            Location the piece is trying to move to (x,y)        //
//  Returns:                                                       //
//            0: Location is not valid                             //
//            1: Location is valid                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int LocationIsValid(GamePiece *pGamePiece, int x, int y){
    
    if(x < 0 || x > BOARD_SIZE-1 || y < 0 || y > BOARD_SIZE-1)
        return 0;
    
    if(pGamePiece->type == BLASTER){
        if(pGamePiece->x == 0 || pGamePiece->x == BOARD_SIZE-1){
            if(y > 0 && y < BOARD_SIZE-1 && (x == 0 || x == BOARD_SIZE-1))
                return 1;
            else
                return 0;
        }
        else if(pGamePiece->y == 0 || pGamePiece->y == BOARD_SIZE-1){
            if(x > 0 && x < BOARD_SIZE-1 && (y == 0 || y == BOARD_SIZE-1))
                return 1;
            else
                return 0;
        }
    }
    
    if(x > 1 && x < BOARD_SIZE-2 && y > 1 && y < BOARD_SIZE-2)
        return 1;
    
    return 0;
}


///////////////////////////////////////////////////////////////////////
//  Function:                                                        //
//            Moves a cat piece one step towards the nearest balloon //
//  Parameters:                                                      //
//            Pointer to the game piece to be moved (pGamePiece)     //
//            Pointer to the gameboard (pGameboard)                  //
//  Returns:                                                         //
//            0: Success                                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

int StepTowardNearestBalloon(GamePiece *pGamePiece, gameboard *pGameboard){
    int loopX;
    int loopY;
    
    int tempDistance;
    int smallestDistance = 1000;
    GamePiece *nearestBalloon = NULL;
    
    int catX = pGamePiece->x;
    int catY = pGamePiece->y;
    int balloonX;
    int balloonY;
    
    if(pGamePiece->moveInProgress == TRUE){
        return 0;
    }
    
    //ITERATE THROUGH BOARD AND CALCULATE THE NEAREST BALLOON PIECE
    for (loopX=0; loopX < BOARD_SIZE; loopX++){
        for (loopY=0; loopY < BOARD_SIZE; loopY++){
            GamePiece *gp = (*pGameboard)[loopX][loopY];
            if(gp->type == BALLOON){
                tempDistance = sqrt(((loopX-catX)*(loopX-catX)) + ((loopY-catY)*(loopY-catY)));

                if(tempDistance < smallestDistance){
                    smallestDistance = tempDistance;
                    nearestBalloon = gp;
                }
            }
        }
    }
    
    if(nearestBalloon == NULL){
        return 0;
    }
    else{
        balloonX = nearestBalloon->x;
        balloonY = nearestBalloon->y;
    }

    //line of game pieces from the cat to the balloon
    GamePiece *lineToBalloon[smallestDistance];
    
    int dx = abs(balloonX-catX), sx = catX<balloonX ? 1 : -1;
    int dy = abs(balloonY-catY), sy = catY<balloonY ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    int loopI;
    for(loopI=0; loopI<1000; loopI++){
        GamePiece *gp = (*pGameboard)[catX][catY];
        lineToBalloon[loopI] = gp;
        
        if (catX==balloonX && catY==balloonY) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; catX += sx; }
        if (e2 < dy) { err += dx; catY += sy; }
    }

    //move cat to new location in the matrix, one step closer to nearest balloon
    
    GamePiece *pNewLocPiece = lineToBalloon[1];
    //The cat will only move toward the balloon if the adjacent space is clear. It will not attempt to go around any other pieces to get to the balloon.
    if(pNewLocPiece->type == NO_PIECE){
        ChangeGamePiece(pNewLocPiece, pGamePiece->type, pGamePiece->direction, TRUE);
        ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, TRUE);
    }
    else if(pNewLocPiece->type == BALLOON){
        //cat popped balloon causing the cat
        ChangeGamePiece(pNewLocPiece, NO_PIECE, DOWN, TRUE);
        ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, TRUE);
    }
    
    return 0;
    
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Gets the opposite direction from a direction         //
//  Parameters:                                                    //
//            Direction to find the opposite of (direction)        //
//  Returns:                                                       //
//            The opposite direction that was computed             //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int GetOppositeDirection(int direction){
    switch (direction){
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            return UP;
    }
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Moves a piece in a direction on the board            //
//  Parameters:                                                    //
//            Pointer to the piece to be moved (pGamePiece)        //
//            Direction to move the piece in (direction)           //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0+: Amount to increment score by                     //
//            -1: A laser piece hit a cat piece (end game)         //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int MoveGamePiece(GamePiece *pGamePiece, int direction, gameboard *pGameboard){
    int x = pGamePiece->x;
    int y = pGamePiece->y;
    int newX = x;
    int newY = y;
    
    int scoreToAdd = 0;
    
    if(pGamePiece->type != BLASTER){
        if(pGamePiece->type == NO_PIECE || pGamePiece->moveInProgress == TRUE)
            return 0;
    }
    
    switch (direction) {
        case UP:
            newX--;
            break;
        case DOWN:
            newX++;
            break;
        case LEFT:
            newY--;
            break;
        case RIGHT:
            newY++;
            break;
        default:
            break;
    }
    
    if(LocationIsValid(pGamePiece, newX, newY)){
        
        GamePiece *pNewLocPiece = (*pGameboard)[newX][newY];
        if(pNewLocPiece->type == NO_PIECE){
            ChangeGamePiece(pNewLocPiece, pGamePiece->type, pGamePiece->direction, TRUE);
            ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, FALSE);
        }
        //laser hit another game piece
        else if(pGamePiece->type == LASER){
           
            if(pNewLocPiece->type == CAT){
                ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, FALSE);
                ChangeGamePiece(pNewLocPiece, NO_PIECE, DOWN, FALSE);
                return -1;
            }
            ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, FALSE);
            ChangeGamePiece(pNewLocPiece, NO_PIECE, DOWN, FALSE);
            
            scoreToAdd++;
        }
        //two balloons run into each other
        else if(pNewLocPiece->type == BALLOON && pGamePiece->type == BALLOON){
            ChangeGamePiece(pNewLocPiece, BALLOON, GetOppositeDirection(pNewLocPiece->direction), TRUE);
            ChangeGamePiece(pGamePiece, BALLOON, GetOppositeDirection(pGamePiece->direction), TRUE);
        }
    }
    //the location moving to is not valid
    else{
        //remove it from the board as it has moved out of bounds (unless it is a BLASTER)
        if(pGamePiece->type != BLASTER)
            ChangeGamePiece(pGamePiece, NO_PIECE, DOWN, FALSE);
    }

    return scoreToAdd;
}


/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Places a game piece in a random open spot            //
//            on a random edge of the gameboard                    //
//  Parameters:                                                    //
//            Type of piece to place (type)                        //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int PlacePieceOnRandomEdge(int type, gameboard *pGameboard){
    int placeX;
    int placeY;
    
    int edge = rand_mid(UP, RIGHT);
    int spot = rand_mid(1, BOARD_SIZE-2);
    
    if(edge == UP){
        placeX = 1;
        placeY = spot;
    }
    else if(edge == DOWN){
        placeX = BOARD_SIZE-2;
        placeY = spot;
    }
    else if(edge == LEFT){
        placeX = spot;
        placeY = 1;
    }
    else{ //edge == RIGHT
        placeX = spot;
        placeY = BOARD_SIZE-2;
    }
    
    GamePiece *pieceToPlace = (*pGameboard)[placeX][placeY];
    
    if (pieceToPlace->type != NO_PIECE){
        return PlacePieceOnRandomEdge(type, pGameboard);
    }
    
    int direction = GetOppositeDirection(edge);
    
    ChangeGamePiece(pieceToPlace, type, direction, FALSE);
    
    return 0;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Places game pieces randomly on the gameboard edges   //
//  Parameters:                                                    //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int PlacePiecesRandomlyAtEdges(gameboard *pGameboard){

    int catsToPlace = 1;
    int balloonsToPlace = 2;
    
    int extraCatChance = rand_mid(0, 10);
    if(extraCatChance > 6)
        catsToPlace++;
    
    int extraBalloonChance = rand_mid(0, 10);
    if(extraBalloonChance > 4)
        balloonsToPlace++;
    
    
    //TODO place all cats and balloons in random spots around edges
    //Only place in spots with NO_PIECE
    
    while (balloonsToPlace > 0 || catsToPlace > 0){

        if(balloonsToPlace > 0){
            balloonsToPlace--;
            PlacePieceOnRandomEdge(BALLOON, pGameboard);
        }
        if(catsToPlace > 0){
            catsToPlace--;
            PlacePieceOnRandomEdge(CAT, pGameboard);
        }
        
    }
    
    return 0;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Iterate all elements on the gameboard                //
//  Parameters:                                                    //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0+: Amount to increment score by, keep game going    //
//            -1: A cat was hit by a laser, end game               //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int IterateGameboard(gameboard *pGameboard){
    int x;
    int y;
    int endGame;
    
    int scoreToAdd = 0;
    
    //iterate through positively for UP and LEFT directions to avoid override
    for (x=1; x < BOARD_SIZE-1; x++){
        for (y=1; y < BOARD_SIZE-1; y++){
            GamePiece *gp = (*pGameboard)[x][y];
            
            if(gp->moveInProgress == FALSE){
                if(gp->type == CAT){
                    StepTowardNearestBalloon(gp, pGameboard);
                }
                if(gp->direction == LEFT || gp->direction == UP){
                    endGame = MoveGamePiece(gp, gp->direction, pGameboard);
                    if(endGame == -1)
                        return -1;
                    else
                        scoreToAdd+=endGame;
                }
            }
        }
    }

    //iterate through negatively for DOWN and RIGHT directions to avoid override
    for (x=BOARD_SIZE-2; x >= 1; x--){
        for (y=BOARD_SIZE-2; y >= 1; y--){
            GamePiece *gp = (*pGameboard)[x][y];
            
            if(gp->moveInProgress == FALSE){
                if(gp->type == CAT){
                    StepTowardNearestBalloon(gp, pGameboard);
                }
                if(gp->direction == RIGHT || gp->direction == DOWN){
                    endGame = MoveGamePiece(gp, gp->direction, pGameboard);
                    if(endGame == -1)
                        return -1;
                    else
                        scoreToAdd+=endGame;
                }
            }
        }
    }
    
    //now change all pieces moveInProgress to false for next iteration
    for (x=BOARD_SIZE-2; x >= 1; x--){
        for (y=BOARD_SIZE-2; y >= 1; y--){
            GamePiece *gp = (*pGameboard)[x][y];
            gp->moveInProgress = FALSE;
        }
    }

    return scoreToAdd;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Creates gameboard and all elements on it             //
//  Returns:                                                       //
//            Pointer to the gameboard that was created            //
//                                                                 //
/////////////////////////////////////////////////////////////////////

gameboard *SetupGameboard(void){
    gameboard *pGameboard;
    pGameboard = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(GamePiece));
    
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y=0; y<BOARD_SIZE; y++){
            
            GamePiece *pGamePiece = NULL;
            pGamePiece = malloc(sizeof(GamePiece));
            
            pGamePiece->type = NO_PIECE;
            pGamePiece->x = x;
            pGamePiece->y = y;
            pGamePiece->direction = DOWN;
            pGamePiece->moveInProgress = FALSE;
            
            (*pGameboard)[x][y] = pGamePiece;
        }
    }
    
    
    GamePiece *topBlaster = (*pGameboard)[0][BOARD_SIZE/2];
    GamePiece *bottomBlaster = (*pGameboard)[BOARD_SIZE-1][BOARD_SIZE/2];
    GamePiece *leftBlaster = (*pGameboard)[BOARD_SIZE/2][0];
    GamePiece *rightBlaster = (*pGameboard)[BOARD_SIZE/2][BOARD_SIZE-1];
    
    ChangeGamePiece(topBlaster, BLASTER, DOWN, FALSE);
    ChangeGamePiece(bottomBlaster, BLASTER, UP, FALSE);
    ChangeGamePiece(leftBlaster, BLASTER, RIGHT, FALSE);
    ChangeGamePiece(rightBlaster, BLASTER, LEFT, FALSE);
    
    return pGameboard;
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Gets the blaster on a specific edge                  //
//  Parameters:                                                    //
//            Direction (or edge) to get blaster on (direction)    //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            Pointer to the blaster that was found                //
//                                                                 //
/////////////////////////////////////////////////////////////////////

GamePiece *GetBlaster(int direction, gameboard *pGameboard){
    int i = 0;

    switch (direction) {
        case UP:
            for(i=0; i<BOARD_SIZE-1; i++){
                GamePiece *gp = (*pGameboard)[0][i];
                if(gp->type == BLASTER)
                    return gp;
            }
            break;
        case DOWN:
            for(i=0; i<BOARD_SIZE-1; i++){
                GamePiece *gp = (*pGameboard)[BOARD_SIZE-1][i];
                if(gp->type == BLASTER)
                    return gp;
            }
            break;
        case LEFT:
            for(i=0; i<BOARD_SIZE-1; i++){
                GamePiece *gp = (*pGameboard)[i][0];
                if(gp->type == BLASTER)
                    return gp;
            }
            break;
        case RIGHT:
            for(i=0; i<BOARD_SIZE-1; i++){
                GamePiece *gp = (*pGameboard)[i][BOARD_SIZE-1];
                if(gp->type == BLASTER)
                    return gp;
            }
            break;
        default:
            break;
    }
    return (*pGameboard)[0][0];
}

/////////////////////////////////////////////////////////////////////
//  Function:                                                      //
//            Spawns a laser in front of a blaster that travels    //
//            in the correct direction                             //
//  Parameters:                                                    //
//            Pointer to the blaster GamePiece (pBlaster)          //
//            Pointer to the gameboard (pGameboard)                //
//  Returns:                                                       //
//            0: Success                                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

int ShootLaser(GamePiece *pBlaster, gameboard *pGameboard){
    int laserX = pBlaster->x;
    int laserY = pBlaster->y;

    switch (pBlaster->direction) {
        case UP:
            laserX--;
            break;
        case DOWN:
            laserX++;
            break;
        case LEFT:
            laserY--;
            break;
        case RIGHT:
            laserY++;
            break;
        default:
            break;
    }
    
    GamePiece *pLazerPiece = (*pGameboard)[laserX][laserY];
    ChangeGamePiece(pLazerPiece, LASER, pBlaster->direction, FALSE);
    
    return 0;
}



