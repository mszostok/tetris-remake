#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <stdbool.h>


#include "define.h"
#include "SDL.h"
#include "mySDLfunction.h"


//TYPE

//struktura zawierajaca poszczegolne skladowe elementu
typedef struct
{
	int posX;
	int posY;
	int rotation;
	int color;
	int state;
	bool(*shape)[COL][ROWS];
}sElements;

//struktura zawieracja sladowe gry
typedef struct{
	sElements *element;
	int level,score;
	char *playerName;
}sGame;



//FUNCTION


/**Funkcja inicjuje zmienna sElement, oraz podstawowe informacje odnoscie rozpoczynanej gry(level, score, nickName)
Zwracana wartosc:
 *wskaznik na strukture z gra
*/
sGame *initGame(char *);

/**Funkcja sprawdza czy plansza do gry zostala zapelniona
Zwracana wartosc:
 *0 - jesli jest jeszcze miejsce, 
 *1 - jesli najwyzszy poziom jest juz zapelniony
*/
int isFull(void);

/**Funkcje kolejno sprawdzaja czy element jest juz na dole, calkowice z prawej strony czy tez calkowicie z lewej
Argumenty wywolania:  
 *wskaznik na element ktory nalezy sprawdzic
Zwracana wartosc:
 *0 - jesli mozna przesunac element w okreslonym kierunku; 
 *1 - jesli nie mozna przesunac juz elementu
*/
bool isAtBottom(sElements *);
bool isAtRight(sElements *);
bool isAtLeft(sElements *);


/**Funkcja sprawdza czy wybrany element mo¿ne zostac obrocony i czy nie wywola to kolizji z elementami znajdujacymi siê juz na planszy.
Argumenty wywolania: 
*element do sprawdzenia (dlatego nie jest to wskaznik, poniewaz zmieniana bêdzie wartosc 
rotation tego elementu a poki funkcja sie nie wykona nie ma pewnosci czy moze byc ona trwale zmieniona,
wiec lepiej wykonac ta operacje na kopii);
Zwracana wartosc: 
*0 - jesli element nie moze zostac obrocony, 
*1 - jesli element moze zostac obrocony;
*/
bool canRotate(sElements );



/**Funkcje kolejno: przesuwa element w dol, opuszcza element calkowicie w dol
Argumenty wywolania:
 *wskaznik na rozgrywana aktualnie gre,
 *wskaznik na strukture zawierajaca wskazniki na texture oraz render
 *wskaznik na strukture zawierajaca: wspolrzedne na ktorych znajduje sie dany element na tex, oraz jego wysokosc i szerokosc
*/
void moveDown(sGame *, sSDLvar *, SDL_Rect *);
void dropElem(sGame *, sSDLvar *, SDL_Rect *);


/**Funkcje przesuwaja element kolejno w prawo i w lewo,
Argumenty wywolania:
 *wskaznik na strukture zawierajaca wskazniki na texture oraz render
 *wskaznik na strukture zawierajaca : wspolrzedne na ktorych znajduje sie dany element na tex, oraz jego wysokosc i szerokosc
*/
void moveRight(sElements *, sSDLvar *, SDL_Rect *);
void moveLeft(sElements *, sSDLvar *, SDL_Rect *);


/**Funkcja wywoluje funkcje canRotate i zmienia zmienna struktury elementu 'rotation' jesli jest taka mozliwosc i rysuje
go na planszy w zmienionej rotacji.
Argumenty wyowalnia: 
 *wsk na element ktory ma ulec rotacji
*/
void rotateElem(sElements *);


/**Funkcja rysuje element na planszy
Argumenty wywolania:
 *wskaznik na element do rysowania
 *wskaznik na strukture zawierajaca wskazniki na texture oraz render
 *wskaznik na strukture zawierajaca : wspolrzedne na ktorych znajduje sie dany element na tex, oraz jego wysokosc i szerokosc
*/
void drawElem(sElements *, sSDLvar *, SDL_Rect *);


/** funkcja rysuje tablice world tylko o kreslonych wspolrzednych
*arg wywolania kolejno: minX, minY, maxX, maxY
*wsk na strukture zawierajaca wsk na texture oraz render
*wsk na strukture zawierajaca : wspolrzedne na ktorych znajduje sie dany element na tex, oraz jego wysokosc i szerokosc
*/
void drawWorld(int, int, int, int, sSDLvar *, SDL_Rect *);


/**funkcja "laczy" element z tablica world, uzywana gdy element nie moze byc juz dalej przesuwany
*arg wywolania: wsk na element do polaczenia
*/
void joinToWorld(sElements *); // tylko dla tetris.c


/**fukcja losuje kolejny wzor elementu z tablicy tabShape oraz kolor elementu
*ustawia rowniez zmienne gry na poczatkowe  //RESTART
*arg wywolania:
*wsk na element do ktorego ma zostac przypisany wzor oraz kolor
*/
void randShape(sElements *);

/**Funkcja sprawdza czy element po opadnieciu przypadkiem nie zapelnil calego wiersza na ktorym to wyladowal,
jesli tak to wywoluje funkcje czyszczaca wiersz ktory zostal zapelniony,
w przeciwnym wypadku sprawdza dalej aa przeszuka wszystkie wiersze na ktorych znajduje sie ostatni opadniety element.
Argumenty wywolania funkcji :
 *indeks wiersza ktory nalezy sprawdzic,
 *liczba dokonywanych sprawdzen, 
 *liczba usunietych wierszy,
 *wskaznik na strukture SDLvar zawieraj¹ca wskaznik na teksture oraz render
 *wskaznik na tablice SDL_Rect, która to zawiera wspolrzedne i dlugosci poszczegolnych elementow znajdujacych sie na teksturze
Zwracana wartoœæ :
 *liczba usunietych wierszy;
*/
int checkRow(int, int, int, sSDLvar *, SDL_Rect *);


/**funkcja czysci wiersz i przesuwa gorne elementy w stosunku do wiersza usuwanego o jeden wiersz w dol
arg wywolania: wiersz do usuniecia
*/
void cleanRow(int);

//TODO -opis
/** funkcja rysujaca ramke zarowno na matrixie jak i na renderze
*wsk na strukture zawierajaca : wspolrzedne na ktorych znajduje sie dany element na tex, oraz jego wysokosc i szerokosc
* wsk na tablice Rect zawieraca wspolrzedne i wymiary poszczegolnych blokow na tex
*/
void drawFrame(sSDLvar *, SDL_Rect *);


//TODO -opis
/**funkcja czeka az uzytkownik nacisnie jeden z dostepnych klawisz po kiedy nastapila przegrana
dostepne klawisze:
F11 - restart gry;
ESC - wyjscie z gry; //wczesniejesze zapisanie wynikow
Zwracana wartosc:
0 - jesli uzytkownik chce grac dalej;
1 - jesli ma nastapic zamkniece okna;
*/
int gameOver();

//TODO -opis
/**funkcja odpowiedzialna jest za zrestartowanie gry; zwalnia strukture element oraz gre i tworzy nowe zwracajac tym samym
wskaznik na nowa gre oraz zrestartowane wartosci elementu;
Zwracana wartosc:
wskaznik na nowa gre
*/
sGame *restartGame(sGame *, sSDLvar *, SDL_Rect *);


//TODO -opis
/**funkcja czysci cala tablice world tj ustawia wszystkie wartosci poza ramka na 0;
*/
void cleanWorld(void);


void changeLevel(sGame *);
#endif