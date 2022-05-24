#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

void printBoard(piece board[12][12], int dimension) {
    printf("       ");
    for (int x = 0; x < dimension; x++) {
        printf("%c   ", 65 + x);
    }
    printf("\n\n\n");
    for (int x = 0; x < dimension; x++) {
        if (dimension - x < 10) printf(" ");
        printf("%d     ", dimension - x);


        for (int y = 0; y < dimension; y++) {
            printf("%d   ", board[y][x].type);
        }
        printf ("\n\n");
    }
}

void canMove(piece board[12][12], int from[2], char to[2], int turnColor) {
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%c\n", 
        pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
        to[0], to[1]);
}

/*void getPieceString(piece board[12][12], int pos[2], char *pieceString[2]) {
    piece selectedPiece = board[pos[0]][pos[1]];
    pieceString[0] = pieceChars[selectedPiece.type];
    pieceString[1] = colorChars[selectedPiece.color];
    return pieceString;
}

void getUserMove(int dimension, int *move[2]) {
    char input[3];
    scanf("%s", &input);
    move[0] = input[0] - 65;
    char secondPart[2] = {input[1], input[2]};
    move[1] = dimension - atoi(secondPart);
}*/

piece board[12][12];
int gameOver = 0;
int turn = white;

void main() {

    int dimension = 0;
    while (dimension < 6 || dimension > 12) {
        printf("Entrez la dimension de plateau souhaitée (6-12):\n");
        scanf("%d", &dimension);
        getchar();
    }

    srand(time(NULL));

    initBoard(board, dimension);

    printBoard(board, dimension);

    sleep(0.1);
    do {
        int correctMove = 1;
        int fromMove[2];
        do {
            printf("Choisissez une pièce à déplacer (A-%c):", dimension + 64);
            
            char input[3];
            scanf("%s", &input);
            fromMove[0] = input[0] - 65;
            char secondPart[2] = {input[1], input[2]};
            fromMove[1] = dimension - atoi(secondPart);

            if (fromMove[0] < 0 || fromMove[0] >= dimension) correctMove = 0;
            if (fromMove[1] < 0 || fromMove[1] >= dimension) correctMove = 0;

        } while (!correctMove);

        char toMove[2];
        do {
            piece selectedPiece = board[fromMove[0]][fromMove[1]];
            printf("Choisissez la case où vous voulez déplacer la pièce %c%c:", 
                pieceChars[selectedPiece.type], colorChars[selectedPiece.color]);
            
            char input[3];
            scanf("%s", &input);
            toMove[0] = input[0] - 65;
            char secondPart[2] = {input[1], input[2]};
            toMove[1] = dimension - atoi(secondPart);

            if (toMove[0] < 0 || toMove[0] >= dimension) correctMove = 0;
            if (toMove[1] < 0 || toMove[1] >= dimension) correctMove = 0;

        } while (!correctMove);
        
        canMove(board, fromMove, toMove, turn);
        
        break;
    } while (!gameOver);
}
