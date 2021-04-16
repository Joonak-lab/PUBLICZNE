
#include "Cglowa.h"
/** konstruktor dla klasy glowa
	@param rozmiar planszy
	*/
glowa::glowa(int R)
{
	x = y = R / 2;
	symbol = 1;
}
/** Metoda ustawiaj�ca sk�adow� x g�owy
	@param aktualna sk�adowa x g�owy na planszy
	*/
void glowa::set_x(int liczba)
{
	x = liczba;
}
/** Metoda ustawiaj�ca sk�adow� y g�owy
@param aktualna sk�adowa y g�owy na planszy
*/
void glowa::set_y(int liczba)
{
	y = liczba;
}
/** Metoda zwracaj�ca sk�adow� x g�owy
	@return aktualna sk�adowa x g�owy na planszy
	*/
int glowa::get_x()
{
	return x;
}
/** Metoda zwracaj�ca sk�adow� y g�owy
	@return aktualna sk�adowa y g�owy na planszy
	*/
int glowa::get_y()
{
	return y;
}
