#include "menu.h"
#include "save.h"
#include "score.h"
#include "options.h"
#include "history.h"
void Menu(SDL_Surface *screen)
{
    int initialMenu = 0;
    int initalVolume = MIX_MAX_VOLUME;
    SDL_Surface *background = NULL, *logo = NULL, *play = NULL, *options = NULL, *scores = NULL, *quit = NULL, *flip = NULL, *text_group = NULL, *menu_text = NULL;
    SDL_Event event;
    Mix_Chunk *son;
    Mix_Music *music;
    SDL_Rect positionBackground, positionLogo, positionPlay, positionOptions, positionScores, positionQuit, positionGroupText, positionTeamText;
    SDL_Color coleur_text;
    SDL_Rect positionFlip;
    TTF_Font *font = NULL, *font_menu = NULL;
    int run = 1;
    int hover = 0;
    int cursPosition = -1, mouseCurs = -1;
    music = Mix_LoadMUS("./assets/audio/river.mp3");
    son = Mix_LoadWAV("./assets/audio/click.wav");
    background = IMG_Load("./assets/backgrounds/background_f.png");
    logo = IMG_Load("./assets/buttons/logo.png");
    play = IMG_Load("./assets/buttons/PLAYN.png");
    options = IMG_Load("./assets/buttons/OPTIONSN.png");
    scores = IMG_Load("./assets/buttons/SCORESN.png");
    quit = IMG_Load("./assets/buttons/HISTOIRE.png");
    flip = IMG_Load("./assets/buttons/flip.png");
    font = TTF_OpenFont("./assets/fonts/HARRYP.TTF", 40);
    font_menu = TTF_OpenFont("./assets/fonts/HARRYP.TTF", 60);
    if ((font == NULL) || (font_menu == NULL))
    {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    }
    coleur_text.r = 255;
    coleur_text.g = 255;
    coleur_text.b = 255;
    text_group = TTF_RenderText_Blended(font, "MADE BY:DIVINE VENDETTA", coleur_text);
    menu_text = TTF_RenderText_Blended(font_menu, "MENU", coleur_text);
    SDL_Surface *menu_hist = TTF_RenderText_Blended(font, "RETURN", coleur_text);
    positionGroupText.x = 1400;
    positionGroupText.y = 1020;
    positionGroupText.w = text_group->w;
    positionGroupText.h = text_group->h;
    positionTeamText.x = 900;
    positionTeamText.y = 500;
    positionTeamText.w = text_group->w;
    positionTeamText.h = text_group->h;

    positionBackground.x = 0;
    positionBackground.y = 0;

    positionLogo.x = 720;
    positionLogo.y = 100;
    positionTeamText.x = 120;
    positionTeamText.y = 100;
    positionPlay.x = 583;
    positionPlay.y = 250;

    positionScores.x = 583;
    positionScores.y = 570;
    positionOptions.x = 583;
    positionOptions.y = 410;

    positionQuit.x = 583;
    positionQuit.y = 730;
    Mix_PlayMusic(music, -1);
    SDL_WM_SetCaption("Menu", NULL);
    while (run)
    {
        if (initialMenu == 0)
        {
            SDL_BlitSurface(background, NULL, screen, &positionBackground);
            SDL_BlitSurface(logo, NULL, screen, &positionLogo);
            SDL_BlitSurface(play, NULL, screen, &positionPlay);
            SDL_BlitSurface(scores, NULL, screen, &positionScores);
            SDL_BlitSurface(options, NULL, screen, &positionOptions);
            SDL_BlitSurface(quit, NULL, screen, &positionQuit);
            SDL_BlitSurface(text_group, NULL, screen, &positionGroupText);
            SDL_BlitSurface(menu_text, NULL, screen, &positionTeamText);
        }
        else if (initialMenu == 1)
        {
            chargement(screen, &run, &initialMenu);
            Mix_FreeMusic(music);
            music = Mix_LoadMUS("./assets/audio/river.mp3");
            Mix_PlayMusic(music, -1);
        }
        else if (initialMenu == 2)
        {
            menu_options(screen, music, &initalVolume, &run, &initialMenu);
        }
        else if (initialMenu == 3)
        {

            score2(screen, &run, &initialMenu);
            Mix_FreeMusic(music);
            music = Mix_LoadMUS("./assets/audio/river.mp3");
            Mix_PlayMusic(music, -1);
        }
        else if (initialMenu == 4)
        {
            history_menu(screen, &run, font, coleur_text);
        }
        hover = 0;

        while (SDL_PollEvent(&event) && run)
        {

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
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 1;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 1 || mouseCurs == 1) && run)
                {
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 2;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 2 || mouseCurs == 2) && run)
                {
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 3;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 3 || mouseCurs == 3) && run)
                {
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 4;
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

                    initialMenu = 1;
                }
                if (event.key.keysym.sym == SDLK_o && run)
                {

                    initialMenu = 2;
                }
                if (event.key.keysym.sym == SDLK_m && run)
                {

                    initialMenu = 3;
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x >= positionPlay.x && event.button.x <= positionPlay.x + play->w && event.button.y >= positionPlay.y && event.button.y <= positionPlay.y + play->h && run)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 1;
                    }
                    if (event.button.x >= positionScores.x && event.button.x <= positionScores.x + scores->w && event.button.y >= positionScores.y && event.button.y <= positionScores.y + scores->h && run)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 2;
                    }
                    if (event.button.x >= positionOptions.x && event.button.x <= positionOptions.x + options->w && event.button.y >= positionOptions.y && event.button.y <= positionOptions.y + options->h && run)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 3;
                    }
                    if (event.button.x >= positionQuit.x && event.button.x <= positionQuit.x + quit->w && event.button.y >= positionQuit.y && event.button.y <= positionQuit.y + quit->h && run)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 4;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= positionPlay.x && event.motion.x <= positionPlay.x + play->w && event.motion.y >= positionPlay.y && event.motion.y <= positionPlay.y + play->h && run)
                {
                    hover = 1;
                    mouseCurs = 0;
                }
                else if (event.motion.x >= positionScores.x && event.motion.x <= positionScores.x + scores->w && event.motion.y >= positionScores.y && event.motion.y <= positionScores.y + scores->h && run)
                {
                    hover = 1;
                    mouseCurs = 1;
                }
                else if (event.motion.x >= positionOptions.x && event.motion.x <= positionOptions.x + options->w && event.motion.y >= positionOptions.y && event.motion.y <= positionOptions.y + options->h && run)
                {
                    hover = 1;
                    mouseCurs = 2;
                }
                else if (event.motion.x >= positionQuit.x && event.motion.x <= positionQuit.x + quit->w && event.motion.y >= positionQuit.y && event.motion.y <= positionQuit.y + quit->h && run)
                {
                    hover = 1;
                    mouseCurs = 3;
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
                positionFlip.x = positionPlay.x + 100;
                positionFlip.y = positionPlay.y + 95;
                buttonMoition(positionFlip, screen, flip);
                break;
            case 1:
                positionFlip.x = positionPlay.x + 100;
                positionFlip.y = positionOptions.y + 95;
                buttonMoition(positionFlip, screen, flip);
                break;
            case 2:
                positionFlip.x = positionPlay.x + 100;
                positionFlip.y = positionScores.y + 95;
                buttonMoition(positionFlip, screen, flip);
                break;
            case 3:
                positionFlip.x = positionPlay.x + 100;
                positionFlip.y = positionQuit.y + 95;
                buttonMoition(positionFlip, screen, flip);
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
                    positionFlip.x = positionPlay.x + 100;
                    positionFlip.y = positionPlay.y + 95;
                    buttonMoition(positionFlip, screen, flip);
                    break;
                case 1:
                    positionFlip.x = positionPlay.x + 100;
                    positionFlip.y = positionOptions.y + 95;
                    buttonMoition(positionFlip, screen, flip);
                    break;
                case 2:
                    positionFlip.x = positionPlay.x + 100;
                    positionFlip.y = positionScores.y + 95;
                    buttonMoition(positionFlip, screen, flip);
                    break;
                case 3:
                    positionFlip.x = positionPlay.x + 100;
                    positionFlip.y = positionQuit.y + 95;
                    buttonMoition(positionFlip, screen, flip);
                    break;
                }
            }
            SDL_Flip(screen);
            Mix_VolumeMusic(initalVolume);
            Mix_VolumeChunk(son, initalVolume);
        }
    }

    Mix_FreeChunk(son);
    son = NULL;
    Mix_FreeMusic(music);
    music = NULL;
    SDL_FreeSurface(screen);
    screen = NULL;
    SDL_FreeSurface(background);
    background = NULL;
    SDL_FreeSurface(play);
    play = NULL;
    SDL_FreeSurface(options);
    options = NULL;
    SDL_FreeSurface(scores);
    scores = NULL;
    SDL_FreeSurface(quit);
    quit = NULL;
    SDL_FreeSurface(flip);
    flip = NULL;
    SDL_FreeSurface(logo);
    logo = NULL;
    SDL_FreeSurface(text_group);
    text_group = NULL;
    SDL_FreeSurface(menu_text);
    menu_text = NULL;
    TTF_CloseFont(font);
    font = NULL;
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}