#pragma once
/** @file */
#ifndef funkcje_h
#define funkcje_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

const int MAXINT = 2147483647;

struct punkty   ///struktura bazy miast
{
	string miasto; // nazwa miasta
	punkty* nextpunkty; //wskaznik na nastepny element listy
};
struct miasta ///struktura przechowujaca wyznaczona trase po zastosowaniu algorytmu
{
	string miasto; // element z bazy danych
	int waga; //koszt dojscia do poprzednika
	miasta* next; //wskaznik do nastepnego elemtu listy
};

struct podroz /// struktura okreslajaca poczatek i koniec trasy
{
	string startn; // nazwa startu
	string celn; // nazwa konca
	podroz* nextcel; // wskaznik na nastepny element listy
};

struct dane /// struktura zawierajaca potrzebne informacje do zadzialania algorytmu
{
	string wierzcholek; //numer wierzcholka
	int waga; //dlugosc drogi do poprzednika
	string poprzednik; // numer poprzednika
	bool zbiorQ; // informacja czy dana liczba znajduje sie w zbiorze wierzcholkow  niepoliczonych przez algorytm
	dane* nextdane; // wskaznik na nastepny element listy
};

struct slistEl  ///lista sasiedztwa
{
	string x; //wierzcholek startowy drogi
	slistEl* nextwierz; //wskaznik na nastepny wierzcholek
	slistEl* nextsasiad; // wskaznik na nastepnego sasiada wierzcholka
	string v; // numer wierzcholka docelowego
	int w; // dlugosc drogi
};
/** Funkcja czysci zawartosc pliku przeznaczonego do zapisu wyniku dzialania programu
@param nazwa pliku, do ktorego wpisywany bedzie wynik dzialania programu
*/
void wyczysc(string o);

/** Funkcja wpisuje miasta do bazy
@param wskaznik do poczatku listy
@param nazwa pliku do wczytania
@return liczba miast w bazie
*/
int wczytaj(punkty*& head, string argv); // wczytywanie miejscowosci

/** Funkcja wczytuje z pliku trasy do wyznaczenia
@param wskaznik do pierwszego elementu listy z trasami do wyznaczenia
@param wskaznik do bazy
@param wskaznik do ostatniego elementu listy z trasami do wyznaczenia
@param nazwa pliku, z ktorego funkcja bêdzie czytaæ dane
@return ilosc tras
*/
int wyznacz(podroz*& head, punkty* headpun, podroz*& tail, string argv); // wczytywanie pliku z trasami do wyznaczenia

/** Funkcja wczytuje do listy sasiedztwa trasy z pliku
@param wskaznik do listy s¹siedztwa
@param nazwa pliku, z ktorego funkcja bedzie czytac dane
*/
void drogi(slistEl*& graf, string dod); // uzupelnianie tablicy list sasiedztwa

/** Funkcja obliczajaca najkrotsze trasy
@param ilocs miast w bazie
@param wskaznik do listy s¹siedztwa
@param wskaznik do bazy
@param wskaznik do listy danych potrzebnych do obliczania tras
*/
void sciezki(int n, slistEl* graf, punkty*& headpunkty, dane* headdane);

/** Funkcja alokujaca pamiec 
@param ilocs miast
@param wskaznik do listy informacji dla argumentu
@param wskaznik do bazy danych
*/
void inicjacja(int n, dane*& head, punkty* punktyhead);

/** Funkcja zapisujaca wynik dzialania programu do pliku txt
@param wskaznik do listy z trasami do obliczneia
@param wskaznik do bazy danych
@param wskaznik do biezacej trasy
@param wskaznik do informacji z algorytmu
@param nazwa pliku zapisu
*/
void zapisz(podroz* headpodroz, punkty* headpunkty, podroz* idz, dane* headdane, string o);

/** Funkcja zwalniajaca pamiec
@param wskacnik do listy z podrozz
@param wskaznik do listy z podroza
@param wskaznik do listy sasiedztwa
@param wskaznik do listy bazy miast
@param wskaznik do listy z informacjami
*/
void zwolnij(podroz*& headpodroz, podroz*& tailpodroz, slistEl*& graf, punkty*& headpunkty, dane*& headdane); //zwalnianie pamieci

#endif
