
#include "info.h"
	/** Konstruktor klasy info
	@param szybkoœæ pocz¹tkowa
	@param d³ugoœæ pocz¹tkowa
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
/** Metoda wypisuj¹ca informacje na temat obiektu */
void info::wypisz()
{
	std::cout << szybkosc << "\t" << dlugosc_weza << "\t" << dlugosc_boku << "\t" << nazwa_gracza << "\t" << nazwa_pliku_do_odczytu << std::endl;
}
/** Metoda zwracaj¹ca d³ugoœæ boku
	@return aktualna d³ugoœæ boku planszy
	*/
int info::get_dlb()
{
	return dlugosc_boku;
}
