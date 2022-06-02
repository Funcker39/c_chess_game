#include<stdio.h>
#include "move.h"

struct board_struct {
    piece board[12][12];
    int dim;
    int turn;
};

