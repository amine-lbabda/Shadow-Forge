#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "save.h"
#include "menu_mode.h"
#include "menu.h"
#include "tache.h"
void chargement(SDL_Surface *ecran, int *run, int *initial_menu)
{
    SDL_Event event;
    save s;
    int quitter = 1;
    int indice = 0;
    init_save(&s);
    while (quitter && *run && *initial_menu)
    {

        

            while (SDL_PollEvent(&event) && *run)
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quitter = 0;
                    *run = 0;
                    break;
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quitter = 0;
                        *run = 0;
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        miseajour(&s);
                        if (s.btn_select == 5)
                        {
                            *initial_menu = 0;
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


        
            afficher_sous_menu(s, ecran);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quitter = 0;
                    *run = 0;
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
                            start_tache(ecran,run,initial_menu);
                            Mix_FreeMusic(s.continu);
                            s.continu = Mix_LoadMUS("../assets/audio/theme2.mp3");
                            Mix_PlayMusic(s.continu, -1);
                        }
                        if (s.btn_select == 5)
                        {
                            quitter = 0;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_n)
                    {
                        start_tache(ecran,run,initial_menu);
                    }
                }
                }
                break;
            }

        
        SDL_Flip(ecran);
    }
    liberer_save(&s);
    *initial_menu = 0; //TODO:fix the save issue
}
