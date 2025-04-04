#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "quiz.h"
void init_menu(menu *m)
{
   m->bg_principale = IMG_Load("./assets/backgrounds/bground.png");
   SDL_Surface *logo = IMG_Load("./assets/backgrounds/bground.png");
   m->bquiz[0] = IMG_Load("./assets/buttons/bquiz1.png");
   m->bquiz[1] = IMG_Load("./assets/buttons/bquiz2.png");
   m->bpuzzle[0] = IMG_Load("./assets/buttons/bpuzzle1.png");
   m->bpuzzle[1] = IMG_Load("./assets/buttons/bpuzzle2.png");
   m->posquiz.x = 1920 / 2 - (m->bquiz[0]->w / 2);
   m->posquiz.y = 700;
   m->posquiz.w = m->bquiz[0]->w;
   m->posquiz.h = m->bquiz[0]->h;
   m->pospuzzle.h = m->bpuzzle[0]->h;
   m->pospuzzle.w = m->bpuzzle[0]->w;
   m->pospuzzle.x = 1920 / 2 - (m->bpuzzle[0]->w / 2);
   m->pospuzzle.y = 900;
   m->pospuzzle2.h = m->bpuzzle[1]->h;
   m->pospuzzle2.w = m->bpuzzle[1]->w;
   m->pospuzzle2.x = 1920 / 2 - (m->bpuzzle[1]->w / 2);
   m->pospuzzle2.y = 840;
   m->posquiz2.h = m->bpuzzle[1]->h;
   m->posquiz2.w = m->bpuzzle[1]->w;
   m->posquiz2.x = 1920 / 2 - (m->bpuzzle[1]->w / 2);
   m->posquiz2.y = 640;
   m->logo = IMG_Load("./assets/buttons/LOGOO.png");
   m->posl.w = 100;
   m->posl.h = 100;
   m->posl.x = 1920 / 2 - m->logo->w / 2;
   m->posl.y = 2;
   SDL_Color color3 = {255, 255, 246};
   m->Return[0] = TTF_RenderText_Solid(TTF_OpenFont("./assets/fonts/HARRYP.TTF", 120), "Return", color3);
   if (!m->Return[0])
   {
      puts("erreur Reuturn");
   }
   m->posr;
   m->posr.x = 20;
   m->posr.y = 920;
   m->posr.w = m->Return[0]->w;
   m->posr.h = m->Return[0]->h;
   SDL_Color red = {255, 0, 0};
   m->Return[1] = TTF_RenderText_Solid(TTF_OpenFont("./assets/fonts/HARRYP.TTF", 120), "Return", red);
}
void afficher_menu(menu m, SDL_Surface *ecran)
{
   TTF_Font *police = TTF_OpenFont("./assets/fonts/HARRYP.TTF", 180);
   SDL_BlitSurface(m.bg_principale, NULL, ecran, NULL);
   SDL_Color color = {255, 255, 255};
   SDL_Surface *text = TTF_RenderText_Solid(police, "QUIZ/PUZZLE TIME!", color);
   if (!text)
   {
      puts("error text!");
   }
   SDL_Rect textRect = {ecran->w / 2 - text->w / 2, 320, 0, 0};

   SDL_BlitSurface(text, NULL, ecran, &textRect);
   SDL_BlitSurface(m.logo, NULL, ecran, &m.posl);
   SDL_Color color2 = {200, 148, 98};
   TTF_Font *police2 = TTF_OpenFont("./assets/fonts/HARRYP.TTF", 80);
   SDL_Surface *text2 = TTF_RenderText_Solid(police2, "choose one option to continue", color2);
   if (!text2)
   {
      puts("error text!");
   }
   SDL_Rect textRect2 = {ecran->w / 2 - text2->w / 2, 634, 0, 0};
   SDL_BlitSurface(text2, NULL, ecran, &textRect2);

   if (!cursor(m.posquiz))
   {
      SDL_BlitSurface(m.bquiz[0], NULL, ecran, &m.posquiz);
   }
   else
   {
      SDL_BlitSurface(m.bquiz[1], NULL, ecran, &m.posquiz2);
   }
   if (!cursor(m.pospuzzle))
      SDL_BlitSurface(m.bpuzzle[0], NULL, ecran, &m.pospuzzle);
   else
      SDL_BlitSurface(m.bpuzzle[1], NULL, ecran, &m.pospuzzle2);
   if (!cursor(m.posr))
      SDL_BlitSurface(m.Return[0], NULL, ecran, &m.posr);
   else
      SDL_BlitSurface(m.Return[1], NULL, ecran, &m.posr);
   SDL_FreeSurface(text);
   SDL_FreeSurface(text2);
   TTF_CloseFont(police);
   TTF_CloseFont(police2);
}
void update(menu *m)
{
   if (cursor(m->posquiz))
   {
      m->poscursor = 1;
   }
   else
   {
      if (cursor(m->pospuzzle))
      {
         m->poscursor = 2;
      }
      else
      {
         if (cursor(m->posr))
         {
            m->poscursor = 3;
         }

         else
         {
            m->poscursor = 0;
         }
      }
   }

   printf("button clicked: %d", m->poscursor);
}
int cursor(SDL_Rect pos)
{
   int x, y;
   SDL_GetMouseState(&x, &y);

   return x > pos.x && x < pos.x + pos.w && y > pos.y && y < pos.y + pos.h;
}
void init_quiz(quiz *q)
{
   q->bg_principale = IMG_Load("./assets/backgrounds/quiz.png");
   SDL_Color color3 = {255, 255, 246};
   q->Return[0] = TTF_RenderText_Solid(TTF_OpenFont("./assets/fonts/HARRYP.TTF", 120), "Return", color3);
   if (!q->Return[0])
   {
      puts("erreur Reuturn");
   }
   q->posr;
   q->posr.x = 20;
   q->posr.y = 920;
   q->posr.w = q->Return[0]->w;
   q->posr.h = q->Return[0]->h;
   SDL_Color red = {255, 0, 0};
   q->Return[1] = TTF_RenderText_Solid(TTF_OpenFont("./assets/fonts/HARRYP.TTF", 120), "Return", red);
}
void afficher_quiz(quiz q, SDL_Surface *ecran)
{
   SDL_BlitSurface(q.bg_principale, NULL, ecran, NULL);
   if (!cursor(q.posr))
      SDL_BlitSurface(q.Return[0], NULL, ecran, &q.posr);
   else
      SDL_BlitSurface(q.Return[1], NULL, ecran, &q.posr);
}
void cleanup(menu *m, quiz *q)
{
   SDL_FreeSurface(m->bg_principale);
   m->bg_principale = NULL;
   SDL_FreeSurface(m->logo);
   m->logo = NULL;
   SDL_FreeSurface(m->bquiz[0]);
   m->bquiz[0] = NULL;
   SDL_FreeSurface(m->bquiz[1]);
   m->bquiz[1] = NULL;
   SDL_FreeSurface(m->bpuzzle[0]);
   m->bpuzzle[0] = NULL;
   SDL_FreeSurface(m->bpuzzle[1]);
   m->bpuzzle[1] = NULL;
   SDL_FreeSurface(m->Return[0]);
   m->Return[0] = NULL;
   SDL_FreeSurface(m->Return[1]);
   m->Return[1] = NULL;
   SDL_FreeSurface(q->bg_principale);
   q->bg_principale = NULL;
   SDL_FreeSurface(q->Return[0]);
   q->Return[0] = NULL;
   SDL_FreeSurface(q->Return[1]);
   q->Return[1] = NULL;
}