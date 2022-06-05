#include<stdio.h>
#include<stdlib.h>

//Fonction permettant d'afficher le menu d'accueil
int menu(){
    printf("Bienvenue sur VeryBadChess\n");
    printf("Merci de choisir un nombre entre 1 et 3 pour effectuer une action\n");
    printf("1-Nouvelle Partie\n");
    printf("2-Reprendre la derniere partie\n");
    printf("3-Quitter\n");
    int input;
    scanf("%d",&input);
    return input;
}