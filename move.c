#include "move.h"
#include "globalVar.h"
#include "board.h"

int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor, int checkTest)
{
    piece selectedPiece = board[from[0]][from[1]];

    /*if (checkTest)
    {
        printf("\nVous voulez déplacer la pièce %c%c vers %c%d.",
               pieceChars[selectedPiece.type], colorChars[selectedPiece.color],
               numberToAsciiLetter(to[0]), dimension - to[1]);

        printf("From %d;%d to %d;%d", from[0], from[1], to[0], to[1]);
    }*/

    //printf("\nTrying to move from %d;%d to %d;%d", from[0], from[1],to[0], to[1]);
    int canMove = 0;

    if (from[0] < 0 || from[0] >= dimension || from[1] < 0 || from[1] >= dimension ||
        to[0] < 0 || to[0] >= dimension || to[1] < 0 || to[1] >= dimension)
        return 0;

    if (board[to[0]][to[1]].type != empty && board[to[0]][to[1]].color == selectedPiece.color)
    {
        return 0;
    }
    switch (selectedPiece.type)
    {
    case pawn:
        if (canMovePawn(board, from, to, turnColor))
        {
            canMove = 1;
        }
        break;
    case bishop:
        if (canMoveBishop(board, from, to))
        {
            canMove = 1;
        }
        break;
    case rook:
        if (canMoveRook(board, from, to))
        {
            canMove = 1;
        }
        break;
    case knight:
        if (canMoveKnight(from, to))
        {
            canMove = 1;
        }
        break;
    case queen:
        if (canMoveQueen(board, from, to))
        {
            canMove = 1;
        }
        break;
    case king:
        if (canMoveKing(from, to))
        {
            canMove = 1;
        }
        break;
    }

    if (canMove && checkTest)
    {
        //printf("\nCanMove");
        piece tmpBoard[12][12];

        for (int x = 0; x < 12; x++)
        {
            for (int y = 0; y < 12; y++)
            {
                tmpBoard[x][y] = board[x][y];
            }
        }
        // copyBoard(board, tmpBoard);

        updateBoard(tmpBoard, dimension, from, to);

        return !isInCheck(tmpBoard, dimension, turnColor);
    }

    return canMove;
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

void printBlockedPiece()
{
    // printf("\nLa case que vous voulez atteindre n'est pas accessible.");
}

int isInCheck(piece board[12][12], int dimension, int color)
{
    int playerKingPos[2];
    int opponentPiecesPos[dimension * 2][2];
    int opponentPiecesIndex = 0;
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            piece curPiece = board[x][y];

            if (curPiece.type == empty || curPiece.type == out)
                continue;

            if (curPiece.color != color)
            {
                opponentPiecesPos[opponentPiecesIndex][0] = x;
                opponentPiecesPos[opponentPiecesIndex][1] = y;
                opponentPiecesIndex++;
            }
            else if (curPiece.type == king)
            {
                playerKingPos[0] = x;
                playerKingPos[1] = y;
            }
        }
    }

    for (int k = 0; k < opponentPiecesIndex; k++)
    {
        if (canMovePiece(board, dimension, opponentPiecesPos[k], playerKingPos, !color, 0))
        {
            /*printBoard(board, dimension);
            printf("\nPos roi:%d-%d", playerKingPos[0], playerKingPos[1]);
            printf("\nEchec à cause de %d-%d, type:%d, color:%d", opponentPiecesPos[k][0], opponentPiecesPos[k][1],
                   board[opponentPiecesPos[k][0]][opponentPiecesPos[k][1]].type, board[opponentPiecesPos[k][0]][opponentPiecesPos[k][1]].color);*/
            //printf("\nCe déplacement vous mets en échec.");
            return 1;   
        }
    }
    return 0;
}

int isInCheckMate(piece board[12][12], int dimension, int color)
{
    int playerKingPos[2];
    int allyPiecesPos[dimension * 2][2];
    int allyPiecesIndex = 0;
    for (int x = 0; x < dimension; x++)
    {
        for (int y = 0; y < dimension; y++)
        {
            piece curPiece = board[x][y];

            if (curPiece.type == empty || curPiece.type == out)
                continue;

            if (curPiece.color == color)
            {
                allyPiecesPos[allyPiecesIndex][0] = x;
                allyPiecesPos[allyPiecesIndex][1] = y;
                allyPiecesIndex++;
            }
            else if (curPiece.type == king)
            {
                playerKingPos[0] = x;
                playerKingPos[1] = y;
            }
        }
    }
    for (int k = 0; k < allyPiecesIndex; k++)
    {
        int curPiecePos[2];
        curPiecePos[0] = allyPiecesPos[k][0];
        curPiecePos[1] = allyPiecesPos[k][1];
        piece curPiece = board[curPiecePos[0]][curPiecePos[1]];

        //printf("\ncurPiecePos:%d;%d", curPiecePos[0], curPiecePos[1]);

        switch (curPiece.type)
        {
        case pawn:
            int dir = color ? 1 : -1;
            int moves[3][2] = {{1, dir}, {0, dir}, {-1, dir}};
            for (int i = 0; i < 3; i++)
            {
                int move[2] = {curPiecePos[0] + moves[i][0], curPiecePos[1] + moves[i][1]};
                if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                {
                    return 0;
                }
            }
            break;

        case bishop:
            for (int i = 0; i < dimension; i++)
            {
                int moves1[4][2] = {{i, i}, {i, -i}, {-i, i}, {-i, -i}};
                
                for (int k = 0; k < 4; k++)
                {
                    int move[2] = {curPiecePos[0] + moves1[k][0], curPiecePos[1] + moves1[k][1]};
                    if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                    {
                        return 0;
                    }
                }
            }
            break;
        case knight:
            int moves2[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
            for (int i = 0; i < 8; i++)
            {
                int move[2] = {curPiecePos[0] + moves2[i][0], curPiecePos[1] + moves2[i][1]};
                if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                {
                    return 0;
                }
            }
            break;
        case rook:
            for (int i = 0; i < dimension; i++)
            {
                int moves3[4][2] = {{i, 0}, {0, i}, {-i, 0}, {0, -i}};
                for (int k = 0; k < 4; k++)
                {
                    int move[2] = {curPiecePos[0] + moves3[k][0], curPiecePos[1] + moves3[k][1]};
                    if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                    {
                        return 0;
                    }
                }
            }
            break;
        case queen:
            for (int i = 0; i < dimension; i++)
            {
                int moves4[8][2] = {{i, 0}, {0, i}, {-i, 0}, {0, -i}, {i, i}, {i, -i}, {-i, i}, {-i, -i}};
                for (int k = 0; k < 8; k++)
                {
                    int move[2] = {curPiecePos[0] + moves4[k][0], curPiecePos[1] + moves4[k][1]};
                    if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                    {
                        return 0;
                    }
                }
            }
            break;
        case king:
            int moves5[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
            for (int i = 0; i < 8; i++)
            {
                int move[2] = {curPiecePos[0] + moves5[i][0], curPiecePos[1] + moves5[i][1]};
                if (canMovePiece(board, dimension, curPiecePos, move, color, 1))
                {
                    return 0;
                }
            }
            break;
        }
    }

    return 1;
}

bool canMovePawn(piece board[12][12], int from[2], int to[2], int color)
{

    if (to[1] == from[1] + (color ? 1 : -1))
    {
        if (to[0] == from[0])
        {
            if (board[to[0]][to[1]].type != empty)
            {
                printBlockedPiece();
                return false;
            }
            return true;
        }
        else if ((to[0] == from[0] + 1 || to[0] == from[0] - 1))
        {
            if (board[to[0]][to[1]].type != empty && board[to[0]][to[1]].type != out && board[to[0]][to[1]].color != color)
            {
                return true;
            }
        }
    }

    return false;
}

bool canMoveBishop(piece board[12][12], int from[2], int to[2])
{
    int horDelta = to[0] - from[0];
    int vertDelta = to[1] - from[1];
    if (abs(horDelta) == abs(vertDelta))
    {
        int horDir = horDelta / abs(horDelta);
        int vertDir = vertDelta / abs(vertDelta);
        int pos[2] = {from[0], from[1]};
        for (int i = 0; i < abs(horDelta) - 1; i++)
        {
            pos[0] += horDir;
            pos[1] += vertDir;

            piece curPiece = board[pos[0]][pos[1]];

            if (curPiece.type != empty)
            {
                printBlockedPiece();
                return false;
            }
        }
        return true;
    }
    return false;
}

bool canMoveRook(piece board[12][12], int from[2], int to[2])
{

    int vertDelta = to[1] - from[1];
    int horDelta = to[0] - from[0];
    int pos[2] = {from[0], from[1]};
    if (to[0] == from[0])
    {
        int vertDir = vertDelta / abs(vertDelta);

        for (int i = 0; i < abs(vertDelta) - 1; i++)
        {

            pos[1] += vertDir;

            piece curPiece = board[pos[0]][pos[1]];

            if (curPiece.type != empty)
            {
                printBlockedPiece();
                return false;
            }
        }
        return true;
    }
    if (to[1] == from[1])
    {
        int horDir = horDelta / abs(horDelta);

        for (int i = 0; i < abs(horDelta) - 1; i++)
        {

            pos[0] += horDir;

            piece curPiece = board[pos[0]][pos[1]];

            if (curPiece.type != empty)
            {
                printBlockedPiece();
                return false;
            }
        }
        return true;
    }

    return false;
}

bool canMoveKnight(int from[2], int to[2])
{
    int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

    int move[2] = {from[0] - to[0], from[1] - to[1]};
    for (int i = 0; i < 8; i++)
    {
        if (move[0] == moves[i][0] && move[1] == moves[i][1]) return true;
    }
    return false;
}

bool canMoveQueen(piece board[12][12], int from[2], int to[2])
{
    if (canMoveBishop(board, from, to) || canMoveRook(board, from, to))
    {
        return true;
    }
    return false;
}

bool canMoveKing(int from[2], int to[2])
{
    if ((abs(to[0] - from[0]) == abs(to[1] - from[1]) == 1) || (to[0] == from[0] - 1 && to[1] == from[1]) || (to[0] == from[0] + 1 && to[1] == from[1]) || (to[0] == from[0] && to[1] == from[1] - 1) || (to[0] == from[0] && to[1] == from[1] + 1))
    {
        return true;
    }
    return false;
}
