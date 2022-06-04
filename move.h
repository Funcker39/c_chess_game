#ifndef __MOVE_H__
#define __MOVE_H__
#include<stdio.h>
#include <stdbool.h>
#include "piece.c"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor, int checkTest);
int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor);
bool canMovePawn(piece board[12][12],int from[2],int to[2], int);
bool canMoveBishop(piece board[12][12], int from[2],int to[2]);
bool canMoveRook(piece board[12][12],int from[2],int to[2]);
bool canMoveQueen(piece board[12][12],int from[2],int to[2]);
bool canMoveKing(int from[2],int to[2]);
bool canMoveKnight(int from[2],int to[2]);

#endif

