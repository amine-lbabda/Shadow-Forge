#include "menu.h"
#include <SDL/SDL.h>
void buttonMoition(SDL_Rect position, SDL_Surface *screen, SDL_Surface *flip)
{
    SDL_BlitSurface(flip, NULL, screen, &position);
    SDL_Flip(screen);
}