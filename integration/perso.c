#include "background.h"
#include "collision.h"
#include "enemy.h"
#include "joueur.h"
#include "minimap.h"
#include "enigme2.h"
#include "enigme_1.h"
#include <stdio.h>
int main(int argc, char **argv)
{
  // SDL_Surface *platform = NULL;
  SDL_Surface *time_surface = NULL;
  int puzzle_active = 0;
  char buffer_time[200];
  SDL_Color color = {255, 255, 255};
  Uint32 temps = 0;
  char buffer_score[50];
  MiniMap minimap;
  TTF_Font *font = NULL;
  int score = 0;
  Mix_Chunk *heal_sound = NULL;
  int player_hp = 50;
  int pack_visible = 1;
  SDL_Rect health_pack = {1500, 800, 0, 0};
  SDL_Surface *guide = NULL;
  int guidance = -1;
  Enemy sengo;
  Uint32 temps_ecoule;
  SDL_Event event;
  SDL_Surface *ecran, *score_surface = NULL;
  background bg;
  perso joueurs[2];
  int etat = 0;
  int quitter = 1;
  Uint32 dt = 0;
  int left_pressed = 0, right_pressed = 0;
  int nb_joueurs = 1;
  Uint32 t_now;
  Uint32 t_press_start = 0;
  Uint32 t_prev;
  int camX = 0, camY = 0;
  SDL_Rect target = {1600, 500, 100, 100};
  int bg_width;
  int scroll_start;
  int scroll_width;
  int largeur_restante;
  int scroll_start1;
  int scroll_width1;
  int largeur_restante1;
  int scroll_start2;
  int scroll_width2;
  int largeur_restante2;
  int centreJoueur;
  int demiEcran;
  int centreJoueurY;
  int demiHauteurEcran;
  SDL_Rect health_pack_screen, pos_guidance, pos_score, pos_timer, pos_platform;
  if (TTF_Init() == -1)
  {
    printf("Erreur TTF_Init: %s\n", TTF_GetError());
    return EXIT_FAILURE;
  }
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    printf("Erreur SDL: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("Erreur audio: %s\n", Mix_GetError());
  }

  ecran = SDL_SetVideoMode(LARGEURFENETRE, HAUTEURFENETRE, 32,
                           SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!ecran)
  {
    printf("Erreur creation ecran: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  SDL_Surface *health_img = IMG_Load("health.png");
  sprintf(buffer_score, "score:%d", score);
  if (!health_img)
  {
    printf("Failed to load health.png: %s\n", IMG_GetError());
  }
  if (health_img)
  {
    health_pack.w = health_img->w;
    health_pack.h = health_img->h;
  }
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
  {
    printf("Erreur IMG_Init: %s\n", IMG_GetError());
    return EXIT_FAILURE;
  }

  init_background(&bg, ecran, "./bg3.jpg");
  heal_sound = Mix_LoadWAV("heal.wav");
  SDL_Surface *mob_sprite = IMG_Load("sengo.png");
  SDL_Surface *boss_sprite = IMG_Load("sengo.png");
  SDL_Surface *boss_sprite2 = IMG_Load("sengo.png");
  // platform = IMG_Load("image.png");
  sprintf(buffer_time, "Time:%d", temps);
  font = TTF_OpenFont("test.ttf", 50);
  time_surface = TTF_RenderText_Solid(font, buffer_time, color);
  score_surface = TTF_RenderText_Solid(font, buffer_score, color);
  SDL_Surface *backgroundMask = SDL_LoadBMP("backgroundMask.bmp");
  bg.direction = -1;
  initMiniMap(&minimap, 1);
  init_perso(&joueurs[0]);
  init_enemy(&sengo, boss_sprite, boss_sprite2, 1);
  guide = IMG_Load("guide_1.png");
  if (!guide)
  {
    printf("Failed to load :%s\n", IMG_GetError());
  }
  sengo.pos.x = 1700;
  sengo.pos.y = 720;
  joueurs[0].nb_joueur = 1;

  joueurs[0].pos.x = 100;

  joueurs[0].pos.y = 650;
  joueurs[0].posinit = joueurs[0].pos.y;
  joueurs[0].posscreen.x = joueurs[0].pos.x;
  joueurs[0].posscreen.y = joueurs[0].pos.y;
  joueurs[0].direction = 1;
  joueurs[0].acceleration = 0;
  joueurs[0].vitesse = 0;
  pos_guidance.x = 500;
  pos_guidance.y = 0;
  pos_guidance.w = guide->w;
  pos_guidance.h = guide->h;
  pos_score.x = 800;
  pos_score.y = 0;
  pos_score.w = score_surface->w + HAUTEURFENETRE;
  pos_score.h = score_surface->h + LARGEURFENETRE;
  pos_timer.x = 1000;
  pos_timer.y = 0;
  pos_timer.w = time_surface->w + HAUTEURFENETRE;
  pos_timer.h = time_surface->h + LARGEURFENETRE;
  // pos_platform.x = 900;
  // pos_platform.y = 850;
  // pos_platform.w = platform->w;
  // pos_platform.h = platform->h;
  while (quitter)
  {

    printf("pos_joueur_x:%d|pos_joueur_y:%d\n", joueurs[0].pos.x,
           joueurs[0].pos.y);

    temps = SDL_GetTicks();

    t_now = SDL_GetTicks();
    dt = t_now - t_prev;
    t_prev = t_now;
    if (dt > 50)
      dt = 50;
    t_prev = t_now;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        quitter = 0;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          quitter = 0;
        }
        if (event.key.keysym.sym == SDLK_g)
        {
          guidance++;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT ||
                 event.key.keysym.sym == SDLK_d)
        {

          right_pressed = 1;
          joueurs[0].direction = 1;
          if (joueurs[0].acceleration < 0.5)
            joueurs[0].acceleration += 0.05;
          if ((etat == 0) || (etat == 1))
          {
            etat = 2;
          }
          if (t_press_start == 0)
          {
            t_press_start = SDL_GetTicks();
          }
          joueurs[0].temps_presse = SDL_GetTicks();
        }
        else if (event.key.keysym.sym == SDLK_LEFT ||
                 event.key.keysym.sym == SDLK_a)
        {
          left_pressed = 1;
          joueurs[0].direction = -1;
          if (joueurs[0].acceleration > -0.5)
            joueurs[0].acceleration -= 0.05;
          if ((etat == 0) || (etat == 1))
          {
            etat = 3;
          }

          if (t_press_start == 0)
          {
            t_press_start = SDL_GetTicks();
          }
          joueurs[0].temps_presse = SDL_GetTicks();
        }
        else if ((event.key.keysym.sym == SDLK_LSHIFT) ||
                 (event.key.keysym.sym == SDLK_RSHIFT))
        {
          joueurs[0].vitesse_max = joueurs[0].vitesse_dash;
          joueurs[0].temps_dash = 0.5;
          joueurs[0].en_dash = 1;
          joueurs[0].distance_parcourue = 0;
          joueurs[0].dash_start_x = joueurs[0].pos.x;
        }

        else if (event.key.keysym.sym == SDLK_SPACE)
        {
          if (joueurs[0].up == 0)
          {
            joueurs[0].type_saut = 0;
            joueurs[0].up = 1;
            joueurs[0].double_saut_dispo = 1;
            joueurs[0].vitesse_y = -380;
            if (joueurs[0].direction == 1)
            {
              etat = 6;
            }
            else
            {
              etat = 7;
            }
            joueurs[0].temps_presse = SDL_GetTicks();
          }
          else
          {
            if (joueurs[0].double_saut_dispo == 1 &&
                joueurs[0].vitesse_y > -300)
            {
              joueurs[0].vitesse_y = -380;
              joueurs[0].double_saut_dispo = 0;
              joueurs[0].temps_presse = SDL_GetTicks();
              if (joueurs[0].direction == 1)
              {
                etat = 6;
              }
              else
              {
                etat = 7;
              }
            }
          }
          joueurs[0].temps_presse = SDL_GetTicks();
        }
        else if (event.key.keysym.sym == SDLK_c)
        {
          if (joueurs[0].up == 0)
          {
            joueurs[0].type_saut = 1;
            joueurs[0].up = 1;
            joueurs[0].posinit_x = joueurs[0].pos_actuelle_x;
            joueurs[0].posinit_y = joueurs[0].pos_actuelle_y;
            joueurs[0].x_rel = 0;
            joueurs[0].frameActuelle = 0;
            joueurs[0].vitesse_y = -300;
            joueurs[0].dernierChangement = SDL_GetTicks();
            joueurs[0].etat_precedent = joueurs[0].etat_animation;
          }
          joueurs[0].temps_presse = SDL_GetTicks();
          if ((etat == 0) || (etat == 2) || (etat == 4))
          {
            joueurs[0].vitesse_y = -300;
            etat = 6;
          }
          else
          {
            if ((etat == 1) || (etat == 3) || (etat == 5))
            {
              joueurs[0].vitesse_y = -300;
              etat = 7;
            }
          }
        }

        else if (event.key.keysym.sym == SDLK_p)
        {
          if (nb_joueurs < 2)
          {
            ajout_autre_joueur(joueurs, &nb_joueurs);
            joueurs[1].pos.y = HAUTEURFENETRE - joueurs[1].pos.h;
            joueurs[1].posscreen.x = joueurs[1].pos.x;
            joueurs[1].posscreen.y = joueurs[1].pos.y;
          }
        }
        else if (event.key.keysym.sym == SDLK_e)
        {
          if (joueurs[0].direction == 1)
          {
            if ((etat == 2) || (etat == 4) || (etat == 0) || (etat == 6))
            {
              etat = 8;
            }
          }
          else
          {
            if ((etat == 3) || (etat == 5) || (etat == 1) || (etat == 7))
            {
              etat = 9;
            }
          }
        }

        break;
      case SDL_KEYUP:
        if ((event.key.keysym.sym == SDLK_RIGHT) ||
            (event.key.keysym.sym == SDLK_d))
        {
          right_pressed = 0;
          if ((etat == 2) || (etat == 4))
          {
            etat = 0;
          }
        }
        if ((event.key.keysym.sym == SDLK_LEFT) ||
            (event.key.keysym.sym == SDLK_a))
        {
          left_pressed = 0;
          if ((etat == 3) || (etat == 5))
          {
            etat = 1;
          }
        }

        if (event.key.keysym.sym == SDLK_SPACE)
        {
        }

        break;
      }
    }

    if (t_press_start != 0)
    {
      temps_ecoule = SDL_GetTicks() - t_press_start;
      if (temps_ecoule > 1500)
      {
        if (etat == 2)
        {
          etat = 4;
        }
        else
        {
          if (etat == 3)
          {
            etat = 5;
          }
        }
      }
    }

    if (joueurs[0].temps_presse > 0)
    {
      temps_ecoule = SDL_GetTicks() - joueurs[0].temps_presse;
      if ((temps_ecoule > 1000) && (joueurs[0].acceleration < 0.2))
      {
        joueurs[0].acceleration += 0.001;
      }
    }
    if (right_pressed)
    {
      score++;
      if (joueurs[0].acceleration < 0.5)
        joueurs[0].acceleration += 0.01;
    }
    else if (left_pressed)
    {
      if (joueurs[0].acceleration > -0.5)
        joueurs[0].acceleration -= 0.01;
    }
    else
    {
      if (!right_pressed && !left_pressed)
        joueurs[0].acceleration = 0;
    }
    if (right_pressed && left_pressed)
    {
      joueurs[0].direction = 0;
      joueurs[0].acceleration = 0;
      joueurs[0].vitesse *= 0.8;
    }
    else if (right_pressed)
    {
      joueurs[0].direction = 1;
    }
    else if (left_pressed)
    {
      joueurs[0].direction = -1;
    }
    if (etat == 8 || etat == 9)
    {
      printf("Attaque en cours... on ne change pas l'Ã©tat !\n");
    }
    else
    {
      if (right_pressed && (etat == 0 || etat == 1))
        etat = 2;
      else if (left_pressed && (etat == 0 || etat == 1))
        etat = 3;
    }
    animer(&joueurs[0], etat);
    if ((etat == 8 || etat == 9) && joueurs[0].frameActuelle >= 7)
    {
      if (joueurs[0].direction == 1)
      {
        etat = 0;
      }
      else if (joueurs[0].direction == -1)
      {
        etat = 1;
      }
    }
    if (etat == 8 || etat == 9)
    {
      joueurs[0].vitesse = 0;
      joueurs[0].acceleration = 0;
    }
    deplacer(&joueurs[0], dt);
    printf("x logique = %d | x affichÃ© = %d\n", joueurs[0].pos.x,
           joueurs[0].posscreen.x);
    if (joueurs[0].up == 0 && joueurs[0].collision_plateforme == 0)
    {
      joueurs[0].up = 1;
      joueurs[0].vitesse_y = 0;
    }

    sauter(&joueurs[0], dt);
    if ((etat == 6 || etat == 7) && joueurs[0].up == 0)
    {
      if (joueurs[0].direction == 1)
      {
        etat = 0;
      }
      else
      {
        etat = 1;
      }
    }
    if (joueurs[0].up == 0)
    {
      joueurs[0].pos.x = (int)joueurs[0].pos_actuelle_x;
      joueurs[0].pos.y = (int)joueurs[0].pos_actuelle_y;
    }

    if (joueurs[0].up == 1 && joueurs[0].type_saut == 0)
    {
      joueurs[0].pos.y = (int)joueurs[0].pos_actuelle_y;
    }
    else if (joueurs[0].up == 1 && joueurs[0].type_saut == 1)
    {
      joueurs[0].pos.x = (int)joueurs[0].pos_actuelle_x;
      joueurs[0].pos.y = (int)joueurs[0].pos_actuelle_y;
    }

    if (joueurs[0].up == 0 && joueurs[0].type_saut == 1)
    {
      joueurs[0].type_saut = 0;
    }

    if (joueurs[0].up == 0)
    {
      joueurs[0].double_saut_dispo = 1;
    }
    update_enemy(&sengo, target, &joueurs[0]);
    animate_enemy(&sengo);

    centreJoueur = joueurs[0].pos.x + joueurs[0].pos.w / 2;
    demiEcran = ecran->w / 2;

    if (centreJoueur <= demiEcran)
    {
      camX = 0;
    }
    else
    {
      camX = centreJoueur - demiEcran;
    }

    centreJoueurY = joueurs[0].pos.y + joueurs[0].pos.h / 2;
    demiHauteurEcran = ecran->h / 2;

    camY = centreJoueurY - demiHauteurEcran;

    if (camY < 0)
      camY = 0;
    else if (camY > bg.image->h - ecran->h)
      camY = bg.image->h - ecran->h;
    sengo.posscreen.x = sengo.pos.x - camX;
    sengo.posscreen.y = sengo.pos.y - camY;
    bg.poscamera.y = camY;

    joueurs[0].posscreen.y = joueurs[0].pos.y - camY;

    bg.poscamera.x = camX % bg.image->w;
    bg.poscamera.y = camY;
    joueurs[0].posscreen.x = joueurs[0].pos.x - camX;
    joueurs[0].posscreen.y = joueurs[0].pos.y - camY;
    SDL_Rect camera = {camX, camY, ecran->w, ecran->h};
    updateMiniMap(&minimap, joueurs[0].pos, camera);
    if (nb_joueurs > 1)
    {

      joueurs[1].posscreen.x = joueurs[1].pos.x - camX;
      joueurs[1].posscreen.y = joueurs[1].pos.y - camY;
    }

    if (nb_joueurs == 2)
    {

      SDL_Rect viewport1 = {0, 0, LARGEURFENETRE / 2, HAUTEURFENETRE};
      SDL_Rect viewport2 = {LARGEURFENETRE / 2, 0, LARGEURFENETRE / 2,
                            HAUTEURFENETRE};

      SDL_Rect cam1 = {
          joueurs[0].pos.x + joueurs[0].pos.w / 2 - viewport1.w / 2,
          joueurs[0].pos.y + joueurs[0].pos.h / 2 - viewport1.h / 2,
          viewport1.w, viewport1.h};

      SDL_Rect cam2 = {
          joueurs[1].pos.x + joueurs[1].pos.w / 2 - viewport2.w / 2,
          joueurs[1].pos.y + joueurs[1].pos.h / 2 - viewport2.h / 2,
          viewport2.w, viewport2.h};

      cam1.x = (joueurs[0].pos.x + joueurs[0].pos.w / 2) - viewport1.w / 2;

      if (cam1.x < 0)
      {
        cam1.x = 0;
      }
      else if (cam1.x > bg.image->w - viewport1.w)
      {
        cam1.x = bg.image->w - viewport1.w;
      }

      cam2.x = (joueurs[1].pos.x + joueurs[1].pos.w / 2) - viewport2.w / 2;

      if (cam2.x < 0)
      {
        cam2.x = 0;
      }
      else if (cam2.x > bg.image->w - viewport2.w)
      {
        cam2.x = bg.image->w - viewport2.w;
      }

      if (cam1.y < 0)
        cam1.y = 0;
      else if (cam1.y > bg.image->h - cam1.h)
        cam1.y = bg.image->h - cam1.h;

      if (cam2.y < 0)
        cam2.y = 0;
      else if (cam2.y > bg.image->h - cam2.h)
        cam2.y = bg.image->h - cam2.h;

      if (joueurs[0].pos.x < 0)
      {
        joueurs[0].pos.x = 0;
      }
      else if (joueurs[0].pos.x + joueurs[0].pos.w > bg.image->w)
      {
        joueurs[0].pos.x = bg.image->w - joueurs[0].pos.w;
      }

      joueurs[0].posscreen.x = joueurs[0].pos.x - cam1.x;

      joueurs[1].posscreen.x = viewport2.x + (joueurs[1].pos.x - cam2.x);
      joueurs[1].posscreen.y = joueurs[1].pos.y - cam2.y;

      SDL_BlitSurface(bg.image, &cam1, ecran, &viewport1);
      SDL_BlitSurface(bg.image, &cam2, ecran, &viewport2);

      afficher_perso(&joueurs[0], ecran);
      afficher_perso(&joueurs[1], ecran);
      SDL_BlitSurface(sengo.sprite, &sengo.possprite, ecran, &sengo.posscreen);
    }
    else
    {

      bg_width = bg.image->w;
      scroll_start = bg.poscamera.x;
      scroll_width = ecran->w;

      if (scroll_start + scroll_width <= bg_width)
      {
        SDL_BlitSurface(bg.image, &bg.poscamera, ecran, NULL);
      }
      else
      {
        largeur_restante = bg_width - scroll_start;

        SDL_Rect src1 = {scroll_start, bg.poscamera.y, largeur_restante,
                         bg.poscamera.h};
        SDL_Rect dest1 = {0, 0};
        SDL_BlitSurface(bg.image, &src1, ecran, &dest1);

        SDL_Rect src2 = {0, bg.poscamera.y, scroll_width - largeur_restante,
                         bg.poscamera.h};
        SDL_Rect dest2 = {largeur_restante, 0};
        SDL_BlitSurface(bg.image, &src2, ecran, &dest2);
      }

      if (pack_visible)
      {
        SDL_Rect health_pack_screen = {health_pack.x - camX,
                                       health_pack.y - camY, health_pack.w,
                                       health_pack.h};
        SDL_BlitSurface(health_img, NULL, ecran, &health_pack_screen);
      }
      afficher_perso(&joueurs[0], ecran);
      SDL_BlitSurface(sengo.sprite, &sengo.possprite, ecran, &sengo.posscreen);
      interaction(&sengo, &joueurs[0]);
      if (heal(joueurs[0].pos, &health_pack, &pack_visible, &player_hp))
      {
        Mix_PlayChannel(-1, heal_sound, 0);
      }
      displayMiniMap(minimap, ecran);
      if (guidance == 0)
      {
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }
      else if (guidance == 1)
      {
        guide = IMG_Load("guide_2.png");
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }
      else if (guidance == 2)
      {
        guide = IMG_Load("guide_3.png");
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }
      else if (guidance == 3)
      {
        guide = IMG_Load("guide_4.png");
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }
      else if (guidance == 4)
      {
        guide = IMG_Load("guide_5.png");
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }
      else if (guidance == 5)
      {
        guide = IMG_Load("guide_6.png");
        SDL_BlitSurface(guide, NULL, ecran, &pos_guidance);
      }

      sprintf(buffer_score, "score:%d", score);
      score_surface = TTF_RenderText_Solid(font, buffer_score, color);
      SDL_BlitSurface(score_surface, NULL, ecran, &pos_score);
      sprintf(buffer_time, "Time:%d", (int)(temps - SDL_GetTicks()) / 1000);
      time_surface = TTF_RenderText_Solid(font, buffer_time, color);
      SDL_BlitSurface(time_surface, NULL, ecran, &pos_timer);
      // if (perfectPixelCollision(platform, joueurs[0].pos))
      // {
      //     joueurs[0].pos.x = (int)joueurs[0].pos_actuelle_x;
      // }
      // if (joueurs[0].pos.x >= 2500)
      // {
      //   enigme_2(ecran, &quitter);
      // }
      if (joueurs[0].pos.x >= 6000)
      {
        enigme_1(ecran, &quitter);
      }
      // SDL_BlitSurface(platform, NULL, ecran, &pos_platform);
    }
    if (quitter == 1)
    {
      SDL_Flip(ecran);
    }

    SDL_Delay(16);
  }

  SDL_FreeSurface(bg.image);
  liberer_enemy(&sengo);
  SDL_FreeSurface(health_img);
  Mix_FreeChunk(heal_sound);
  freeMiniMap(&minimap);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_FreeSurface(score_surface);
  SDL_FreeSurface(backgroundMask);
  for (int i = 0; i < nb_joueurs; ++i)
  {
    liberation(&joueurs[i]);
  }
  IMG_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
