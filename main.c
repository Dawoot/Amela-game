#include <stdio.h>
#include "raylib.h"

#define FPS 144
#define window_width 800
#define window_height 600

int main(){
    Texture2D player;
    InitWindow(window_width, window_height, "Love to amela");
    player = LoadTexture("textures/player.png");
    SetTargetFPS(FPS);
    
    int speed_x, speed_y = 0;
    int playerpos_y = 200;
    int playerpos_x = 200;
    int player_width = (window_width/2)-250;
    int player_height = (window_height/2) -250;

    Camera2D player_camera = {0};

    player_camera.target = (Vector2){player_width + 20.0f, player_height + 20.0f};
    player_camera.offset = (Vector2){window_width/2.0f, window_height/2.0f};
    player_camera.rotation = 0.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();
        if (IsKeyDown(KEY_D)) {
            speed_x = 10 + dt;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        if (IsKeyDown(KEY_S)) {
            speed_y = 10 + dt;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        if (IsKeyDown(KEY_A)) {
        speed_x = -10 -dt;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        if (IsKeyDown(KEY_W)) {
        speed_y = -10-dt;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        if (playerpos_x+player.width>window_width || playerpos_x <0) {
            speed_x = speed_x *-1.2;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        if (playerpos_y+player.height>window_height || playerpos_y < 0) {
            speed_y = speed_y *-1.2;
        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        else {
        speed_y = 0;
        speed_x = 0;

        playerpos_x = speed_x + playerpos_x;
        playerpos_y = speed_y + playerpos_y;
        }
        player_camera.target = (Vector2){player_width + 20.0f, player_height + 20.0f};
        BeginDrawing();
        ClearBackground(RED);
        DrawTexture(player, playerpos_x, playerpos_y, BLACK);
        BeginMode2D(player_camera); 
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
