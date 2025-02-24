#include "menu.h"
#include "stdbool.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "save.h"
#include "score.h"
#include "options.h"
void buttonMoition(SDL_Rect position, SDL_Surface *screen, SDL_Surface *flip)
{
    SDL_BlitSurface(flip, NULL, screen, &position);
    SDL_Flip(screen);
}
void Menu(SDL_Surface *screen)
{
    SDL_Surface *background = NULL, *logo = NULL, *play = NULL, *options = NULL, *scores = NULL, *quit = NULL, *flip = NULL;
    SDL_Event event;
    Mix_Chunk *son;
    Mix_Music *music;
    SDL_Rect positionBackground, positionLogo, positionPlay, positionOptions, positionScores, positionQuit;
    bool run = true;
    int hover = 0;
    int cursPosition = -1, mouseCurs = -1, volume = 128;
    Uint32 start;
    const int FPS = 20;
    music = Mix_LoadMUS("../assets/audio/menu.mp3");
    son = Mix_LoadWAV("../assets/audio/click.wav");
    Mix_PlayMusic(music, -1);
    background = IMG_Load("../assets/backgrounds/background_f.png");
    logo = IMG_Load("../assets/buttons/logo.png");
    play = IMG_Load("../assets/buttons/play.png");
    options = IMG_Load("../assets/buttons/options.png");
    scores = IMG_Load("../assets/buttons/scores.png");
    quit = IMG_Load("../assets/buttons/exit.png");
    flip = IMG_Load("../assets/buttons/flip.png");

    SDL_EnableKeyRepeat(10, 10);

    positionBackground.x = 0;
    positionBackground.y = 0;

    positionLogo.x = 1100;
    positionLogo.y = 40;

    positionPlay.x = 80;
    positionPlay.y = 220;

    positionScores.x = 80;
    positionScores.y = 300;
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        run = false;
    }
    positionOptions.x = 80;
    positionOptions.y = 380;

    positionQuit.x = 80;
    positionQuit.y = 460;
    SDL_WM_SetCaption("Menu", NULL);
    while (run)
    {
        start = SDL_GetTicks();
        hover = 0;
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        SDL_BlitSurface(logo, NULL, screen, &positionLogo);
        SDL_BlitSurface(play, NULL, screen, &positionPlay);
        SDL_BlitSurface(scores, NULL, screen, &positionScores);
        SDL_BlitSurface(options, NULL, screen, &positionOptions);
        SDL_BlitSurface(quit, NULL, screen, &positionQuit);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
            {

                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    run = false;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 0 || mouseCurs == 0))
                {
                    buttonMoition(positionPlay, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 1 || mouseCurs == 1))
                {
                    buttonMoition(positionScores, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 2 || mouseCurs == 2))
                {
                    buttonMoition(positionOptions, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 3 || mouseCurs == 3))
                {
                    buttonMoition(positionQuit, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                    run = false;
                }
                if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) && !hover)
                {
                    mouseCurs = -1;
                    if (event.key.keysym.sym == SDLK_DOWN || (event.key.keysym.sym == SDLK_UP && cursPosition == -1))
                    {
                        cursPosition++;
                        if (cursPosition == 4)
                        {
                            cursPosition = 0;
                        }
                    }
                    else
                    {
                        cursPosition--;
                        if (cursPosition == -1)
                        {
                            cursPosition = 3;
                        }
                    }

                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_j)
                {
                    chargement(screen);
                }
                if (event.key.keysym.sym == SDLK_o)
                {
                    menu_options(screen);
                }
                if (event.key.keysym.sym == SDLK_m)
                {
                    score2(screen);
                }
            }
            break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 220 && event.button.y <= 275)
                    {
                        buttonMoition(positionPlay, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        chargement(screen);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 300 && event.button.y <= 355)
                    {
                        buttonMoition(positionScores, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        score2(screen);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 380 && event.button.y <= 435)
                    {
                        buttonMoition(positionOptions, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        menu_options(screen);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 460 && event.button.y <= 515)
                    {
                        buttonMoition(positionQuit, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        run = false; 
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 220 && event.motion.y <= 275)
                {
                    hover = 1;
                    mouseCurs = 0;
                    buttonMoition(positionPlay, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 300 && event.motion.y <= 355)
                {
                    hover = 1;
                    mouseCurs = 1;
                    buttonMoition(positionScores, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 380 && event.motion.y <= 435)
                {
                    hover = 1;
                    mouseCurs = 2;
                    buttonMoition(positionOptions, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 460 && event.motion.y <= 515)
                {
                    hover = 1;
                    mouseCurs = 3;
                    buttonMoition(positionQuit, screen, flip);
                }
                else
                {
                    mouseCurs = -1;
                }
                break;
            }
        }
        switch (mouseCurs)
        {
        case 0:
            buttonMoition(positionPlay, screen, flip);
            break;
        case 1:
            buttonMoition(positionScores, screen, flip);
            break;
        case 2:
            buttonMoition(positionOptions, screen, flip);
            break;
        case 3:
            buttonMoition(positionQuit, screen, flip);
            break;
        }
        if (hover)
        {
            cursPosition = mouseCurs;
        }
        else if (!hover && mouseCurs == -1)
        {
            switch (cursPosition)
            {
            case 0:
                buttonMoition(positionPlay, screen, flip);
                break;
            case 1:
                buttonMoition(positionScores, screen, flip);
                break;
            case 2:
                buttonMoition(positionOptions, screen, flip);
                break;
            case 3:
                buttonMoition(positionQuit, screen, flip);
                break;
            }
        }
        SDL_Flip(screen); 
        Mix_VolumeMusic(volume);
        Mix_VolumeChunk(son, volume);

        if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
    }

    Mix_FreeChunk(son);
    Mix_FreeMusic(music);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    SDL_FreeSurface(play);
    SDL_FreeSurface(options);
    SDL_FreeSurface(scores);
    SDL_FreeSurface(quit);
    SDL_FreeSurface(flip);
    SDL_Quit();
}