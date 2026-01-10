#ifndef COLLISION_H
#define COLLISION_H
#include "top_lev.h"

#define TILE_EMPTY 0
#define TILE_WATER 5
#define TILE_FLOOR 1
#define TILE_OBSTACLE 3
#define TILE_WALL  4
#define TILE_LAVA  2  

bool checkMapCollision(Vector2 newPosition, Texture2D playerTexture, Rectangle **rect, int gridwidth, int gridheight, int blocksize);
bool isSolidTile(int tileType);
void check_map_boundry(player_t *player, enemies_t *enemy, int enemy_count);
void check_enemy_collision(player_t *player, enemies_t *enemy, int enemy_count);

#endif // COLLISION_H


