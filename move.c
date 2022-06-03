#include "move.h"
#include "globalVar.h"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor)
{
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%d.",
           pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
           numberToAsciiLetter(to[0]), dimension - to[1]);

    printf("From %d;%d to %d;%d", from[0], from[1], to[0], to[1]);

    if (board[to[0]][to[1]].type != empty && board[to[0]][to[1]].color==selectedPiece.color)
    {
        return 0;
    }
    switch (selectedPiece.type)
    {
    case pawn:
        if (movePawn(board,from, to, turnColor))
        {
            return 1;
        }
        break;
    case bishop:
        if (moveBishop(board, from, to))
        {
            return 1;
        }
        break;
    case rook:
        if (moveRook(board,from, to))
        {
            return 1;
        }
        break;
    case knight:
        if (moveKnight(from, to))
        {
            return 1;
        }
        break;
    case queen:
        if (moveQueen(board,from, to))
        {
            return 1;
        }
        break;
    case king:
        if (moveKing(from, to))
        {
            return 1;
        }
        break;
    }

    return 0;
}

int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor)
{
    piece selectedPiece = board[piecePos[0]][piecePos[1]];

    switch (selectedPiece.type)
    {
    case out:
        printf("\nLa case choisie est hors du plateau.");
        return 0;
    case empty:
        printf("\nIl n'y a pas de pièce sur la case choisie.");
        return 0;
    }

    if (selectedPiece.color != turnColor)
    {
        printf("\nLa pièce choisie ne vous appartient pas.");
        return 0;
    }

    return 1;
}

void printBlockedPiece() {
    printf("\nLa case que vous voulez atteindre n'est pas accessible.");
}

bool isInCheck(piece board[12][12], int dimension, int color)
{
}

bool movePawn(piece board[12][12],int from[2], int to[2], int color)
{

    int horDelta = to[0] - from[0];
    int vertDelta = to[1] - from[1];
    int val=-1;
    if(color){
        val =1;
    }
  


    if (to[0] == from[0] && to[1] == from[1]+val )
    {
        if(board[to[0]][to[1]].type!=empty){
            printBlockedPiece();
            return false;
        }
        return true;
    }
    if(abs(abs(horDelta)-abs(vertDelta))==0){
        if(board[to[0]][to[1]].type!=empty){
            return true;
        }
    }
    return false;
}

bool moveBishop(piece board[12][12], int from[2], int to[2])
{
    int horDelta = to[0] - from[0];
    int vertDelta = to[1] - from[1];
    if (abs(horDelta) == abs(vertDelta))
    {
        int horDir = horDelta / abs(horDelta);
        int vertDir = vertDelta / abs(vertDelta);
        int pos[2] = {from[0], from[1]};
        for (int i = 0; i < abs(horDelta) - 1; i++) {
            pos[0] += horDir;
            pos[1] += vertDir;

            piece curPiece = board[pos[0]][pos[1]];

            if (curPiece.type != empty) {
                printBlockedPiece();
                return false;
            }
        }
        return true;
    }
    return false;
}

bool moveRook(piece board[12][12],int from[2], int to[2])
{


    int vertDelta = to[1]-from[1]; 
    int horDelta = to[0]-from[0];
    int pos[2]={from[0],from[1]};
    if (to[0] == from[0])
    {
        int vertDir = vertDelta/abs(vertDelta);
    
        for (int i =0;i<abs(vertDelta)-1;i++){
       
            pos[1]+=vertDir;
         
            piece curPiece = board[pos[0]][pos[1]];

            if(curPiece.type!=empty){
                printBlockedPiece();
                return false;
            }
        }
        return true;
        

      
    }
    if (to[1] == from[1])
    {
        int horDir = horDelta/abs(horDelta);
    
        for (int i =0;i<abs(horDelta)-1;i++){
       
            pos[0]+=horDir;
         
            piece curPiece = board[pos[0]][pos[1]];

            if(curPiece.type!=empty){
                printBlockedPiece();
                return false;
            }
        }
        return true;
        

      
    }

    return false;
}

bool moveKnight(int from[2], int to[2])
{

    if (abs((abs(to[0] - from[0]) - abs(to[1] - from[1]))) == 1)
    {

        return true;
    }
    return false;
}

bool moveQueen(piece board[12][12],int from[2], int to[2])
{
    if(moveBishop(board,from,to)||moveRook(board,from,to)){
        return true;
    }
    return false;
}

bool moveKing(int from[2], int to[2])
{
    if ((abs(to[0] - from[0]) == abs(to[1] - from[1]) == 1) || (to[0] == from[0] - 1 && to[1] == from[1]) || (to[0] == from[0] + 1 && to[1] == from[1]) || (to[0] == from[0] && to[1] == from[1] - 1) || (to[0] == from[0] && to[1] == from[1] + 1))
    {
        return true;
    }
    return false;
}
