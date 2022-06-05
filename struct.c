#include<stdio.h>
#include "move.h"
//Structure permettant de recuperer le tableau sauvegarder
struct board_struct {
    piece board[12][12];
    int dim;
    int turn;
};

