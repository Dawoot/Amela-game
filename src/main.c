#include "top_lev.h"
#include "both.h"
#include "collision.h"
#include <raylib.h>
#include <stdio.h>

#define _GNU_SOURCE

void freerectmem(Rectangle **rect, int gridheight) {
    for (int y = 0; y < gridheight; y++) {
        free(rect[y]);
    }
    free(rect);
}

int main(){
    
    int blocksize = 25;
    int gridwidth = window_width/blocksize;
    int gridheight = (window_height)/blocksize;
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
    Texture heart_f = LoadTexture("../textures/heart.png");
    Texture heart_e = LoadTexture("../textures/empty_heart.png");

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
    

    enemy.player_sx = 1;
    
    player.player_sx = 0;
    player.player_sy = 0;
    player.player_hp = 5;
    printf("Sizeof struct: %lu", sizeof(player_t));
    while (!WindowShouldClose()) {
        
        //Movement logic
        Vector2 oldPosition = player.position;
        Vector2 newPosition = player.position;
        float dt = GetFrameTime();
        enemy.position.x  = enemy.position.x+enemy.player_sx;
        if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) {
            player.player_sy = 0;
            player.player_sy = player.player_sy+50*dt;
            if (player.player_sy >= 50)player.player_sy = 50;
             newPosition.y = newPosition.y + player.player_sy;
            player.player_r = 90;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) {
            player.player_sx = 0;
            player.player_sx = player.player_sx-100*dt;
            if (player.player_sx <= -50) player.player_sx = -50; 
            newPosition.x = newPosition.x + player.player_sx;
            player.player_r = 180;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) {
            player.player_sx = 0;
            player.player_sx = player.player_sx+100*dt;
            if (player.player_sx >= 50) player.player_sx = 50;
            newPosition.x = newPosition.x + player.player_sx;
            player.player_r = 0;
                if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
        if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) {
            player.player_sy = 0;
            player.player_sy =player.player_sy-100*dt;
            if (player.player_sy<=-50) player.player_sy = -50;
             newPosition.y = newPosition.y +player.player_sy;
            player.player_r = 270;
            if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
                player.position = newPosition;
            }
        }
       check_map_boundry(&player, &enemy); 
        Rectangle p =  {player.position.x, player.position.y, player.texture.width, player.texture.height};
        Rectangle e = {enemy.position.x, enemy.position.y, enemy.texture.width, enemy.texture.height};
        if (CheckCollisionRecs(p, e)) {
            player.player_hp = player.player_hp-1;
            if (player.player_sx == 0 && player.player_sy == 0) {

            }
            player.player_sx = -player.player_sx;
            player.player_sy = -player.player_sy;
        }
        if (player.player_hp <= 0) {
            player.position.x = 25;
            player.position.y = 25;
            player.player_hp = 5;
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
            }
        }
        for (int i = 0; i<player.player_hp; i++) {
            DrawTexture(heart_f, 0+(heart_f.width*i), 0, WHITE);
        }
        for (int i=MAX_HP; i>player.player_hp; i--) {
            DrawTexture(heart_e, 0+(heart_e.width*(i-1)), 0, WHITE);
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
