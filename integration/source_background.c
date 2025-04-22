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
void scrolling_deplacement(background *b, SDL_Surface *e, int dx, perso *p,
                           Uint32 dt, int toggle_background)
{
  int vitesse_effective;
  double dt_sec;
  double dy;

  // Convert milliseconds to seconds
  dt_sec = (double)dt / 1000.0;
  vitesse_effective = fabs(p->vitesse);
  if (toggle_background == 0)
  {
    switch (b->direction)
    {
    case 0:
    { // Scrolling left
      dx = vitesse_effective * dt_sec * 100;
      if (b->poscamera.x > 0)
      {
        b->poscamera.x -= dx;
        // Prevent scrolling past left boundary
        if (b->poscamera.x < 0)
        {
          b->poscamera.x = 0;
        }
      }
    }
    break;

    case 1:
    {
      if (p->pos_actuelle_x > e->w / 2)
      {
        dx = vitesse_effective * dt_sec * 100;

        // Allow scrolling to the full width of the background image
        if (b->poscamera.x < b->image->w - b->poscamera.w)
        {
          b->poscamera.x += dx;
        }

      } 
    }
    break;
    case 2:
    { // Scrolling up
      dy = vitesse_effective * dt_sec * 100;

      if (b->poscamera.y > 0)
      {
        b->poscamera.y += p->vitesse_y;
      }
    }
    break;
    }
  }
  else
  {
  }
}