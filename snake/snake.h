#pragma once

#include<iostream>
#include"info.h"
#include"Cglowa.h"
#include"pokarm.h"
#include"wektor.h"
#ifndef snake_h
#define snake_h

class snake ///klasa przedstawiaj�ca informacje o rozgrywce
{
protected:
	int punkty; /// punkty zdobyte podczas rozgrywki
	int dlugosc; /// aktualna d�ugo�� w�a
	int szybkosc; /// aktualna szybko�� w�a
	int kierunek; /// aktualny kierunek w�a
	int stan; /// informacja o kolizji w�a 
public:
	/** Metoda zwracaj�ca aktualny stan rozgrywki
@return stan
*/
	int sprawdz_stan();

	/** konstruktor klasy snake
@param d�ugo�� startowa w�a
@param szybko�� startowa w�a
@param kierunek startowy w�a
@param stan pocz�tkowy w�a
@param ilo�� punkt�w
*/
	snake(int _dlugosc = 0, int _szybkosc = 0, int _kierunek = 77,int _stan = 0,int punkty = 0);

	/** Metoda zwracaj�ca aktualny kierunek
@return kierunek
*/
	int get_kierunek();

	/** Metoda ustawiaj�ca kierunek
@param kierunek
*/
	void set_kierunek(int kier);
	/** Metoda ustawiaj�ca d�ugo�� w�a
@param d�ugo�� w�a
*/

	void set_dlugosc(int liczba);

	/** Metoda zwracaj�ca aktualn� szybko��
@return szybko��
*/
	int get_szybkosc();

	/** Metoda zwracaj�ca aktualn� liczb� punkt�w
@return punkty
*/
	int get_punkty();

	/** Metoda zwracaj�ca aktualn� d�ugo��
	@return d�ugo��
	*/
	int get_dlugosc();

	/** Metoda ustawiaj�ca stan rozgrywki
@param aktualny stan
*/
	void set_stan(int liczba);
	/** Metoda aktualizuj�ca punkty po zjedzeniu pokarmu
@param liczba punkt�w
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