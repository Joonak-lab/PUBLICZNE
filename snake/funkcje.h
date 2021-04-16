#pragma once

#include "Cglowa.h"
#include "pokarm.h"
#include "snake.h"
#include "wektor.h"
#include "info.h"
#include <iostream>
#include <fstream>
#include <time.h>

#ifndef funkcje_h
#define funkcje_h


/** Funkcja wstawia do planszy wê¿a
	@param podwójny wskaŸnik na plansze do gry
	@param dlugosc wê¿a
	@param wskaŸnik na pocz¹tkowy element listy
	@param sk³adowa x g³owy wê¿a
	@param sk³adowa y g³owy wê¿a
	*/
void narysujweza(char**& plansza, int dl, wektor* head, int gl_x, int gl_y);

/** wyœwietla komunikat o pauzie w grze
@return decyzje o zapisaniu gry
*/
int menu();

/** Funkcja zapisuje wynik rozgrywki do pliku
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na obiekt klasy info
	*/
void zapisz_wynik(snake* snake1, info* info1);

/** Funkcja zapisuje stan aktualnej rozgrywki do pliku zapisu

	@param wskaŸnik na obiekt klasy glowa
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy info
	@param nazwa pliku do zapisu
	*/
void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1,wektor* head, info* info1,std::string s);

/** Funkcja wczytuje stan rozgrywki z pliku
	@param wskaŸnik na obiekt klasy glowa
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy info
	*/
void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1,wektor*& head,info*& info1);

/** Funkcja modyfikuje plansze do aktualnej rozgrywki i sprawdza czy wyst¹pi³a kolizja
   @param podwójny wskaŸnik na plansze do gry
   @param wskaŸnik na obiekt klasy pokarm
   @param aktualny kierunek wê¿a
   @param wskaŸnik na obiekt klasy glowa
   @param wskaŸnik na obiekt klasy snake
   @param wskaŸnik na pierwszy element listy
   @param d³ugoœæ boku planszy
   */
void modyfplansze(char**& plansza, pokarm* pokarm1, int kier, glowa*& glowa1, snake*& snake1, wektor* head, int R);

/** Funkcja powiêksza wê¿a o wpisany w parametrach rozmiar
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ wê¿a
	@param wskaŸnik na pierwszy element listy
	@param d³ugoœæ boku planszy
	*/
void powiekszweza(char**& plansza,int dl,wektor*& head,int dlb);

/** Funkcja wyœwietla plansze
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ boku planszy
	*/
void narysuj_plansze(char** plansza,int R);

/** Funkcja zmienia aktualny kierunek wê¿a
@param wskaŸnik na obiekt klasy snake
*/
void zmienkierunek(snake*& snake1);

/** Funkcja przesuwa g³owê wê¿a na planszy
	@param aktualny kierunek wê¿a
	@param wskaŸnik na obiekt klasy glowa
	@param podwójny wskaŸnik na plansze
	@param wskaŸnik na obiekt klasy snake
	*/
void zmienglowa(int kier, glowa*& glowa1, char**& plansza, snake*& snake1);

/** Funkcja powiêksza wê¿a o wpisany w parametrach rozmiar
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ boku planszy
	*/
void sprawdzczyzjedzone(glowa* glowa1, pokarm*& pokarm1,snake*& snake1,char**& plansza,int R);

/** Funkcja tworzy plansze
	@param sk³adowa x g³owy wê¿a
	@param sk³adowa y g³owy wê¿a
	@param sk³adowa x owoca
	@param sk³adowa y owoca
	@param wskaŸnik na obiekt klasy pokarm
	@param d³ugoœæ boku planszy
	@return podwójny wskaŸnik na tablice char
	*/
char** stworz_plansze(int glowa_x, int glowa_y, int owoc_x, int owoc_y, pokarm* pokarm1, int R);

/** Funkcja tworzy nazwe pliku do zapisu stanu gry
	@return ³añcuch znaków
*/
std::string generuj_nazwe();

/** Funkcja wyœwietla na ekranie zawartoœæ obiektu klasy snake
	@param strumieñ wyjœcia do zmodyfikowania
	@param wskaŸnik na obiekt klasyt snake
	@return strumieñ wyjœcia
*/
std::ostream& operator<<(std::ostream& s,  snake* info1);
#endif