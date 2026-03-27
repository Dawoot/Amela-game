#include "both.h"
#include "top_lev.h"
#include <stdlib.h>
#include <stdio.h>
//initializes the memory for maping

void loadmap(char *filename, int **position, map_t *maps){
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
    printf("Error loadingmap\n");
        return;
    }
    int localwidth, localheight;
    fread(&localwidth, sizeof(int), 1, file);
    fread(&localheight, sizeof(int), 1, file);
    if (localheight != maps->gridheight || localwidth != maps->gridwidth) {
        printf("\nSomething went wrong here!\n");
    }
    for (int i = 0; i<maps->gridheight; i++) {
    fread(maps->map[i], sizeof(int), maps->gridwidth, file);    
    }
    for (int i = 0; i<maps->gridheight; i++) {
    fread(position[i], sizeof(int), maps->gridwidth, file);
    }
    fclose(file);
}
        
void initializetiledmap(map_t *maps){
    maps->map = (int **)malloc(maps->gridheight*sizeof(int*));
    if (maps->map == NULL) {
        printf("Bro something went wrong when initalizing memory for map\n");
    }
    for (int i = 0; i<maps->gridheight ; i++) {
        maps->map[i] = (int*)malloc(maps->gridwidth*sizeof(int*));
        if (maps->map[i] == NULL) {
        printf("Something went wrong initalizing the memory of y map\n");
        }
    for (int x =0 ; x<maps->gridwidth; x++) {

    maps->map[i][x] = 0;
        }
    }
}

//saves map to a .bin file typically
void save(char *s, map_t *maps){
   FILE *file; 
    file = fopen(s, "wb");
    if (file == NULL) {
    printf("\nError saving\n");
    }
    fwrite(&maps->gridwidth, sizeof(int), 1 ,file);
    fwrite(&maps->gridheight, sizeof(int), 1 ,file);
   for (int y = 0; y<maps->gridheight; y++) {
        fwrite(maps->map[y], sizeof(int), maps->gridwidth, file);
   } 
    fclose(file);
}


//frees map memory from ram, done at the end of the program
void freemapmem(map_t *maps){
    for (int y = 0; y<maps->gridheight; y++) {
    free(maps->map[y]);
    }
    free(maps->map);
}
