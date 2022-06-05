#include "move.h"
#include "globalVar.h"
#include "board.h"

// Fonction principale permettant de verifier si une piece peut effectuer un deplacement
int canMovePiece(piece board[12][12], int dimension, int from[2], int to[2], int turnColor, int checkTest)
{
    piece selectedPiece = board[from[0]][from[1]]; // Recuperation de la pièce

    int canMove = 0;

    if (from[0] < 0 || from[0] >= dimension || from[1] < 0 || from[1] >= dimension ||
        to[0] < 0 || to[0] >= dimension || to[1] < 0 || to[1] >= dimension)
        return 0;

    if (board[to[0]][to[1]].type != empty && board[to[0]][to[1]].color == selectedPiece.color) // Verification de si la case destination n'est pas deja occupée par une piece de la meme couleur
    {
        return 0;
    }

    switch (selectedPiece.type) // En fonction du type de piece on appelle la fonction correspondante pour verifier si un mouvement est possible.
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

    if (canMove && checkTest) // On verifie si le roi est en echec
    {

        piece tmpBoard[12][12]; // Copie du plateau dans un tableau temporaire

        for (int x = 0; x < 12; x++)
        {
            for (int y = 0; y < 12; y++)
            {
                tmpBoard[x][y] = board[x][y];
            }
        }

        updateBoard(tmpBoard, dimension, from, to); // On met a jour le plateau temporaire

        return !isInCheck(tmpBoard, dimension, turnColor); // On verifie si le roi est en echec dans le plateau temporaire (si isInCheck renvoie 1 on renvoie 0 car le mouvement n'est pas possible)
    }

    return canMove;
}

// Fonction permettant de verifier si la piece peut etre choisie ou non
int canChoosePiece(piece board[12][12], int dimension, int piecePos[2], int turnColor)
{
    piece selectedPiece = board[piecePos[0]][piecePos[1]]; // On recupere la piece

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

// Fonction permettant de verifier si le roi est en echec
int isInCheck(piece board[12][12], int dimension, int color)
{
    int playerKingPos[2];                    // Coordonées du roi
    int opponentPiecesPos[dimension * 2][2]; // Coordonées de toutes les pièces adverses
    int opponentPiecesIndex = 0;

    // Remplissage des tableaux initalisées ci dessus
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

    // On verifie si les pièces adverses peuvent mettre le roi en echec en verifiant si elles peuvent atteindre le roi à l'aide de la fonction canMovePiece
    for (int k = 0; k < opponentPiecesIndex; k++)
    {
        if (canMovePiece(board, dimension, opponentPiecesPos[k], playerKingPos, !color, 0))
        {
            return 1;
        }
    }
    return 0;
}

// Fonction permettant de verifier l'echec et mat
int isInCheckMate(piece board[12][12], int dimension, int color)
{
    int playerKingPos[2];                // Coordonées du roi
    int allyPiecesPos[dimension * 2][2]; // Coordonées des pièces alliées
    int allyPiecesIndex = 0;

    // Remplissage des tableaux initialisés ci-dessus
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

    // On essaie de déplacer chaque pièce alliée dans toutes les potentiels positions en vérifiant si le déplacement est possible
    // et si le roi est toujours en échec.
    // On return 0 (pas en échec et mat) si un des déplacements permet d'éviter l'échec sinon on return 1 (joueur en échec et mat)
    for (int k = 0; k < allyPiecesIndex; k++)
    {
        int curPiecePos[2];
        curPiecePos[0] = allyPiecesPos[k][0];
        curPiecePos[1] = allyPiecesPos[k][1];
        piece curPiece = board[curPiecePos[0]][curPiecePos[1]];

        // On détermine grossièrement les potentiels cases à tester selon le type de pièce puis on les test toutes avec canMovePiece
        switch (curPiece.type)
        {
        case pawn:
        {
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
        }

        case bishop:
        {
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
        }

        case knight:
        {
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
        }

        case rook:
        {
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
        }

        case queen:
        {
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
        }

        case king:
        {
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
    }

    return 1;
}

int canMovePawn(piece board[12][12], int from[2], int to[2], int color)
{
    if (to[1] == from[1] + (color ? 1 : -1))
    {
        if (to[0] == from[0])
        {
            if (board[to[0]][to[1]].type != empty)
            {

                return 0;
            }
            return 1;
        }
        else if ((to[0] == from[0] + 1 || to[0] == from[0] - 1))
        {
            if (board[to[0]][to[1]].type != empty && board[to[0]][to[1]].type != out && board[to[0]][to[1]].color != color)
            {
                return 1;
            }
        }
    }

    return 0;
}

int canMoveBishop(piece board[12][12], int from[2], int to[2])
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
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int canMoveRook(piece board[12][12], int from[2], int to[2])
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

                return 0;
            }
        }
        return 1;
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

                return 0;
            }
        }
        return 1;
    }

    return 0;
}

int canMoveKnight(int from[2], int to[2])
{
    int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

    int move[2] = {from[0] - to[0], from[1] - to[1]};
    for (int i = 0; i < 8; i++)
    {
        if (move[0] == moves[i][0] && move[1] == moves[i][1])
            return 1;
    }
    return 0;
}

int canMoveQueen(piece board[12][12], int from[2], int to[2])
{
    if (canMoveBishop(board, from, to) || canMoveRook(board, from, to))
    {
        return 1;
    }
    return 0;
}

int canMoveKing(int from[2], int to[2])
{
    if ((abs(to[0] - from[0]) == abs(to[1] - from[1]) == 1) || (to[0] == from[0] - 1 && to[1] == from[1]) || (to[0] == from[0] + 1 && to[1] == from[1]) || (to[0] == from[0] && to[1] == from[1] - 1) || (to[0] == from[0] && to[1] == from[1] + 1))
    {
        return 1;
    }
    return 0;
}
