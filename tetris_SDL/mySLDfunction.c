#include <stdlib.h>

#include "mySDLfunction.h"

void logSDLError(FILE * file, char * msg_err){
	fprintf(file, "%s Error : %s", msg_err, SDL_GetError());
}

SDL_Texture* loadTexture(char * fileName, SDL_Renderer *ren){

	SDL_Texture *texture = NULL;
	//ladowanie bmp
	SDL_Surface *loadedImage = SDL_LoadBMP(fileName);
	//jesli ladowanie sie powiodlo, przekonwertuj na teksture i ja zwroc
	if (loadedImage != NULL){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//sprawdzenie czy wszystko poszlo ok
		if (texture == NULL)
			logSDLError(stderr, "CreateTextureFromSurface");
	}
	else
		logSDLError(stderr, "LoadBMP");

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *src){
	//Wartosci wspolrzednych na ktorych zakonczone bedzie wczytywanie
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//if (src != NULL) { //dlugosc i wysokosc obiektu rysowanego na ren, ma byc taka sama jak "pobrana" z tex
		dst.w = src->w; 
		dst.h = src->h;


		SDL_RenderCopy(ren, tex, src, &dst);
}

sSDLvar * initSDLToStartGame(void){

	sSDLvar *SDLvar;

	SDLvar = (sSDLvar *)malloc(sizeof(sSDLvar));

	///INICJALIZACJA SDL I PODST KOMPONENTOW
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(stderr, "SDL Init");
		return 1;

	};

	SDL_Window *window = SDL_CreateWindow("tetris", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		logSDLError(stderr, "SDL CreateWindow");
		return 2;
	};

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL){
		logSDLError(stderr, "SDL CreateRenderer");
		return 3;
	};

	//////////////////////////////////////

	//ladowanie pliku bmp ze wzorami
	SDL_Texture *tex = loadTexture("./sprite/sheet.bmp", renderer);
	if (tex == NULL)
		return 4;

	///czyszczenie/ rysowanie tla (105,105,105) - szary
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
	////////////

	
	SDL_Rect info;
	info.x = 40;
	info.y = 0;
	info.h = 120;
	info.w = 60;
	/////
	//rysowanie informacji o klawiszach
	renderTexture(tex, renderer, 40, 40, &info);
	SDL_RenderPresent(renderer);


	SDLvar->renderer = renderer;
	SDLvar->tex = tex;
	SDLvar->window = window;

	return SDLvar;
}