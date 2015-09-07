#ifndef _DEFINE_H_
#define _DEFINE_H_


//rozmiar okna
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

//rozmiar matrixa
#define M_Y 20
#define M_X 12

//stale dotyczace wczytywanego pliku sheet.bmp
#define SHEET_W	20 //szerokosc pojedynczego bloku
#define SHEET_H	20 //wysokosc pojedynczego bloku
#define SHEET_COUNT 12 // ilosc komorek na jaki podzielony jest plik

//wspolrzedne wyrysowanego matrixa w oknie
#define M_YonWINDOW ( (SCREEN_HEIGHT/2) - (8*SHEET_W) )
#define M_XonWINDOW ( (SCREEN_WIDTH/2) - ((M_X*SHEET_W)/2) )


//stale okreslajace stan gry
#define CREATENEW -1 // oznacza ze nalezy wylosowac nowy element
#define FULLWORLD -30
#define OK 1

#define STARTX	M_X/2 //poczatkowa pozycja klocka (liczmy od lewej strony) (X -rozmiar matrixa nie okna)

//stale  okreslajace tablice tablice klockow
#define SHAPE  7 //liczba roznych elementow
#define ROTATION 4 //liczba mozliwych rotacji
#define ROWS 4 //rozmiar klocka Y
#define COL 4 //rozmiar klocka X

#endif