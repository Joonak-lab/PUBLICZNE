
#include "info.h"
	/** Konstruktor klasy info
	@param szybko�� pocz�tkowa
	@param d�ugo�� pocz�tkowa
	@param bok planszy
	@param nazwa gracza
	@param nazwa pliku do odczytu
	*/
info::info(int szyb, int dl, int dlb , const char* gr,std::string naz )
{
	szybkosc = szyb;
	dlugosc_weza = dl;
	dlugosc_boku = dlb;
	nazwa_gracza = new char[strlen(gr)+1];
	memcpy(nazwa_gracza, gr, strlen(gr) + 1);
	nazwa_pliku_do_odczytu = naz;
}
/** Destruktor klasy info*/
info::~info()
{
	delete nazwa_gracza;
	nazwa_gracza = 0;
}
/** Metoda wypisuj�ca informacje na temat obiektu */
void info::wypisz()
{
	std::cout << szybkosc << "\t" << dlugosc_weza << "\t" << dlugosc_boku << "\t" << nazwa_gracza << "\t" << nazwa_pliku_do_odczytu << std::endl;
}
/** Metoda zwracaj�ca d�ugo�� boku
	@return aktualna d�ugo�� boku planszy
	*/
int info::get_dlb()
{
	return dlugosc_boku;
}
