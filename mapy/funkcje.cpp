/** @file */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <crtdbg.h>

#include "funkcje.h"


//wyszukiwanie wycieków pamiêci
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


using namespace std;


void wyczysc(string o)
{
	fstream plik;
	plik.open(o, ios::out | ios::trunc);
	plik.close();

}


int wczytaj(punkty*& head, string argv) //tworzenie bazy danych o miastach
{
	bool p; 
	int powt = 0;
	string punkt;
	ifstream plik;
	plik.open(argv);

	if (plik.good() == false) 
	{
		cerr << "Nie wczytano pliku drogi!";
		return 0;
	}

	else 
	{
		while (!plik.eof())
		{
			powt++;
			p = 0;

			punkty* szukaj; 
			szukaj = head;

			plik >> punkt;

			for (int i = 0; i < punkt.size(); i++)//zamiana na wielkie litery
			  punkt[i]=toupper(punkt[i]); 
		
			
			

			if (powt % 3 != 0) //co 3 wczytanie to liczba - wiec je trzeba pominac
			{
				while (szukaj != NULL) //szukanie czy miasto nie znajduje sie juz w bazie
				{
					if (punkt == szukaj->miasto) 
						p = 1;

					szukaj = szukaj->nextpunkty;
				}

				if (p != 1) //jesli go nie ma w niej dodajemy je do bazy
				{
					punkty* temp = new punkty;
					temp->miasto = punkt;

					if (head == nullptr)
					{
						head = temp;
						temp->nextpunkty = nullptr;
					}

					else
					{
						temp->nextpunkty = head;			
						head = temp;
					}
				}
			}
		}
	}

	plik.close();
	int n = 0;
	punkty* szukaj = head;

	while (szukaj != nullptr) //ilosc unikatowych miast
	{
		n++;
		szukaj = szukaj->nextpunkty;
	}

	return n; 
}


int wyznacz(podroz*& head, punkty* headpun, podroz*& tail, string argv) 
{
	string punkt;
	ifstream plik;
	bool x = 1;
	bool y = 1;
	plik.open(argv);

	if (plik.good() == false) 
	{
		cout << "Nie udalo sie wczytac pliku do_wyznaczenia!";
		return 0;
	}

	else 
	{
		while (!plik.eof())
		{
			x = 1;
			y = 1;
			punkty* szukaj; 
			szukaj = headpun;
			podroz* temp = new podroz;

			plik >> punkt;
			for (int i = 0; i < punkt.size(); i++)
				punkt[i] = toupper(punkt[i]);
			temp->startn = punkt;

			while (szukaj != nullptr) //wyznaczanie miasta, ktory ma byc punktem poczatkowym na trasie
			{
				if (szukaj->miasto == punkt) 		
					x = 0; //znalezione - zmieniam wartosc bool na 0
		
				szukaj = szukaj->nextpunkty;
			}

			if (x == 1) //jesli nie ma miasta w bazie
			{
				cout << "Miasto " << punkt << " nie wystepuje na mapie. Trasa " << punkt << " ";
				plik >> punkt;
				for (int i = 0; i < punkt.size(); i++)//zamiana na wielkie litery
					punkt[i] = toupper(punkt[i]);
				cout << punkt << " nie zostanie wpisana do mapy" << endl;
				delete temp;
			}

			szukaj = headpun;

			if (x == 0)
			{
				plik >> punkt;
				for (int i = 0; i < punkt.size(); i++)//zamiana na wielkie litery
					punkt[i] = toupper(punkt[i]);

				temp->celn = punkt;

				while (szukaj != nullptr) //wyznaczanie miasta, ktory ma byc celem podrozy
				{
					if (szukaj->miasto == punkt) 
						y = 0; //znalezione - zmieniam wartosc bool na 0
					
					szukaj = szukaj->nextpunkty;
				}

				if (y == 1) //jesli miasto nie zostalo znalezione
				{
					cout << "Miasto " << punkt << " nie wystepuje na mapie. Trasa " << temp->startn << " " << punkt << " nie zostanie wpisana do mapy" << endl;
					delete temp;
				}
			}

			if (x == 0 && y == 0) //jesli punkt startowy i cel zostal wyznaczony pomyslnie dodaje go do listy
			{
				temp->nextcel = nullptr;

				if (head == 0)
				{
					head = temp;
					tail = temp;
					temp = NULL;
				}

				else
				{
					tail->nextcel = temp;
					tail = temp;
					temp = NULL;
				}
			}
		}
	}

	plik.close();
	cout << endl;
	int petla = 0;
	podroz* temp = head;

	while (temp != nullptr) //wyznaczanie liczby tras do wyznaczenia
	{
		petla++;
		temp = temp->nextcel;
	}

	return petla; 
}

void drogi(slistEl*& graf, string dod)
{
	slistEl* nowy;
	string punkt; 
	ifstream plik;
	string temp; 
	int w = 0;
	string x;
	string y;
	plik.open(dod);
	if (plik)
	{
		while (!plik.eof())
		{

			plik >> punkt;
			for (int i = 0; i < punkt.size(); i++)//zamiana na wielkie litery
				punkt[i] = toupper(punkt[i]);
			temp = punkt;
			x = punkt;


			plik >> punkt;
			for (int i = 0; i < punkt.size(); i++)//zamiana na wielkie litery
				punkt[i] = toupper(punkt[i]);
			y = punkt;

			plik >> w; 

			if (w <= 0) //jesli dlugosc trasy jest niedodatnia
				cout << "Nieprawidlowa dlugosc drogi " << temp << " " << punkt << ". Ta droga zostaje pominieta." << endl;

			else 
			{
				bool p = 0;
				nowy = new slistEl;            
				nowy->x = x;
				nowy->v = y;
				nowy->w = w;
				nowy->nextsasiad = 0;
				nowy->nextwierz = 0;

				if (graf==0)//jesli nie ma elementow w liscie
					graf = nowy;	

				else 
				{
					slistEl* temp = graf;

					while (temp)//szukanie czy miasto poczatkowe istnieje juz w liscie 
					{
						if (temp->x == nowy->x) // jesli istnieje wpisuje go jako sasiada wierzcholka
						{
							while (temp->nextsasiad)//ustawienie wskaŸnika na koniec listy
								temp = temp->nextsasiad;
							
							temp->nextsasiad = nowy;//dodanie do sasiadow na koniec
							p = 1;
						}
						temp = temp->nextwierz;
					}

					if (p != 1)//jesli nie ma wierzcholka poczatkowego w liscie dodaje go jako nowy wierzcholek
					{
						nowy->nextwierz = graf;
						graf = nowy;
				
					}
				}
								
			}
		}
	}
	plik.close();
	cout << endl;

}

void sciezki(int n, slistEl* graf, punkty*& headpunkty, dane* headdane) 
{

	string min;
	slistEl* obl = nullptr;
	
	for (int i = 0; i < n; i++)
	{
		dane* temp = headdane;
		slistEl* pw = graf;
		punkty* usun = headpunkty;
		dane* save = 0;
		dane* szukacz = headdane;
		int minwaga = MAXINT;

		while (szukacz)
		{
			if (minwaga > szukacz->waga && szukacz->zbiorQ == true)
			{
				min = szukacz->wierzcholek;
				save = szukacz;
				minwaga = szukacz->waga;

			}

			szukacz = szukacz->nextdane;
		}

		if (save)
		{
			save->zbiorQ = false;

			while (pw) //szukanie wierzcholka o najmniejszym koszcie dotarcia w grafie
			{
				if (pw->x == min)
					obl = pw;

				pw = pw->nextwierz;
			}

			while (obl)
			{
				dane* szukaj = headdane;
				while (szukaj->wierzcholek != obl->v)//szukanie miasta sasiedztwa w liœcie informacji 
					szukaj = szukaj->nextdane;
				

				if (szukaj->waga > save->waga + obl->w)//jesli znaleziona waga jest mniejsza od wpisanej w informacjach
				{
					szukaj->waga = save->waga + obl->w;
					szukaj->poprzednik = save->wierzcholek;
				}
				obl = obl->nextsasiad;
			}
		}
		else
			break;
	}


}
	

void inicjacja(int n, dane*& head, punkty* punktyhead)
{
	punkty* nazwa = punktyhead;
	for (int i = 0; i < n; i++)
	{
		dane* nowy = new dane;

		nowy->wierzcholek = nazwa->miasto;
		nowy->waga = MAXINT;
		nowy->poprzednik = "KONIEC";
		nowy->zbiorQ = true;
		

		if (head == 0)
		{
			nowy->nextdane = nullptr;
			head = nowy;
		
		}
		else
		{
			nowy->nextdane = head;
			head = nowy;
		}
		nazwa = nazwa->nextpunkty;
	}

}

void zapisz(podroz* headpodroz, punkty* headpunkty, podroz* idz, dane* headdane, string o)
{
	miasta* head = 0;
	int ode = 0;
	fstream plik;

	plik.open(o, ios::out | ios::ate | ios::app);
	string j;
	plik << idz->startn << "-->" << idz->celn << ": ";

	dane* koniec = headdane;
	while (koniec->wierzcholek != idz->celn)//szukanie informacji o wierzcholku koncowym
		koniec = koniec->nextdane;

	if (koniec->waga == MAXINT)//jesli algorytm nie wyznaczyl drogi do punktu docelowego
	plik << "TRASA NIEMOZLIWA DO WYZNACZENIA!" << endl;

	else
	{
		plik << "(" << koniec->waga << ") km" << endl;
		for (j = idz->celn; j != "KONIEC"; j = koniec->poprzednik)//zapisujemy sciezke do napotkania napisu "KONIEC"
		{
			koniec = headdane;
			while (j != koniec->wierzcholek)
				koniec = koniec->nextdane;

			miasta* temp = new miasta;
			temp->miasto = koniec->wierzcholek;
			temp->waga = koniec->waga;
			temp->next = nullptr;

			if (head == nullptr)
				head = temp;

			else
			{
				temp->next = head;
				head = temp;
			}

		}

		miasta* wys = head;

		while (wys->next)//wyswietlanie kolejnych etapow drogi
		{
			plik<< wys->miasto << "--->" << wys->next->miasto << "\t" << wys->next->waga - ode << "km" << endl;
			ode = wys->next->waga;

			wys = wys->next;
		}

		while (head)//usuwanie niepotrzebnych informacji wyswietlajacych
		{
			auto p = head->next;
			delete head;
			head = p;
		}
	}
	plik << endl;
	plik.close();
}




void zwolnij(podroz*& headpodroz, podroz*& tailpodroz, slistEl*& graf, punkty*& headpunkty, dane*& headdane) 
{
	while (headdane)
	{
		auto p = headdane;
		headdane = headdane->nextdane;
		delete p;
	}

	while (headpunkty)
	{
		auto p = headpunkty;
		headpunkty = headpunkty->nextpunkty;
		delete p;
	}

	while (headpodroz) 
	{
		auto p = headpodroz->nextcel;
		delete headpodroz;
		headpodroz = p;
	}

	tailpodroz = 0;
	headdane = 0;
	headpunkty = 0;
	headpodroz = 0;
	
	while (graf)
	{
		
		slistEl* szukaj = graf;
		slistEl* sasiad = szukaj;
	
		if (szukaj->nextsasiad)
		{
			sasiad = szukaj->nextsasiad;
			while (sasiad)
			{
				slistEl* temp = sasiad;
				sasiad = sasiad->nextsasiad;
				delete temp;
			}
			
		}

		graf = graf->nextwierz;
		delete szukaj;
	}
	
	graf = 0;

}