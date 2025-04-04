#include "history.h"
void history_menu(SDL_Surface *ecran, int *run, TTF_Font *font, SDL_Color couleurText, int *initial_menu)
{
    SDL_Rect positionhist, positionreturn;
    SDL_Surface *menu_hist = NULL;
    SDL_Surface *return_hist = NULL;
    int quit = 0;
    return_hist = TTF_RenderText_Blended(font, "RETURN", couleurText);
    menu_hist = IMG_Load("./assets/backgrounds/hist.png");
    positionhist.x = 0;
    positionhist.y = 0;
    positionreturn.x = 20;
    positionreturn.y = 1000;
    SDL_Event e;
    while (quit == 0 && *run)
    {
        SDL_BlitSurface(menu_hist, NULL, ecran, &positionhist);
        SDL_BlitSurface(return_hist, NULL, ecran, &positionreturn);
        while (SDL_PollEvent(&e) && quit == 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                *run = 0;
                break;

            case SDL_KEYDOWN:
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    *run = 0;
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                if (e.button.x >= positionreturn.x && e.button.x <= positionreturn.x + return_hist->w && e.button.y >= positionreturn.y && e.button.y <= positionreturn.y + return_hist->h)
                {
                    quit = 1;
                }
            }
            break;
            }
        }
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu_hist);
    menu_hist = NULL;
    SDL_FreeSurface(return_hist);
    return_hist = NULL;
    *initial_menu = 0;
}