#ifndef __MOVE_H__
#define __MOVE_H__
#include<stdio.h>
#include "piece.c"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor);
int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor);

#endif

