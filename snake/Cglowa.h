#pragma once

#include "funkcje.h"
#include "punkt.h"
#include "pokarm.h"
#include "snake.h"


#ifndef Cglowa_h
#define Cglowa_h

class glowa : public punkt /// klasa opisuj¹ca g³owê wê¿a
{
	char symbol; /// symbol g³owy
public:
	/** konstruktor dla klasy glowa
	@param rozmiar planszy
	*/
	glowa(int R);

	/** Metoda ustawiaj¹ca sk³adow¹ x g³owy
	@param aktualna sk³adowa x g³owy na planszy
	*/
	void set_x(int liczba);

	/** Metoda ustawiaj¹ca sk³adow¹ y g³owy
@param aktualna sk³adowa y g³owy na planszy
*/
	void set_y(int liczba);

	/** Metoda zwracaj¹ca sk³adow¹ x g³owy
	@return aktualna sk³adowa x g³owy na planszy
	*/
	int get_x();

	/** Metoda zwracaj¹ca sk³adow¹ y g³owy
	@return aktualna sk³adowa y g³owy na planszy
	*/
	int get_y();

	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void zmienglowa(int kier, glowa*& glowa1, char**& plansza, snake*& snake1);
	friend void modyfplansze(char**& plansza, pokarm* pokarm1, int kier, glowa*& glowa1, snake*& snake1, wektor* head, int R);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif