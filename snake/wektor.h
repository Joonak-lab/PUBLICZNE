#pragma once

#include "funkcje.h"
#include "Cglowa.h"
#include "pokarm.h"
#include "snake.h"
#ifndef wektor_h
#define wektor_h


class wektor ///klasa przestawiaj¹ca liste jednokierunkow¹. Przechowywane s¹ w niej informacje na temat historii poruszania siê wê¿a
{
	int kierunek; ///ruch wê¿a
	wektor* next; ///wska¿nik na nastêpny element
public:

	/** Metoda usuwa pamiêæ zaalokowan¹ przez elementy listy
	@param wskaŸnik na pocz¹tkowy element listy
	@param wskaŸnik na koñcowy element listy
	*/
	void usun(wektor*& head, wektor*& tail);

	/** Metoda liczy ile elementów ma lista
	@param wskaŸnik na pocz¹tkowy element listy
	@return liczba elemetów
	*/
	int ile_elementow(wektor* head);
	/** Metoda dodaje element na pocz¹tek listy
	@param wskaŸnik na pocz¹tkowy element listy
	@param ostatni kierunek wê¿a
	*/
	void dodaj_na_poczatek(wektor*& head, int kierunek);

	/** Metoda ustawia wskaŸnik na koniec listy
	@param wskaŸnik na pocz¹tkowy element listy
	@return wskaŸnik na koniec listy
	*/
	wektor* ustaw_tail(wektor* head);

	/** Metoda usuwa ostatni element z listy
	@param wskaŸnik na pocz¹tkowy element listy
	@param wskaŸnik na koñcowy element listy
	*/
	void usun_ostatni(wektor*& head,wektor*& tail);
	/** Metoda wypisuje ca³¹ liste na ekran
	@param wskaŸnik na pocz¹tkowy element listy
	*/
	void wypisz(wektor* head);

	/** Metoda informuj¹ca o aktualnym kierunku wê¿a
	@return aktualny kierunek wê¿a
	*/
	int get_kierunek();

	friend void narysujweza(char**& plansza, int dl, wektor* head, int gl_x, int gl_y);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif