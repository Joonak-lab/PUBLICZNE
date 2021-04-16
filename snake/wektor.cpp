
#include "snake.h"

#include "wektor.h"

/** Metoda usuwa pamiÍÊ zaalokowanπ przez elementy listy
	@param wskaünik na poczπtkowy element listy
	@param wskaünik na koÒcowy element listy
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
/** Metoda liczy ile elementÛw ma lista
	@param wskaünik na poczπtkowy element listy
	@return liczba elemetÛw
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
/** Metoda dodaje element na poczπtek listy
	@param wskaünik na poczπtkowy element listy
	@param ostatni kierunek wÍøa
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
/** Metoda ustawia wskaünik na koniec listy
	@param wskaünik na poczπtkowy element listy
	@return wskaünik na koniec listy
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
	@param wskaünik na poczπtkowy element listy
	@param wskaünik na koÒcowy element listy
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
/** Metoda wypisuje ca≥π liste na ekran
	@param wskaünik na poczπtkowy element listy
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
/** Metoda informujπca o aktualnym kierunku wÍøa
	@return aktualny kierunek wÍøa
	*/
int wektor::get_kierunek()
{
	return kierunek;
}
