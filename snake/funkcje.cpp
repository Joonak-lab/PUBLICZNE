

#include "Cglowa.h"
#include "pokarm.h"
#include "snake.h"
#include "wektor.h"

#include "funkcje.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
#define	GORA 72
#define	DOL 80
#define	LEWO 75
#define	PRAWO 77
#define	CIALO '#'
/** Funkcja wstawia do planszy wê¿a
	@param podwójny wskaŸnik na plansze do gry
	@param dlugosc wê¿a
	@param wskaŸnik na pocz¹tkowy element listy
	@param sk³adowa x g³owy wê¿a
	@param sk³adowa y g³owy wê¿a
	*/
void narysujweza(char**& plansza, int dl, wektor* head,int gl_x , int gl_y)
{
	while (dl!=0)
	{
		char ch = CIALO;
		if (dl == 1)
			ch = '?';

		switch (head->kierunek)
		{
		case GORA:
		{
			gl_y++;
			plansza[gl_x][gl_y] = ch;
				break;
		}
		case DOL:
		{
			gl_y--;
			plansza[gl_x][gl_y] = ch;
			break;
		}
		case LEWO:
		{
			gl_x++;
			plansza[gl_x][gl_y] = ch;
			break;
		}
		case PRAWO:
		{
			gl_x--;
			plansza[gl_x][gl_y] = ch;
			break;
		}
		}

		head = head->next;
		dl--;
	}
}

/** wyœwietla komunikat o pauzie w grze
@return decyzje o zapisaniu gry
*/
int menu()
{
	std::cout << "\n\n\n\n\n\t\tNACISNIJ P, ZEBY ZAPISAC GRE..." << std::endl << "\t\tJESLI NIE, WCISNIJ INNY KLAWISZ...";
	char ch = _getch();
	if (ch == 'p' || ch == 'P')
		return 1;
	system("cls");
	return 0;
}

/** Funkcja zapisuje wynik rozgrywki do pliku
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na obiekt klasy info
	*/
void zapisz_wynik(snake* snake1, info* info1)
{
	ofstream plik;
	plik.open("historia.txt",ios::app |  ios::out);
	
	plik << "Gracz " << info1->nazwa_gracza << " uzyskal: " << snake1->get_punkty() << " punktow" << endl << "------------------------------------------------------------------------------" << endl;
	
	plik.close();

}
/** Funkcja zapisuje stan aktualnej rozgrywki do pliku zapisu

	@param wskaŸnik na obiekt klasy glowa
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy info
	@param nazwa pliku do zapisu
	*/
void zapisz_do_pliku(glowa* glowa1, pokarm* pokarm1, snake* snake1, wektor* head,info* info1,string s)
{

	ofstream plik(s, ios::binary | ios::out);
	plik.write((const char*)&info1->dlugosc_boku, sizeof(int));
	plik.write((const char*)&glowa1->x, sizeof(int));
	plik.write((const char*)&glowa1->y, sizeof(int));
	plik.write((const char*)&pokarm1->x, sizeof(int));
	plik.write((const char*)&pokarm1->y, sizeof(int));
	plik.write((const char*)&pokarm1->rodzaj_pokarmu, sizeof(int));
	plik.write((const char*)&snake1->punkty, sizeof(int));
	plik.write((const char*)&snake1->dlugosc, sizeof(int));
	plik.write((const char*)&snake1->szybkosc, sizeof(int));
	plik.write((const char*)&snake1->kierunek, sizeof(int));
	while (head)
	{
		plik.write((const char*)&head->kierunek, sizeof(int));
		head = head->next;
	}
	plik.close();

}
/** Funkcja wczytuje stan rozgrywki z pliku
	@param wskaŸnik na obiekt klasy glowa
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy info
	*/
 void wczytaj_z_pliku(glowa*& glowa1, pokarm*& pokarm1, snake*& snake1, wektor*& head, info*& info1)
{

	 ifstream plik(info1->nazwa_pliku_do_odczytu, ios::binary | ios::in);
	 if (plik)
	 {
		 plik.read((char*)&info1->dlugosc_boku, sizeof(int));
		 plik.read((char*)&glowa1->x, sizeof(int));
		 plik.read((char*)&glowa1->y, sizeof(int));
		 plik.read((char*)&pokarm1->x, sizeof(int));
		 plik.read((char*)&pokarm1->y, sizeof(int));
		 plik.read((char*)&pokarm1->rodzaj_pokarmu, sizeof(int));
		 pokarm1->ile_punktow = 10 * pokarm1->rodzaj_pokarmu;
		 switch (pokarm1->rodzaj_pokarmu)
		 {
		 case 1:
		 {
			 pokarm1->symbol = 222;
			 break;
		 }
		 case 2:
		 {
			 pokarm1->symbol = 251;
			 break;
		 }
		 case 3:
		 {
			 pokarm1->symbol = 212;
			 break;
		 }
		 }
		 plik.read((char*)&snake1->punkty, sizeof(int));
		 plik.read((char*)&snake1->dlugosc, sizeof(int));
		 plik.read((char*)&snake1->szybkosc, sizeof(int));
		 plik.read((char*)&snake1->kierunek, sizeof(int));
		 int dl = snake1->dlugosc;

		 while (dl != 0)
		 {
			 if (head == 0)
			 {
				 head = new wektor;
				 plik.read((char*)&head->kierunek, sizeof(int));
				 head->next = 0;
			 }
			 else
			 {
				 wektor* p = head;
				 wektor* tail = p->ustaw_tail(p);

				 wektor* nowy = new wektor;
				 tail->next = nowy;
				 plik.read((char*)&nowy->kierunek, sizeof(int));
				 nowy->next = 0;

			 }
			 dl--;
		 }
	 }
}

 /** Funkcja modyfikuje plansze do aktualnej rozgrywki i sprawdza czy wyst¹pi³a kolizja
	@param podwójny wskaŸnik na plansze do gry
	@param wskaŸnik na obiekt klasy pokarm
	@param aktualny kierunek wê¿a
	@param wskaŸnik na obiekt klasy glowa
	@param wskaŸnik na obiekt klasy snake
	@param wskaŸnik na pierwszy element listy
	@param d³ugoœæ boku planszy
	*/
void modyfplansze(char**& plansza, pokarm* pokarm1, int kier, glowa*& glowa1, snake*& snake1,wektor* head,int R)
{
	for (int i = 1; i < R - 1; i++)
	{
		for (int j = 1; j < R - 1; j++)
			plansza[j][i] = ' ';
	}
	zmienglowa(kier, glowa1, plansza,snake1);
	narysujweza(plansza, snake1->get_dlugosc(), head, glowa1->get_x(), glowa1->get_y());
	if (plansza[glowa1->get_x()][glowa1->get_y()] != ' ')
		snake1->set_stan(1);
	
	plansza[pokarm1->get_x()][pokarm1->get_y()] = pokarm1->get_symbol();
	plansza[glowa1->get_x()][glowa1->get_y()] = glowa1->symbol;
	
}
/** Funkcja powiêksza wê¿a o wpisany w parametrach rozmiar
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ wê¿a
	@param wskaŸnik na pierwszy element listy
	@param d³ugoœæ boku planszy
	*/
void powiekszweza(char**& plansza, int dl, wektor*& head, int dlb)
{
	int i = dlb / 2;
	int j = i;
	while (dl>-1)
	{
		plansza[i][j] = CIALO;
		dl--;
		i--;
		head->dodaj_na_poczatek(head, PRAWO);
	}
}
/** Funkcja tworzy plansze
	@param sk³adowa x g³owy wê¿a
	@param sk³adowa y g³owy wê¿a
	@param sk³adowa x owoca
	@param sk³adowa y owoca
	@param wskaŸnik na obiekt klasy pokarm
	@param d³ugoœæ boku planszy
	@return podwójny wskaŸnik na tablice char
	*/
char** stworz_plansze(int glowa_x,int glowa_y,int owoc_x, int owoc_y, pokarm* pokarm1,int R)
{
		char** tab = new char* [R];

		for (int i = 0; i < R; i++)
			tab[i] = new char[R];

		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < R; j++)
				tab[j][i] = ' ';
		}

		for (int i = 0; i < R; i++)
			tab[0][i] = 'X';

		for (int i = 0; i < R; i++)
			tab[i][0] = 'X';

		for (int i = 0; i < R; i++)
			tab[i][R-1] = 'X';

		for (int i = 0; i < R; i++)
			tab[R-1][i] = 'X';

			tab[glowa_x][glowa_y] = 1;

			tab[owoc_x][owoc_y] = pokarm1->symbol;

			
		return tab;
}
/** Funkcja tworzy nazwe pliku do zapisu stanu gry
	@return ³añcuch znaków
*/
std::string generuj_nazwe()
{
	string tmp_s;
	const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";


	for (int i = 0; i < 10; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

	tmp_s = tmp_s + ".bin";
	return tmp_s;
}

/** Funkcja wyœwietla na ekranie zawartoœæ obiektu klasy snake
	@param strumieñ wyjœcia do zmodyfikowania
	@param wskaŸnik na obiekt klasyt snake
	@return strumieñ wyjœcia
*/
std::ostream& operator<<(std::ostream& s,  snake* info1)
{
	s << "szybkosc: " << info1->szybkosc << "\t dlugosc: " << info1->dlugosc << "\t punkty: " << info1->punkty << std::endl;
	return s;
}
/** Funkcja wyœwietla plansze
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ boku planszy
	*/
void narysuj_plansze(char** plansza,int R)
{
	system("cls");
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++)
			std::cout << plansza[j][i];
		std::cout << std::endl;
	}
}
/** Funkcja zmienia aktualny kierunek wê¿a
@param wskaŸnik na obiekt klasy snake
*/
void zmienkierunek(snake*& snake1)
{
	char ch = _getch();
	switch (ch)
	{
	case GORA:
	{
		if (snake1->get_kierunek()!= DOL)
			snake1->set_kierunek(ch);
		break;
		
	}
	case DOL:
	{
		if (snake1->get_kierunek() != GORA)
			snake1->set_kierunek(ch);
			break;
		
	}	
	case LEWO:
	{
		if (snake1->get_kierunek() != PRAWO)
			snake1->set_kierunek(ch);
			break;
		
	}
	case PRAWO:
	{
		if (snake1->get_kierunek() != LEWO)
			snake1->set_kierunek(ch);
			break;
		
	}
		
	}
}
/** Funkcja przesuwa g³owê wê¿a na planszy
	@param aktualny kierunek wê¿a
	@param wskaŸnik na obiekt klasy glowa
	@param podwójny wskaŸnik na plansze
	@param wskaŸnik na obiekt klasy snake
	*/
void zmienglowa(int kier, glowa*& glowa1, char**& plansza,snake*& snake1)
{
	plansza[glowa1->get_x()][glowa1->get_y()] = ' ';
	switch (kier)
	{
	case GORA:
	{
		glowa1->set_y((glowa1->get_y()) - 1);
		break;
	}
	case DOL:
	{
		glowa1->set_y((glowa1->get_y()) + 1);
		break;
	}
	case LEWO:
	{
		glowa1->set_x((glowa1->get_x()) - 1);
		break;
	}
	case PRAWO:
	{
		glowa1->set_x((glowa1->get_x()) + 1);
		break;
	}
	}
	
}
/** Funkcja powiêksza wê¿a o wpisany w parametrach rozmiar
	@param wskaŸnik na pierwszy element listy
	@param wskaŸnik na obiekt klasy pokarm
	@param wskaŸnik na obiekt klasy snake
	@param podwójny wskaŸnik na plansze do gry
	@param d³ugoœæ boku planszy
	*/
void sprawdzczyzjedzone(glowa* glowa1, pokarm*& pokarm1, snake*& snake1,char**& plansza,int R)
{
	if ((glowa1->get_x() == pokarm1->get_x()) && (glowa1->get_y() == pokarm1->get_y()))
	{
		snake1->zjedzony(pokarm1->get_punkt());
		pokarm1->zjedzony(plansza,R);
		plansza[pokarm1->get_x()][pokarm1->get_y()] = pokarm1->symbol;
	
	}

}



