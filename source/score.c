#include "score.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "quiz.h"
void score2(SDL_Surface *ecran, int *run, int *initial_menu)
{
	int show_new_interface = 0;
	int mouseX, mouseY;
	int inside_button;
	int inside_button2;
	int inside_confirm;
	int inside_return;
	Uint8 mouseState;
	Mix_Music *musique = NULL;
	SDL_Surface *current_button;
	SDL_Surface *current_button2;
	SDL_Surface *image, *button, *buttons, *button2, *buttons2, *re = NULL;
	SDL_Surface *text = NULL;
	TTF_Font *font = NULL;
	int quitter = 1;
	SDL_Rect posbg;
	SDL_Rect posb, posb2, pos2;
	SDL_Rect posre, posconf, posscore, posname;
	SDL_Color Color;
	SDL_Event event;
	Mix_Chunk *tick = NULL;
	SDL_Surface *button_hover, *button2_hover;
	SDL_Surface *text_return = NULL;
	SDL_Surface *text_return_hover = NULL;
	SDL_Surface *text_confirm = NULL;
	SDL_Surface *text_confirm_hover = NULL;
	SDL_Surface *text_score = NULL;
	SDL_Surface *text_name = NULL;
	SDL_Color white = {255, 255, 255};
	SDL_Color red = {255, 0, 0};
	posre.x = 100;
	posre.y = 980;
	posconf.x = 1700;
	posconf.y = 980;
	posname.x = 740;
	posname.y = 420;
	posscore.x = 800;
	posscore.y = 330;

	image = affichage("../assets/backgrounds/bgscore.jpg", &posbg);
	button = affichageb("../assets/buttons/button.png", &posb);
	button2 = affichageb2("../assets/buttons/button2.png", &posb2);

	button_hover = affichageb("../assets/buttons/buttons.png", &posb);
	button2_hover = affichageb2("../assets/buttons/buttons2.png", &posb2);

	font = affichage_text2("../assets/fonts/HARRYP.TTF");

	text_return = TTF_RenderText_Solid(font, "RETURN", white);
	text_return_hover = TTF_RenderText_Solid(font, "RETURN", red);
	text_confirm = TTF_RenderText_Solid(font, "CONFIRM", white);
	text_confirm_hover = TTF_RenderText_Solid(font, "CONFIRM", red);
	font = affichage_score("../assets/fonts/HARRYP.TTF");
	text_score = TTF_RenderText_Solid(font, "SCORE", white);
	font = affichage_name("../assets/fonts/HARRYP.TTF");
	text_name = TTF_RenderText_Solid(font, "NICKNAME", white);
	tick = Mix_LoadWAV("../assets/audio/tick.wav");
	if (!text_return || !text_confirm || !text_score)
	{
		printf("Error rendering text: %s\n", TTF_GetError());
	}
	while (quitter && *run)
	{
		while (SDL_PollEvent(&event) && quitter && *run)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quitter = 0;
				*run = 0;
				break;
			case SDL_KEYDOWN:
			{
				if (event.key.keysym.sym == SDLK_e)
				{
					menu_quiz(ecran, run);
				}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quitter = 0;
					*run = 0;
				}
			}
			break;
			}
			if (quitter && *run)
			{
				mouseState = SDL_GetMouseState(&mouseX, &mouseY);
				inside_button = mousehover(posb);
				inside_button2 = mousehover(posb2);
				current_button2 = inside_button2 ? button2_hover : button2;
				inside_confirm = mousehover(posconf);
				inside_return = mousehover(posre);
				if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					if (inside_confirm && !show_new_interface)
					{

						SDL_FreeSurface(image);
						image = affichage("../assets/backgrounds/bgscore.jpg", &posbg);
						musique = Mix_LoadMUS("../assets/audio/theme.mp3");
						Mix_PlayMusic(musique, -1);
						Mix_PlayChannel(-1, tick, 0);
						show_new_interface = 1;
					}
					else if (inside_confirm && show_new_interface == 1)
					{
						menu_quiz(ecran, run);
					}

					if (inside_return && (show_new_interface == 1))
					{
						SDL_FreeSurface(image);
						image = affichage("../assets/backgrounds/bgscore.jpg", &posbg);
						show_new_interface = 0;
					}
					if (inside_return && (show_new_interface == 0))
					{
						quitter = 0;
					}
				}
				current_button = inside_button ? button_hover : button;

				afficher_ecran(image, &posbg, ecran);
				if (show_new_interface)
				{
					SDL_BlitSurface(inside_return ? text_return_hover : text_return, NULL, ecran, &posre);
					SDL_BlitSurface(inside_confirm ? text_confirm_hover : text_confirm, NULL, ecran, &posconf);
					afficher_ecran(current_button2, &posb2, ecran);
					SDL_BlitSurface(text_score, NULL, ecran, &posscore);
				}
				else
				{
					afficher_ecran(current_button, &posb, ecran);
					SDL_BlitSurface(inside_return ? text_return_hover : text_return, NULL, ecran, &posre);
					SDL_BlitSurface(inside_confirm ? text_confirm_hover : text_confirm, NULL, ecran, &posconf);
					SDL_BlitSurface(text_name, NULL, ecran, &posname);
				}
				SDL_Flip(ecran);
			}
		}
	}

	liberer2(image, font, tick, *run);
	Mix_FreeMusic(musique);
	*initial_menu = 0;
}
