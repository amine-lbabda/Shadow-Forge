#include "menu.h"
#include <SDL/SDL.h>
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL :%s \n", SDL_GetError());
    }
    SDL_Surface *screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    if (screen == NULL)
    {
        printf("Unable to Set video mode :%s \n", SDL_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    Menu(screen);
    return 0;
}