#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "globalVar.h"
#include "move.h"
#include "board.h"
#include "enum.c"
#include "menu.h"





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
 int dimension = 0;
void main() {

    int choice = menu();
    
    switch (choice){
        case 1:
           
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
            break;
        default:
            printf("WIP");
    }

    
}
