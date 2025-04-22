#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme_1.h"
void enigme_1(SDL_Surface *ecran,int *quitter)
{
    int test = 0;
    SDL_Event event;
    int indice = 0;
    menu m;
    init_menu(&m);
    quiz q;
    q.score = 0;
    int n = 0, t[100];
    SDL_Color color = {255, 255, 246};
    TTF_Font *police = TTF_OpenFont("HARRYP__.TTF", 140);
    int a, play_mus, animation = 0;
    while (*quitter)
    {
        SDL_Flip(ecran);
        switch (indice)
        {
        case 0:
            // menu principale
            afficher_menu(m, ecran);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    *quitter = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        *quitter = 0;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        if (m.poscursor == 1)
                        {
                            indice = 1;
                            Mix_PlayChannel(-1, m.click, 0);
                        }
                        else
                        {
                            if (cursor(q.posr))
                            {
                                Mix_PlayChannel(-1, m.click, 0);
                                indice = 0;
                            }
                            else
                            {
                                if (cursor(m.pospuzzle))
                                {
                                    Mix_PlayChannel(-1, m.click, 0);
                                }
                            }
                        }
                        break;
                    }
                    break;
                }
            }
            update(&m);
            break;
        case 1:
            test = 0;
            init_quiz(&q, t, &n);
            a = Mix_PlayChannel(-1, q.clock, 0);
            play_mus = 0;
            unsigned int d = SDL_GetTicks();
            int quitter2 = 0, test_score = 0;
            while (!quitter2)
            {
                unsigned int startTime = SDL_GetTicks() - d;
                SDL_Flip(ecran);
                afficher_quiz(q, ecran, startTime / 1000, &animation);
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        *quitter = quitter2 = 1;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            *quitter = quitter2 = 1;
                            break;
                        case SDLK_a:
                            if (memcmp(&q.true_rep, &q.poscadre2[0], sizeof(SDL_Rect)) == 0)
                            {
                                test = 1;
                            }
                            else
                            {
                                test = 2;
                            }
                            break;
                        case SDLK_b:
                            if (memcmp(&q.true_rep, &q.poscadre2[1], sizeof(SDL_Rect)) == 0)
                                test = 1;
                            else
                                test = 2;
                            break;
                        case SDLK_c:
                            if (memcmp(&q.true_rep, &q.poscadre2[2], sizeof(SDL_Rect)) == 0)
                                test = 1;
                            else
                                test = 2;
                            break;
                        case SDLK_d:
                            if (memcmp(&q.true_rep, &q.poscadre2[3], sizeof(SDL_Rect)) == 0)
                                test = 1;
                            else
                                test = 2;
                            break;
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        switch (event.button.button)
                        {
                        case SDL_BUTTON_LEFT:
                            Mix_PlayChannel(-1, q.click, 0);
                            if (cursor(q.posr) && (test > 0))
                            {
                                Mix_PlayChannel(-1, m.click, 0);
                                ;
                                indice = 0;
                                quitter2 = 1;
                            }
                            if (test == 0 && (cursor(q.poscadre2[0]) || cursor(q.poscadre2[1]) ||
                                              cursor(q.poscadre2[2]) || cursor(q.poscadre2[3])))
                            {
                                if (cursor(q.true_rep))
                                {
                                    test = 1;
                                }
                                else
                                {
                                    test = 2;
                                }
                            }
                            break;
                        }
                        break;
                    }
                }
                if (startTime / 1000 == 9 && test == 0)
                {
                    test = 3;
                }
                if (test == 1)
                {
                    if (!test_score)
                    {
                        q.score++;
                        test_score++;
                    }
                    if (play_mus == 0)
                    {
                        Mix_PlayMusic(q.win, 0);
                        play_mus++;
                    }
                    Mix_HaltChannel(a);
                    SDL_BlitSurface(q.box[1], NULL, ecran, NULL);
                    !cursor(q.posr) ? SDL_BlitSurface(q.Return[0], NULL, ecran, &q.posr) : SDL_BlitSurface(q.Return[1], NULL, ecran, &q.posr);
                    SDL_BlitSurface(q.label_score, NULL, ecran, &q.pos_labelscore);
                    SDL_Surface *score = TTF_RenderText_Solid(TTF_OpenFont("HARRYP__.TTF", 120), convch(q.score), color);
                    SDL_BlitSurface(score, NULL, ecran, &q.posscore);
                }
                else
                {
                    if (test == 2 || test == 3)
                    {
                        Mix_HaltChannel(a);
                        if (!test_score && q.score != 0)
                        {
                            q.score--;
                            test_score++;
                        }
                        if (play_mus == 0)
                        {
                            Mix_PlayMusic(q.lose, 0);
                            play_mus++;
                        }
                        if (test == 2)
                            SDL_BlitSurface(q.box[2], NULL, ecran, NULL);
                        else
                            SDL_BlitSurface(q.box[0], NULL, ecran, NULL);
                        !cursor(q.posr) ? SDL_BlitSurface(q.Return[0], NULL, ecran, &q.posr) : SDL_BlitSurface(q.Return[1], NULL, ecran, &q.posr);
                        SDL_BlitSurface(q.label_score, NULL, ecran, &q.pos_labelscore);
                        puts(convch(q.score));
                        SDL_Surface *score = TTF_RenderText_Solid(TTF_OpenFont("HARRYP__.TTF", 120), convch(q.score), color);
                        SDL_BlitSurface(score, NULL, ecran, &q.posscore);
                    }
                }
            }
        }
    }
    cleanup(&m, &q);
}