#include "options.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
void menu_options(SDL_Surface *window, Mix_Music *music_chunk, int *currentVolume, int *run, int *initial_menu)
{
    image background;
    image btn1;
    image btn2;
    image volp;
    image volm;
    image fs;
    image returntxt;
    image win;
    image volcon;
    image wincon;
    image options;
    image music;
    image logo;

    image btn1f;
    image btn2f;
    image volpf;
    image volmf;
    image fsf;
    image returntxtf;
    image winf;
    image volconf;
    image winconf;
    image optionsf;
    image musicf;
    image logof;
    int quit = 0;
    SDL_Event e;
    int fullscreen = 0;

    background.image = IMG_Load("../assets/backgrounds/bgf.png");
    btn1.image = IMG_Load("../assets/buttons/buttonvs.png");
    btn2.image = IMG_Load("../assets/buttons/buttonvs.png");
    volp.image = IMG_Load("../assets/buttons/volp.png");
    volm.image = IMG_Load("../assets/buttons/volm.png");
    fs.image = IMG_Load("../assets/buttons/Fullscreen.png");
    win.image = IMG_Load("../assets/buttons/Windowed.png");
    volcon.image = IMG_Load("../assets/buttons/VolumeConfig.png");
    wincon.image = IMG_Load("../assets/buttons/WindowConfig.png");
    options.image = IMG_Load("../assets/buttons/Option.png");
    returntxt.image = IMG_Load("../assets/buttons/Return_1.png");
    music.image = IMG_Load("../assets/buttons/Music.png");
    logo.image = IMG_Load("../assets/buttons/logo1.png");

    btn1f.image = IMG_Load("../assets/buttons/button1.png");
    btn2f.image = IMG_Load("../assets/buttons/button1.png");
    volpf.image = IMG_Load("../assets/buttons/volp1.png");
    volmf.image = IMG_Load("../assets/buttons/volm1.png");
    fsf.image = IMG_Load("../assets/buttons/Fullscreen1.png");
    winf.image = IMG_Load("../assets/buttons/Windowed1.png");
    volconf.image = IMG_Load("../assets/buttons/VolumeConfig1.png");
    winconf.image = IMG_Load("../assets/buttons/WindowConfig1.png");
    optionsf.image = IMG_Load("../assets/buttons/Options1.png");
    returntxtf.image = IMG_Load("../assets/buttons/Return1.png");
    musicf.image = IMG_Load("../assets/buttons/Music1.png");
    logof.image = IMG_Load("../assets/buttons/log.png");

    if ((background.image == NULL) || (btn1.image == NULL) || (volp.image == NULL) || (volm.image == NULL) || (btn2.image == NULL) || (fs.image == NULL) || (win.image == NULL) || (volcon.image == NULL) || (wincon.image == NULL) || (options.image == NULL) || (returntxt.image == NULL) || (music.image == NULL) || (btn1f.image == NULL) || (volpf.image == NULL) || (volmf.image == NULL) || (btn2f.image == NULL) || (fsf.image == NULL) || (winf.image == NULL) || (volconf.image == NULL) || (winconf.image == NULL) || (optionsf.image == NULL) || (returntxtf.image == NULL) || (musicf.image == NULL) || (logo.image == NULL) || (logof.image == NULL))

    {
        printf("Error loading images: %s\n", SDL_GetError());
        SDL_Quit();
    }

    background.rect.x = 0;
    background.rect.y = 0;
    background.rect.w = background.image->w;
    background.rect.h = background.image->h;

    btn1.rect.x = 485;
    btn1.rect.y = 500;
    btn1.rect.w = btn1.image->w;
    btn1.rect.h = btn1.image->h;

    btn2.rect.x = 785;
    btn2.rect.y = 500;
    btn2.rect.w = btn2.image->w;
    btn2.rect.h = btn2.image->h;

    volp.rect.x = 620;
    volp.rect.y = 360;
    volp.rect.w = volp.image->w;
    volp.rect.h = volp.image->h;

    volm.rect.x = 720;
    volm.rect.y = 360;
    volm.rect.w = volm.image->w;
    volm.rect.h = volm.image->h;

    fs.rect.x = 850;
    fs.rect.y = 504;
    fs.rect.w = fs.image->w;
    fs.rect.h = fs.image->h;

    win.rect.x = 550;
    win.rect.y = 502;
    win.rect.w = win.image->w;
    win.rect.h = win.image->h;

    options.rect.x = 300;
    options.rect.y = 80;
    options.rect.w = options.image->w;
    options.rect.h = options.image->h;

    volcon.rect.x = 150;
    volcon.rect.y = 365;
    volcon.rect.w = volcon.image->w;
    volcon.rect.h = volcon.image->h;

    wincon.rect.x = 160;
    wincon.rect.y = 480;
    wincon.rect.w = wincon.image->w;
    wincon.rect.h = wincon.image->h;

    music.rect.x = 478;
    music.rect.y = 365;
    music.rect.w = music.image->w;
    music.rect.h = music.image->h;

    returntxt.rect.x = 48;
    returntxt.rect.y = 942;
    returntxt.rect.w = returntxt.image->w;
    returntxt.rect.h = returntxt.image->h;

    logo.rect.x = 900;
    logo.rect.y = 50;
    logo.rect.w = logo.image->w;
    logo.rect.h = logo.image->h;

    // full screen rect

    background.rect.x = 0;
    background.rect.y = 0;
    background.rect.w = background.image->w;
    background.rect.h = background.image->h;

    btn1f.rect.x = 727;
    btn1f.rect.y = 675;
    btn1f.rect.w = btn1f.image->w;
    btn1f.rect.h = btn1f.image->h;

    btn2f.rect.x = 1177;
    btn2f.rect.y = 675;
    btn2f.rect.w = btn2f.image->w;
    btn2f.rect.h = btn2f.image->h;

    volpf.rect.x = 930;
    volpf.rect.y = 486;
    volpf.rect.w = volpf.image->w;
    volpf.rect.h = volpf.image->h;

    volmf.rect.x = 1080;
    volmf.rect.y = 486;
    volmf.rect.w = volmf.image->w;
    volmf.rect.h = volmf.image->h;

    fsf.rect.x = 1275;
    fsf.rect.y = 680;
    fsf.rect.w = fsf.image->w;
    fsf.rect.h = fsf.image->h;

    winf.rect.x = 825;
    winf.rect.y = 677;
    winf.rect.w = winf.image->w;
    winf.rect.h = winf.image->h;

    optionsf.rect.x = 450;
    optionsf.rect.y = 108;
    optionsf.rect.w = optionsf.image->w;
    optionsf.rect.h = optionsf.image->h;

    volconf.rect.x = 225;
    volconf.rect.y = 492;
    volconf.rect.w = volconf.image->w;
    volconf.rect.h = volconf.image->h;

    winconf.rect.x = 240;
    winconf.rect.y = 648;
    winconf.rect.w = winconf.image->w;
    winconf.rect.h = winconf.image->h;

    musicf.rect.x = 717;
    musicf.rect.y = 492;
    musicf.rect.w = musicf.image->w;
    musicf.rect.h = musicf.image->h;

    returntxtf.rect.x = 50;
    returntxtf.rect.y = 930;
    returntxtf.rect.w = returntxtf.image->w;
    returntxtf.rect.h = returntxtf.image->h;

    logof.rect.x = 1300;
    logof.rect.y = 75;
    logof.rect.w = logof.image->w;
    logof.rect.h = logof.image->h;

    if (!music_chunk)
    {
        printf("Failed to load background music: %s\n", Mix_GetError());
        SDL_Quit();
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e) && !quit)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = 1;
                *run = 0;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:

                if (verif_collision_2(e, volp))
                {
                    *currentVolume += MIX_MAX_VOLUME * 0.1;
                    if (*currentVolume > MIX_MAX_VOLUME)
                        *currentVolume = MIX_MAX_VOLUME;
                    Mix_VolumeMusic(*currentVolume);
                    printf("Volume Increased: %d\n", ((*currentVolume) * 100) / MIX_MAX_VOLUME);
                }

                if (verif_collision_2(e, volm))
                {
                    *currentVolume -= MIX_MAX_VOLUME * 0.1;
                    if (*currentVolume < 0)
                        *currentVolume = 0;
                    Mix_VolumeMusic(*currentVolume);
                    printf("Volume Decreased: %d\n", ((*currentVolume) * 100) / MIX_MAX_VOLUME);
                    break;
                }
                if (verif_collision_2(e, volpf))
                {
                    *currentVolume += MIX_MAX_VOLUME * 0.1;
                    if (*currentVolume > MIX_MAX_VOLUME)
                        *currentVolume = MIX_MAX_VOLUME;
                    Mix_VolumeMusic(*currentVolume);
                    printf("Volume Increased: %d\n", ((*currentVolume) * 100) / MIX_MAX_VOLUME);
                    break;
                }

                if (verif_collision_2(e, volmf))
                {
                    *currentVolume -= MIX_MAX_VOLUME * 0.1;
                    if (*currentVolume < 0)
                        *currentVolume = 0;
                    Mix_VolumeMusic(*currentVolume);
                    printf("Volume Decreased: %d\n", ((*currentVolume) * 100) / MIX_MAX_VOLUME);
                    break;
                }
                if (verif_collision_2(e, btn2))
                {
                    fullscreen = 1;

                    if (fullscreen == 1)
                    {
                        SDL_FreeSurface(background.image);
                        background.image = IMG_Load("../assets/backgrounds/bgf.png");
                        SDL_FreeSurface(window);
                        SDL_WM_ToggleFullScreen(window);
                    }
                }
                if (verif_collision_2(e, btn1f))
                {
                    fullscreen = 0;
                    SDL_FreeSurface(window);
                    window = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
                    SDL_FreeSurface(background.image);
                    background.image = IMG_Load("../assets/backgrounds/bgf.png");
                }
                if (verif_collision_2(e, returntxt))
                {
                    quit = 1;
                }
            }
            if (fullscreen == 0)
            {
                SDL_BlitSurface(background.image, NULL, window, &background.rect);
                SDL_BlitSurface(btn1.image, NULL, window, &btn1.rect);
                SDL_BlitSurface(btn2.image, NULL, window, &btn2.rect);
                SDL_BlitSurface(volp.image, NULL, window, &volp.rect);
                SDL_BlitSurface(volm.image, NULL, window, &volm.rect);
                SDL_BlitSurface(fs.image, NULL, window, &fs.rect);
                SDL_BlitSurface(win.image, NULL, window, &win.rect);
                SDL_BlitSurface(volcon.image, NULL, window, &volcon.rect);
                SDL_BlitSurface(wincon.image, NULL, window, &wincon.rect);
                SDL_BlitSurface(music.image, NULL, window, &music.rect);
                SDL_BlitSurface(options.image, NULL, window, &options.rect);
                SDL_BlitSurface(returntxt.image, NULL, window, &returntxt.rect);
                SDL_BlitSurface(logo.image, NULL, window, &logo.rect);
            }
            else if (fullscreen == 1)
            {
                SDL_BlitSurface(background.image, NULL, window, &background.rect);
                SDL_BlitSurface(btn1f.image, NULL, window, &btn1f.rect);
                SDL_BlitSurface(btn2f.image, NULL, window, &btn2f.rect);
                SDL_BlitSurface(volpf.image, NULL, window, &volpf.rect);
                SDL_BlitSurface(volmf.image, NULL, window, &volmf.rect);
                SDL_BlitSurface(fsf.image, NULL, window, &fsf.rect);
                SDL_BlitSurface(winf.image, NULL, window, &winf.rect);
                SDL_BlitSurface(volconf.image, NULL, window, &volconf.rect);
                SDL_BlitSurface(winconf.image, NULL, window, &winconf.rect);
                SDL_BlitSurface(musicf.image, NULL, window, &musicf.rect);
                SDL_BlitSurface(optionsf.image, NULL, window, &optionsf.rect);
                SDL_BlitSurface(logof.image, NULL, window, &logof.rect);
                SDL_BlitSurface(returntxt.image, NULL, window, &returntxt.rect);
            }
            SDL_Flip(window);
        }
    }

    SDL_FreeSurface(background.image);
    SDL_FreeSurface(btn1.image);
    SDL_FreeSurface(btn2.image);
    SDL_FreeSurface(volp.image);
    SDL_FreeSurface(fs.image);
    SDL_FreeSurface(win.image);
    SDL_FreeSurface(volcon.image);
    SDL_FreeSurface(wincon.image);
    SDL_FreeSurface(music.image);
    SDL_FreeSurface(options.image);
    SDL_FreeSurface(returntxt.image);
    SDL_FreeSurface(logo.image);

    SDL_FreeSurface(btn1f.image);
    SDL_FreeSurface(btn2f.image);
    SDL_FreeSurface(volpf.image);
    SDL_FreeSurface(fsf.image);
    SDL_FreeSurface(winf.image);
    SDL_FreeSurface(volconf.image);
    SDL_FreeSurface(winconf.image);
    SDL_FreeSurface(musicf.image);
    SDL_FreeSurface(optionsf.image);
    SDL_FreeSurface(returntxtf.image);
    SDL_FreeSurface(logof.image);
    *initial_menu = 0;
}
