#ifndef COLLISION_H
#define COLLISION_H

#include <SDL/SDL.h>

int boundingBoxCollision(SDL_Rect player, SDL_Rect platform);
SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
int perfectPixelCollision(SDL_Surface *mask, SDL_Rect posPlayer);
void animateBackground(SDL_Surface *background, int *toggle);

#endif
