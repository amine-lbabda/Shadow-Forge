#include "minimap.h"
#include <stdio.h>

void initMiniMap(MiniMap *m, int level) {
    char path[50];
    if (level == 1)
        sprintf(path, "mini_background1.bmp");
    else
        sprintf(path, "mini_background2.bmp");

    m->miniBackground = SDL_LoadBMP(path);
    m->miniPlayer = SDL_LoadBMP("mini_player.bmp"); 
    m->posMiniMap.x = 10;
    m->posMiniMap.y = 10;
    m->scale = 20; 
}

void updateMiniMap(MiniMap *m, SDL_Rect playerPos, SDL_Rect camera) {
    SDL_Rect absPos;
    absPos.x = playerPos.x + camera.x;
    absPos.y = playerPos.y + camera.y;

    m->posMiniPlayer.x = m->posMiniMap.x + (absPos.x * m->scale / 100);
    m->posMiniPlayer.y = m->posMiniMap.y + (absPos.y * m->scale / 100);
}

void displayMiniMap(MiniMap m, SDL_Surface *screen) {
    SDL_BlitSurface(m.miniBackground, NULL, screen, &m.posMiniMap);
    SDL_BlitSurface(m.miniPlayer, NULL, screen, &m.posMiniPlayer);
}

void freeMiniMap(MiniMap *m) {
    SDL_FreeSurface(m->miniBackground);
    SDL_FreeSurface(m->miniPlayer);
}
