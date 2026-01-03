#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "both.h"
#define _GNU_SOURCE
#define FPS 144
#define window_width 1920
#define window_height 1080
#define TILE_EMPTY 0
#define TILE_WATER 1      // Collision
#define TILE_FLOOR 4     // No collision
#define TILE_OBSTACLE 5  // Collision
#define TILE_WALL 2     // No collision
#define TILE_LAVA 3   



        
typedef struct player{
    Vector2 position;
    Texture2D texture; 
}player_t;

void freerectmem(Rectangle **rect, int gridheight) {
    for (int y = 0; y < gridheight; y++) {
        free(rect[y]);
    }
    free(rect);
}
bool isSolidTile(int tileType) {
    switch(tileType) {
        case TILE_WALL:
        case TILE_OBSTACLE:
        case TILE_LAVA:
        case TILE_WATER:
            return true;
        default:
            return false;
    }
}
bool checkMapCollision(Vector2 newPosition, Texture2D playerTexture, Rectangle **rect, int gridwidth, int gridheight, int blocksize) {
    
    Rectangle playerRect = {
        newPosition.x,
        newPosition.y,
        (float)playerTexture.width,
        (float)playerTexture.height
    };
    
    int startX = (int)(newPosition.x / blocksize);
    int endX = (int)((newPosition.x + playerTexture.width) / blocksize);
    int startY = (int)((newPosition.y - 25) / blocksize); 
    int endY = (int)((newPosition.y + playerTexture.height - 25) / blocksize);
    
    startX = (startX < 0) ? 0 : startX;
    endX = (endX >= gridwidth) ? gridwidth - 1 : endX;
    startY = (startY < 0) ? 0 : startY;
    endY = (endY >= gridheight) ? gridheight - 1 : endY;
    
    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (isSolidTile(map[y][x])) {
                if (CheckCollisionRecs(playerRect, rect[y][x])) {
                    return true; 
                }
            }
        }
    } 
    return false; 
}
int main(){
    int blocksize = 25;
    int gridwidth = window_width/blocksize;
    int gridheight = (window_height-25)/blocksize;
    uint8_t level_counter = 0;

    initializetiledmap(gridwidth, gridheight);
    
    InitWindow(window_width, window_height, "Love to amela");
    
    loadmap("../maps/map.bin", gridwidth, gridheight);

    Color palette[] = {BLUE, BROWN, RED, GREEN, PURPLE};

    player_t player;
    player_t enemy;
    player.texture= LoadTexture("../textures/Amela.png");
    enemy.texture = LoadTexture("../textures/Enemy.png");
    SetTargetFPS(FPS);
    
    Rectangle **rect;

    rect = (Rectangle **)malloc(sizeof(Rectangle*)*gridheight);

    for (int x = 0; x<gridheight; x++) {
        rect[x]  = (Rectangle*)malloc(sizeof(Rectangle)*gridwidth);
    }
    for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
            Rectangle temp = {(float)x * blocksize, (float)y * blocksize, (float)blocksize, (float)blocksize};
            rect[y][x] = temp;
        }
    }

    if (rect == NULL) {
    printf("Error: rect is not allocated\n");
    return 1;
    }
    
    player.position.x = 25;
    player.position.y = 25;

    enemy.position.x = 500;
    enemy.position.y = 500;
    

    int enemyspeed_x = 1;
    float amela_speed_x = 0;
    float amela_speed_y = 0;
    while (!WindowShouldClose()) {

        Vector2 oldPosition = player.position;
        Vector2 newPosition = player.position;
        //For movement
        float dt = GetFrameTime();
        enemy.position.x  = enemy.position.x+enemyspeed_x;
        if (IsKeyPressed(KEY_S)) {
            amela_speed_y = 10;
             newPosition.y = newPosition.y + amela_speed_y;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_A)) {
            amela_speed_x = -10;
            newPosition.x = newPosition.x + amela_speed_x;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_D)) {
            amela_speed_x = 10;
            newPosition.x = newPosition.x + amela_speed_x;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_W)) {
            amela_speed_y =-10;
             newPosition.y = newPosition.y +amela_speed_y;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }else{

        }
        if (player.position.y<0) {
        player.position.y = 0;
        player.position.x = player.position.x;
        }
        if (player.position.y+player.texture.height>window_height) {
            player.position.y = window_height-player.texture.height;
        }
        if (player.position.x<0) {
        player.position.x = 0;
            player.position.y = player.position.y;
        }
        if (player.position.x + player.texture.width > window_width) {
        player.position.x = window_width - player.texture.width;
        }
        if (enemy.position.x + enemy.texture.width > window_width) {
            enemyspeed_x = -1;
        }
        if (enemy.position.x<=0) {
        enemyspeed_x = 1;
        }
        Rectangle p =  {player.position.x, player.position.y, player.texture.width, player.texture.height};
        Rectangle e = {enemy.position.x, enemy.position.y, enemy.texture.width, enemy.texture.height};
        if (CheckCollisionRecs(p, e)) {
            player.position.x = 25;
            player.position.y = 25;
        }
        //updating drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] > 0) {
                    DrawRectangleRec(rect[y][x], palette[map[y][x]-1]);
                    if (CheckCollisionPointRec(player.position, rect[y][x])  ) {
                    }
                }
                DrawRectangleLines(x* blocksize, y* blocksize, blocksize, blocksize, GRAY);
            }
        }
        DrawTexture(player.texture, player.position.x, player.position.y, BLACK);
        DrawTexture(enemy.texture,enemy.position.x,enemy.position.y, RED);
        EndDrawing();
    }
    freemapmem(gridwidth, gridheight);
    freerectmem(rect, gridheight);
    UnloadTexture(enemy.texture);
    UnloadTexture(player.texture);
    CloseWindow();
    return 0;
}
