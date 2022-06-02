#ifndef __SAVE_H__
#define __SAVE_H__
#include "move.h"
void saveBoard(piece board[12][12],int dimension,int turn);
struct board_struct loadBoard();
#endif