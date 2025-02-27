#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "quiz.h"
void menu_quiz(SDL_Surface *ecran, int *run)
{
    int quitter = 0;
    SDL_Event event;
    int indice = 0;
    menu m;
    init_menu(&m);
    quiz q;
    init_quiz(&q);
    while (!quitter)
    {
        SDL_Flip(ecran);
        switch (indice)
        {
        case 0:
            afficher_menu(m, ecran);
            break;
        case 1:

            afficher_quiz(q, ecran);
            break;
        }
        while (SDL_PollEvent(&event) && *run)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quitter = 1;
                *run = 0;
                break;
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quitter = 1;
                    *run = 0;
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if (m.poscursor == 1)
                    {
                        indice = 1;
                    }
                    else
                    {

                        if (cursor(q.posr))
                        {
                            indice = 0;
                        }
                    }
                }
                break;
            }
        }
        if (*run)
        {
            update(&m);
        }
    }
    cleanup(&m, &q);
}