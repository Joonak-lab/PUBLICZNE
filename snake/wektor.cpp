
#include "snake.h"

#include "wektor.h"

/** Metoda usuwa pami�� zaalokowan� przez elementy listy
	@param wska�nik na pocz�tkowy element listy
	@param wska�nik na ko�cowy element listy
	*/
void wektor::usun(wektor*& head, wektor*& tail)
{
	while (head)
	{
		wektor* usun = head;
		head = head->next;
		delete usun;
	}
	tail = 0;
	head = 0;
}
/** Metoda liczy ile element�w ma lista
	@param wska�nik na pocz�tkowy element listy
	@return liczba elemet�w
	*/
int wektor::ile_elementow(wektor* head)
{
	int ile = 0;
	while (head)
	{
		ile++;
		head = head->next;
	}
	return ile;
}
/** Metoda dodaje element na pocz�tek listy
	@param wska�nik na pocz�tkowy element listy
	@param ostatni kierunek w�a
	*/
void wektor::dodaj_na_poczatek(wektor*& head,int kierunek)
{
	if (!head)
	{
		head = new wektor;
		head->kierunek = kierunek;
		head->next = 0;

	}
	else
	{
		wektor* nowy = new wektor;
		nowy->kierunek = kierunek;
		nowy->next = head;
		head = nowy;
	}
}
/** Metoda ustawia wska�nik na koniec listy
	@param wska�nik na pocz�tkowy element listy
	@return wska�nik na koniec listy
	*/
wektor* wektor::ustaw_tail(wektor* head)
{

	while (head)
	{
		if (head->next == 0)
			break;
		head = head->next;
	}
	return head;
}
/** Metoda usuwa ostatni element z listy
	@param wska�nik na pocz�tkowy element listy
	@param wska�nik na ko�cowy element listy
	*/
void wektor::usun_ostatni(wektor*& head,wektor*& tail)
{
	if (head == tail)
	{
		delete tail;
		head = 0;
		tail = 0;
		return;
	}
	wektor* seek = head;
	while (head)
	{
		if (seek->next == tail)
			break;
		seek = seek->next;
	}
	seek->next = 0;
	if (tail)
		delete tail;
	tail = 0;
}
/** Metoda wypisuje ca�� liste na ekran
	@param wska�nik na pocz�tkowy element listy
	*/
void wektor::wypisz(wektor* head)
{
	while (head)
	{
		std::cout << head->kierunek << "\t";
		head = head->next;
	}
	std::cout <<std::endl;
}
/** Metoda informuj�ca o aktualnym kierunku w�a
	@return aktualny kierunek w�a
	*/
int wektor::get_kierunek()
{
	return kierunek;
}
