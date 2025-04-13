#ifndef COLLISION_H
#define COLLISION_H

#include <SDL/SDL.h>

int boundingBoxCollision(SDL_Rect player, SDL_Rect platform);
int perfectPixelCollision(SDL_Surface *player, SDL_Surface *platform, SDL_Rect posPlayer, SDL_Rect posPlatform);
void animateBackground(SDL_Surface *background, int *toggle);

#endif
