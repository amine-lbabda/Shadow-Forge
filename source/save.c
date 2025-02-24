#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "save.h"
void init_save(save *s)
{
    s->bg = IMG_Load("../assets/backgrounds/bgf.png");
    if (s->bg == NULL)
    {
        printf("erreur %s\n", IMG_GetError());
        SDL_Quit();
    }

    s->yes[0] = IMG_Load("../assets/buttons/yes0.png");
    s->yes[1] = IMG_Load("../assets/buttons/yes1.png");

    s->no[0] = IMG_Load("../assets/buttons/no0.png");
    s->no[1] = IMG_Load("../assets/buttons/no1.png");

    s->load[0] = IMG_Load("../assets/buttons/load0.png");
    s->load[1] = IMG_Load("../assets/buttons/load1.png");

    s->new[0] = IMG_Load("../assets/buttons/new0.png");
    s->new[1] = IMG_Load("../assets/buttons/new1.png");

    s->pos_yes.x = 300;
    s->pos_yes.y = 650;
    s->pos_yes.w = s->yes[0]->w;
    s->pos_yes.h = s->yes[0]->h;

    s->pos_no.x = 300;
    s->pos_no.y = 800;
    s->pos_no.w = s->no[0]->w;
    s->pos_no.h = s->no[0]->h;

    s->pos_load.x = 300;
    s->pos_load.y = 650;
    s->pos_load.w = s->load[0]->w;
    s->pos_load.h = s->load[0]->h;

    s->pos_new.x = 300;
    s->pos_new.y = 800;
    s->pos_new.w = s->new[0]->w;
    s->pos_new.h = s->new[0]->h;

    if (TTF_Init() == -1)
    {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
    }

    s->font = TTF_OpenFont("../assets/fonts/aa.TTF", 45);
    if (s->font == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->color_blanc.r = 255;
    s->color_blanc.g = 255;
    s->color_blanc.b = 255;

    s->color_rouge.r = 255;
    s->color_rouge.g = 0;
    s->color_rouge.b = 0;

    s->retour_blanc = TTF_RenderText_Blended(s->font, "RETURN", s->color_blanc);
    s->retour_rouge = TTF_RenderText_Blended(s->font, "RETURN", s->color_rouge);
    s->pos_retour.x = 140;
    s->pos_retour.y = 970;
    s->pos_retour.w = s->retour_blanc->w;
    s->pos_retour.h = s->retour_blanc->h;

    s->font_text = TTF_OpenFont("../assets/fonts/aa.TTF", 150);
    if (s->font_text == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->text = TTF_RenderText_Blended(s->font_text, "SAVE", s->color_blanc);
    s->pos_text.x = 450;
    s->pos_text.y = 450;

    s->font_question = TTF_OpenFont("../assets/fonts/aa.TTF", 60);
    if (s->font_question == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->question = TTF_RenderText_Blended(s->font_question, "Do you want to save your progress?", s->color_rouge);
    s->pos_question.x = 250;
    s->pos_question.y = 586;

    s->logo = IMG_Load("../assets/buttons/logos.png");
    if (s->logo == NULL)
    {
        printf("erreur %s\n", IMG_GetError());
        SDL_Quit();
    }
    s->pos_logo.x = 350;
    s->pos_logo.y = 150;
    s->pos_logo.w = s->logo->w;
    s->pos_logo.h = s->logo->h;
    s->continu = Mix_LoadMUS("../assets/audio/theme2.mp3");
    if (s->continu == NULL)
    {
        printf("Erreur Mix_LoadMUS : %s\n", Mix_GetError());
    }
    else
    {
        Mix_PlayMusic(s->continu, -1);
    }
    s->hover_sound = Mix_LoadWAV("../assets/audio/tick.wav");
    if (s->hover_sound == NULL)
    {
        printf("Erreur Mix_LoadWAV : %s\n", Mix_GetError());
    }
    s->btn_select = 0;
}

int collisionsouris(SDL_Rect pos)
{
    int x_souris, y_souris;
    SDL_GetMouseState(&x_souris, &y_souris);
    if ((x_souris > pos.x) && (x_souris < pos.x + pos.w) && (y_souris > pos.y) && (y_souris < pos.y + pos.h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void afficher_save(save s, SDL_Surface *ecran)
{
    SDL_BlitSurface(s.bg, NULL, ecran, NULL);
    SDL_BlitSurface(s.logo, NULL, ecran, &s.pos_logo);
    SDL_BlitSurface(s.text, NULL, ecran, &s.pos_text);
    SDL_BlitSurface(s.question, NULL, ecran, &s.pos_question);
    if (collisionsouris(s.pos_yes) == 0)
    {
        SDL_BlitSurface(s.yes[0], NULL, ecran, &s.pos_yes);
    }
    else
    {
        SDL_BlitSurface(s.yes[1], NULL, ecran, &s.pos_yes);
    }
    if (collisionsouris(s.pos_no) == 0)
    {
        SDL_BlitSurface(s.no[0], NULL, ecran, &s.pos_no);
    }
    else
    {
        SDL_BlitSurface(s.no[1], NULL, ecran, &s.pos_no);
    }
    if (collisionsouris(s.pos_retour) == 0)
    {
        SDL_BlitSurface(s.retour_blanc, NULL, ecran, &s.pos_retour);
    }
    else
    {
        SDL_BlitSurface(s.retour_rouge, NULL, ecran, &s.pos_retour);
    }
    SDL_Flip(ecran);
}

void miseajour(save *s)
{
    static int last_hovered_button = 0;

    if (collisionsouris(s->pos_yes) == 1)
    {
        s->btn_select = 1;
        if (last_hovered_button != 1)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 1;
        }
    }
    else if (collisionsouris(s->pos_no) == 1)
    {
        printf("noooooo ");
        s->btn_select = 2;
        if (last_hovered_button != 2)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 2;
        }
    }
    else if (collisionsouris(s->pos_retour) == 1)
    {
        s->btn_select = 5;
        if (last_hovered_button != 5)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 5;
        }
    }
    else
    {
        s->btn_select = 0;
        last_hovered_button = 0;
    }
    last_hovered_button = 0;
}

void afficher_sous_menu(save s, SDL_Surface *ecran)
{
    SDL_BlitSurface(s.bg, NULL, ecran, NULL);
    SDL_BlitSurface(s.logo, NULL, ecran, &s.pos_logo);
    SDL_BlitSurface(s.text, NULL, ecran, &s.pos_text);
    if (collisionsouris(s.pos_load) == 0)
    {
        SDL_BlitSurface(s.load[0], NULL, ecran, &s.pos_load);
    }
    else
    {
        SDL_BlitSurface(s.load[1], NULL, ecran, &s.pos_load);
    }
    if (collisionsouris(s.pos_new) == 0)
    {
        SDL_BlitSurface(s.new[0], NULL, ecran, &s.pos_new);
    }
    else
    {
        SDL_BlitSurface(s.new[1], NULL, ecran, &s.pos_new);
    }
    if (collisionsouris(s.pos_retour) == 0)
    {
        SDL_BlitSurface(s.retour_blanc, NULL, ecran, &s.pos_retour);
    }
    else
    {
        SDL_BlitSurface(s.retour_rouge, NULL, ecran, &s.pos_retour);
    }
    SDL_Flip(ecran);
}

void miseajour_sous_menu(save *s)
{
    if (collisionsouris(s->pos_load) == 1)
    {
        s->btn_select = 3;
    }
    else
    {
        if (collisionsouris(s->pos_new) == 1)
        {
            s->btn_select = 4;
        }
        else
        {
            if (collisionsouris(s->pos_retour) == 1)
            {
                s->btn_select = 5;
            }
            else
            {
                s->btn_select = 0;
            }
        }
    }
}

void liberer_save(save *s)
{
    SDL_FreeSurface(s->bg);
    SDL_FreeSurface(s->logo);
    SDL_FreeSurface(s->retour_blanc);
    SDL_FreeSurface(s->retour_rouge);
    SDL_FreeSurface(s->text);
    SDL_FreeSurface(s->question);
    TTF_CloseFont(s->font);
    TTF_CloseFont(s->font_text);
    TTF_CloseFont(s->font_question);
    Mix_FreeMusic(s->continu);
    Mix_FreeChunk(s->hover_sound);
    Mix_CloseAudio();
}
