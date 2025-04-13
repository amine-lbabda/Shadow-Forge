#include "sharedscreen.h"
int main(int *argc, char **argv)
{

    int ready;
    int player_1;
    int player_2;
    int quit = 0;
    SDL_Surface *ecran = NULL;
    background b;
    background b2;
    SDL_Event e;
    b.direction = -1;
    player_1 = 0;
    player_2 = 0;
    int tabkeys[323] = {0};
    ready = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == IMG_Init(IMG_INIT_PNG);
    if (ready < 0)
    {
        printf("Erreur:%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    else
    {
        ecran = SDL_SetVideoMode(LARGEURFENETRE, HAUTEURFENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        if (ecran == NULL)
        {
            printf("Erreur:%s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        else
        {
            init_background(&b, ecran);
            poscam(&b, 0, (b.image->h - ecran->h) / 2, ecran->w / 2, ecran->h);
            posbackground(&b, 0, 0, ecran->w / 2, ecran->h);
            init_background(&b2, ecran);
            poscam(&b2, 0, (b2.image->h - ecran->h) / 2, ecran->w / 2, ecran->h);
            posbackground(&b2, ecran->w / 2, 0, ecran->w / 2, ecran->h);
            while (!quit)
            {
                SDL_BlitSurface(b.image, &b.poscamera, ecran, &b.posimage);
                SDL_BlitSurface(b2.image, &b2.poscamera, ecran, &b2.posimage);
                while (SDL_PollEvent(&e))
                {
                    switch (e.type)
                    {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_KEYDOWN:
                    {
                        tabkeys[e.key.keysym.sym] = 1;
                        if (tabkeys[SDLK_ESCAPE])
                        {
                            quit = 1;
                        }
                        if (tabkeys[SDLK_z])
                        {
                            b.direction = 3;
                            player_1 = 1;
                        }
                        else if (tabkeys[SDLK_s])
                        {
                            player_1 = 1;
                            b.direction = 2;
                        }
                        else if (tabkeys[SDLK_q])
                        {
                            b.direction = 1;
                            player_1 = 1;
                        }
                        else if (tabkeys[SDLK_d])
                        {
                            b.direction = 0;
                            player_1 = 1;
                        }
                        else if (tabkeys[SDLK_UP])
                        {
                            b2.direction = 3;
                            player_2 = 1;
                        }
                        if (tabkeys[SDLK_DOWN])
                        {
                            b2.direction = 2;
                            player_2 = 1;
                        }
                        else if (tabkeys[SDLK_LEFT])
                        {
                            b2.direction = 1;
                            player_2 = 1;
                        }
                        else if (tabkeys[SDLK_RIGHT])
                        {
                            b2.direction = 0;
                            player_2 = 1;
                        }
                    }
                    break;
                    case SDL_KEYUP:
                    {
                        if (tabkeys[SDLK_z] || tabkeys[SDLK_s] ||
                            tabkeys[SDLK_q] || tabkeys[SDLK_d])
                        {
                            b.direction = -1;
                        }
                        if (tabkeys[SDLK_UP] || tabkeys[SDLK_DOWN] ||
                            tabkeys[SDLK_LEFT] || tabkeys[SDLK_RIGHT])
                        {
                            b2.direction = -1;
                        }
                        tabkeys[e.key.keysym.sym] = 0;
                    }
                    break;
                    }
                }
                if (b.direction != -1 && player_1)
                {
                    scrolling(&b, ecran);
                }
                if (b2.direction != -1 && player_2)
                {
                    scrolling(&b2, ecran);
                }
                SDL_Flip(ecran);
            }
            SDL_FreeSurface(ecran);
            SDL_FreeSurface(b.image);
            IMG_Quit();
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }
}