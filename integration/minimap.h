#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Surface *miniBackground;
    SDL_Surface *miniPlayer;
    SDL_Rect posMiniMap;
    SDL_Rect posMiniPlayer;
    int scale; 
} MiniMap;

void initMiniMap(MiniMap *m, int level);
void updateMiniMap(MiniMap *m, SDL_Rect playerPos, SDL_Rect camera);
void displayMiniMap(MiniMap m, SDL_Surface *screen);
void freeMiniMap(MiniMap *m);

#endif
