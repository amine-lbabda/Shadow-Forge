#include "background.h"
#include "joueur.h"
void init_background(background *b, SDL_Surface *e, char nom_fichier[])
{
    b->image = IMG_Load(nom_fichier);
    if (b->image == NULL)
    {
        printf("Erreur:%s", IMG_GetError());
    }
    else
    {
        poscam(b, 0, 0, LARGEURFENETRE / ECRAN, HAUTEURFENETRE / ECRAN);
        posbackground(b, 0, 0, e->w, e->h);
    }
}

void posbackground(background *b, int x, int y, int w, int h)
{
    b->posimage.x = x;
    b->posimage.y = y;
    b->posimage.w = w;
    b->posimage.h = h;
}

void poscam(background *b, int x, int y, int w, int h)
{
    b->poscamera.x = x;
    b->poscamera.y = y;
    b->poscamera.w = w;
    b->poscamera.h = h;
}
void animate_leaves(SDL_Surface *leaves, SDL_Rect leaves_pos, int world_x, int *bounce_y, int *direction,
                    int bounce_min, int bounce_max, int bounce_speed, int camX, SDL_Surface *screen)
{
    *bounce_y += (*direction) * bounce_speed;
    if (*bounce_y > bounce_max)
    {
        *bounce_y = bounce_max;
        *direction = -1;
    }
    else if (*bounce_y < bounce_min)
    {
        *bounce_y = bounce_min;
        *direction = 1;
    }
    SDL_Rect leaves_screen_pos = leaves_pos;
    leaves_screen_pos.x = world_x - camX;
    leaves_screen_pos.y = leaves_pos.y - (*bounce_y);
    SDL_BlitSurface(leaves, NULL, screen, &leaves_screen_pos);
}