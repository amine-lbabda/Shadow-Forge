#include "menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL :%s \n", SDL_GetError());
        return 1;
    }
    else
    {
        screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
        if (screen == NULL)
        {
            printf("Unable to Set video mode :%s \n", SDL_GetError());
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        {
            printf("Error:%s", Mix_GetError());
        }
        if (TTF_Init() < 0)
        {
            printf("Error:%s\n", TTF_GetError());
        }
    }
    Menu(screen);
    return 0;
}