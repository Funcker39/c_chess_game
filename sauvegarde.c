#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sauvegarde.h"
#include "board.h"

void saveBoard(piece board[12][12],int dimension){
    FILE *saveFile;
    saveFile = fopen("save.bin","w");
    fprintf(saveFile,"Dimension: %d",dimension);
    for(int i =0;i<dimension;i++){
         
            for(int j =0;j<dimension;j++){
                fwrite(&board[j][i],sizeof(piece),1,saveFile);
            }
       
     }
 
 
    fclose(saveFile);

}

void loadBoard(){
    int dim;
           
  
    int row_count =0;
    int col_count = 0;
    piece test;
    piece savedBoard[12][12];

    FILE *saveFile;

 
    saveFile = fopen("save.bin","rb");

    

    if(fscanf(saveFile,"Dimension: %d",&dim)!=EOF){
         printf("");
    }
    while(fread(&test,sizeof(piece),1,saveFile) ){
        
            if(col_count<dim){
        
                savedBoard[col_count][row_count]=test;
             
            
            }
            else if(col_count>=dim){
                col_count=0;
               
           
                
                row_count+=1;
                savedBoard[col_count][row_count]=test;
           
            }
          
            col_count+=1;
        

        

    }
   

   
    fclose(saveFile);

    printBoard(savedBoard,dim);
    

   
}