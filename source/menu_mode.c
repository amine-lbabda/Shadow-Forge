#include <stdio.h>
#include "menu_mode.h"
#include "score.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
void menu_mode(SDL_Surface *ecran, int *run, int *initial_menu)
{
	Mix_Music *music_theme;
	Mix_Chunk *music_click;
	image background;
	image background_secondaire;
	image button_mono;
	image button_multi;
	image button_clicked;
	image button_clicked_mono;
	image button_clicked_multi;
	image button_name_1;
	image button_name_1_clicked;
	image button_name_2;
	image button_name_2_clicked;
	image return_image;
	image return_image_clicked;
	image confirm_image;
	image confirm_image_clicked;
	SDL_Event e;
	text Text;
	text button_mono_text;
	text button_multi_text;
	text button_name_1_text;
	text button_name_2_text;
	text avatar_1;
	text avatar_2;
	int confirm = 0;
	int confirm_score = 0;
	int quitter = 0;
	int affiche_multi = 1;
	int menu_mode = 0;
	int affiche_menu = 0;
	if (ecran == NULL)
	{
		printf("Erreur:%s\n", SDL_GetError());
	}
	else
	{
		music_theme = Mix_LoadMUS("../assets/audio/theme_menu.mp3");
		music_click = Mix_LoadWAV("../assets/audio/click_menu.wav");
		background.image = load_image("../assets/backgrounds/bg_secondaire.png");
		background_secondaire.image = load_image("../assets/backgrounds/bg_secondaire.png");
		button_mono.image = load_image("../assets/buttons/button_1.png");
		button_multi.image = load_image("../assets/buttons/button_1.png");
		button_clicked.image = load_image("../assets/buttons/button_clicked.png");
		button_clicked_multi.image = load_image("../assets/buttons/button_clicked.png");
		button_name_1.image = load_image("../assets/buttons/button_1.png");
		button_name_2.image = load_image("../assets/buttons/button_1.png");
		button_name_2_clicked.image = load_image("../assets/buttons/button_clicked.png");
		return_image.image = load_image("../assets/buttons/RETURN.png");
		return_image_clicked.image = load_image("../assets/buttons/RETURN_clicked.png");
		confirm_image.image = load_image("../assets/buttons/CONFIRM.png");
		confirm_image_clicked.image = load_image("../assets/buttons/CONFIRM_clicked.png");
		if ((background.image == NULL) || (button_mono.image == NULL) || (button_multi.image == NULL) || (button_clicked.image == NULL) || (button_clicked_multi.image == NULL) || (return_image.image == NULL) || (return_image_clicked.image == NULL) || (confirm_image.image == NULL) || (confirm_image_clicked.image == NULL) || (background_secondaire.image == NULL) || (button_name_1.image == NULL) || (button_name_2.image == NULL) || (button_name_2_clicked.image == NULL))
		{
			printf("Erreur:%s\n", SDL_GetError());
		}
		else if ((music_theme == NULL) || (music_click == NULL))
		{
			printf("Erreur:%s\n", Mix_GetError());
		}
		else
		{
			position_image(0, 0, background.image->w, background.image->w, &background.posimage);
			background_secondaire.posimage = background.posimage;
			position_image(248, 523, button_mono.image->w, button_mono.image->h, &button_mono.posimage);
			position_image(248, 693, button_multi.image->w, button_multi.image->h, &button_multi.posimage);
			position_image(164, 423, button_clicked.image->w, button_clicked.image->h, &button_clicked.posimage);
			position_image(164, 595, button_clicked_multi.image->w, button_clicked_multi.image->h, &button_clicked_multi.posimage);
			position_image(48, 942, return_image.image->w, return_image.image->h, &return_image.posimage);
			position_image(48, 942, return_image_clicked.image->w, return_image_clicked.image->h, &return_image_clicked.posimage);
			position_image(1645, 960, confirm_image.image->w, confirm_image.image->h, &confirm_image.posimage);
			confirm_image_clicked.posimage = confirm_image.posimage;
			// button_name_1.posimage = button_mono.posimage;
			position_image(248, 599, button_name_1.image->w, button_name_1.image->h, &button_name_1.posimage);
			button_clicked_mono = button_clicked;
			position_image(158, 494, button_clicked_mono.image->w, button_clicked_mono.image->h, &button_clicked_mono.posimage);

			// button_name_1_clicked = button_clicked;
			position_image(248, 793, button_name_2.image->w, button_name_2.image->h, &button_name_2.posimage);
			position_image(164, 695, button_name_2_clicked.image->w, button_name_2_clicked.image->h, &button_name_2_clicked.posimage);
			button_mono_text.font = load_font("../assets/fonts/HARRYP.TTF", 60);
			if (button_mono_text.font == NULL)
			{
				printf("Erreur%s\n", SDL_GetError());
			}
			else
			{
				couleur_text(&Text.textcouleur, 255, 255, 255);
				couleur_text(&button_mono_text.textcouleur, 255, 255, 255);
				couleur_text(&button_multi_text.textcouleur, 255, 255, 255);
				button_mono_text.text = affichage_text(button_mono_text.font, "SINGLEPLAYER", button_mono_text.textcouleur);
				button_multi_text.text = affichage_text(button_mono_text.font, "MULTIPLAYER", button_multi_text.textcouleur);
				avatar_1.text = affichage_text(button_mono_text.font, "AVATAR 1", button_mono_text.textcouleur);
				avatar_2.text = affichage_text(button_mono_text.font, "AVATAR 2", button_multi_text.textcouleur);
				position_image(360, 480, 0, 0, &avatar_1.postext);
				position_image(360, 710, 0, 0, &avatar_2.postext);
				position_image(300, 361, 1014, 161, &Text.postext);
				position_image(320, 545, 69, 379, &button_mono_text.postext);
				position_image(320, 710, 434, 77, &button_multi_text.postext);
				Mix_PlayMusic(music_theme, -1);
				while (quitter == 0 && *run)
				{
					if (menu_mode == 0 && *run)
					{
						afficher(background.image, NULL, ecran, &background.posimage);
						afficher(button_mono.image, NULL, ecran, &button_mono.posimage);
						afficher(button_multi.image, NULL, ecran, &button_multi.posimage);
						aficher_text(button_mono_text.text, &button_mono_text.postext, ecran);
						aficher_text(button_multi_text.text, &button_multi_text.postext, ecran);
						afficher(return_image.image, NULL, ecran, &return_image.posimage);
					}
					else
					{
						afficher(background_secondaire.image, NULL, ecran, &background_secondaire.posimage);
						afficher(return_image.image, NULL, ecran, &return_image.posimage);
						if (affiche_multi == 0)
						{
							button_name_1_text.text = affichage_text(button_mono_text.font, "NAME 1", button_mono_text.textcouleur);
							position_image(385, 615, 578, 126, &button_name_1_text.postext);
							afficher(avatar_1.text, NULL, ecran, &avatar_1.postext);
							afficher(button_name_1.image, NULL, ecran, &button_name_1.posimage);
							aficher_text(button_name_1_text.text, &button_name_1_text.postext, ecran);
						}
						if (affiche_multi == 1 && *run)
						{
							button_name_1_text.text = affichage_text(button_mono_text.font, "NAME 1", button_mono_text.textcouleur);
							position_image(400, 615, 578, 126, &button_name_1_text.postext);
							position_image(400, 810, 1051, 81, &button_name_2_text.postext);
							button_name_2_text.text = affichage_text(button_mono_text.font, "NAME 2", button_multi_text.textcouleur);
							afficher(avatar_1.text, NULL, ecran, &avatar_1.postext);
							afficher(avatar_2.text, NULL, ecran, &avatar_2.postext);
							afficher(button_name_1.image, NULL, ecran, &button_name_1.posimage);
							afficher(button_name_2.image, NULL, ecran, &button_name_2.posimage);
							aficher_text(button_name_1_text.text, &button_name_1_text.postext, ecran);
							aficher_text(button_name_2_text.text, &button_name_2_text.postext, ecran);
						}
					}
					if (confirm == 1 && *run)
					{
						afficher(confirm_image.image, NULL, ecran, &confirm_image.posimage);
					}
					while (SDL_PollEvent(&e) && quitter == 0 && *run)
					{
						switch (e.type)
						{
						case SDL_QUIT:
							quitter = 0;
							*run = 0;
							break;

						case SDL_KEYDOWN:
						{
							if (e.key.keysym.sym == SDLK_ESCAPE)
							{
								quitter = 1;
								*run = 0;
							}
						}
						break;
						case SDL_MOUSEMOTION:
						{
							if (menu_mode == 0)
							{
								if (verif_collision(e, button_mono))
								{
									afficher(button_clicked.image, NULL, ecran, &button_clicked.posimage);
								}
								else if (verif_collision(e, button_multi))
								{
									afficher(button_clicked_multi.image, NULL, ecran, &button_clicked_multi.posimage);
								}
							}
							else
							{
								if (affiche_multi == 1 && verif_collision(e, button_name_2))
								{
									afficher(button_name_2_clicked.image, NULL, ecran, &button_name_2_clicked.posimage);
								}
								else if (verif_collision(e, button_name_1))
								{
									afficher(button_clicked_mono.image, NULL, ecran, &button_clicked_mono.posimage);
								}
							}
							if (verif_collision(e, return_image))
							{
								afficher(return_image_clicked.image, NULL, ecran, &return_image_clicked.posimage);
							}
							if (confirm == 1 && verif_collision(e, confirm_image))
							{
								afficher(confirm_image_clicked.image, NULL, ecran, &confirm_image_clicked.posimage);
							}
						}
						break;
						case SDL_MOUSEBUTTONDOWN:
						{
							if (menu_mode == 0)
							{
								if (verif_collision(e, button_mono))
								{
									menu_mode = 1;
									confirm = 1;
									affiche_multi = 0;
									affiche_menu = 1;
									Mix_PlayChannel(-1, music_click, 0);
								}
							}
							else
							{
								if (verif_collision(e, button_name_1))
								{
									Mix_PlayChannel(-1, music_click, 0);
								}
							}
							if (verif_collision(e, return_image))
							{
								menu_mode = 0;
								affiche_menu -= 1;
								Mix_PlayChannel(-1, music_click, 0);
								if (menu_mode == 0 && affiche_menu < 0)
								{
									quitter = 1;
								}
							}
							if (verif_collision(e, button_multi))
							{
								menu_mode = 1;
								affiche_multi = 1;
								confirm = 1;
								Mix_PlayChannel(-1, music_click, 0);
							}
							if (verif_collision(e, confirm_image))
							{
								Mix_PlayChannel(-1, music_click, 0);
								confirm_score = 1;
							}
							if (verif_collision(e, button_name_2))
							{
								Mix_PlayChannel(-1, music_click, 0);
							}
							if (confirm_score == 1 && verif_collision(e, confirm_image))
							{
								score2(ecran, run, initial_menu);
							}
						}
						break;
						}
						break;
					}
					SDL_Flip(ecran);
				}
			}
		}
	}
	liberer(background.image, button_mono.image, button_multi.image, button_name_1.image, button_name_2.image, button_mono_text.font);

	background.image = NULL;
	button_mono.image = NULL;
	button_multi.image = NULL;
	button_name_1.image = NULL;
	button_name_2.image = NULL;
	button_mono_text.font = NULL;

	Mix_FreeMusic(music_theme);
	music_theme = NULL;
	Mix_FreeChunk(music_click);
	music_click = NULL;
	SDL_FreeSurface(background_secondaire.image);
	background_secondaire.image = NULL;
	SDL_FreeSurface(button_clicked_mono.image);
	button_clicked_mono.image = NULL;
}
