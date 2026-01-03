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

void check_map_boundry(player_t *player, player_t *enemy, int enemyspeed_x){
    
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
        if (enemy->position.x + enemy->texture.width > window_width) {
            enemyspeed_x = -1;
        }
        if (enemy->position.x<=0) {
        enemyspeed_x = 1;
        }
}
