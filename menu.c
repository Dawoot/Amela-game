#include "raylib.h"
#include <stdbool.h>
#include <raymath.h>
#include <stdio.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define FPS 144
#define window_height 1080
#define window_width 1920

int **map = NULL;

//initializes the memory for maping
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

int main()
{
    InitWindow(window_width, window_height, "Map-maker");
    int blocksize = 100;
    int gridwidth = window_width/blocksize;
    int gridheight = window_height/blocksize;
    gridheight = gridheight + 100;
    initializetiledmap(gridwidth, gridheight);
    Color color = WHITE;
    Color palette[] = {BLUE, BROWN, RED, GREEN, PURPLE};
    int selected_color;
    bool menu = false;
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    int zoom = 0;
    Vector2 mousepos = GetMousePosition();
    int gridx = ((int)mousepos.x)/blocksize;
    int gridy = ((int)mousepos.y)/blocksize;
    SetTargetFPS(FPS);

    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE)) zoom = 0;
        else if (IsKeyPressed(KEY_TWO)) zoom = 1;
        mousepos = GetMousePosition();
        if (zoom ==0 && menu == false) {
            float wheel = GetMouseWheelMove();
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }
            if (wheel != 0)
            {
                
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

                camera.offset = GetMousePosition();

                camera.target = mouseWorldPos;

                float scale = 0.2f*wheel;
                camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);
            }
        }
        
        if (IsKeyPressed(KEY_B)) {
            menu = true;
        }
        if (IsKeyPressed(KEY_C)) {
            menu = false;
    }
            BeginDrawing();
        if (menu) {
            ClearBackground(WHITE);
            if (GuiButton((Rectangle){ 24, 260, 200, 30 }, "RED")) selected_color = 2;
            if (GuiButton((Rectangle){ 124, 324, 200, 30 }, "BLUE")) selected_color = 0;
            if (GuiButton((Rectangle){ 94, 450, 200, 30 }, "BROWN")) selected_color = 1;
            if (GuiButton((Rectangle){ 70, 550, 200, 30 }, "GREEN")) selected_color = 3;
            if (GuiButton((Rectangle){ 48, 650, 200, 30 }, "PURPLE")) selected_color = 4;
        }
        else {

        BeginMode2D(camera);
        ClearBackground( color);
            gridx = ((int)mousepos.x)/blocksize;
            gridy = ((int)mousepos.y)/blocksize;
            if (zoom < 0) {
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight ||
            IsMouseButtonDown(MOUSE_BUTTON_LEFT) && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight && zoom != 0) {
                map[gridy][gridx] = selected_color + 1; 
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight)) {
                map[gridy][gridx] =  0; 
            }
            }
        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] > 0) { 
                DrawRectangle(x * blocksize, y*blocksize, blocksize,blocksize, palette[map[y][x] - 1]);
                }
                DrawRectangleLines(x* blocksize, y*blocksize, blocksize, blocksize, GRAY);
            }
        }
        }
        EndMode2D();
        EndDrawing();
    }
    save("map.bin", gridwidth, gridheight);
    freemapmem(gridwidth, gridheight);
    CloseWindow();
    return 0;
}
