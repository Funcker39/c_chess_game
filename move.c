#include "move.h"
#include "globalVar.h"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor)
{
    piece selectedPiece = board[from[0]][from[1]];
    printf("\nVous voulez déplacer la pièce %c%c vers %c%d.",
           pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
           numberToAsciiLetter(to[0]), dimension - to[1]);

    printf("From %d;%d to %d;%d", from[0], from[1], to[0], to[1]);

    /*if (board[to[0]][to[1]].type != empty)
    {
        return 0;
    }*/
    switch (selectedPiece.type)
    {
    case pawn:
        if (movePawn(from, to, turnColor))
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
        if (moveRook(from, to))
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
        if (moveQueen(from, to))
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

bool movePawn(int from[2], int to[2], int color)
{
    if (to[0] == from[0] && to[1] == from[1] + color ? -1 : 1)
    {
        return true;
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

bool moveRook(int from[2], int to[2])
{
    if (to[0] == from[0] || to[1] == from[1])
    {
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

bool moveQueen(int from[2], int to[2])
{
    if ((abs(to[0] - from[0]) == abs(to[1] - from[1])) || (to[0] == from[0] || to[1] == from[1]))
    {
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
