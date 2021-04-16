
#include "Cglowa.h"
/** konstruktor dla klasy glowa
	@param rozmiar planszy
	*/
glowa::glowa(int R)
{
	x = y = R / 2;
	symbol = 1;
}
/** Metoda ustawiaj¹ca sk³adow¹ x g³owy
	@param aktualna sk³adowa x g³owy na planszy
	*/
void glowa::set_x(int liczba)
{
	x = liczba;
}
/** Metoda ustawiaj¹ca sk³adow¹ y g³owy
@param aktualna sk³adowa y g³owy na planszy
*/
void glowa::set_y(int liczba)
{
	y = liczba;
}
/** Metoda zwracaj¹ca sk³adow¹ x g³owy
	@return aktualna sk³adowa x g³owy na planszy
	*/
int glowa::get_x()
{
	return x;
}
/** Metoda zwracaj¹ca sk³adow¹ y g³owy
	@return aktualna sk³adowa y g³owy na planszy
	*/
int glowa::get_y()
{
	return y;
}
