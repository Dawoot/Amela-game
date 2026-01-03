#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "both.h"

#define _GNU_SOURCE

#define TILE_EMPTY 0
#define TILE_WATER 5      // Collision
#define TILE_FLOOR 1     // No collision
#define TILE_OBSTACLE 3  // Collision
#define TILE_WALL  4    // No collision
#define TILE_LAVA  2  



        
typedef struct player{
    Vector2 position;
    Texture2D texture;
    Rectangle player_s;
    Rectangle player_d;
    Vector2 player_o;
    int player_r;
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

    Image dirt = LoadImage("../textures/dirt.png");
    Image lava = LoadImage("../textures/lava.png");
    Image m_wood = LoadImage("../textures/magic_wood.png");
    Image ocean = LoadImage("../textures/ocean.png");
    Image mountain = LoadImage("../textures/mountain.png");
    

    player_t player;
    player_t enemy;
    player.texture= LoadTexture("../textures/Amela.png");
    enemy.texture = LoadTexture("../textures/Enemy.png");
    player.player_s = (Rectangle){0.0f,0.0f, player.texture.width, player.texture.height};
    player.player_d = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    player.player_o = (Vector2){((float)(player.texture.width/2)), ((float)(player.texture.height/2))};

    ImageResizeNN(&dirt, dirt.width*TEXTURE_MUL, dirt.height*TEXTURE_MUL);
    ImageResizeNN(&lava, lava.width*TEXTURE_MUL, lava.height*TEXTURE_MUL);
    ImageResizeNN(&m_wood, m_wood.width * TEXTURE_MUL, m_wood.height * TEXTURE_MUL);
    ImageResizeNN(&ocean, ocean.width * TEXTURE_MUL, ocean.height* TEXTURE_MUL);
    ImageResizeNN(&mountain, mountain.width * TEXTURE_MUL, mountain.height * TEXTURE_MUL);
    
    SetTargetFPS(FPS);
    
    Texture dirt_t = LoadTextureFromImage(dirt); 
    Texture lava_t = LoadTextureFromImage(lava);
    Texture m_wood_t = LoadTextureFromImage(m_wood);
    Texture ocean_t = LoadTextureFromImage(ocean);
    Texture mountain_t = LoadTextureFromImage(mountain);
    
    Rectangle **rect;
    Texture list[] = {dirt_t, lava_t, m_wood_t, ocean_t, mountain_t};
    Rectangle source = {0.0f, 0.0f, 25.0, 25.0};
    Vector2 origin = {0.0f,0.0f};

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
        
        //Movement logic
        Vector2 oldPosition = player.position;
        Vector2 newPosition = player.position;
        float dt = GetFrameTime();
        enemy.position.x  = enemy.position.x+enemyspeed_x;
        if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) {
            amela_speed_y = 0;
            amela_speed_y = amela_speed_y+100*dt;
            if (amela_speed_y >= 10)amela_speed_y = 10;
             newPosition.y = newPosition.y + amela_speed_y;
            player.player_r = 90;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) {
            amela_speed_x = 0;
            amela_speed_x = amela_speed_x-100*dt;
            if (amela_speed_x <= -10) amela_speed_x = -10; 
            newPosition.x = newPosition.x + amela_speed_x;
            player.player_r = 180;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) {
            amela_speed_x = 0;
            amela_speed_x = amela_speed_x+100*dt;
            if (amela_speed_x >= 10) amela_speed_x = 10;
            newPosition.x = newPosition.x + amela_speed_x;
            player.player_r = 0;
                if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) {
            amela_speed_y = 0;
            amela_speed_y =amela_speed_y-100*dt;
            if (amela_speed_y<=-10) amela_speed_y = -10;
             newPosition.y = newPosition.y +amela_speed_y;
            player.player_r = 270;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
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

        //Rendering logic
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] > 0) {
                    
                    DrawRectangleRec(rect[y][x], WHITE);
                    Rectangle dest ={x*blocksize, y*blocksize,25.0,25.0};
                    DrawTexturePro(list[map[y][x]-1],source, dest,(Vector2){0.0f, 0.0f},0.0f ,WHITE);

                    if (CheckCollisionPointRec(player.position, rect[y][x])) {
                    }
                }
                DrawRectangleLines(x* blocksize, y* blocksize, blocksize, blocksize, GRAY);
            }
        }
        player.player_d = (Rectangle){player.position.x, player.position.y, player.texture.width, player.texture.height};
        DrawTexturePro(player.texture, player.player_s, player.player_d,player.player_o,player.player_r, WHITE);
        DrawTexture(enemy.texture,enemy.position.x,enemy.position.y, WHITE);
        EndDrawing();
    }
    freemapmem(gridwidth, gridheight);
    freerectmem(rect, gridheight);
    UnloadTexture(enemy.texture);
    UnloadTexture(player.texture);
    CloseWindow();
    return 0;
}
