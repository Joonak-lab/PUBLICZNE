#pragma warning(disable : 4996)

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "info.h"
#include "punkt.h"
#include "Cglowa.h"
#include "snake.h"
#include "pokarm.h"
#include "wektor.h"
#include "funkcje.h"
#include <time.h>
#include <fstream>
#define	KLAWISZFUNSTRZALKI 0
#define	KLAWISZFUNNUMPAD -32
#define	GORA 72
#define	DOL 80
#define	LEWO 75
#define	PRAWO 77
using namespace std;


int main(int argc, char* argv[])
{
	bool zapisz = 0;
	bool wczytaj = 0;
	time_t t;
	srand((unsigned)time(&t));
	int sz = 0;
	int dl = 0;
	int dlb = 20;
	char* gr = new char[5];
	strcpy(gr, "anon");
	string nz;

	if (argc < 2)
	{
		cout << "NIE WPISANO ZADNYCH PARAMETROW STARTOWYCH. STOSUJE DOMYSLNE... LISTA MOZLIWYCH PRZELACZNIKOW:\n" <<
			"-sz (wartosc) : szybkosc startowa weza\n-dl (wartosc) : dlugosc startowa weza\n-b (wartosc) : dlugosc boku planszy\n-ng (nazwa) : nazwa gracza\n-pl (sciezka) : sciezka dostepu zapisu gry" << endl
			<< "W kazdym momencie mozna zapauzowac i zapisac gre przyciskiem p" << endl;
		cout << "Wcisnij dowolny przycisk, aby zagrac w gre..." << endl;
		_getch();
		system("cls");
	}
	else
	{

		for (int i = 0; i < argc; i++)
		{

			if (_stricmp(argv[i], "-sz") == 0)
			{
				i++;
				sz = atoi(argv[i]);
			}

			else if (_stricmp(argv[i], "-dl") == 0)
			{
				i++;
				dl = atoi(argv[i]);
			}

			else if (_stricmp(argv[i], "-b") == 0)
			{
				i++;
				dlb = atoi(argv[i]);
				if (dlb < 10)
				{
					cout << "Za maly bok planszy..." << endl;
					dlb = 30;
				}
			}

			else if (_stricmp(argv[i], "-ng") == 0)
			{
				i++;
				delete[] gr;
				gr = argv[i];
			}

			else if (_stricmp(argv[i], "-pl") == 0)
			{
				
				i++;
				wczytaj = 1;
				nz = argv[i];
			}
		}
	}
	info* info1 = new info(sz,dl,dlb,gr,nz);
	snake* snake1 = new snake(dl,sz);
	glowa* glowa1 = new glowa(dlb);
	pokarm* pokarm1 = new pokarm(dlb);

	punkt* pglowa = glowa1;
	punkt* ppokarm = pokarm1;
	wektor* head = 0;
	wektor* tail = head;

	if (wczytaj)
	{
		cout << "Wczytuje zapis..." << endl;
		wczytaj_z_pliku(glowa1, pokarm1, snake1, head,info1);
		dlb = info1->get_dlb();
		tail = head->ustaw_tail(head);
	}

	if (dl > ((dlb / 2) - 1)&& wczytaj == 0)
	{
		dl = (dlb / 2) - 1;
		snake1->set_dlugosc(dl);
	}

	char** plansza = stworz_plansze(pglowa->get_x(),pglowa->get_y(), ppokarm->get_x(), ppokarm->get_y(),pokarm1,dlb);

	if (dl > 0 && wczytaj == 0)
		powiekszweza(plansza, dl, head, dlb);
	
	modyfplansze(plansza, pokarm1, snake1->get_kierunek(), glowa1, snake1, head,dlb);
	cout << "GRA ZARAZ SIE ROZPOCZNIE!" << endl;
	Sleep(5000);
	system("cls");

	while (snake1->sprawdz_stan() != 1)
	{		
		int szybkosc = 250 - (5 * snake1->get_szybkosc());
		if (szybkosc < 0)
			szybkosc = 0;
		if (snake1->get_kierunek() == GORA || snake1->get_kierunek() == DOL)
			szybkosc = szybkosc + 30;

		cout << snake1;
		Sleep(szybkosc);

		if (_kbhit())
		{
			char ch = _getch();
			if (ch == KLAWISZFUNSTRZALKI || ch == KLAWISZFUNNUMPAD)
				zmienkierunek(snake1);
			else if (ch == 'p' || ch == 'P')
			{
				zapisz = menu();
				if (zapisz)
				{
					string nazwa;
					nazwa = generuj_nazwe();
					zapisz_do_pliku(glowa1, pokarm1, snake1, head, info1,nazwa);
					break;
				}
				
			}
		}

		sprawdzczyzjedzone(glowa1,pokarm1,snake1,plansza,dlb);

		head->dodaj_na_poczatek(head, snake1->get_kierunek());
		tail = head->ustaw_tail(head);
		
		if (head->ile_elementow(head) != (snake1->get_dlugosc()))
		{
			tail->usun_ostatni(head, tail);
			tail = head->ustaw_tail(head);
		}

		modyfplansze(plansza,pokarm1,snake1->get_kierunek(),glowa1,snake1,head,dlb);	
		narysuj_plansze(plansza,dlb);
	}

	narysuj_plansze(plansza,dlb);

	if (snake1->sprawdz_stan() == 1)
	{
		zapisz_wynik(snake1, info1);
		cout << "PRZEGRALES! UZYSKALES: " << snake1->get_punkty() << " PUNKTOW" << endl;
	}

	delete glowa1;
	delete info1;
	delete snake1;
	delete pokarm1;
	for (int i = 0; i < dlb; i++)
		delete[] plansza[i];
	delete plansza;
	head->usun(head, tail);
	delete[] gr;
	return 0;
} 

