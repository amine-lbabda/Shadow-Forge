#include "menu_mode.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
SDL_Surface *initialiser(int w, int h)
{
    SDL_Surface *ecran;
    int ready;
    ready = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == TTF_Init() == Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == IMG_Init(IMG_INIT_PNG);

    if (ready < 0)
    {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
    }

    else
        printf("Bonjour le monde, SDL est initialisé avec succès.\n");
    ecran = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    if (ecran == NULL)
    {
        fprintf(stderr, "Echec de creation de la fenetre de %d*%d: %s.\n", w, h, SDL_GetError());
    }

    return ecran;
}
SDL_Surface *load_image(char *name)
{

    return IMG_Load(name);
}

void afficher(SDL_Surface *image, SDL_Rect *posimage, SDL_Surface *ecran, SDL_Rect *pos)
{
    SDL_BlitSurface(image, posimage, ecran, pos);
}

void aficher_text(SDL_Surface *text, SDL_Rect *postext, SDL_Surface *ecran)
{
    SDL_BlitSurface(text, NULL, ecran, postext);
}

SDL_Surface *affichage_text(TTF_Font *font, char *text, SDL_Color color)
{

    return TTF_RenderText_Blended(font, text, color);
}

int verif_collision(SDL_Event e, image button)
{
    return e.motion.x >= button.posimage.x && e.motion.x <= button.posimage.x + button.posimage.w && e.motion.y >= button.posimage.y && e.motion.y <= button.posimage.y + button.posimage.h;
}

void position_image(int x, int y, int w, int h, SDL_Rect *pos_image)
{
    pos_image->x = x;
    pos_image->y = y;
    pos_image->w = w;
    pos_image->h = h;
}

TTF_Font *load_font(char *name, int size)
{
    return TTF_OpenFont(name, size);
}

void couleur_text(SDL_Color *color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

void liberer(SDL_Surface *ecran, SDL_Surface *background, SDL_Surface *button_mono, SDL_Surface *button_multi, SDL_Surface *button_name_1, SDL_Surface *button_name_2, TTF_Font *font)
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(button_mono);
    SDL_FreeSurface(button_multi);
    SDL_FreeSurface(button_name_1);
    SDL_FreeSurface(button_name_2);
    Mix_CloseAudio();
    SDL_Quit();
    TTF_CloseFont(font);
}
