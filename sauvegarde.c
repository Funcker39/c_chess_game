#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "sauvegarde.h"
#include "board.h"
#include "struct.c"



//Fonction permettant de sauvegarder une partie en cours
void saveBoard(piece board[12][12],int dimension,int turn){
    FILE *saveFile;
    saveFile = fopen("save.bin","w"); //Ouverture du fichier save.bin en mode ecriture 
    fprintf(saveFile,"Dimension: %d",dimension);//Sauvegarde de la dimension du plateau
    fprintf(saveFile,"Turn: %d",turn);//Sauvegarde de la couleur du joueur qui doit effectuer un coup
    for(int i =0;i<dimension;i++){
         
            for(int j =0;j<dimension;j++){
                fwrite(&board[j][i],sizeof(piece),1,saveFile); //On ecrit toute les pièces du plateau 1 par 1 dans le fichier
            }
       
     }
 
    fclose(saveFile);

    printf("\nPartie sauvegardée avec succès.");

}
//Fonction permettant de restaurer la derniere partie sauvegarder
struct board_struct loadBoard(){
    
    int dim;
    int turn;
           
  
    int row_count =0;
    int col_count = 0;
    piece test;
  

    FILE *saveFile;
    struct board_struct savedStruct;
 
    saveFile = fopen("save.bin","rb"); //On ouvre le fichier save.bin en mode lecture

    

    if(fscanf(saveFile,"Dimension: %d",&dim)!=EOF){//On recupere  la dimension
         printf("");
    }

    if(fscanf(saveFile,"Turn: %d",&turn)!=EOF){//On recupere la couleur du joueur qui doit effectuer un mouvement
         printf("");
    }
    while(fread(&test,sizeof(piece),1,saveFile) ){//Tant qu'il y'a des pièces dans le fichier
            //Reconsitution du plateau de jeu dans un tableau
            if(col_count<dim){
        
                savedStruct.board[col_count][row_count]=test;
             
            
            }
            else if(col_count>=dim){
                col_count=0;
               
           
                
                row_count+=1;
                savedStruct.board[col_count][row_count]=test;
           
            }
          
            col_count+=1;
        

        

    }
   

   
    fclose(saveFile);
    
    savedStruct.dim=dim;
    savedStruct.turn=turn;
    return savedStruct;//On renvoie la structure contenant le tableau sauvegarder ,la dimension de celui-ci et la couleur du joueur
    

   
}