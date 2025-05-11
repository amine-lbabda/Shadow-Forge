#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "tache.h"
void mode_init_menu(joueur *s)
{
    s->bg = IMG_Load("./assets/mode assets/bgf.png");
    if (!s->bg)
    {
        printf("Erreur chargement bgf.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->gp[0] = IMG_Load("./assets/mode assets/gp0.png");
    if (!s->gp[0])
    {
        printf("Erreur chargement gp0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->gp[1] = IMG_Load("./assets/mode assets/gp1.png");
    if (!s->gp[1])
    {
        printf("Erreur chargement gp1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->key[0] = IMG_Load("./assets/mode assets/key0.png");
    if (!s->key[0])
    {
        printf("Erreur chargement key0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->key[1] = IMG_Load("./assets/mode assets/key1.png");
    if (!s->key[1])
    {
        printf("Erreur chargement key1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->multi[0] = IMG_Load("./assets/mode assets/multi0.png");
    if (!s->multi[0])
    {
        printf("Erreur chargement multi0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->multi[1] = IMG_Load("./assets/mode assets/multi1.png");
    if (!s->multi[1])
    {
        printf("Erreur chargement multi1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->single[0] = IMG_Load("./assets/mode assets/single0.png");
    if (!s->single[0])
    {
        printf("Erreur chargement single0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->single[1] = IMG_Load("./assets/mode assets/single1.png");
    if (!s->single[1])
    {
        printf("Erreur chargement single1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->rika[0] = IMG_Load("./assets/mode assets/rika0.png");
    if (!s->rika[0])
    {
        printf("Erreur chargement rika0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->rika[1] = IMG_Load("./assets/mode assets/rika1.png");
    if (!s->rika[1])
    {
        printf("Erreur chargement rika1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->rikam[0] = IMG_Load("./assets/mode assets/rikam0.png");
    if (!s->rikam[0])
    {
        printf("Erreur chargement rikam0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->rikam[1] = IMG_Load("./assets/mode assets/rikam1.png");
    if (!s->rikam[1])
    {
        printf("Erreur chargement rikam1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->zone[0] = IMG_Load("./assets/mode assets/zone0.png");
    if (!s->zone[0])
    {
        printf("Erreur chargement zone0.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->zone[1] = IMG_Load("./assets/mode assets/zone1.png");
    if (!s->zone[1])
    {
        printf("Erreur chargement zone1.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->logo = IMG_Load("./assets/mode assets/logo.png");
    if (!s->logo)
    {
        printf("Erreur chargement logo.png : %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    s->pos_multi.x = 300;
    s->pos_multi.y = 800;
    s->pos_multi.w = s->multi[0]->w;
    s->pos_multi.h = s->multi[0]->h;

    s->pos_single.x = 300;
    s->pos_single.y = 650;
    s->pos_single.w = s->single[0]->w;
    s->pos_single.h = s->single[0]->h;

    s->pos_gp.x = 1128;
    s->pos_gp.y = 605;
    s->pos_gp.w = s->gp[0]->w;
    s->pos_gp.h = s->gp[0]->h;

    s->pos_key.x = 1128;
    s->pos_key.y = 444;
    s->pos_key.w = s->key[0]->w;
    s->pos_key.h = s->key[0]->h;

    s->pos_rika.x = 90;
    s->pos_rika.y = 300;
    s->pos_rika.w = s->rika[0]->w;
    s->pos_rika.h = s->rika[0]->h;

    s->pos_rikam.x = 504;
    s->pos_rikam.y = 300;
    s->pos_rikam.w = s->rikam[0]->w;
    s->pos_rikam.h = s->rikam[0]->h;

    s->pos_zone.x = 183;
    s->pos_zone.y = 840;
    s->pos_zone.w = s->zone[0]->w;
    s->pos_zone.h = s->zone[0]->h;

    if (TTF_Init() == -1)
    {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
    }

    s->font = TTF_OpenFont("./assets/fonts/aa.TTF", 45);
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

    s->confirm_blanc = TTF_RenderText_Blended(s->font, "CONFIRM", s->color_blanc);
    s->confirm_rouge = TTF_RenderText_Blended(s->font, "CONFIRM", s->color_rouge);
    s->pos_confirm.x = 1700;
    s->pos_confirm.y = 970;
    s->pos_confirm.w = s->confirm_rouge->w;
    s->pos_confirm.h = s->confirm_rouge->h;

    s->font_text = TTF_OpenFont("./assets/fonts/aa.TTF", 60);
    if (s->font_text == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->text = TTF_RenderText_Blended(s->font_text, "CHOOSE YOUR CHARACTER", s->color_blanc);
    s->pos_text.x = 200;
    s->pos_text.y = 260;

    s->font_textname = TTF_OpenFont("./assets/fonts/aa.TTF", 80);
    if (s->font_textname == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    s->textname = TTF_RenderText_Blended(s->font_textname, "NAME", s->color_blanc);
    if (s->textname == NULL)
    {
        printf("Erreur affichage textname : %s\n", TTF_GetError());
    }
    s->pos_textname.x = 361;
    s->pos_textname.y = 761;

    s->font_question = TTF_OpenFont("./assets/fonts/aa.TTF", 60);
    if (s->font_question == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->question = TTF_RenderText_Blended(s->font_question, "CHOOSE YOUR INPUT", s->color_blanc);
    s->pos_question.x = 1109;
    s->pos_question.y = 268;

    s->font_textmode = TTF_OpenFont("./assets/fonts/aa.TTF", 150);
    if (s->font_textmode == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
    }
    s->textmode = TTF_RenderText_Blended(s->font_textmode, "GAME MODE", s->color_blanc);
    s->pos_textmode.x = 180;
    s->pos_textmode.y = 450;

    s->logo = IMG_Load("./assets/mode assets/logo.png");
    if (s->logo == NULL)
    {
        printf("erreur %s\n", IMG_GetError());
        SDL_Quit();
    }
    s->pos_logo.x = 250;
    s->pos_logo.y = 100;
    s->pos_logo.w = s->logo->w;
    s->pos_logo.h = s->logo->h;
    s->continu = Mix_LoadMUS("./assets/mode assets/theme2.mp3");
    if (s->continu == NULL)
    {
        printf("Erreur Mix_LoadMUS : %s\n", Mix_GetError());
    }
    else
    {
        Mix_PlayMusic(s->continu, -1);
    }
    s->hover_sound = Mix_LoadWAV("./assets/mode assets/tick.wav");
    if (s->hover_sound == NULL)
    {
        printf("Erreur Mix_LoadWAV : %s\n", Mix_GetError());
    }
    s->btn_select = 0;
    strcpy(s->nom_joueur, "");
    s->saisie_active = 0;
}

int mode_collisionsouris(SDL_Rect pos)
{
    int x_souris, y_souris;
    SDL_GetMouseState(&x_souris, &y_souris);
    // printf("new x : ");
    // printf("%d ",x_souris);
    // printf("new y : ");
    // printf("%d \n",y_souris);
    if ((x_souris > pos.x) && (x_souris < pos.x + pos.w) && (y_souris > pos.y) && (y_souris < pos.y + pos.h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void mode_afficher_sous_menu(joueur s, SDL_Surface *ecran)
{
    SDL_BlitSurface(s.bg, NULL, ecran, NULL);
    SDL_BlitSurface(s.logo, NULL, ecran, &s.pos_logo);
    SDL_BlitSurface(s.textmode, NULL, ecran, &s.pos_textmode);
    if (mode_collisionsouris(s.pos_single) == 0)
    {
        SDL_BlitSurface(s.single[0], NULL, ecran, &s.pos_single);
    }
    else
    {
        SDL_BlitSurface(s.single[1], NULL, ecran, &s.pos_single);
    }
    if (mode_collisionsouris(s.pos_multi) == 0)
    {
        SDL_BlitSurface(s.multi[0], NULL, ecran, &s.pos_multi);
    }
    else
    {
        SDL_BlitSurface(s.multi[1], NULL, ecran, &s.pos_multi);
    }
    if (mode_collisionsouris(s.pos_retour) == 0)
    {
        SDL_BlitSurface(s.retour_blanc, NULL, ecran, &s.pos_retour);
    }
    else
    {
        SDL_BlitSurface(s.retour_rouge, NULL, ecran, &s.pos_retour);
    }
    SDL_Flip(ecran);
}

void mode_miseajour_sous_menu(joueur *s)
{
    static int last_hovered_button = 0;
    if (mode_collisionsouris(s->pos_single) == 1)
    {
        s->btn_select = 8;
        if (last_hovered_button != 8)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 8;
        }
    }
    else
    {
        if (mode_collisionsouris(s->pos_multi) == 1)
        {
            s->btn_select = 9;
            if (last_hovered_button != 9)
            {
                Mix_PlayChannel(-1, s->hover_sound, 0);
                last_hovered_button = 9;
            }
        }
        else
        {
            if (mode_collisionsouris(s->pos_retour) == 1)
            {
                s->btn_select = 5;
                if (last_hovered_button != 5)
                {
                    Mix_PlayChannel(-1, s->hover_sound, 0);
                    last_hovered_button = 5;
                }
                else
                {
                    s->btn_select = 0;
                    last_hovered_button = 0;
                }
                last_hovered_button = 0;
            }
        }
    }
}

void mode_afficher_menu(joueur s, SDL_Surface *ecran, int show_cursor)
{
    SDL_Surface *nom_surface;
    SDL_Rect pos_nom;
    char texte_affiche[32];
    SDL_BlitSurface(s.bg, NULL, ecran, NULL);
    SDL_BlitSurface(s.logo, NULL, ecran, &s.pos_logo);
    SDL_BlitSurface(s.text, NULL, ecran, &s.pos_text);
    SDL_BlitSurface(s.question, NULL, ecran, &s.pos_question);
    SDL_BlitSurface(s.textname, NULL, ecran, &s.pos_textname);
    if (s.selected_input == 1)
    {
        SDL_BlitSurface(s.gp[1], NULL, ecran, &s.pos_gp);
    }
    else if (mode_collisionsouris(s.pos_gp))
    {
        SDL_BlitSurface(s.gp[1], NULL, ecran, &s.pos_gp);
    }
    else
    {
        SDL_BlitSurface(s.gp[0], NULL, ecran, &s.pos_gp);
    }

    if (s.selected_input == 2)
    {
        SDL_BlitSurface(s.key[1], NULL, ecran, &s.pos_key);
    }
    else if (mode_collisionsouris(s.pos_key))
    {
        SDL_BlitSurface(s.key[1], NULL, ecran, &s.pos_key);
    }
    else
    {
        SDL_BlitSurface(s.key[0], NULL, ecran, &s.pos_key);
    }

    if (mode_collisionsouris(s.pos_retour) == 0)
    {
        SDL_BlitSurface(s.retour_blanc, NULL, ecran, &s.pos_retour);
    }
    else
    {
        SDL_BlitSurface(s.retour_rouge, NULL, ecran, &s.pos_retour);
    }
    if (mode_collisionsouris(s.pos_confirm) == 0)
    {
        SDL_BlitSurface(s.confirm_blanc, NULL, ecran, &s.pos_confirm);
    }
    else
    {
        SDL_BlitSurface(s.confirm_rouge, NULL, ecran, &s.pos_confirm);
    }
    if (s.selected_character == 1)
    {
        SDL_BlitSurface(s.rika[1], NULL, ecran, &s.pos_rika);
    }
    else if (mode_collisionsouris(s.pos_rika))
    {
        SDL_BlitSurface(s.rika[1], NULL, ecran, &s.pos_rika);
    }
    else
    {
        SDL_BlitSurface(s.rika[0], NULL, ecran, &s.pos_rika);
    }
    if (s.selected_character == 2)
    {
        SDL_BlitSurface(s.rikam[1], NULL, ecran, &s.pos_rikam);
    }
    else if (mode_collisionsouris(s.pos_rikam))
    {
        SDL_BlitSurface(s.rikam[1], NULL, ecran, &s.pos_rikam);
    }
    else
    {
        SDL_BlitSurface(s.rikam[0], NULL, ecran, &s.pos_rikam);
    }
    if (mode_collisionsouris(s.pos_zone))
    {
        SDL_BlitSurface(s.zone[1], NULL, ecran, &s.pos_zone);
    }
    else
    {
        SDL_BlitSurface(s.zone[0], NULL, ecran, &s.pos_zone);
    }
    if (strlen(s.nom_joueur) == 0)
    {
        strcpy(texte_affiche, " ");
    }
    else
    {
        strcpy(texte_affiche, s.nom_joueur);
    }
    if (s.saisie_active && show_cursor && strlen(texte_affiche) < sizeof(texte_affiche) - 1)
    {
        strcat(texte_affiche, "|");
    }
    nom_surface = TTF_RenderText_Blended(s.font_textname, texte_affiche, s.color_blanc);
    if (nom_surface == NULL)
    {
        printf("Erreur texte_affiche : %s\n", TTF_GetError());
        return;
    }
    pos_nom.x = s.pos_zone.x + (s.pos_zone.w - nom_surface->w) / 2;
    pos_nom.y = s.pos_zone.y + (s.pos_zone.h - nom_surface->h) / 2;
    SDL_BlitSurface(nom_surface, NULL, ecran, &pos_nom);
    SDL_FreeSurface(nom_surface);
    SDL_Flip(ecran);
}

void mode_miseajour(joueur *s)
{
    static int last_hovered_button = 0;

    if (mode_collisionsouris(s->pos_gp) == 1)
    {
        s->btn_select = 1;
        if (last_hovered_button != 1)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 1;
        }
    }
    else if (mode_collisionsouris(s->pos_key) == 1)
    {
        s->btn_select = 2;
        if (last_hovered_button != 2)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 2;
        }
    }
    else if (mode_collisionsouris(s->pos_retour) == 1)
    {
        s->btn_select = 5;
        if (last_hovered_button != 5)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 5;
        }
    }
    else if (mode_collisionsouris(s->pos_rika) == 1)
    {
        s->btn_select = 3;
        if (last_hovered_button != 3)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 3;
        }
    }
    else if (mode_collisionsouris(s->pos_rikam) == 1)
    {
        s->btn_select = 4;
        if (last_hovered_button != 4)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 4;
        }
    }
    else if (mode_collisionsouris(s->pos_confirm) == 1)
    {
        s->btn_select = 6;
        if (last_hovered_button != 6)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 6;
        }
    }
    else if (mode_collisionsouris(s->pos_zone) == 1)
    {
        s->btn_select = 7;
        if (last_hovered_button != 7)
        {
            Mix_PlayChannel(-1, s->hover_sound, 0);
            last_hovered_button = 7;
        }
    }
    else
    {
        s->btn_select = 0;
        last_hovered_button = 0;
    }
    last_hovered_button = 0;
}

void mode_liberer_save(joueur *s)
{
    SDL_FreeSurface(s->bg);
    SDL_FreeSurface(s->logo);
    SDL_FreeSurface(s->retour_blanc);
    SDL_FreeSurface(s->retour_rouge);
    SDL_FreeSurface(s->confirm_blanc);
    SDL_FreeSurface(s->confirm_rouge);
    SDL_FreeSurface(s->text);
    SDL_FreeSurface(s->textname);
    SDL_FreeSurface(s->question);
    SDL_FreeSurface(s->textmode);
    TTF_CloseFont(s->font);
    TTF_CloseFont(s->font_text);
    TTF_CloseFont(s->font_question);
    TTF_CloseFont(s->font_textmode);
    Mix_FreeMusic(s->continu);
    Mix_FreeChunk(s->hover_sound);
    Mix_CloseAudio();
}
