#include "move.h"
#include "globalVar.h"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor) {
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%d\n", 
        pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
        numberToAsciiLetter(to[0]), dimension - to[1]);

    
    switch (selectedPiece.type) {
        case pawn:
            printf("");
            break;
    }
}

int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor) {
    piece selectedPiece = board[piecePos[0]][piecePos[1]];

    switch (selectedPiece.type) {
        case out:
            printf("La case choisie est hors du plateau.\n");
            return 0;
        case empty:
            printf("Il n'y a pas de pièce sur la case choisie.\n");
            return 0;
    }

    if (selectedPiece.color != turnColor) {
        printf("La pièce choisie ne vous appartient pas.\n");
        return 0;
    }

    return 1;
}