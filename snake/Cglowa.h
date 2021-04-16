#pragma once

#include "funkcje.h"
#include "punkt.h"
#include "pokarm.h"
#include "snake.h"


#ifndef Cglowa_h
#define Cglowa_h

class glowa : public punkt /// klasa opisuj�ca g�ow� w�a
{
	char symbol; /// symbol g�owy
public:
	/** konstruktor dla klasy glowa
	@param rozmiar planszy
	*/
	glowa(int R);

	/** Metoda ustawiaj�ca sk�adow� x g�owy
	@param aktualna sk�adowa x g�owy na planszy
	*/
	void set_x(int liczba);

	/** Metoda ustawiaj�ca sk�adow� y g�owy
@param aktualna sk�adowa y g�owy na planszy
*/
	void set_y(int liczba);

	/** Metoda zwracaj�ca sk�adow� x g�owy
	@return aktualna sk�adowa x g�owy na planszy
	*/
	int get_x();

	/** Metoda zwracaj�ca sk�adow� y g�owy
	@return aktualna sk�adowa y g�owy na planszy
	*/
	int get_y();

	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void zmienglowa(int kier, glowa*& glowa1, char**& plansza, snake*& snake1);
	friend void modyfplansze(char**& plansza, pokarm* pokarm1, int kier, glowa*& glowa1, snake*& snake1, wektor* head, int R);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif