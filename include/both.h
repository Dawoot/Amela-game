#ifndef BOTH_H
#define BOTH_H
#include "top_lev.h"

#define TEXTURE_MUL 5


void initializetiledmap(map_t *maps);
void loadmap(char *filename,map_t *maps);
void save(char *s, map_t *maps);
void freemapmem(map_t *maps);

#endif
