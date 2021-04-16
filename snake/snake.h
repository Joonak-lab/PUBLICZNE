#pragma once

#include<iostream>
#include"info.h"
#include"Cglowa.h"
#include"pokarm.h"
#include"wektor.h"
#ifndef snake_h
#define snake_h

class snake ///klasa przedstawiaj¹ca informacje o rozgrywce
{
protected:
	int punkty; /// punkty zdobyte podczas rozgrywki
	int dlugosc; /// aktualna d³ugoœæ wê¿a
	int szybkosc; /// aktualna szybkoœæ wê¿a
	int kierunek; /// aktualny kierunek wê¿a
	int stan; /// informacja o kolizji wê¿a 
public:
	/** Metoda zwracaj¹ca aktualny stan rozgrywki
@return stan
*/
	int sprawdz_stan();

	/** konstruktor klasy snake
@param d³ugoœæ startowa wê¿a
@param szybkoœæ startowa wê¿a
@param kierunek startowy wê¿a
@param stan pocz¹tkowy wê¿a
@param iloœæ punktów
*/
	snake(int _dlugosc = 0, int _szybkosc = 0, int _kierunek = 77,int _stan = 0,int punkty = 0);

	/** Metoda zwracaj¹ca aktualny kierunek
@return kierunek
*/
	int get_kierunek();

	/** Metoda ustawiaj¹ca kierunek
@param kierunek
*/
	void set_kierunek(int kier);
	/** Metoda ustawiaj¹ca d³ugoœæ wê¿a
@param d³ugoœæ wê¿a
*/

	void set_dlugosc(int liczba);

	/** Metoda zwracaj¹ca aktualn¹ szybkoœæ
@return szybkoœæ
*/
	int get_szybkosc();

	/** Metoda zwracaj¹ca aktualn¹ liczbê punktów
@return punkty
*/
	int get_punkty();

	/** Metoda zwracaj¹ca aktualn¹ d³ugoœæ
	@return d³ugoœæ
	*/
	int get_dlugosc();

	/** Metoda ustawiaj¹ca stan rozgrywki
@param aktualny stan
*/
	void set_stan(int liczba);
	/** Metoda aktualizuj¹ca punkty po zjedzeniu pokarmu
@param liczba punktów
*/
	void zjedzony(int liczba);

	/** Operator inkrementacji
*/
	snake operator++();

	/** Operator inkrementacji
*/
	snake operator++(int);

	friend std::ostream& operator<<(std::ostream& s, snake* info1);
	friend void zapisz_wynik(snake* snake1, info* info1);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);
};
#endif