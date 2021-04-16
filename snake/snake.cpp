
#include "snake.h"
	/** Metoda zwracaj�ca aktualny stan rozgrywki
	@return stan
	*/
int snake::sprawdz_stan()
{
	return stan;
}
/** konstruktor klasy snake
@param d�ugo�� startowa w�a
@param szybko�� startowa w�a
@param kierunek startowy w�a
@param stan pocz�tkowy w�a
@param ilo�� punkt�w
*/
snake::snake(int _dlugosc, int _szybkosc, int _kierunek, int _stan, int _punkty)
{
	punkty = _punkty;
	dlugosc = _dlugosc;
	szybkosc = _szybkosc;
	kierunek = _kierunek;
	stan = _stan;
}
/** Metoda zwracaj�ca aktualny kierunek
@return kierunek
*/
int snake::get_kierunek()
{
	return kierunek;
}
/** Metoda ustawiaj�ca kierunek
@param kierunek
*/
void snake::set_kierunek(int kier)
{
	kierunek = kier;
}
/** Metoda ustawiaj�ca d�ugo�� w�a
@param d�ugo�� w�a
*/
void snake::set_dlugosc(int liczba)
{
	dlugosc = liczba;
}
/** Metoda zwracaj�ca aktualn� szybko��
@return szybko��
*/
int snake::get_szybkosc()
{
	return szybkosc;
}
/** Metoda zwracaj�ca aktualn� liczb� punkt�w
@return punkty
*/
int snake::get_punkty()
{
	return punkty;
}
/** Metoda zwracaj�ca aktualn� d�ugo��
	@return d�ugo��
	*/
int snake::get_dlugosc()
{
	return dlugosc;
}
/** Metoda ustawiaj�ca stan rozgrywki
@param aktualny stan
*/
void snake::set_stan(int liczba)
{
	stan = liczba;
}

/** Metoda aktualizuj�ca punkty po zjedzeniu pokarmu
@param liczba punkt�w
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

