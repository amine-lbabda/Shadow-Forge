#include "menu.h"
#include "save.h"
#include "score.h"
#include "options.h"
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
    TTF_Font *font = NULL, *font_menu = NULL;
    int run = 1;
    int hover = 0;
    int cursPosition = -1, mouseCurs = -1;
    music = Mix_LoadMUS("../assets/audio/river.mp3");
    son = Mix_LoadWAV("../assets/audio/click.wav");
    background = IMG_Load("../assets/backgrounds/background_f.png");
    logo = IMG_Load("../assets/buttons/logo.png");
    play = IMG_Load("../assets/buttons/play.png");
    options = IMG_Load("../assets/buttons/options.png");
    scores = IMG_Load("../assets/buttons/scores.png");
    quit = IMG_Load("../assets/buttons/exit.png");
    flip = IMG_Load("../assets/buttons/flip.png");
    font = TTF_OpenFont("../assets/fonts/HARRYP.TTF", 40);
    font_menu = TTF_OpenFont("../assets/fonts/HARRYP.TTF", 60);
    if ((font == NULL) || (font_menu == NULL))
    {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    }
    coleur_text.r = 255;
    coleur_text.g = 255;
    coleur_text.b = 255;
    text_group = TTF_RenderText_Blended(font, "MADE BY:DIVINE VENDETTA", coleur_text);
    menu_text = TTF_RenderText_Blended(font_menu, "MENU", coleur_text);

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

    positionLogo.x = 1100;
    positionLogo.y = 40;
    positionTeamText.x = 120;
    positionTeamText.y = 100;
    positionPlay.x = 80;
    positionPlay.y = 220;

    positionScores.x = 80;
    positionScores.y = 300;
    positionOptions.x = 80;
    positionOptions.y = 380;

    positionQuit.x = 80;
    positionQuit.y = 460;
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
            music = Mix_LoadMUS("../assets/audio/river.mp3");
            Mix_PlayMusic(music, -1);
        }
        else if (initialMenu == 2)
        {

            score2(screen, &run, &initialMenu);
            Mix_FreeMusic(music);
            music = Mix_LoadMUS("../assets/audio/river.mp3");
            Mix_PlayMusic(music, -1);
        }
        else
        {
            menu_options(screen, music, &initalVolume, &run, &initialMenu);
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
                    buttonMoition(positionPlay, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 1;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 1 || mouseCurs == 1) && run)
                {
                    buttonMoition(positionScores, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 2;
                }
                if (event.key.keysym.sym == SDLK_RETURN && (cursPosition == 2 || mouseCurs == 2) && run)
                {
                    buttonMoition(positionOptions, screen, flip);
                    Mix_PlayChannel(-1, son, 0);
                    initialMenu = 3;
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
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 220 && event.button.y <= 275 && run)
                    {
                        buttonMoition(positionPlay, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 1;
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 300 && event.button.y <= 355 && run)
                    {
                        buttonMoition(positionScores, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 2;
                    }
                    if (event.button.x >= 80 && event.button.x <= 355 && event.button.y >= 380 && event.button.y <= 435 && run)
                    {
                        buttonMoition(positionOptions, screen, flip);
                        Mix_PlayChannel(-1, son, 0);
                        initialMenu = 3;
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
    SDL_FreeSurface(logo);
    SDL_FreeSurface(text_group);
    SDL_FreeSurface(menu_text);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}