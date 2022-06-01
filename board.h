#ifndef __BOARD_H__
#define __BOARD_H__
#include "move.h"
void initBoard(piece board[12][12],int dimension);
void printBoard (piece board[12][12],int dimension);
void updateBoard(piece board[12][12], int dimension, int from[2], int to[2]);
#endif