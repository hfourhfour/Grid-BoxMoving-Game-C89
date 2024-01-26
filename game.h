#ifndef GAME_H
#define GAME_H

#include "main.h"

void gameArray(int mRow, int mCol, int pRow, int pCol, int gRow, int gCol, int bRow, int bCol, struct Coordinates (*pWalls)[2], struct Coordinates (*pBoxMoves)[2], int numMoves);

#endif