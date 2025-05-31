#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define _GNU_SOURCE

#define FPS 144
#define window_width 1920
#define window_height 1080

int **map;

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
    for (int y = 0; y<gridheight; y++) {
    for (int x = 0; x<gridwidth; x++) {
            printf("Mapvalue at: y:%d x:%d  value:%d\n", y,x,map[y][x]);
    }
    }
    fclose(file);
}
void freemapmem(int gridwidth, int gridheight){
    for (int y = 0; y<gridheight; y++) {
    free(map[y]);
    }
    free(map);
}

int main(){
    Texture2D player;
    int blocksize = 100;
    int gridwidth = window_width/blocksize;
    int gridheight = (window_height-100)/blocksize;
    initializetiledmap(gridwidth, gridheight);
    InitWindow(window_width, window_height, "Love to amela");
    loadmap("map.bin", gridwidth, gridheight);
    Color palette[] = {BLUE, BROWN, RED, GREEN, PURPLE};
    player = LoadTexture("textures/player.png");
    SetTargetFPS(FPS);
    UnloadTexture(player);
    int playerpos_y = 100;
    int playerpos_x = 100;


    while (!WindowShouldClose()) {
        //For movement
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_S)) {
            playerpos_y = playerpos_y+100;
        }
        if (IsKeyPressed(KEY_A)) {
            playerpos_x = playerpos_x -100;
        }
        if (IsKeyPressed(KEY_D)) {
        playerpos_x = playerpos_x+100;
        }
        if (IsKeyPressed(KEY_W)) {
        playerpos_y = playerpos_y-100;
        }
        if (playerpos_y<0) {
        playerpos_y = 0;
        playerpos_x = playerpos_x;
        }
        if (playerpos_y+player.height>window_height) {
            playerpos_y = window_height - player.height;
        }
        if (playerpos_x<0) {
        playerpos_x = 0;
            playerpos_y = playerpos_y;
        }
        if (playerpos_x + player.width > window_width) {
        playerpos_x = window_width - player.width;
        }

        //Camera
        //updating drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] > 0) {
                DrawRectangle(x * blocksize, y*blocksize+100, blocksize,blocksize, palette[map[y][x] - 1]);
                }
                DrawRectangleLines(x* blocksize, y* blocksize+100, blocksize, blocksize, GRAY);
            }
        }
        DrawTexture(player, playerpos_x, playerpos_y, BLACK);
        
        EndDrawing();
    }
    freemapmem(gridwidth, gridheight);
    CloseWindow();
    return 0;
}
