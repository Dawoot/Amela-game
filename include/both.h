#ifndef BOTH_H

#define FPS 144
#define window_height 1080
#define window_width 1920
#define TEXTURE_MUL 5

extern int **map;

void initializetiledmap(int gridwidth, int gridheight);
void loadmap(char *filename, int gridwidth, int gridheight);
void save(char *s, int gridwidth, int gridheight);
void freemapmem(int gridwidth, int gridheight);

#endif
