#include "sharedscreen.h"

void init_background(background *b, SDL_Surface *e)
{
    b->image = IMG_Load("./background_f.png");
    if (b->image == NULL)
    {
        printf("Erreur:%s", IMG_GetError());
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

void scrolling(background *b, SDL_Surface *e)
{
    switch (b->direction)
    {
    case 0:
    {
        if (b->poscamera.x < e->w)
        {
            b->poscamera.x += dx;
        }
        if (b->poscamera.x == e->w)
        {
            b->poscamera.x = 0;
        }
    }

    break;

    case 1:
    {
        b->poscamera.x -= dx;

        if (b->poscamera.x < 0)
        {
            b->poscamera.x = 0;
        }
    }
    break;
    case 2:
    {
        if (b->poscamera.y < e->h)
        {
            b->poscamera.y += dy;
        }
    }

    break;
    case 3:
    {
        b->poscamera.y -= dy;
        if (b->poscamera.y < 0)
        {
            b->poscamera.y = 0;
        }
    }

    break;
    }
}
