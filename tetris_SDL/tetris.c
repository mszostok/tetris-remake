#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include "tetris.h"
#include "elements.h"
#include "define.h"
#include "SDL.h"
#include "mySDLfunction.h"

//function
int maxRowElem(sElements *);


sGame *initGame(char *name){
	sGame *game;
	sElements *element;

	game = (sGame *)malloc(sizeof(sGame));
	element = (sElements*)malloc(sizeof(sElements));

	randShape(element);
	game->element = element;
	game->level = 1;
	game->score = 0;
	game->playerName = name;
	return game;
};



//zrobione !!
bool isAtBottom(sElements *element){

	int row, col, elem;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++){
			if (element->shape[element->rotation][row][col]){
				elem = world[element->posY + (row + 1)][element->posX + col];
				if (elem > 0 && elem < 6) return 1;
			}
		}
	}

	return 0;
};

bool isAtRight(sElements *element){
	int row, col,elem;
	for (col = 3; col >= 1; col--) {
		for (row = 0; row <= 3; row++){
			if (element->shape[element->rotation][row][col]){
				elem = world[element->posY + row][element->posX + (col + 1)];
				if (elem > 0 && elem < 6) return 1;
			}
		}
	}

	return 0;
}

bool isAtLeft(sElements *element){
	int row, col, elem;
	for (col = 0; col <= 3; col++) {
		for (row = 0; row <= 3; row++){
			if (element->shape[element->rotation][row][col]){
				elem = world[element->posY + row][element->posX + (col - 1)];
				if (elem > 0 && elem < 6) return 1;
			}
		}
	}

	return 0;
}

bool canRotate(sElements element){
	element.rotation++;

	int row, col;
	for (row = 0; row <  4; row++){
		for (col = 0; col < 4; col++){
			if (element.shape[element.rotation][row][col] == 1){
				if (world[element.posY + row][element.posX + col] != 0)
					return 0;
			};
		};
	};

	return 1;
}


//zrobione !!
void moveDown(sGame *game, sSDLvar *SDLvar, SDL_Rect(sheet)[SHEET_COUNT]){
	bool collision;
	int i, xR, yR, earnRow;
	sElements *element = game->element;

	collision = isAtBottom(element);
	if (!collision) {
		for (i = 0; i < 4; i++)	{
			if (element->posY < 0 || element->posY >= M_Y) continue;
			if (world[element->posY][element->posX + i] == 0) {
			
				xR = M_XonWINDOW + ((element->posX * SHEET_W) + (i * SHEET_W)); //iW to skala czyli jak duza jest pojedyncza komorka na matrixie
				yR = M_YonWINDOW + (element->posY * SHEET_H);
				renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, &sheet[0]);

			}

		}
		element->posY++;
	}
	else {
		joinToWorld(element);
		i = maxRowElem(element);
		earnRow = checkRow((element->posY + i),0, 0, SDLvar, sheet);
		element->state = CREATENEW; 
		game->score += (game->level * 2) + (game->level * (earnRow *10));
	}
		

}

void moveRight(sElements *element, sSDLvar *SDLvar, SDL_Rect *sheet){
	bool collision;
	int row, xR, yR;

	collision = isAtRight(element);
	if (!collision){

		for (row = 0; row <= 3; row++){
			if (((element->posY + 3) < element->posY) || element->posY > M_Y) continue; //potrzebne bo zaczynamy z elem poza obczarem tj. Y = -4
			if (world[element->posY + row][element->posX] == 0) {
				xR = M_XonWINDOW + ((element->posX) * SHEET_W); //iW to skala czyli jak duza jest pojedyncza komorka na matrixie
				yR = M_YonWINDOW + (element->posY * SHEET_H) + (row * SHEET_H);
				renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, sheet); //wsk na prostokat na puste pole
			};
		};
		element->posX++;
	};

}

void moveLeft(sElements *element, sSDLvar *SDLvar, SDL_Rect *sheet){
	bool collision;
	int row, xR, yR;


	collision = isAtLeft(element);
	if (!collision){
		for (row = 0; row <= 3; row++) {
			if ( ((element->posY + 3) < element->posY) || element->posY > M_Y) continue;

			// +3 do wymiaru X bo rozmiar elementu jest 4jednostki, a spr jest obszar po prawej
			if (world[element->posY + row][element->posX + 3] == 0) {// jesli na planszy po lewej str nie ma elementow
				// to nalezy wyczyscic bo funkcja moveDown bedzie przesuwala element na kolejnym X i nie bd mogla nadpisac obrazu
				xR = M_XonWINDOW + (element->posX * SHEET_W) +(3*SHEET_W); // 3 -bo tam sprawdzamy pole, SHEET_W skala do przerysowania
				yR = M_YonWINDOW + (element->posY * SHEET_H) + (row * SHEET_H);
				renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, sheet);
								
			};
		};
		element->posX--;
	};

}

void rotateElem(sElements *element){

	bool collision;
	collision = !(canRotate(*element));
	if (!collision){
		if (element->rotation < 3) {
			element->rotation++; //nastepna rotacja
		}
		else {
			element->rotation = 0; //restart rotacji, zaczynamy od poczatku
		};
	};


}

void dropElem(sGame *game, sSDLvar *SDLvar, SDL_Rect(sheet)[SHEET_COUNT]){

	while (game->element->state != CREATENEW){
		moveDown(game, SDLvar, sheet);
		if (game->element->state != CREATENEW){
			drawElem(game->element, SDLvar, sheet);
			SDL_Delay(1000 / 20);
		};
	};
}


void joinToWorld(sElements *element){
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++){
			if (element->shape[element->rotation][i][j] == true)
				world[element->posY + i][element->posX + j] = element->color;
		};
	};
}

//zrobione !!
void drawElem(sElements * element, sSDLvar *SDLvar, SDL_Rect(sheet)[SHEET_COUNT]){
	int row, col, xR, yR;

	for (row = element->posY; row < element->posY + 4; row++) {
		//dalej jesli wystapilo wyjscie poza zakres tablicy
		if (row < 0 || row >= M_Y) continue;
		for (col = element->posX; col < element->posX + 4; col++) {
			//dalej jesli wystapilo wyjscie poza zakres tablicy
			if (col < 0 || col >= M_X) continue;

			if (element->shape[element->rotation][row - element->posY][col - element->posX] == true){
				xR = M_XonWINDOW + (col * SHEET_W); //iW to skala czyli jak duza jest pojedyncza komorka na matrixie
				yR = M_YonWINDOW + (row * SHEET_H);
				renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, &sheet[element->color] );
			}
			else if (world[row][col] == 0){
				xR = M_XonWINDOW + (col * SHEET_W); //iW to skala czyli jak duza jest pojedyncza komorka na matrixie
				yR = M_YonWINDOW + (row * SHEET_H);
				renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, &sheet[0]); //czyszczenie, dlatego sheet[0]

			};
		};
	};
	SDL_RenderPresent(SDLvar->renderer);
}

void drawWorld(int minX, int minY, int maxX, int maxY, sSDLvar *SDLvar, SDL_Rect(sheet)[SHEET_COUNT]){
	int row, col, xR, yR, elemNumber;

	for (row = minY; row < maxY-1; row++){
		for (col = minX+1; col < maxX-1; col++) {
			xR = M_XonWINDOW + (col * SHEET_W);
			yR = M_YonWINDOW + (row * SHEET_H);
			elemNumber = world[row][col];

			renderTexture(SDLvar->tex, SDLvar->renderer, xR, yR, &sheet[elemNumber]);
		};
	};
	SDL_RenderPresent(SDLvar->renderer);
	SDL_Delay(1000 / 3);
}

void drawFrame(sSDLvar *SDLvar, SDL_Rect (sheet)[SHEET_COUNT]){
	int row, col, x, y;


	for (row = 0; row < M_Y-1; row++) {
		world[row][0] = 1;
		world[row][M_X - 1] = 1;
		// wspolrzedna matrixa w oknie dodac przeskalowana wspolrzedna komorki o jej wyswietlany rozmiar
		y = M_YonWINDOW + (row *SHEET_H); 
		//rysowanie lewej strony ramki
		renderTexture(SDLvar->tex, SDLvar->renderer, M_XonWINDOW, y, &sheet[6]);

		//koncowa wspolrzedna matrixa wyswietlanego w oknie
		x = M_XonWINDOW + (M_X - 1) * SHEET_W;
		//rysowanie prawej str ramki
		renderTexture(SDLvar->tex, SDLvar->renderer, x, y, &sheet[7]);
	};
	//zmiana wsp y na maksymalna
	y = M_YonWINDOW + (M_Y - 1) * SHEET_H;

	for (col = 1; col < M_X-1; col++){
		world[M_Y - 1][col] = 1;

		x = M_XonWINDOW + (col * SHEET_W);
		renderTexture(SDLvar->tex, SDLvar->renderer, x, y, &sheet[8]);
	};

	SDL_RenderPresent(SDLvar->renderer);
}



void randShape(sElements *element) {
	int number, seed;
	seed = time(NULL);
	srand(seed);

	number = rand() % (SHAPE); //<0,6> //tutaj duzy blad // bylo od <0,7> 
	element->shape = tabShape[number];

	number = 1 + (rand() % 5); //<1,5>
	element->color = number;

	//RESET
	element->posX = STARTX;
	element->posY =  -3;
	element->rotation = 0;
	element->state = OK;
}

int isFull(void){
	int i;
	for (i = STARTX; i < STARTX + 4; i++) //sprawdzam tylko góre i to w tym mc gdzie moze byc nastepny elem
	if (world[1][i])
		return FULLWORLD;

	return 0;
}

int maxRowElem(sElements *element){
	int row, col;
	for (row = 3; row >= 0; row--){
		for (col = 0; col <= 3; col++)
		if (element->shape[element->rotation][row][col])
			return row;
	}
	return row;
}

int checkRow(int row, int earnRow, int count, sSDLvar *SDLvar, SDL_Rect(sheet)[SHEET_COUNT]){
	int col = 0, full = 1;
	if (count < 4) {
		for (col = 1; col < M_X-1; col++){
			if (world[row][col] == 0) {
				full = 0;
				break;
			};
		};

		if (full){
			cleanRow(row);
			drawWorld(0, 0, M_X, M_Y, SDLvar, sheet);
			++count;
			++earnRow;
			checkRow(row, earnRow, count, SDLvar, sheet); //wiersze opadly wiec trzeba spr jeszcze raz ten sam wiersz
		}
		else {
			++count;
			--row; //spr w gore nastepnych wierszy
			checkRow(row, earnRow, count, SDLvar, sheet);
		};

	};
	return earnRow;
}

void cleanRow(int rowRemove){
	int col = 0, row = 0;
	for (col = 1; col < M_X - 1; col++){//col = 1 wynika z tego ze jeszcze na matrixie jest ramka
		for (row = rowRemove; row >0; row--) {
			world[row][col] = world[row - 1][col];
		};
	};

}

void cleanWorld(void){
	int row, col;
	for (row = 0; row < M_Y - 1; row++){ //-2 poniewaz ramka zostaje
		for (col = 1; col < M_X - 1; col++)
			world[row][col] = 0;
	};
}



int gameOver(void){
	SDL_Event e;

	while (SDL_WaitEvent(&e)){

		if (e.type == SDL_QUIT)
			return true;

		if (e.type == SDL_KEYDOWN){
			switch (e.key.keysym.sym){
			case SDLK_F1 :
				return false;
				break;
			case SDLK_ESCAPE:
				return true;
				break;
			default:
				continue;
				break;
			};
		};
	};
	return 0;
}

sGame * restartGame(sGame *game, sSDLvar *SDLvar, SDL_Rect (sheet)[SHEET_COUNT]){
	sGame *newGame;
	char *name;
	name = game->playerName;
	cleanWorld();
	drawWorld(0, 0, M_X, M_Y, SDLvar, sheet);
	free(game->element);// zwalnianie pamieci przydzielonej na poczatku tworzenia gry
	free(game);
	newGame = initGame(name);

	return newGame;

}

void changeLevel(sGame *game){

	int score = game->score;
	if ((score <= 2000) && (score >= game->level *200)){
		game->level++;
	};
}
