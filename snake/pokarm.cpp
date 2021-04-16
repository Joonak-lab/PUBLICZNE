
#include "pokarm.h"
	/** Metoda ustawiaj¹ca sk³adow¹ x pokarmu
	@param aktualna sk³adowa x pokarmu na planszy
	*/
void pokarm::set_x(int liczba)
{
	x = liczba;
}
/** Metoda ustawiaj¹ca sk³adow¹ y pokarmu
@param aktualna sk³adowa y pokarmu na planszy
*/
void pokarm::set_y(int liczba)
{
	y = liczba;
}
/** Metoda zwracaj¹ca sk³adow¹ x pokarmu
@return aktualna sk³adowa x pokarmu na planszy
*/
int pokarm::get_x()
{
	return x;
}
/** Metoda zwracaj¹ca sk³adow¹ y pokarmu
@return aktualna sk³adowa y pokarmu na planszy
*/
int pokarm::get_y()
{
	return y;
}
/** konstruktor dla klasy pokarm
@param d³ugoœæ bloku planszy
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
/** Metoda zwracaj¹ca wartoœæ punktow¹ pokarmu
@return punkty za pokarm
*/
int pokarm::get_punkt()
{
	return ile_punktow;
}
/** Metoda zwracaj¹ca symbol pokarmu
@return symbol
*/
int pokarm::get_symbol()
{
	return symbol;
}
/** Metoda ustawiaj¹ca nowy pokarm po zjedzeniu
@param podwójny wskaŸnik na tablice char
@param d³ugoœæ planszy
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
