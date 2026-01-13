#include "top_lev.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

void player_movement(player_t *player, Vector2 *oldPosition, float dt){
        oldPosition->x = player->position.x;
        oldPosition->y = player->position.y;
        //Movement logic
        if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) {
            player->speed.y = 0;
            player->speed.y = player->speed.y+100;
            if (player->speed.y >= 100)player->speed.y = 100;
            player->player_r = 90;
        }
        if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) {
            player->speed.x = 0;
            player->speed.x = player->speed.x-100;
            if (player->speed.x <= -100) player->speed.x = -100; 
            player->player_r = 180;
        }
        if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) {
            player->speed.x = 0;
            player->speed.x = player->speed.x+100;
            if (player->speed.x >= 100) player->speed.x = 100;
            player->player_r = 0;
        }
        if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) {
            player->speed.y = 0;
            player->speed.y =player->speed.y-100;
            if (player->speed.y<=-100) player->speed.y=-100;
            player->player_r = 270;
        }
        if (IsKeyPressed(KEY_SPACE) && !player->attack){
            player->attack = true;
            player->attack_timer = 0.2f;
        }
}
