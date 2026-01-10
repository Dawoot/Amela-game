#include "both.h"
#include <stdlib.h>
#include <stdio.h>
int **map = NULL;
//initializes the memory for maping


void loadmap(char *filename, int gridwidth, int gridheight){
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
    printf("Error loadingmap\n");
        return;
    }
    int localwidth, localheight;
    fread(&localwidth, sizeof(int), 1, file);
    fread(&localheight, sizeof(int), 1, file);
    if (localheight != gridheight || localwidth != gridwidth) {
        printf("\nSomething went wrong here!\n");
    }
    for (int i = 0; i<gridheight; i++) {
    fread(map[i], sizeof(int), gridwidth, file);    
    }
    fclose(file);
}
        
void initializetiledmap(int gridwidth, int gridheight){
    map = (int **)malloc(gridheight*sizeof(int*));
    if (map == NULL) {
        printf("Bro something went wrong when initalizing memory for map\n");
    }
    for (int i = 0; i<gridheight ; i++) {
        map[i] = (int*)malloc(gridwidth*sizeof(int*));
        if (map[i] == NULL) {
        printf("Something went wrong initalizing the memory of y map\n");
        }
    for (int x =0 ; x<gridwidth; x++) {

    map[i][x] = 0;
        }
    }
}

//saves map to a .bin file typically
void save(char *s, int gridwidth, int gridheight){
   FILE *file; 
    file = fopen(s, "wb");
    if (file == NULL) {
    printf("\nError saving\n");
    }
    fwrite(&gridwidth, sizeof(int), 1 ,file);
    fwrite(&gridheight, sizeof(int), 1 ,file);
   for (int y = 0; y<gridheight; y++) {
        fwrite(map[y], sizeof(int), gridwidth, file);
   } 
    fclose(file);
}


//frees map memory from ram, done at the end of the program
void freemapmem(int gridwidth, int gridheight){
    for (int y = 0; y<gridheight; y++) {
    free(map[y]);
    }
    free(map);
}
