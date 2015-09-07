#include "list.h"
#include "tetris.h"
#include <stdlib.h>
#include <stdio.h>

void pushBack(sList * list, sGame *game ){
	sElem *newElem;

	newElem = (sElem*)malloc(sizeof(sElem));

	newElem->earnedLevel = game->level;
	newElem->name = game->playerName;
	newElem->score = game->score;

	newElem->next = NULL;
	newElem->prev = list->tail;
	list->tail = newElem;

	if (newElem->prev)
		newElem->prev->next = newElem;
	else 
		list->head = newElem;
	++list->count;
}

sList * initLHistory(void){
	sList *list;
	
	list = (sList *)malloc(sizeof(sList));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;

}

void saveHistory(sList *history){

	FILE *fdst;
	sElem *actualElem = history->head;
	if ((fdst = fopen("history.txt", "a"))) { //proba otwarcia pliku z historia

		while (actualElem != NULL) {
			fprintf(fdst, "\n\nNazwa gracza: %s\tZdobyty poziom: %d\tUzyskany wynik:%d\t",
				actualElem->name, actualElem->earnedLevel, actualElem->score);
			actualElem = actualElem->next;
		};
		fclose(fdst);
	}
	else {
		fprintf(stderr, "Blad otwarcia pliku do odczytu!");
	};

}

void releaseList(sList *list){

	sElem *elemNext, *elemActual = list->head;

	 while (elemActual != NULL) {

		 elemNext = elemActual->next;
		 free(elemActual);

		 if (elemActual = elemNext){
			 break;
		 }
	 };

	 free(list);
}