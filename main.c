#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "globalVar.h"
#include "move.h"
#include "board.h"
#include "enum.c"
#include "menu.h"
#include "utilities.h"
#include "sauvegarde.h"
#include "struct.c"

piece board[12][12];
int gameOver = 0;

int dimension = 0;

int checkInput(char input, int turn)
{
    if (input == 'S')
    {
        saveBoard(board, dimension, turn);
        return 1;
    }
    return 0;
}

void game(piece board[12][12], int dimension, int turn)
{
    do
    {

        printBoard(board, dimension);

        int correctMove = 0;
        int fromMove[2];
        do
        {
            correctMove = 0;
            printf("\nC'est au tour des ");
            turn ? printf("noirs.") : printf("blancs.");
            printf("\nChoisissez une pièce à déplacer (A-%c):", dimension + 64);

            char input[3];
            scanf("%s", &input);
            if (checkInput(input[0], turn))
            {
                continue;
            }

            fromMove[0] = input[0] - 65;
            char secondPart[2] = {input[1], input[2]};
            fromMove[1] = dimension - atoi(secondPart);

            if (fromMove[0] >= 0 && fromMove[0] < dimension)
                correctMove = 1;
            if (fromMove[1] >= 0 && fromMove[1] < dimension)
                correctMove = 1;

            correctMove = canChoosePiece(board, dimension, fromMove, turn);
        } while (!correctMove);

        int toMove[2];
        do
        {
            correctMove = 0;

            piece selectedPiece = board[fromMove[0]][fromMove[1]];
            printf("\nChoisissez la case où vous voulez déplacer votre %c%c:",
                   pieceChars[selectedPiece.type], colorChars[selectedPiece.color]);

            char input[3];
            scanf("%s", &input);
            if (checkInput(input[0], turn))
            {
                continue;
            }

            toMove[0] = input[0] - 65;
            char secondPart[2] = {input[1], input[2]};
            toMove[1] = dimension - atoi(secondPart);

            if (toMove[0] >= 0 && toMove[0] < dimension)
                correctMove = 1;
            if (toMove[1] >= 0 && toMove[1] < dimension)
                correctMove = 1;

        } while (!correctMove);

        //printf("\nMoving %d;%d to %d;%d", fromMove[0], fromMove[1], toMove[0], toMove[1]);
        correctMove = canMovePiece(board, dimension, fromMove, toMove, turn, 1);

        if (!correctMove)
        {
            printf("\nDéplacement interdit.");
            continue;
        }

        updateBoard(board, dimension, fromMove, toMove);
        turn = !turn;

    } while (!gameOver);
}

void main()
{

    int choice = menu();

    switch (choice)
    {

    case 1:

        while (dimension < 6 || dimension > 12)
        {
            printf("\nEntrez la dimension de plateau souhaitée (6-12):\n");
            scanf("%d", &dimension);
            getchar();
        }

        srand(time(NULL));

        initBoard(board, dimension);
        int turn = white;
        game(board, dimension, turn);

        break;
    case 2:;
        struct board_struct savedStruct = loadBoard();
        game(savedStruct.board, savedStruct.dim, savedStruct.turn);
        break;
    case 3:
        printf("Merci d'avoir jouer, au revoir ! ");
        system("exit");
        break;
    default:
        printf("Merci de choisir un nombre entre 1 et 3 pour effectuer une action");
        break;
    }
}
