
#include "pokarm.h"
	/** Metoda ustawiaj�ca sk�adow� x pokarmu
	@param aktualna sk�adowa x pokarmu na planszy
	*/
void pokarm::set_x(int liczba)
{
	x = liczba;
}
/** Metoda ustawiaj�ca sk�adow� y pokarmu
@param aktualna sk�adowa y pokarmu na planszy
*/
void pokarm::set_y(int liczba)
{
	y = liczba;
}
/** Metoda zwracaj�ca sk�adow� x pokarmu
@return aktualna sk�adowa x pokarmu na planszy
*/
int pokarm::get_x()
{
	return x;
}
/** Metoda zwracaj�ca sk�adow� y pokarmu
@return aktualna sk�adowa y pokarmu na planszy
*/
int pokarm::get_y()
{
	return y;
}
/** konstruktor dla klasy pokarm
@param d�ugo�� bloku planszy
*/
pokarm::pokarm(int bok)
{
	x = 2;
	y = 2;
	rodzaj_pokarmu = rand()%3 + 1;
	ile_punktow = 10 * rodzaj_pokarmu;

	switch (rodzaj_pokarmu)
	{
	case 1:
	{
		symbol = 222;
		break;
	}
	case 2:
	{
		symbol = 251;
		break;
	}
	case 3:
	{
		symbol = 212;
		break;
	}
	}
}
/** Metoda zwracaj�ca warto�� punktow� pokarmu
@return punkty za pokarm
*/
int pokarm::get_punkt()
{
	return ile_punktow;
}
/** Metoda zwracaj�ca symbol pokarmu
@return symbol
*/
int pokarm::get_symbol()
{
	return symbol;
}
/** Metoda ustawiaj�ca nowy pokarm po zjedzeniu
@param podw�jny wska�nik na tablice char
@param d�ugo�� planszy
*/
void pokarm::zjedzony(char** plansza,int bok)
{
	while (1)
	{
		int a = rand() % (bok - 2);
		int b = rand() % (bok - 2);
		if (plansza[a][b] == ' ' )
		{
			set_x(a);
			set_y(b);
			rodzaj_pokarmu = rand() % 3 + 1;
			ile_punktow = 10 * rodzaj_pokarmu;
			switch (rodzaj_pokarmu)
			{
			case 1:
			{
				symbol = 222;
				break;
			}
			case 2:
			{
				symbol = 251;
				break;
			}
			case 3:
			{
				symbol = 212;
				break;
			}
			}
			return;
		}
		
	}


	
}
