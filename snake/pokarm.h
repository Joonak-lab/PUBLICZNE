#pragma once

#ifndef pokarm_h

#define pokarm_h
#include "punkt.h"
#include "Cglowa.h"
#include "snake.h"
#include "wektor.h"
#include "funkcje.h"
#include <iostream>


class pokarm : public punkt /// klasa opisuj¹ca owoc
{
protected:
	char symbol; /// symbol owoca 
	int rodzaj_pokarmu; /// rodzaj pokarmu 
	int ile_punktow; /// wartoœæ punktowa owoca

public:
	/** Metoda ustawiaj¹ca sk³adow¹ x pokarmu
	@param aktualna sk³adowa x pokarmu na planszy
	*/
	void set_x(int liczba);

	/** Metoda ustawiaj¹ca sk³adow¹ y pokarmu
@param aktualna sk³adowa y pokarmu na planszy
*/
	void set_y(int liczba);

	/** Metoda zwracaj¹ca sk³adow¹ x pokarmu
@return aktualna sk³adowa x pokarmu na planszy
*/
	int get_x();

	/** Metoda zwracaj¹ca sk³adow¹ y pokarmu
@return aktualna sk³adowa y pokarmu na planszy
*/
	int get_y();

	/** konstruktor dla klasy pokarm
@param d³ugoœæ bloku planszy
*/
	pokarm(int bok);

	/** Metoda zwracaj¹ca wartoœæ punktow¹ pokarmu
@return punkty za pokarm
*/
	int get_punkt();

	/** Metoda zwracaj¹ca symbol pokarmu
@return symbol
*/
	int get_symbol();

	/** Metoda ustawiaj¹ca nowy pokarm po zjedzeniu
@param podwójny wskaŸnik na tablice char
@param d³ugoœæ planszy
*/
	void zjedzony(char** plansza,int bok);

	friend char** stworz_plansze(int glowa_x, int glowa_y, int owoc_x, int owoc_y, pokarm* pokarm1, int R);
	friend void sprawdzczyzjedzone(glowa* glowa1, pokarm*& pokarm1, snake*& snake1, char**& plansza, int R);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif