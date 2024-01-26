#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "main.h"
#include "terminal.h"
#include "UCPLinkedList.h"

/*
Title:      		main.c
Author:     		Jet Ng
Date/LastModified:  31/05/2023
Description:       	main function for the Box game, Assignment 2 COMP1000 - UCP

                    Utilises game.c, UCPLinkedList.c, and terminal.c using user provided parameters via a 
                    file with game information (map size, player, box, goal, walls) to create 
                    a game map (2D array) with a border, a player, a goal position, walls,
                    and spawn a box for the player to push into the goal to win.

                    Takes 'w','a','s','d' as user controls to move the player position on the map
                    in terminal(P). Player then aims to push the box into the goal by moving their
                    P position in a way that pushes the box(B) towards the goal (G).

                    I've made the player (P) yellow, to have the P figure on the terminal to be more prominent
                    and visually interact more pleasantly with the box trail rather than a clear/no background.

                    The user can also choose to undo their previous move by pressing 'u', which will move the 
                    game state one user action back.

                    The box (B) will have a blue-coloured trail to show where it has been and this is also
                    reversed as part of the undo action by pressing 'u'.

                    Player can also have the ability to PULL the box, 
                    if makefile is defined with PULL=1 (make PULL=1 in terminal)

                    Game finishes when the box is moved into the goal, goal turns from red
                    to green, win message is printed to terminal and game/main ends.

                    *** PLEASE SEE COMMENT BLOCK ON LINES 518-528 REGARDING MEMORY LEAK DIAGNOSIS ***
                    I have tried to troubleshoot what is wrong, but summary is if that code block is implemented
                    (comment tags removed), the program will have no memory leaks as the prevGameState is free'd
                    appropriately and the program will work PERFECTLY under valgrind execution, but if you try
                    under normal execution, the undo functionality will hit segmentation fault and crash.

                    With that block commented out, VALGRIND will detect memory leaks (as expected), BUT the
                    program WILL WORK normally under NORMAL EXECUTION and UNDO will work CORRECTLY.

                    I don't know why this is, tried for a couple days to do all kinds to fix it but ultimately
                    this is the compromise I have, I hope I can get some feedback as to why this is and how
                    I can get it working with no memory leaks + normal functionality under normal execution.
*/

int main(int argc, char* argv[])
{
    system("clear");
    if (argc == 2)
    { 
        FILE* file;
        file = fopen(argv[1], "r");

        /*  If check for invalid file or no file found */
        if (file == NULL)
        {
            printf("File failed to open or doesn't not exist, please check filename spelling and try again.\n");
        } 

        /* Else, the conditions have passed checks above and therefore are appropriate parameters and we start the game logic */
        else
        {
            char currentLine[20];
            char mapRow[10];
            char mapCol[10];
            char rowCoord[10];
            char colCoord[10];
            char featureType[10]; /* all of the above are to store game info from the file opened */
            int mapRowSize, mapColSize;
            int i = 0;
            int moveCount = 0;
            int initialRun = 1;

            struct Coordinates wallCoords[1000][2];
            struct Coordinates boxHistory[1000][2]; /* using same structure for walls to track the box move history */
            struct gameState gState; /* declare gameState (gState) struct to hold current values for the game map */

            int bRow, bCol, playerCol, playerRow, goalRow, goalCol, gActive = 0;
            char moveCh;

            /* initialise linked list to hold gState structs for undo functionality */
            UCPLinkedList* gameList = (UCPLinkedList*)malloc(sizeof(UCPLinkedList));
            gameList->listHead = NULL;
            gameList->listTail = NULL;

            /* read first line of map file to get map rows/col (map size) */
            fgets(currentLine, sizeof(currentLine), file);
            sscanf(currentLine, "%s %s", mapRow, mapCol);
            memset(wallCoords, 0, sizeof(wallCoords));
            memset(boxHistory, 0, sizeof(boxHistory));
            
            mapRowSize = atoi(mapRow);
            mapColSize = atoi(mapCol);

            /* then 2nd line onwards in map file is for game info (player/box/walls) */
            while (fgets(currentLine, sizeof(currentLine), file) != NULL)
            {
                sscanf(currentLine, "%s %s %s", rowCoord, colCoord, featureType);
                if (featureType[0] == 'P')
                {
                    playerRow = atoi(rowCoord);
                    playerCol = atoi(colCoord);
                }
                else if (featureType[0] == 'B')
                {
                    bRow = atoi(rowCoord);
                    bCol = atoi(colCoord);
                }
                else if (featureType[0] == 'G')
                {
                    goalRow = atoi(rowCoord);
                    goalCol = atoi(colCoord);
                }
                else if (featureType[0] == 'O')
                {
                    wallCoords[i][0].wallRow = atoi(rowCoord);
                    wallCoords[i][1].wallCol = atoi(colCoord);
                    i++;
                }
            }

            fclose(file); /* got all info from file, close file */

            /* Print out introductory program text and information */
            printf("\nWelcome to Assignment 1 - Box Game\nIn this game you(P) will try and push a box(B) into a goal(G) using the keys w,a,s,d.\n");
            printf("Box Parameter Format: As given in the map file provided (%s x %s)\n,",mapRow,mapCol);

            /* initiate starting state of game map */
            gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);

            /* assign current game values to struct for holding the current game state (gState), and insert into gameList
            to track history of game states */
            gState.mapRows = mapRowSize;
            gState.mapCols = mapColSize;
            gState.playerRowPos = playerRow;
            gState.playerColPos = playerCol;
            gState.goalRowPos = goalRow;
            gState.goalColPos = goalCol;
            gState.boxRowPos = bRow;
            gState.boxColPos = bCol;
            gState.gameWalls = wallCoords;
            insertFirst(gameList, &gState);
            
            
            /* Game loop */
            while ((gActive) == 0) 
            {
                /* Print movement options to terminal and use provided terminal.c functions to scanf and take user input */
                struct gameState* prevGameState = (struct gameState*)malloc(sizeof(struct gameState));
                
                boxHistory[moveCount][0].wallRow = bRow;
                boxHistory[moveCount][1].wallCol = bCol;             
                
                if (initialRun == 1) /* on first loop of game, input invalid key to save gameState to linkedList */
                {
                    moveCh = 'P';
                    initialRun = 0;
                    moveCount++;
                }
                
                /* this if-else is to prevent undo functionality eating itself and causing segmentation error when you spam it and there are no more moves to undo.*/
                if (moveCount != 0)
                {
                    *prevGameState = gState;
                    insertFirst(gameList, prevGameState);
                }
                else
                {
                    if ((moveCount == 0) && (gameList->listHead == NULL))
                    {
                        *prevGameState = gState;
                        insertFirst(gameList, prevGameState);
                    }
                }
                
                printf("\n");
                printf("\nMove the box to the goal to win the game!\nPress w to move up\nPress s to move down\nPress a to move left\nPress d to move right\nPress u to undo/go back to your previous move\n");
                disableBuffer();
                scanf(" %c", &moveCh);
                enableBuffer();

            
                /* all 'w' case movement options, logic for PULL + PUSH, and print out new gameArray state after movement of player + box (if it has been pushed/pulled) */
                if ((moveCh) == 'w')
                {
                    system("clear");
                    #ifdef PULL
                        if ((bRow == 1))
                        {
                            /* do nothing / don't let box move past border */
                        }
                        else if (((bRow) == ((playerRow)+1)) && ((bCol) == (playerCol)))
                        {
                            bRow--;
                        }
                    #endif
                    if ((bRow == 0) || (bRow == (mapRowSize)))
                    {
                        /* do nothing / don't let box move past border */
                    }
                    else if (((bRow) == ((playerRow-1))) && ((bCol) == (playerCol)))
                    {
                        bRow--;
                    }

                    /* wall collision logic for box */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((bRow) == (wallCoords[i][0].wallRow)) && ((bCol) == (wallCoords[i][1].wallCol)))
                        {
                            bRow++;
                        }
                        i++;
                    }
                    i = 0;

                    if ((playerRow == 0) || ((playerRow == (bRow+1) && playerCol == (bCol)) && (playerRow == 1)))
                    {
                        /* do nothing / don't let player move past border or let player move into box position on border */
                    }
                    else
                    {
                        playerRow--;
                    }

                    /* wall collision logic for player */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((playerRow) == (wallCoords[i][0].wallRow)) && ((playerCol) == (wallCoords[i][1].wallCol)))
                        {
                            playerRow++;
                        }
                        i++;
                    }
                    i = 0;

                    /* redraw game with updated values, and update values of current game state */
                    gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);

                    gState.mapRows = mapRowSize;
                    gState.mapCols = mapColSize;
                    gState.playerRowPos = playerRow;
                    gState.playerColPos = playerCol;
                    gState.goalRowPos = goalRow;
                    gState.goalColPos = goalCol;
                    gState.boxRowPos = bRow;
                    gState.boxColPos = bCol;
                    gState.gameWalls = wallCoords;
                    
                    moveCount++;                  
                }
                
                /* all 'a' case movement options, logic for PULL + PUSH, and print out new gameArray state after movement of player + box (if it has been pushed/pulled) */
                else if ((moveCh) == 'a')
                {

                    system("clear");
                    #ifdef PULL
                        if ((bCol == 1))
                        {
                            /* do nothing / don't let box move past border */
                        }
                        else if (((bCol) == ((playerCol)+1)) && ((bRow) == (playerRow)))
                        {
                            bCol--;
                        }
                    #endif
                    if ((bCol == 0))
                    {
                        /* do nothing / don't let box move past border */
                    }
                    else if ((bCol-1) == 'O')
                    {
                        /* do nothing / don't let box move past border */
                    }
                    else if (((bCol) == ((playerCol-1))) && ((bRow) == (playerRow)))
                    {
                        bCol--;
                    }

                    /* wall collision logic for box */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((bRow) == (wallCoords[i][0].wallRow)) && ((bCol) == (wallCoords[i][1].wallCol)))
                        {
                            bCol++;
                        }
                        i++;
                    }
                    i = 0;
                    
                    if ((playerCol == 0) || ((playerRow == (bRow) && playerCol == (bCol+1)) && (playerCol == 1)))
                    {
                        /* do nothing / don't let player move past border or let player move into box position on border */
                    }
                    else
                    {
                        playerCol--;
                    }

                    /* wall collision logic for player */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((playerRow) == (wallCoords[i][0].wallRow)) && ((playerCol) == (wallCoords[i][1].wallCol)))
                        {
                            playerCol++;
                        }
                        i++;
                    }
                    i = 0;

                    /* redraw game with updated values, and update values of current game state */
                    gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);

                    gState.mapRows = mapRowSize;
                    gState.mapCols = mapColSize;
                    gState.playerRowPos = playerRow;
                    gState.playerColPos = playerCol;
                    gState.goalRowPos = goalRow;
                    gState.goalColPos = goalCol;
                    gState.boxRowPos = bRow;
                    gState.boxColPos = bCol;
                    gState.gameWalls = wallCoords;
                    moveCount++;                   
                }
                
                /* all 's' case movement options, logic for PULL + PUSH, and print out new gameArray state after movement of player + box (if it has been pushed/pulled) */
                else if ((moveCh) == 's')
                {
                
                    system("clear");
                    #ifdef PULL
                        if (((bRow) == (mapRowSize-2)))
                        {
                            /* do nothing / don't let box move past border */
                        }
                        else if (((bRow) == ((playerRow)-1)) && ((bCol) == (playerCol)))
                        {
                            bRow++;
                        }
                    #endif   
                    if (((bRow == (mapRowSize-1))))
                    {
                        /* do nothing / don't let box move past border */
                    }
                    else if (((bRow) == ((playerRow+1))) && ((bCol) == (playerCol)))
                    {
                        bRow++;
                    }

                    /* wall collision logic for box */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((bRow) == (wallCoords[i][0].wallRow)) && ((bCol) == (wallCoords[i][1].wallCol)))
                        {
                            bRow--;
                        }
                        i++;
                    }
                    i = 0;

                    
                    if ((playerRow == (mapRowSize-1)) || ((playerRow == (bRow-1) && playerCol == (bCol)) && (playerRow == (mapRowSize-2))))
                    {
                        /* do nothing / don't let player move past border or let player move into box position on border */
                    }
                    else
                    {
                        playerRow++;
                    }

                    /* wall collision logic for player */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((playerRow) == (wallCoords[i][0].wallRow)) && ((playerCol) == (wallCoords[i][1].wallCol)))
                        {
                            playerRow--;
                        }
                        i++;
                    }
                    i = 0;

                    /* redraw game with updated values, and update values of current game state */
                    gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);

                    gState.mapRows = mapRowSize;
                    gState.mapCols = mapColSize;
                    gState.playerRowPos = playerRow;
                    gState.playerColPos = playerCol;
                    gState.goalRowPos = goalRow;
                    gState.goalColPos = goalCol;
                    gState.boxRowPos = bRow;
                    gState.boxColPos = bCol;
                    gState.gameWalls = wallCoords;

                    moveCount++;                  
                }
                
                /* all 'd' case movement options, logic for PULL + PUSH, and print out new gameArray state after movement of player + box (if it has been pushed/pulled) */
                else if ((moveCh) == 'd')
                {   
                    system("clear");
                    #ifdef PULL
                        if ((bCol == ((mapColSize)-2)))
                        {
                            /* do nothing / don't let box move past border */
                        }
                        else if (((bCol) == ((playerCol-1))) && ((bRow) == (playerRow)))
                        {
                            bCol++;
                        }
                    #endif
                    if ((bCol == ((mapColSize-1))))
                    {
                        /* do nothing / don't let box move past border */
                    }
                    else if (((bCol) == ((playerCol)+1)) && ((bRow) == (playerRow)))
                    {
                        bCol++;
                    }

                    /* wall collision logic for box */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((bRow) == (wallCoords[i][0].wallRow)) && ((bCol) == (wallCoords[i][1].wallCol)))
                        {
                            bCol--;
                        }
                        i++;
                    }
                    i = 0;
                    
                    if ((playerCol == (mapColSize-1)) || ((playerRow == (bRow)) && (playerCol == (bCol-1)) && (playerCol == (mapColSize-2))))
                    {
                        /* do nothing / don't let player move past border or let player move into box position on border */
                    }
                    else
                    {
                        playerCol++;
                    }

                    /* wall collision logic for player */
                    while (wallCoords[i][0].wallRow != 0)
                    {
                        if (((playerRow) == (wallCoords[i][0].wallRow)) && ((playerCol) == (wallCoords[i][1].wallCol)))
                        {
                            playerCol--;
                        }
                        i++;
                    }
                    i = 0;

                    /* redraw game with updated values, and update values of current game state */
                    gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);

                    gState.mapRows = mapRowSize;
                    gState.mapCols = mapColSize;
                    gState.playerRowPos = playerRow;
                    gState.playerColPos = playerCol;
                    gState.goalRowPos = goalRow;
                    gState.goalColPos = goalCol;
                    gState.boxRowPos = bRow;
                    gState.boxColPos = bCol;
                    gState.gameWalls = wallCoords;

                    moveCount++; 
                }

                else if ((moveCh) == 'u')
                {
                    system("clear");

                    /* check if game state is at initial, if not then proceed */
                    if (gameList->listHead != NULL && (moveCount != 0))
                    {
                        removeFirst(gameList);
                        free(prevGameState);
                        prevGameState = NULL;

                        /* remove/get last gameState from linked list, assign to current gameState, refresh map with this gameState, and update values of game */
                        prevGameState = (struct gameState*)removeFirst(gameList);
                        gState = *prevGameState;
                        gameArray(gState.mapRows, gState.mapCols, gState.playerRowPos, gState.playerColPos, gState.goalRowPos, gState.goalColPos, gState.boxRowPos, gState.boxColPos, gState.gameWalls, boxHistory, moveCount);
                        
                        mapRowSize = gState.mapRows;
                        mapColSize = gState.mapCols;
                        playerRow = gState.playerRowPos;
                        playerCol = gState.playerColPos;
                        goalRow = gState.goalRowPos;
                        goalCol = gState.goalColPos;
                        bRow = gState.boxRowPos;
                        bCol = gState.boxColPos;
                        
                        moveCount--;
                    }
                    
                    /* else, game is at initial state, print game again as it were and give message to user */
                    else
                    {
                        gameArray(gState.mapRows, gState.mapCols, gState.playerRowPos, gState.playerColPos, gState.goalRowPos, gState.goalColPos, gState.boxRowPos, gState.boxColPos, gState.gameWalls, boxHistory, moveCount);
                        printf("\nNo more undos, game at initial state.");
                        free(prevGameState);
                        prevGameState = NULL;
                    }
                    

                }
                
                /* logic to cover any other user input other than 'w', 'a', 's', and 'd' */
                else
                {
                    system("clear");
                    gameArray(mapRowSize, mapColSize, playerRow, playerCol, goalRow, goalCol, bRow, bCol, wallCoords, boxHistory, moveCount);
                    moveCount++;
                    printf("You pressed an invalid key, no changes made to game.\n");
                    free(prevGameState); 
                    prevGameState = NULL;
                }

                /* If you/I include this block, to make sure prevGameState is free'd
                which makes sense, the program WILL work on VALGRIND EXECUTION
                with no memory leaks, but the undo functionality WILL NOT 
                work on NORMAL EXECUTION and lead to segmentation fault */
                /*
                if (prevGameState != NULL)
                {
                    free(prevGameState);
                    prevGameState = NULL;
                }
                */

                /* if box is in goal, free linked list+nodes, end game loop and print win message */
                if (((bRow) == goalRow) && ((bCol) == goalCol))
                {
                    gActive = 1;
                    printf("\n\nYou've moved the box to the goal and won the game!\n\n");
                    freeListNodes(gameList); 
                    free(gameList);
                    gameList = NULL;
                }
            }   
        }
    }    
    /* End program if parameters are != 1, print usage to terminal to show how to execute ./box */
    else
    {
        printf("Please execute the program with 1 parameter as follows in the terminal: \nusage: ./box <MAPFILENAME>\n");
    }
    return 0;
}