#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "save.h"
#include "menu_mode.h"
#include "menu.h"
void chargement(SDL_Surface *ecran)
{
    SDL_Event event;
    save s;
    int quitter = 1;
    int indice = 0;
    init_save(&s);
    while (quitter)
    {
        switch (indice)
        {
        case 0:
            afficher_save(s, ecran);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quitter = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        miseajour(&s);
                        if (s.btn_select == 5)
                        {
                            Menu(ecran);
                        }
                        if (s.btn_select == 1)
                        {
                            indice = 1;
                        }
                        if (s.btn_select == 2)
                        {
                            quitter = 0;
                        }
                    }
                    break;
                }
            }
            SDL_Flip(ecran);
            break;

        case 1:
            afficher_sous_menu(s, ecran);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quitter = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        miseajour_sous_menu(&s);
                        if (s.btn_select == 3)
                        {
                            printf("Load Game sélectionné\n");
                        }
                        if (s.btn_select == 4)
                        {
                            printf("New Game sélectionné\n");
                            menu_mode(ecran);
                        }
                        if (s.btn_select == 5)
                        {
                            indice = 0;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_n)
                    {
                        menu_mode(ecran);
                    }
                }
                }
                break;
            }
            SDL_Flip(ecran);
            break;
        }
    }
    liberer_save(&s);
    SDL_FreeSurface(ecran);
    SDL_Quit();
}
