#include "top_lev.h"
#include "both.h"
#include "collision.h"
#include "movement.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#define MOVEMENT_SPEED 100;
#define blocksize 25

void freerectmem(Rectangle **rect, int gridheight) {
    for (int y = 0; y < gridheight; y++) {
        free(rect[y]);
    }
    free(rect);
}
int main(){
    
    int gridwidth = window_width/blocksize;
    int gridheight = (window_height)/blocksize;
    uint8_t level_counter = 0;
    printf("gridheight: %d gridwidth: %d \n", gridheight, gridwidth);
    int **position;
    initializetiledmap(gridwidth, gridheight);

    position = (int **)malloc(gridheight*sizeof(int*));
    if (position == NULL) {
        printf("Bro something went wrong when initalizing memory for position\n");
    }
    for (int i = 0; i<gridheight ; i++) {
        position[i] = (int*)malloc(gridwidth*sizeof(int*));
        if (position[i] == NULL) {
        printf("Something went wrong initalizing the memory of y position\n");
        }
    for (int x =0 ; x<gridwidth; x++) {
    position[i][x] = 0;
        }
    }
    
    InitWindow(window_width, window_height, "Love to amela");
    
    loadmap("../maps/map.bin", gridwidth, gridheight, position);

    Color palette[] = {BLUE, BROWN, RED, GREEN, PURPLE};

    Image dirt = LoadImage("../textures/dirt.png");
    Image lava = LoadImage("../textures/lava.png");
    Image m_wood = LoadImage("../textures/magic_wood.png");
    Image ocean = LoadImage("../textures/ocean.png");
    Image mountain = LoadImage("../textures/mountain.png");
    Image sword = LoadImage("../textures/sword.png");

    player_t player;
    enemies_t *enemies; 
    player.texture= LoadTexture("../textures/Amela.png");
    player.player_s = (Rectangle){0.0f,0.0f, player.texture.width, player.texture.height};
    player.player_d = (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    player.player_o = (Vector2){((float)(player.texture.width/2)), ((float)(player.texture.height/2))};

    ImageResizeNN(&dirt, dirt.width*TEXTURE_MUL, dirt.height*TEXTURE_MUL);
    ImageResizeNN(&lava, lava.width*TEXTURE_MUL, lava.height*TEXTURE_MUL);
    ImageResizeNN(&m_wood, m_wood.width * TEXTURE_MUL, m_wood.height * TEXTURE_MUL);
    ImageResizeNN(&ocean, ocean.width * TEXTURE_MUL, ocean.height* TEXTURE_MUL);
    ImageResizeNN(&mountain, mountain.width * TEXTURE_MUL, mountain.height * TEXTURE_MUL);
    ImageResizeNN(&sword, sword.width * TEXTURE_MUL, sword.height * TEXTURE_MUL); 
    
    SetTargetFPS(FPS);
    
    Texture dirt_t = LoadTextureFromImage(dirt); 
    Texture lava_t = LoadTextureFromImage(lava);
    Texture m_wood_t = LoadTextureFromImage(m_wood);
    Texture ocean_t = LoadTextureFromImage(ocean);
    Texture mountain_t = LoadTextureFromImage(mountain);
    Texture heart_f = LoadTexture("../textures/heart.png");
    Texture heart_e = LoadTexture("../textures/empty_heart.png");
    Texture enemy_t = LoadTexture("../textures/Enemy.png");
    player.weapon_texture = LoadTextureFromImage(sword);

    UnloadImage(dirt);
    UnloadImage(lava);
    UnloadImage(m_wood);
    UnloadImage(ocean);
    UnloadImage(mountain);
    UnloadImage(sword);

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
    
    int enemy_count=0;
    for (int y=0; y<gridheight; y++) {
        for (int x =0; x<gridwidth; x++) {
            if (position[y][x] == 2) {
            player.position.x = x*player.texture.width; 
            player.position.y = y*player.texture.height;
            }
            if (position[y][x]==1) {
                enemy_count++;
                //Every increment add one to i 
                //When we do blocks of enemies!
            }
        }
    }
    enemies = (enemies_t* )malloc((sizeof(enemies_t)*enemy_count));
    enemy_count = 0;
    for (int y=0; y<gridheight; y++) {
        for (int x =0; x<gridwidth; x++) {
            if (position[y][x] == 1) {
                enemies[enemy_count].position.x = x*blocksize;
                enemies[enemy_count].position.y = y*blocksize;
                enemies[enemy_count].speed.x = 1.2;
            enemy_count++;
            
            }
        }
    } 
    if (enemies == NULL) {
        printf("Enemy failed to allocate\n");
        exit(1);
    }
    printf("SIZEOF ENEMIES!: %lu\n", sizeof(enemies_t)*enemy_count);

    
    player.speed.x = 0;
    player.speed.y = 0;
    player.player_hp = MAX_HP;

    Vector2 oldPosition = player.position;
    Vector2 newPosition = player.position;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (player.player_hp <= 0) {

            player.position.x = 25;
            player.position.y = 25;
            player.player_hp = MAX_HP;
        }
        if (!checkMapCollision(newPosition, player.texture, rect, gridwidth, gridheight, blocksize)) {
            player.position = newPosition;
        }
        player_movement(&player,&oldPosition, dt);
        for (int i = 0; i<enemy_count; i++) {
            enemies[i].position.x = enemies[i].position.x + enemies[i].speed.x;
        }
        check_enemy_collision(&player, enemies, enemy_count, &enemy_t);
        Vector2 final = {player.knockback.x + player.speed.x, player.speed.y + player.knockback.y};
        player.knockback.x = player.knockback.x * 0.9f;
        player.knockback.y = player.knockback.y * 0.9f;
        
        newPosition.x = newPosition.x + final.x*dt;
        newPosition.y = newPosition.y + final.y*dt;
        
        check_map_boundry(&player, enemies, enemy_count); 

        player.speed.x = 0;
        player.speed.y = 0;
        if (player.attack) {
            player.attack_timer -=dt;
            if (player.attack_timer<=0) {
                player.attack = false;
                player.attack_timer = 0;
            
            }
        }
        BeginDrawing();
        //Rendering logic
        ClearBackground(RAYWHITE);

        for (int y = 0; y<gridheight; y++) {
        for (int x = 0; x<gridwidth; x++) {
                if (map[y][x] >0 && map[y][x]!= 6 && map[y][x]!= 7) {
                    

                    DrawRectangleRec(rect[y][x], WHITE);
                    Rectangle dest ={x*blocksize, y*blocksize,25.0,25.0};
                    DrawTexturePro(list[map[y][x]-1],source, dest,(Vector2){0.0f, 0.0f},0.0f ,WHITE);

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
        
        if (player.attack) {
            Vector2 sword_r = {
                cosf(player.player_r * DEG2RAD),
                sinf(player.player_r * DEG2RAD)};
            Rectangle sword_dest = {
                player.position.x + 6 * sword_r.x, 
                player.position.y + 6 * sword_r.y, 
                player.weapon_texture.width,
                player.weapon_texture.height};

            DrawTexturePro(player.weapon_texture, (Rectangle){0.0f, 0.0f, player.weapon_texture.width, player.weapon_texture.height}, sword_dest , (Vector2) {0.0f, player.weapon_texture.height/2}, player.player_r, WHITE);
        }

        DrawTexturePro(player.texture, player.player_s, player.player_d,player.player_o,player.player_r, WHITE); 

        for (int i=0; i<enemy_count; i++) {
        DrawTexture(enemy_t, enemies[i].position.x,enemies[i].position.y , WHITE);
        }
        EndDrawing();
    }
    freemapmem(gridwidth, gridheight);
    freerectmem(rect, gridheight);
    free(enemies);
    for (int i =0; i<(sizeof(list)/sizeof(list[0])); i++) {
        UnloadTexture(list[i]);
    }
    UnloadTexture(player.texture);
    UnloadTexture(enemy_t);
    UnloadTexture(player.weapon_texture);
    CloseWindow();
    return 0;
}
