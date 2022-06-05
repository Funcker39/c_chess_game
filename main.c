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

int save(char input, int turn)
{
    if (input == 'S')
    {
        saveBoard(board, dimension, turn);
        return 1;
    }
  
    return 0;
}
int quit(char input,int turn){
    if(input=='X'){
        printf("Les ");
        turn ? printf("noirs ") : printf("blancs ");
        printf("abandonnent");
        return 1;
    }
    return 0;
}

//Fonction principale du jeu
void game(piece board[12][12], int dimension, int turn)
{
    int wrongMove = 0;
    do
    {
        int correctMove = 0;
        int fromMove[2];
        int inCheck = 0;
        //On verifie si la partie est finie ou non.
        if (isInCheck(board, dimension, turn))
        {
            inCheck = 1;
            if (isInCheckMate(board, dimension, turn))
            {
                gameOver = 1;
                printf("\n========\nGAME OVER\n========");
                printf("\nVictoire des ");
                turn ? printf("blancs.") : printf("noirs.");
                return;
            }
        }
        else {
            inCheck = 0;
        }

        printf("\e[1;1H\e[2J"); // On efface le plateau
        printBoard(board, dimension); //Affichage du tableau

        do
        {
            // Affichage d'un message d'erreur si le déplacement était mauvais 
            if (wrongMove) {
                printf("\nDéplacement interdit.");
            }

            correctMove = 0;
            printf("\nC'est au tour des ");
            turn ? printf("noirs.") : printf("blancs.");
            if (inCheck) printf("\nAttention, vous êtes en échec.");
            printf("\nChoisissez une pièce à déplacer (A-%c):", dimension + 64);

            //Verification de l'input (sauvegarde ou quitter)
            char input[3];
            scanf("%s", &input);
            if (save(input[0], turn))
            {
                continue;
            }
            if(quit(input[0],turn)){
                
                return;
            }

            //Récuperation des coordonées de la piece selectionne 
            fromMove[0] = input[0] - 65;//Conversion de la lettre en un chiffre
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
            if (save(input[0], turn))
            {
                continue;
            }
            if(quit(input[0],turn)){
                return;
            }

            //Recuperation de la case cible
            toMove[0] = input[0] - 65;
            char secondPart[2] = {input[1], input[2]};
            toMove[1] = dimension - atoi(secondPart);

            if (toMove[0] >= 0 && toMove[0] < dimension)
                correctMove = 1;
            if (toMove[1] >= 0 && toMove[1] < dimension)
                correctMove = 1;

        } while (!correctMove);
        //On verifie si le mouvement peut etre effectué
        correctMove = canMovePiece(board, dimension, fromMove, toMove, turn, 1);

        if (!correctMove)
        {
            wrongMove = 1;
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

    }
}
