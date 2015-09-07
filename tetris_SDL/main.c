#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "tetris.h"
#include "define.h"
#include "mySDLfunction.h"
#include "SDL.h"
#include "list.h"


int main(int argc, char**argv){

	//inicjalizacja gry i zmiennych pom.
	sSDLvar *SDLvar = NULL;
	SDL_Event e;
	bool quit = 0;

	sGame *game;
	sList *LHistory;
	char *name;
	double delay = 0.5;
	double Tnow, Tdrop;

	// pobranie aktualnego czasu w milisekundach
	Tdrop = SDL_GetTicks();

	//inicjalizacja listy historii
	LHistory = initLHistory();

	//inicjalizacja SDL (window, renderer, texture)
	SDLvar = initSDLToStartGame();

	//spr parametrow wywolani programu i przypisanie nazwy gracza
	name = getParam(argc, argv);
	///inicjalizacja gry (name, element, score, level)
	game = initGame(name);
	
	//tablica zawierajace wzory elementow indeksy od 0 do 5 zawieraja kolory klockow, od 6 do 8 wzorzec ramki, od 9 do 11 (puste)
	SDL_Rect sheet[SHEET_COUNT];

	for (int i = 0; i < SHEET_COUNT; ++i){
		sheet[i].x = i / 6 * SHEET_W;
		sheet[i].y = i % 6 * SHEET_H;
		sheet[i].w = SHEET_W;
		sheet[i].h = SHEET_H;
	};


	//rysowanie ramki matrixa i zmieniene skrajnych elementow tablicy matrixa tj. stworzenie ramki z "1"
	drawFrame(SDLvar, sheet);
	//////


	while (!quit){

		if (game->element->state == CREATENEW) {
			//spr czy plansza jest pusta
			if (isFull() == 0) randShape(game->element);

			else {// pelna plansza, wiec dodaje gre do listy historii
				pushBack(LHistory, game);
				//spr czy uzytkownik chce grac dalej
				if (gameOver() == true){ //jesli koniec gry to nalezy zapisac historie w pliku
					saveHistory(LHistory);
					quit = 1;
					break;
				}
				else if (gameOver() == false){//jesli uzytkownik chce gra dalej nastepuje restart gry(wszystkich zmiennych)
					game = restartGame(game, SDLvar, sheet);
				};
			};
		};
		Tnow = SDL_GetTicks();
		if ( (Tnow - Tdrop) > delay) {
			moveDown(game, SDLvar, sheet);
			if (game->element->state != CREATENEW){
				drawElem(game->element, SDLvar, sheet);
			};
			Tdrop = SDL_GetTicks();
		};
		///przechwycenie nacisnietych klawiszy
		while (SDL_PollEvent(&e)){

			if (e.type == SDL_QUIT){//przy zamknieciu program nastepuje zapis historii czyli wyniku uzyskanego w trakcie zamykania
				pushBack(LHistory, game);
				saveHistory(LHistory);
				quit = true;
			};

		if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
				case SDLK_a :
				case SDLK_LEFT:
					moveLeft(game->element, SDLvar, &sheet[0]);
					break;

				case SDLK_d:
				case SDLK_RIGHT:
							moveRight(game->element, SDLvar, &sheet[0]);
					break;
				case SDLK_DOWN:
							moveDown(game, SDLvar, sheet);
					break;
				case SDLK_s:
				case SDLK_SPACE:
							dropElem(game, SDLvar, sheet);
					break;

				case SDLK_w:
				case SDLK_UP:
							rotateElem(game->element);
					break;

				case SDLK_F1:
							game = restartGame(game, SDLvar, sheet);
					break;

				case SDLK_ESCAPE:
							pushBack(LHistory, game);
							saveHistory(LHistory);
							quit = true;
					break;
				default:
					break;
				};
			};
		};
		/////////////////////////

		/**
		*potrzebne ze wzgledu na funkcje opdajaca
		*inaczej wyrysuje element ktory juz nie istnieje na matrixie */
		if (game->element->state != CREATENEW)
			drawElem(game->element, SDLvar, sheet);
		
		//zmiana poziomu gry jesli uzytkownik przekroczyl okreslona liczbe pkt
		changeLevel(game);
		delay = ((11 - game->level) * 70);
	};



	free(game->element);// zwalnianie pamieci przydzielonej na poczatku tworzenia gry
	free(game);
	releaseList(LHistory);
	

	SDL_DestroyTexture(SDLvar->tex); //zwalniam zmienne zwiazane z SDL
	SDL_DestroyRenderer(SDLvar->renderer);
	SDL_DestroyWindow(SDLvar->window);
	SDL_Quit();
	free(SDLvar);

	return 0;
}