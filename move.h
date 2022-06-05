#ifndef __MOVE_H__
#define __MOVE_H__
#include<stdio.h>

#include "piece.c"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor, int checkTest);
int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor);
int isInCheckMate(piece board[12][12], int dimension, int color);
int isInCheck(piece board[12][12], int dimension, int color);
int canMovePawn(piece board[12][12],int from[2],int to[2], int);
int canMoveBishop(piece board[12][12], int from[2],int to[2]);
int canMoveRook(piece board[12][12],int from[2],int to[2]);
int canMoveQueen(piece board[12][12],int from[2],int to[2]);
int canMoveKing(int from[2],int to[2]);
int canMoveKnight(int from[2],int to[2]);

#endif

