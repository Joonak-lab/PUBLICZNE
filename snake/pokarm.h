#pragma once

#ifndef pokarm_h

#define pokarm_h
#include "punkt.h"
#include "Cglowa.h"
#include "snake.h"
#include "wektor.h"
#include "funkcje.h"
#include <iostream>


class pokarm : public punkt /// klasa opisuj�ca owoc
{
protected:
	char symbol; /// symbol owoca 
	int rodzaj_pokarmu; /// rodzaj pokarmu 
	int ile_punktow; /// warto�� punktowa owoca

public:
	/** Metoda ustawiaj�ca sk�adow� x pokarmu
	@param aktualna sk�adowa x pokarmu na planszy
	*/
	void set_x(int liczba);

	/** Metoda ustawiaj�ca sk�adow� y pokarmu
@param aktualna sk�adowa y pokarmu na planszy
*/
	void set_y(int liczba);

	/** Metoda zwracaj�ca sk�adow� x pokarmu
@return aktualna sk�adowa x pokarmu na planszy
*/
	int get_x();

	/** Metoda zwracaj�ca sk�adow� y pokarmu
@return aktualna sk�adowa y pokarmu na planszy
*/
	int get_y();

	/** konstruktor dla klasy pokarm
@param d�ugo�� bloku planszy
*/
	pokarm(int bok);

	/** Metoda zwracaj�ca warto�� punktow� pokarmu
@return punkty za pokarm
*/
	int get_punkt();

	/** Metoda zwracaj�ca symbol pokarmu
@return symbol
*/
	int get_symbol();

	/** Metoda ustawiaj�ca nowy pokarm po zjedzeniu
@param podw�jny wska�nik na tablice char
@param d�ugo�� planszy
*/
	void zjedzony(char** plansza,int bok);

	friend char** stworz_plansze(int glowa_x, int glowa_y, int owoc_x, int owoc_y, pokarm* pokarm1, int R);
	friend void sprawdzczyzjedzone(glowa* glowa1, pokarm*& pokarm1, snake*& snake1, char**& plansza, int R);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif