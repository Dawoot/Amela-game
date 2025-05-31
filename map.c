#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>


#define FPS 144
#define window_height 1080
#define window_width 1920

int **map = NULL;

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

void freemapmem(int gridwidth, int gridheight){
    for (int y = 0; y<gridheight; y++) {
    free(map[y]);
    }
    free(map);
}

int main()
{
    int blocksize = 100;
    int gridwidth = window_width/blocksize;
    int gridheight = (window_height-100)/blocksize;
    

    initializetiledmap(gridwidth, gridheight);
    

    InitWindow(window_width, window_height, "mapu maka");
    
    Color palette[] = {BLUE, BROWN, RED, GREEN, PURPLE};
    int selected_color = 0;

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        Vector2 mousepos = GetMousePosition();
        for (int i = 0;  i< 5; i++) {
        Rectangle paletterect = {(float)(i*100), 0.0f, 100.0f, 100.0f};
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousepos, paletterect)) {
                selected_color = i;
        }
    }
        if (mousepos.y>100) {
            int gridx = ((int)mousepos.x)/blocksize;
            int gridy = ((int)mousepos.y-100)/blocksize;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight ||
            IsMouseButtonDown(MOUSE_BUTTON_LEFT) && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight) {
                map[gridy][gridx] = selected_color + 1; 
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT && gridx >=0 && gridx <gridwidth && gridy >= 0 && gridy <gridheight)) {
                map[gridy][gridx] =  0; 
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0;  i< 5; i++) {
        Rectangle paletterect = {(float)(i*100), 0.0f, 100.0f, 100.0f};
        DrawRectangleRec(paletterect,palette[i]);
        if (selected_color == i) {
        DrawRectangleLinesEx(paletterect,3 ,BLACK);
        }
        }
        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] > 0) { 
                DrawRectangle(x * blocksize, y*blocksize+100, blocksize,blocksize, palette[map[y][x] - 1]);
                }
                DrawRectangleLines(x* blocksize, y* blocksize+100, blocksize, blocksize, GRAY);
            }
        }

        EndDrawing();
    }
    save("map.bin", gridwidth, gridheight);
    freemapmem(gridwidth, gridheight);
    CloseWindow();
    return 0;
}
