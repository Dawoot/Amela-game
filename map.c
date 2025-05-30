#include <raylib.h>

#define FPS 144
#define window_height 1020
#define window_width 1900


int main()
{
    InitWindow(window_width, window_height, "mapu maka");
    SetTargetFPS(FPS);
    ClearBackground(WHITE);
    while (!WindowShouldClose()) {
        BeginDrawing();
    ClearBackground(WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangle(GetMouseX(), GetMouseY(), 10, 10, BLACK);
        }
        for (int i = 0; i<1920; i +=10) {
            DrawLine(0, 10+i, 1920, 10+i, BLACK);
            DrawLine(10+i, 0, 10+i, 1020, BLACK);
        }
        
    EndDrawing();
    }
    CloseWindow();
    return 0;
}
