#ifndef TOP_LEV_H
#define TOP_LEV_H

#include <stdint.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "raymath.h"


#define FPS 144
#define window_height 1080
#define window_width 1920
#define MAX_HP 5


extern int **map;

typedef struct enemies{
    Vector2 position;
    Vector2 speed;
    Texture2D texture;
    int8_t hp;
}enemies_t;

typedef struct player{
    Vector2 position;
    Vector2 player_o;
    Vector2 speed;
    Vector2 knockback;
    Texture2D texture;
    Rectangle player_s;
    Rectangle player_d;
    float attack_timer;
    float i_frame;
    int player_r;
    int8_t player_hp;
    bool attack;
}player_t;


#endif // !TOP_LEV_H

