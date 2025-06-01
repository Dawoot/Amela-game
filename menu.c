#include <raylib.h>
#include <stdlib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(){
    InitWindow(1920, 1080, "menu test");
    SetExitKey(KEY_G);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
