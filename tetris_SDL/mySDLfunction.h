#ifndef _MYSDLFUNCTION_H_
#define	 _MYSDLFUNCTION_H_

#include <stdio.h>
#include "SDL.h"
#include "define.h"

//TYPE

typedef struct {
	SDL_Texture *tex;
	SDL_Renderer *renderer;
	SDL_Window *window;

}sSDLvar;


/**Funkcja wpisuje do okreslonego pliku typ bledu zwracanego przez SDL_GetError()
Argumenty wywolania:
 *wskaznik na plik
 *nazwa bledu ktory wystapil
*/
void logSDLError(FILE *, char *);

/**Funkcja laduje plik bmp i zwraca teskure
Argumenty wywolania:
 *nazwa pliku
 *wskaznik na render
*/
SDL_Texture* loadTexture(char *, SDL_Renderer *);

/**Funkcja wyrysowywuje element na plotnie
Argumenty wywolania:
 *wskaznik na teksture
 *wskaznik na render
 *wspolrzedne na ktorych ma zostac wyrysowany obiekt
 *wspolrzedne na ktorych znajduje sie obiekt na teksturze
*/
void renderTexture(SDL_Texture *, SDL_Renderer *, int , int , SDL_Rect *);

/**Funkcja inicjalizuje wszystkie komponenty SDL
Zwracana wartosc:
 *strukura z wskaznikami na render, window oraz teksture z wczytanym plikiem sheet.bmp
*/
sSDLvar * initSDLToStartGame(void);
#endif