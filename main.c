#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum pieceType {
    out = 0,
    empty = 1,
    pawn = 2,
    bishop = 3,
    knight = 4,
    rook = 5,
    queen = 6,
    king = 7
};

char pieceChars[8] = {
    '/',
    '-',
    'P',
    'F',
    'C',
    'T',
    'D',
    'R'
};

char colorChars[2] = {
    'B',
    'N'
};

enum colors {
    white = 0,
    black = 1
};

typedef struct {
    int type;
    int color;
} piece;

piece board[12][12];

void initBoard(piece board[12][12], int dimension) {

    // Assignation aléatoire de la position des 2 rois (noir et blanc)
    board[rand() % dimension][0].type = king;
    board[rand() % dimension][0].color = black;
    board[rand() % dimension][dimension - 1].type = king;
    board[rand() % dimension][dimension - 1].color = white;


    for (int x = 0; x < dimension; x++) {
        for (int y = 0; y < 2; y++) {
            if (board[x][y].type & king) continue;
            
            board[x][y].type = rand() % 4 + 2;
            board[x][y].color = black;
        }
        for (int y = 2; y < dimension - 2; y++) {
            board[x][y].type = empty;
        }
        for (int y = dimension - 2; y < dimension; y++) {
            if (board[x][y].type & king) continue;
            
            board[x][y].type = rand() % 4 + 2;
            board[x][y].color = white;
        }
    }


    for (int x = dimension; x < 12; x++) {
        for (int y = dimension; y < 12; y++) {
            board[x][y].type = out;
        }
    }
};

void printBoard(piece board[12][12]) {
    printf("     ");
    for (int x = 0; x < 12; x++) {
        printf("%c   ", 65 + x);
    }
    printf("\n\n");
    for (int x = 0; x < 12; x++) {
        if (x < 10) printf(" ");
        printf("%d   ", x);
        for (int y = 0; y < 12; y++) {
            printf("%d   ", board[y][x].type);
        }
        printf ("\n\n");
    }
}

void canMove(piece board[12][12], int from[2], int to[2], int turnColor) {
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nTrying to move piece %c%c", pieceChars[selectedPiece.type], colorChars[selectedPiece.color]);
}

void main() {

    int dimension = 0;
    while (dimension < 6 || dimension > 12) {
        printf("Entrez la dimension de plateau souhaitée (6-12):\n");
        scanf("%d", &dimension);
    }

    srand(time(NULL));

    initBoard(board, dimension);

    printBoard(board);
}
