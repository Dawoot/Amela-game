#include "collision.h"
#include "top_lev.h"
#include <raylib.h>

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
    int startY = (int)((newPosition.y-12.5) / blocksize); 
    int endY = (int)((newPosition.y + playerTexture.height) / blocksize);
    
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

void check_map_boundry(player_t *player, enemies_t *enemy, int enemy_count){
    
        if (player->position.y<0) {
        player->position.y = 0;
        player->position.x = player->position.x;
        }
        if (player->position.y+player->texture.height>window_height) {
            player->position.y = window_height-player->texture.height;
        }
        if (player->position.x<0) {
        player->position.x = 0;
            player->position.y = player->position.y;
        }
        if (player->position.x + player->texture.width > window_width) {
        player->position.x = window_width - player->texture.width;
        }
    for (int i = 0; i<enemy_count; i++) {
    
        if (enemy[i].position.x >=window_width) {
        enemy[i].speed.x = -enemy[i].speed.x;
        }
        if (enemy[i].position.x<=0) {
        enemy[i].speed.x = -enemy[i].speed.x;
        }
    }
}
void check_enemy_collision(player_t *player, enemies_t *enemy, int enemy_count, Texture *enemy_t){
    for (int i=0; i<enemy_count; i++) { 
    Rectangle p =  {player->position.x-12.5, player->position.y-12.5, (float)player->texture.width,(float) player->texture.height};
    Rectangle e = {enemy[i].position.x, enemy[i].position.y, (float)enemy_t->width, (float)enemy_t->height};

    if (CheckCollisionRecs(p, e)){
    float strength = 500;
    Vector2 p_c = {(float)(p.x + p.width *0.5), (float)(p.y + p.height*0.5)};
    Vector2 e_c = {(float)(e.x + e.width *0.5), (float)(e.y + e.height*0.5)};
        
    Vector2 direction = Vector2Subtract(p_c, e_c);
    if (Vector2Length(direction) < 0.001f) direction = (Vector2){ 0.0f, -1.0f };
        
    direction = Vector2Normalize(direction);
    player->knockback.x += strength*direction.x;
    player->knockback.y += strength*direction.y;
    player->player_hp--;
        }
    }
}
