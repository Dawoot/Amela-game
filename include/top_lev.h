#ifndef TOP_LEV_H
#define TOP_LEV_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#define FPS 144
#define window_height 1080
#define window_width 1920

extern int **map;
typedef struct player{
    Vector2 position;
    Texture2D texture;
    Rectangle player_s;
    Rectangle player_d;
    Vector2 player_o;
    float player_sx;
    float player_sy;
    int player_r;
    int8_t player_hp;
}player_t;


#endif // !TOP_LEV_H

