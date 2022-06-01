#include "move.h"
#include "globalVar.h"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor) {
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%d.", 
        pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
        numberToAsciiLetter(to[0]), dimension - to[1]);

    printf("From %d;%d to %d;%d", from[0], from[1], to[0], to[1]);

    if(board[to[0]][to[1]].type !=empty){
        return 0;
    }
    switch (selectedPiece.type) {
        case pawn:
            if (to[0] == from[0] && to[1] == from[1] - 1) {
                return 1;
            }
            break;
        case bishop:
            if(abs(to[0]-from[0])==abs(to[1]-from[1])){
                return 1;
            }  
            break;
        case rook:
            if(to[0]==from[0] || to[1]==from[1]){
                return 1;
            }
            break;
        case queen:
            if((abs(to[0]-from[0])==abs(to[1]-from[1]))||(to[0]==from[0] || to[1]==from[1])){
                return 1;
            }
            break;
     
        
    }

    return 0;
}

int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor) {
    piece selectedPiece = board[piecePos[0]][piecePos[1]];

    switch (selectedPiece.type) {
        case out:
            printf("\nLa case choisie est hors du plateau.");
            return 0;
        case empty:
            printf("\nIl n'y a pas de pièce sur la case choisie.");
            return 0;
    }

    if (selectedPiece.color != turnColor) {
        printf("\nLa pièce choisie ne vous appartient pas.");
        return 0;
    }

    return 1;
}