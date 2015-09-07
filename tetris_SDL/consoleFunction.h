#ifndef _CONSOLEFUNCTION_H_
#define _CONSOLEFUNCTION_H_

/**Funkcja zwraca wskaznik na "string" z danymi zgodnymi z parametrami wywolania programu
Argumenty wywylania:
 *liczba argumentow wywloania programu,
 *tablica z argumentami wywolania programu
*/
char *getParam(int, char *argv[]);

#endif