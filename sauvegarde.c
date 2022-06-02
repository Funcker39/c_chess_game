#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "sauvegarde.h"
#include "board.h"
#include "struct.c"




void saveBoard(piece board[12][12],int dimension,int turn){
    FILE *saveFile;
    saveFile = fopen("save.bin","w");
    fprintf(saveFile,"Dimension: %d",dimension);
    fprintf(saveFile,"Turn: %d",turn);
    for(int i =0;i<dimension;i++){
         
            for(int j =0;j<dimension;j++){
                fwrite(&board[j][i],sizeof(piece),1,saveFile);
            }
       
     }
 
    fclose(saveFile);

    printf("\nPartie sauvegardée avec succès.");

}

struct board_struct loadBoard(){
    int dim;
    int turn;
           
  
    int row_count =0;
    int col_count = 0;
    piece test;
  

    FILE *saveFile;
    struct board_struct savedStruct;
 
    saveFile = fopen("save.bin","rb");

    

    if(fscanf(saveFile,"Dimension: %d",&dim)!=EOF){
         printf("");
    }

    if(fscanf(saveFile,"Turn: %d",&turn)!=EOF){
         printf("");
    }
    while(fread(&test,sizeof(piece),1,saveFile) ){
        
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
    return savedStruct;
    

   
}