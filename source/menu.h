#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_mixer.h>

void Menu(SDL_Surface *screen);
void buttonMoition(SDL_Rect position,SDL_Surface *screen,SDL_Surface *flip);
void getDesktopResolution(int *width, int *height);