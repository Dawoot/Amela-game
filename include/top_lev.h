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
typedef struct player{
    Vector2 position;
    Vector2 player_o;
    Vector2 speed;
    Vector2 knockback;
    Texture2D texture;
    Rectangle player_s;
    Rectangle player_d;
    int player_r;
    int8_t player_hp;
}player_t;


#endif // !TOP_LEV_H

