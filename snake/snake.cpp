
#include "snake.h"
	/** Metoda zwracaj¹ca aktualny stan rozgrywki
	@return stan
	*/
int snake::sprawdz_stan()
{
	return stan;
}
/** konstruktor klasy snake
@param d³ugoœæ startowa wê¿a
@param szybkoœæ startowa wê¿a
@param kierunek startowy wê¿a
@param stan pocz¹tkowy wê¿a
@param iloœæ punktów
*/
snake::snake(int _dlugosc, int _szybkosc, int _kierunek, int _stan, int _punkty)
{
	punkty = _punkty;
	dlugosc = _dlugosc;
	szybkosc = _szybkosc;
	kierunek = _kierunek;
	stan = _stan;
}
/** Metoda zwracaj¹ca aktualny kierunek
@return kierunek
*/
int snake::get_kierunek()
{
	return kierunek;
}
/** Metoda ustawiaj¹ca kierunek
@param kierunek
*/
void snake::set_kierunek(int kier)
{
	kierunek = kier;
}
/** Metoda ustawiaj¹ca d³ugoœæ wê¿a
@param d³ugoœæ wê¿a
*/
void snake::set_dlugosc(int liczba)
{
	dlugosc = liczba;
}
/** Metoda zwracaj¹ca aktualn¹ szybkoœæ
@return szybkoœæ
*/
int snake::get_szybkosc()
{
	return szybkosc;
}
/** Metoda zwracaj¹ca aktualn¹ liczbê punktów
@return punkty
*/
int snake::get_punkty()
{
	return punkty;
}
/** Metoda zwracaj¹ca aktualn¹ d³ugoœæ
	@return d³ugoœæ
	*/
int snake::get_dlugosc()
{
	return dlugosc;
}
/** Metoda ustawiaj¹ca stan rozgrywki
@param aktualny stan
*/
void snake::set_stan(int liczba)
{
	stan = liczba;
}

/** Metoda aktualizuj¹ca punkty po zjedzeniu pokarmu
@param liczba punktów
*/
void snake::zjedzony(int liczba)
{
	(*this)++;
	punkty = punkty + liczba;
}
/** Operator inkrementacji
*/
snake snake::operator++(int)
{
	snake kopia(*this);
	szybkosc = szybkosc + 1;
	dlugosc = dlugosc + 1;
	return kopia;
}
/** Operator inkrementacji
*/
snake snake::operator++()
{
	szybkosc++;
	dlugosc++;
	return *this;
}

