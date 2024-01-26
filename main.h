#ifndef MAIN_H
#define MAIN_H

struct Coordinates
{
    int wallRow;
    int wallCol;
};

struct gameState
{
    int mapRows;
    int mapCols;
    int playerRowPos;
    int playerColPos;
    int goalRowPos;
    int goalColPos;
    int boxRowPos;
    int boxColPos;
    struct Coordinates (*gameWalls)[2];
};

#endif