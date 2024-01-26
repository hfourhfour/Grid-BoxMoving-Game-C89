#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/*
Title:      		game.c
Author:     		Jet Ng
Date/LastModified:  31/05/2023
Description:       	game.c only has one function, gameArray() which takes in the user-specified parameters 
                    for the map size, player position, goal position. box position, two structs for the
                    wall positions and the box movement history, as well as a integer for the total moves
                    done in the game.
*/


/*
METHOD: 	gameArray
IMPORT: 	mRow (int), mCol(int), pRow (int), pCol (int), gRow (int), gCol (int), bRow (int), bCol(int),
            pWalls (struct Coordinates), pBoxMoves(struct Coordinates), numMoves (int)
EXPORT: 	void, prints colours, symbols and empty space to terminal to form a map for the game to be played on.
ASSERTION: 	Game map will be printed to terminal with positions for player, goal, box and walls as they change
            from main.c from user input (player movement, box pushing/pulling, undo)
ALGORITHM:
			Allocate memory for dynamic 2D array to act as game map.
            Initialise all values in array as 0 (blank space), 
            then set values for border (1), player(2), goal(3), box(4), walls(5), and box trail (9).

            Print game map to terminal according to their value in the array:
            border(1) = *, player(2) = P, goal(3) = G, box(4) = B, wall(5) = 0, box trail(9) = BLUE.

            Goal has red background when box has not been pushed into it,
            which changes to green after box is in goal and game is won.
            Player has yellow background and box has a BLUE trail to show where
            it has travelled/been pushed and pulled.

            Finally free malloc'd array and end function.

*/

void gameArray(int mRow, int mCol, int pRow, int pCol, int gRow, int gCol, int bRow, int bCol, struct Coordinates (*pWalls)[2], struct Coordinates (*pBoxMoves)[2], int numMoves)
{
    int** gameMap = (int**)malloc((mRow+2)*sizeof(int*));
    int i,j, boxR, boxC;
    int wRow, wCol, boxFlagCol, boxFlagRow;
    /* int playerR, playerC; variables used to track player position for debugging */
    int goalRow = gRow;
    int goalCol = gCol;
 
    printf("\n");

    /* initialise/set up 2D game map values */
    for (i = 0; i < (mRow+2); i++)
    {
        gameMap[i] = (int*)malloc((mCol+2)*sizeof(int));
        for (j = 0; j < (mCol+2); j++)
        {
            gameMap[i][j] = 0;
        }
    }
    
    /* set wall map values */
    i = 0;
    while ((i < 50) && (pWalls[i][0].wallRow != 500))
    {
        wRow = (pWalls[i][0].wallRow);
        wCol = (pWalls[i][1].wallCol);
        gameMap[(wRow+1)][(wCol+1)] = 5;
        i++;
    }

    /* set box history map values (where box has been) */
    i = 0;
    while ((i < numMoves) && (pBoxMoves[i][0].wallRow != 500))
    {
        boxFlagRow = (pBoxMoves[i][0].wallRow);
        boxFlagCol = (pBoxMoves[i][1].wallCol);
        gameMap[(boxFlagRow+1)][(boxFlagCol+1)] = 9;
        i++;
    }
    
    /* set up border values */
    for (i = 0; i < (mRow+2); i++)
    {
        gameMap[i][0] = 1;
        gameMap[i][(mCol+1)] = 1;
    }

    for (i = 0; i < (mCol+2); i++)
    {
        gameMap[0][i] = 1;
        gameMap[(mRow+1)][i] = 1;
    }
    
    /* set up player, goal and box values */
    gameMap[1][1] = 0;
    gameMap[(pRow+1)][(pCol+1)] = 2;
    gameMap[(gRow+1)][(gCol+1)] = 3;
    gameMap[(bRow+1)][(bCol+1)] = 4;
 
    /* loop for drawing game map, draws colours/symbols as per their
    values set up in the previous code blocks */
    for (i = 0; i < (mRow+2); i++)
    {
        printf("\n");
        for (j = 0; j < (mCol+2); j++)
        {
            if (gameMap[i][j] == 1)
            {
                printf("* ");
            }
            else if (gameMap[i][j] == 2)
            {
                printf("\033[43m");
                printf("P ");
                printf("\033[49m");

                /* variable assignment for testing/debugging
                playerR = i;
                playerC = j; 
                */
            }
            else if (gameMap[i][j] == 3)
            {
                printf("\033[41m"); /* set G to Red */ 
                printf("G ");
                printf("\033[49m"); /* reset after G */ 
            }
            else if (gameMap[i][j] == 4)
            {
                boxR = i;
                boxC = j;
                if (((boxR-1) == goalRow) && ((boxC-1) == goalCol))
                {
                    printf("\033[42m"); /* set B to Green if in goal*/ 
                    printf("B ");
                    printf("\033[49m"); /* reset after B */ 
                }
                else if (gameMap[i][j] != 9)
                {
                    printf("\033[44m");
                    printf("B ");
                    printf("\033[49m");
                }
                else
                {
                    printf("  ");
                }
            }
            else if (gameMap[i][j] == 5)
            {
                printf("O ");
            }
            else if (gameMap[i][j] == 9)
            {
                printf("\033[44m");
                printf("  ");
                printf("\033[49m");
            }
            else
            {
                printf("  ");
            }
        }
    }

    /* TO TRACK POSITIONS FOR DEBUGGING */
    /*
    printf("\nPLAYER ROW: %d PLAYER COL: %d", playerR, playerC);
    printf("\nBOX ROW: %d BOX COL: %d", boxR, boxC);
    printf("\nGOAL ROW: %d GOAL COL: %d\n", goalRow, goalCol); 
    
    */
    
    /* at tne end, freeing malloc'd game array */
    for (i = 0; i < (mRow+2); i++) 
    {
        free(gameMap[i]);
    }
    free(gameMap);
}

