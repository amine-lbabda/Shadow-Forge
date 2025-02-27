#include "menu.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "save.h"
#include "score.h"
#include "options.h"
#define FPS 60
void Menu(SDL_Surface *screen)
{
    int initalVolume = MIX_MAX_VOLUME;
    SDL_Surface *background = NULL, *logo = NULL, *play = NULL, *options = NULL, *scores = NULL, *quit = NULL, *flip = NULL;
    SDL_Event event;
    Mix_Chunk *son;
    Mix_Music *music;
    SDL_Rect positionBackground, positionLogo, positionPlay, positionOptions, positionScores, positionQuit;
    int run = 1;
    int hover = 0;
    int cursPosition = -1, mouseCurs = -1;
    Uint32 start;
    music = Mix_LoadMUS("../assets/audio/river.mp3");
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
        run = 0;
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

        while (SDL_PollEvent(&event) && run)
        {
            SDL_BlitSurface(background, NULL, screen, &positionBackground);
            SDL_BlitSurface(logo, NULL, screen, &positionLogo);
            SDL_BlitSurface(play, NULL, screen, &positionPlay);
            SDL_BlitSurface(scores, NULL, screen, &positionScores);
            SDL_BlitSurface(options, NULL, screen, &positionOptions);
            SDL_BlitSurface(quit, NULL, screen, &positionQuit);
            switch (event.type)
            {
            case SDL_QUIT:
                run = 0;
                break;
            case SDL_KEYDOWN:
            {

                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    run = 0;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 0 || mouseCurs == 0) && run)
                {
                    buttonMoition(positionPlay, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 1 || mouseCurs == 1) && run)
                {
                    buttonMoition(positionScores, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 2 || mouseCurs == 2) && run)
                {
                    buttonMoition(positionOptions, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 3 || mouseCurs == 3) && run)
                {
                    buttonMoition(positionQuit, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                    run = 0;
                }
                if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) && !hover && run)
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
                if (event.key.keysym.sym == SDLK_j && run)
                {
                    chargement(screen, &run);
                }
                if (event.key.keysym.sym == SDLK_o && run)
                {
                    menu_options(screen, music, &initalVolume, &run);
                }
                if (event.key.keysym.sym == SDLK_m && run)
                {
                    score2(screen, &run);
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 220 && event.button.y <= 275 && run)
                    {
                        buttonMoition(positionPlay, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        chargement(screen, &run);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 300 && event.button.y <= 355 && run)
                    {
                        buttonMoition(positionScores, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        score2(screen, &run);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 380 && event.button.y <= 435 && run)
                    {
                        buttonMoition(positionOptions, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        menu_options(screen, music, &initalVolume, &run);
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 460 && event.button.y <= 515 && run)
                    {
                        buttonMoition(positionQuit, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        run = 0;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 220 && event.motion.y <= 275 && run)
                {
                    hover = 1;
                    mouseCurs = 0;
                    buttonMoition(positionPlay, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 300 && event.motion.y <= 355 && run)
                {
                    hover = 1;
                    mouseCurs = 1;
                    buttonMoition(positionScores, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 380 && event.motion.y <= 435 && run)
                {
                    hover = 1;
                    mouseCurs = 2;
                    buttonMoition(positionOptions, screen, flip);
                }
                else if (event.motion.x >= 80 && event.motion.x <= 355 && event.motion.y >= 460 && event.motion.y <= 515 && run)
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
        if (run)
        {
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
            Mix_VolumeMusic(initalVolume);
            Mix_VolumeChunk(son, initalVolume);
            if (1000 / FPS > SDL_GetTicks() - start)
            {
                SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
            }
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
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}