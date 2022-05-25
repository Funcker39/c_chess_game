#include "move.h"
#include "globalVar.h"

void canMove(piece board[12][12], int from[2], char to[2], int turnColor) {
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%c\n", 
        pieceChars[selectedPiece.type], colorChars[selectedPiece.color],to[0], to[1]);
   
}