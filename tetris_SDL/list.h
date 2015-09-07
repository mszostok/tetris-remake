#ifndef _LIST_H_
#define	 _LIST_H_
#include "tetris.h"

//TYPE
//element listy
typedef struct elem{
	char * name;
	int score;
	int earnedLevel;
	struct elem *next, *prev;
}sElem;

//struktura listy
typedef struct {
	sElem *head, *tail;
	int count;
}sList;

/**Funkcja dodaje element na koncu listy
Argumenty wywo³ania:
 *wskaznik na liste,
 *element do wstawienia
*/
void pushBack(sList *, sGame *);

/**Funkcja ustawia wartosci poczatkowe listy
Zwracana wartosc:
 *wskaznik na zainicjowana liste
*/
sList * initLHistory(void);

/**Funkcja zapisuje liste do pliku, jesli plik  nie istnieje zostanie utworzony
Argumenty wywowlania:
 *wskaznik na liste do zapisania
*/
void saveHistory(sList *);

//TODO - czyszczenie listy
void releaseList(sList *);
#endif