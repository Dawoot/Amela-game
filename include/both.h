#ifndef BOTH_H
#define BOTH_H
#include "top_lev.h"

#define TEXTURE_MUL 5


void initializetiledmap(int gridwidth, int gridheight);
void loadmap(char *filename, int gridwidth, int gridheight);
void save(char *s, int gridwidth, int gridheight);
void freemapmem(int gridwidth, int gridheight);

#endif
