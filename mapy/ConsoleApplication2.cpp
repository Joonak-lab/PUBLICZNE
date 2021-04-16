/** @file */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <crtdbg.h>

#include "funkcje.h"

///wyświetlanie wycieków pamięci
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;



int main(int argc, char* argv[])
{

	int n; //ilosc miejscowosci
	int petla; //ilosc tras do wyznaczenia
	string o, t, dod;
	punkty* headpunkty = 0;
	podroz* headpodroz = 0;
	podroz* tailpodroz = 0;
	dane* headdane = 0;
	slistEl* graf=0;                

	//wczytywanie parametrow startowych
	if (argc < 7)
	{
		cout << "Nie wprowadzono wszystkich argumentow. " << endl;
		cout << "-d: wczytaj plik z drogami" << endl;
		cout << "-t: wczytaj plik z trasami do wyznaczenia" << endl;
		cout << "-o: zapisz do pliku wynikowego" << endl;
		return 0;
	}
	
	else
	{
		for (int i = 0; i < argc; i++)
		{

			if (_stricmp(argv[i], "-d") == 0)
			{
				i++;
				dod = argv[i];
			}

			else if (_stricmp(argv[i], "-t") == 0)
			{
				i++;
				t = argv[i];
			}

			else if (_stricmp(argv[i], "-o") == 0)
			{
				i++;
				o = argv[i];
			}
		}
	}
	
	wyczysc(o);

	n = wczytaj(headpunkty, dod);



	petla = wyznacz(headpodroz, headpunkty, tailpodroz, t);

	drogi(graf, dod);
	
	inicjacja(n, headdane, headpunkty);

	podroz* idz = headpodroz;
	
	while (petla > 0)
	{
		
		petla--;

		dane* startowy = headdane;
		while (startowy) //koszt dotarcia do punktu poczatkowego jest rowny 0
		{
			if (startowy->wierzcholek == idz->startn)
				startowy->waga = 0;

			startowy = startowy->nextdane;
		}

		sciezki(n, graf, headpunkty, headdane);

		zapisz(headpodroz, headpunkty, idz, headdane, o);

		cout << endl;
		idz = idz->nextcel;
		if (petla > 0) //resetowanie informacji dla algorytmu 
		{
			punkty* nazwa = headpunkty;
			dane* czyszczenie = headdane;

			while (czyszczenie)
			{
				czyszczenie->wierzcholek = nazwa->miasto;
				czyszczenie->waga = MAXINT;
				czyszczenie->poprzednik = "KONIEC";
				czyszczenie->zbiorQ = true;
				czyszczenie = czyszczenie->nextdane;
				nazwa = nazwa->nextpunkty;
			}
			
		}
		
	}
	
	zwolnij(headpodroz, tailpodroz, graf, headpunkty, headdane);
	
	_CrtDumpMemoryLeaks();
	return 0;
}
