#pragma once

#include "pokarm.h"
#include "snake.h"
#include "funkcje.h"
#include <iostream>
#include <time.h>
#include<string>
#ifndef info_h
#define info_h


class info /// klasa opisuj�ca parametry startowe 
{
protected:
	int szybkosc; /// szybko�� w�a
	int dlugosc_weza; /// d�ugo�� w�a
	int dlugosc_boku; /// d�ugo�� boku planszy
	char* nazwa_gracza; /// nazwa gracza
	std::string nazwa_pliku_do_odczytu; /// nazwa pliku do odczytania zapisu gry
public:
	/** Konstruktor klasy info
@param szybko�� pocz�tkowa
@param d�ugo�� pocz�tkowa
@param bok planszy
@param nazwa gracza
@param nazwa pliku do odczytu
*/
	info(int szyb = 0, int dl = 0, int dlb = 30, const char* gr = "anon", std::string naz = "brak");

	/** Destruktor klasy info*/
	~info();

	/** Metoda wypisuj�ca informacje na temat obiektu */
	void wypisz();

	/** Metoda zwracaj�ca d�ugo�� boku
	@return aktualna d�ugo�� boku planszy
	*/
	int get_dlb();

	friend void zapisz_wynik(snake* snake1, info* info1);
	friend void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head, info* info1, std::string s);
	friend void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1);

};
#endif // !