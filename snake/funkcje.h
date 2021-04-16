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


/** Funkcja wstawia do planszy w�a
	@param podw�jny wska�nik na plansze do gry
	@param dlugosc w�a
	@param wska�nik na pocz�tkowy element listy
	@param sk�adowa x g�owy w�a
	@param sk�adowa y g�owy w�a
	*/
void narysujweza(char**& plansza, int dl, wektor* head, int gl_x, int gl_y);

/** wy�wietla komunikat o pauzie w grze
@return decyzje o zapisaniu gry
*/
int menu();

/** Funkcja zapisuje wynik rozgrywki do pliku
	@param wska�nik na obiekt klasy snake
	@param wska�nik na obiekt klasy info
	*/
void zapisz_wynik(snake* snake1, info* info1);

/** Funkcja zapisuje stan aktualnej rozgrywki do pliku zapisu

	@param wska�nik na obiekt klasy glowa
	@param wska�nik na obiekt klasy pokarm
	@param wska�nik na obiekt klasy snake
	@param wska�nik na pierwszy element listy
	@param wska�nik na obiekt klasy info
	@param nazwa pliku do zapisu
	*/
void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1,wektor* head, info* info1,std::string s);

/** Funkcja wczytuje stan rozgrywki z pliku
	@param wska�nik na obiekt klasy glowa
	@param wska�nik na obiekt klasy pokarm
	@param wska�nik na obiekt klasy snake
	@param wska�nik na pierwszy element listy
	@param wska�nik na obiekt klasy info
	*/
void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1,wektor*& head,info*& info1);

/** Funkcja modyfikuje plansze do aktualnej rozgrywki i sprawdza czy wyst�pi�a kolizja
   @param podw�jny wska�nik na plansze do gry
   @param wska�nik na obiekt klasy pokarm
   @param aktualny kierunek w�a
   @param wska�nik na obiekt klasy glowa
   @param wska�nik na obiekt klasy snake
   @param wska�nik na pierwszy element listy
   @param d�ugo�� boku planszy
   */
void modyfplansze(char**& plansza, pokarm* pokarm1, int kier, glowa*& glowa1, snake*& snake1, wektor* head, int R);

/** Funkcja powi�ksza w�a o wpisany w parametrach rozmiar
	@param podw�jny wska�nik na plansze do gry
	@param d�ugo�� w�a
	@param wska�nik na pierwszy element listy
	@param d�ugo�� boku planszy
	*/
void powiekszweza(char**& plansza,int dl,wektor*& head,int dlb);

/** Funkcja wy�wietla plansze
	@param podw�jny wska�nik na plansze do gry
	@param d�ugo�� boku planszy
	*/
void narysuj_plansze(char** plansza,int R);

/** Funkcja zmienia aktualny kierunek w�a
@param wska�nik na obiekt klasy snake
*/
void zmienkierunek(snake*& snake1);

/** Funkcja przesuwa g�ow� w�a na planszy
	@param aktualny kierunek w�a
	@param wska�nik na obiekt klasy glowa
	@param podw�jny wska�nik na plansze
	@param wska�nik na obiekt klasy snake
	*/
void zmienglowa(int kier, glowa*& glowa1, char**& plansza, snake*& snake1);

/** Funkcja powi�ksza w�a o wpisany w parametrach rozmiar
	@param wska�nik na pierwszy element listy
	@param wska�nik na obiekt klasy pokarm
	@param wska�nik na obiekt klasy snake
	@param podw�jny wska�nik na plansze do gry
	@param d�ugo�� boku planszy
	*/
void sprawdzczyzjedzone(glowa* glowa1, pokarm*& pokarm1,snake*& snake1,char**& plansza,int R);

/** Funkcja tworzy plansze
	@param sk�adowa x g�owy w�a
	@param sk�adowa y g�owy w�a
	@param sk�adowa x owoca
	@param sk�adowa y owoca
	@param wska�nik na obiekt klasy pokarm
	@param d�ugo�� boku planszy
	@return podw�jny wska�nik na tablice char
	*/
char** stworz_plansze(int glowa_x, int glowa_y, int owoc_x, int owoc_y, pokarm* pokarm1, int R);

/** Funkcja tworzy nazwe pliku do zapisu stanu gry
	@return �a�cuch znak�w
*/
std::string generuj_nazwe();

/** Funkcja wy�wietla na ekranie zawarto�� obiektu klasy snake
	@param strumie� wyj�cia do zmodyfikowania
	@param wska�nik na obiekt klasyt snake
	@return strumie� wyj�cia
*/
std::ostream& operator<<(std::ostream& s,  snake* info1);
#endif