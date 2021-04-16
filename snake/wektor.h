#pragma once

#include "funkcje.h"
#include "Cglowa.h"
#include "pokarm.h"
#include "snake.h"
#ifndef wektor_h
#define wektor_h


class wektor ///klasa przestawiaj�ca liste jednokierunkow�. Przechowywane s� w niej informacje na temat historii poruszania si� w�a
{
	int kierunek; ///ruch w�a
	wektor* next; ///wska�nik na nast�pny element
public:

	/** Metoda usuwa pami�� zaalokowan� przez elementy listy
	@param wska�nik na pocz�tkowy element listy
	@param wska�nik na ko�cowy element listy
	*/
	void usun(wektor*& head, wektor*& tail);

	/** Metoda liczy ile element�w ma lista
	@param wska�nik na pocz�tkowy element listy
	@return liczba elemet�w
	*/
	int ile_elementow(wektor* head);
	/** Metoda dodaje element na pocz�tek listy
	@param wska�nik na pocz�tkowy element listy
	@param ostatni kierunek w�a
	*/
	void dodaj_na_poczatek(wektor*& head, int kierunek);

	/** Metoda ustawia wska�nik na koniec listy
	@param wska�nik na pocz�tkowy element listy
	@return wska�nik na koniec listy
	*/
	wektor* ustaw_tail(wektor* head);

	/** Metoda usuwa ostatni element z listy
	@param wska�nik na pocz�tkowy element listy
	@param wska�nik na ko�cowy element listy
	*/
	void usun_ostatni(wektor*& head,wektor*& tail);
	/** Metoda wypisuje ca�� liste na ekran
	@param wska�nik na pocz�tkowy element listy
	*/
	void wypisz(wektor* head);

	/** Metoda informuj�ca o aktualnym kierunku w�a
	@return aktualny kierunek w�a
	*/
	int get_kierunek();

	friend void narysujweza(char**& plansza, int dl, wektor* head, int gl_x, int gl_y);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif