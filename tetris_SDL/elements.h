#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_
#include <stdbool.h>
#include "tetris.h"
#include "define.h"

//tablica zawierajaca plansze gry
int world[M_Y][M_X];

//tablica zawierajaca wszystkie elementy oraz ich mozliwe rotacje
bool tabShape[SHAPE][ROTATION][ROWS][COL];


#endif