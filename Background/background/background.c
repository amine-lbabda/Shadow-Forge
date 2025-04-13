#include "background.h"
#include <stdio.h>
#include <stdlib.h>

int main(int *argc, char **argv)
{
    int ready;
    int quit = 0;
    SDL_Surface *ecran = NULL;
    background b;
    SDL_Event e;

    // Initialisation des variables
    b.direction = -1; // Aucune direction initialement

    // Initialisation de SDL et SDL_image
    ready = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == IMG_Init(IMG_INIT_PNG);
    if (ready < 0)
    {
        printf("Erreur: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    else
    {
        // Création de la fenêtre
        ecran = SDL_SetVideoMode(LARGEURFENETRE, HAUTEURFENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
        if (ecran == NULL)
        {
            printf("Erreur: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        else
        {
            // Initialisation du fond
            init_background(&b, ecran);

            // Boucle principale
            while (quit==0)
            {
                // Gestion des événements
                while (SDL_PollEvent(&e))
                {
                    switch (e.type)
                    {
                    case SDL_QUIT:
                        quit = 1;
                        break;

                    case SDL_KEYDOWN:
                        // Définir la direction en fonction de la touche pressée
                        if (e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = 1;
                        }
                        else if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP)
                        {
                            b.direction = 3; // Haut
                        }
                        else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
                        {
                            b.direction = 2; // Bas
                        }
                        else if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT)
                        {
                            b.direction = 1; // Gauche
                        }
                        else if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
                        {
                            b.direction = 0; // Droite
                        }
                        break;

                    case SDL_KEYUP:
                        // Réinitialiser la direction lorsque la touche est relâchée
                        b.direction = -1; // Aucune direction
                        break;
                    }
                }

                // Si une direction est active, appliquer le scrolling
                if (b.direction != -1)
                {
                    scrolling(&b, ecran);
                    printf("Position caméra: x=%d, y=%d\n", b.poscamera.x, b.poscamera.y);
                }

                // Affichage du fond
                SDL_BlitSurface(b.image, &b.poscamera, ecran, NULL);
                SDL_Flip(ecran);
            }

            // Libération des ressources
            SDL_FreeSurface(ecran);
            SDL_FreeSurface(b.image);
            IMG_Quit();
            SDL_Quit();
            return EXIT_SUCCESS;
        }
    }
}