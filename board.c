#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "enum.c"
void initBoard(piece board[12][12], int dimension) {

    // Assignation aléatoire de la position des 2 rois (noir et blanc)
    board[rand() % dimension][0].type = king;
    board[rand() % dimension][0].color = black;
    board[rand() % dimension][dimension - 1].type = king;
    board[rand() % dimension][dimension - 1].color = white;


    for (int x = 0; x < dimension; x++) {
        for (int y = 0; y < 2; y++) {
            if (board[x][y].type & king) continue;
            
            board[x][y].type = rand() % 4 + 2;
            board[x][y].color = black;
        }
        for (int y = 2; y < dimension - 2; y++) {
            board[x][y].type = empty;
        }
        for (int y = dimension - 2; y < dimension; y++) {
            if (board[x][y].type & king) continue;
            
            board[x][y].type = rand() % 4 + 2;
            board[x][y].color = white;
        }
    }


    for (int x = dimension; x < 12; x++) {
        for (int y = dimension; y < 12; y++) {
            board[x][y].type = out;
        }
    }
};

void printBoard(piece board[12][12], int dimension) {
   
    printf("       ");
    for (int x = 0; x < dimension; x++) {
        printf("%c   ", 65 + x);
    }
    printf("\n\n\n");
    printf("       ");
     for(int j =  0;j<(dimension*3)-3;j++){
            printf("_ ");
    }
    printf("\n\n");
    for (int x = 0; x < dimension; x++) {
        if (dimension - x < 10) printf(" ");
        printf("%d    ", dimension - x);

    
        for (int y = 0; y < dimension; y++) {
            if(x==0 || x==1){
                printf("\033[0;34m");
            }
         
            switch(board[y][x].type){
                case 1:
                    printf("|   |");
                    break;
                case 2:
                    printf("| P |");
                    break;
                case 3:
                    printf("| F |");
                    break;
                case 4:
                    printf("| C |");
                    break;
                case 5:
                    printf("| T |");
                    break;
                case 6:
                    printf("| D |");
                    break;
                case 7:
                    printf("| R |");
                default:
                 
                    break;

            }
         
        }
        printf("\033[0m");
        printf ("\n\n");
           
 
       
    }
}
