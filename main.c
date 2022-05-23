#include <stdio.h>

#include "board.h"

void main() {
    struct board board;

    initBoard(&board, 6);

    for (int x = 0; x < 12; x++) {
        for (int y = 0; y < 12; y++) {
            printf("%d %d = %d\n", x, y, board.cases[x][y]);
        }
    }

    
}
