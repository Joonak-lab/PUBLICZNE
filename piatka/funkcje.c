#pragma warning(disable : 4996)
/** @file */

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include "funkcje.h"

#define R 20
#define ENTER 13
#define	KLAWISZFUNSTRZALKI 0
#define	KLAWISZFUNNUMPAD -32
#define	GORA 72
#define	DOL 80
#define	LEWO 75
#define	PRAWO 77

char** plansza()
{
	char** plansza = malloc(R * sizeof(char*));

	if (plansza)
	{
		for (int i = 0; i < R; i++)
			plansza[i] = malloc(R * sizeof(char));

		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < R; j++)
				plansza[i][j] = ' ';
		}

	}
	return plansza;
}

int losujktopierwszy()
{
	time_t t;
	srand((unsigned)time(&t));

	int liczba = rand() % 2;
	return liczba;
}

int ktopierwszy(char** gra, int* pwiersz, int* pkolumna)
{
	puts("Witaj w grze piatka!");
	int losujktopierwszy();

	int ktozaczyna = losujktopierwszy();
	if (ktozaczyna == 1)
	{
		puts("Zaczyna komputer!");
		wylosuj(gra, pwiersz, pkolumna);
	}
	else
		puts("Zaczyna gracz!");
	return ktozaczyna;
}

element* DodajDoListyO(element* head, int wierszkomputer, int kolumnakomputer)
{
	if (head == NULL)
	{
		head = (element*)malloc(sizeof(element));
		head->kto_sie_ruszyl = malloc(9 * sizeof(char));
		strcpy(head->kto_sie_ruszyl, "Komputer");
		head->nr_kolumny = kolumnakomputer;
		head->nr_wiersza = wierszkomputer;
		head->pnext = NULL;
	}
	else
	{
		element* koniec = head;
		while (koniec->pnext != NULL) 
			koniec = koniec->pnext;
		koniec->pnext = (element*)malloc(sizeof(element));
		koniec->pnext->nr_kolumny = kolumnakomputer;
		koniec->pnext->nr_wiersza = wierszkomputer;
		koniec->pnext->kto_sie_ruszyl = malloc(9 * sizeof(char));
		strcpy(koniec->pnext->kto_sie_ruszyl, "Komputer");
		koniec->pnext->pnext = NULL;
	}
	return head;
}

element* DodajDoListyX(element* head, int wierszgracz, int kolumnagracz)
{
	if (head == NULL)
	{
		head = (element*)malloc(sizeof(element));
		head->kto_sie_ruszyl = malloc(6 * sizeof(char));
		strcpy(head->kto_sie_ruszyl, "Gracz");
		head->nr_kolumny = kolumnagracz;
		head->nr_wiersza = wierszgracz;
		head->pnext = NULL;
	}
	else
	{
		element* koniec = head;
		while (koniec->pnext != NULL)
			koniec = koniec->pnext;
		koniec->pnext = (element*)malloc(sizeof(element));
		koniec->pnext->nr_kolumny = kolumnagracz;
		koniec->pnext->nr_wiersza = wierszgracz;
		koniec->pnext->kto_sie_ruszyl = malloc(6 * sizeof(char));
		strcpy(koniec->pnext->kto_sie_ruszyl, "Gracz");
		koniec->pnext->pnext = NULL;
	}
	return head;
}

void rozgrywka()
{
	int wygrana, czyremis, kolumnagracz, wierszgracz, zap_kolumna, zap_wiersz, flagapriorytet;
	wygrana = czyremis = kolumnagracz = wierszgracz = flagapriorytet = 0;
	zap_kolumna = zap_wiersz = (R+1);
	element* pHead = NULL;
	char** gra = plansza();
	int ktozaczyna = ktopierwszy(gra, &zap_wiersz, &zap_kolumna);
	if (ktozaczyna == 1)
		pHead = DodajDoListyO(pHead,zap_wiersz,zap_kolumna);
	while(1)
	{
		wygrana = SprawdzCzyWygrana(gra);
		if (wygrana == 1)
			break;
		czyremis = ruchy(&kolumnagracz, &wierszgracz, gra, &zap_wiersz, &zap_kolumna, &flagapriorytet);
		if (czyremis != 0)
		{
			pHead = DodajDoListyX(pHead, wierszgracz, kolumnagracz);
			break;
		}
		pHead = DodajDoListyX(pHead, wierszgracz, kolumnagracz);
		pHead = DodajDoListyO(pHead, zap_wiersz, zap_kolumna);
	} 
	ZapiszDoPliku(pHead);
	pHead = wyczyscliste(pHead);
	gra = wyczyscplansze(gra);
}

int ruchy(int* pkolumnagracz, int* pwierszgracz, char** gra, int* pzap_wiersz, int* pzap_kolumna, int* pflagapriorytet)
{
	int czyremis = 0;

	ruch(pkolumnagracz, pwierszgracz, gra, pzap_wiersz, pzap_kolumna);
	czyremis = remis(gra);
	if (czyremis == 1)
		return 1;

	int wygranaX = SprawdzCzyWygrana(gra);
	if (wygranaX == 1)
		return 2;

	ruchkomputer(gra, pzap_wiersz, pzap_kolumna, pflagapriorytet);
	czyremis = remis(gra);
	if (czyremis == 1)
		return 1;

	return 0;
}

void tab(char** gra, int pozycjag, int pozycjak)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if (pozycjag == 0)
			{
				printf("\033[1;31m");
				printf("<%c>", gra[i][j]);
				printf("\033[0m");
			}
			else if (pozycjak == 0 && pozycjag != 0)
			{
				printf("\033[1;32m");
				printf(">%c<", gra[i][j]);
				printf("\033[0m");
			}
			else
				printf("[%c]", gra[i][j]);

			pozycjag--;
			pozycjak--;
		}
		printf("\n");
	}
}

void komunikat(int wygrana, char** gra)
{
	switch (wygrana)
	{
	case 1:
		{
			tab(gra,-1,-1);
			puts("Wygrales!");
			break;
		}
	case 2:
		{
			tab(gra,-1,-1);
			puts("Przegrales...");
			break;
		}
	}
}

int remis(char** gra)
{
	void tab(char** gra,int pozycjag, int pozycjak);

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if(gra[i][j]==' ')
				return 0;
		}
	}
	puts("Remis!");
	tab(gra,-1,-1);
	return 1;
}

void ruch(int* pkolumnagracz, int* pwierszgracz, char** gra, int* pwierszkomputer, int* pkolumnakomputer)
{
	while (1)
	{
		wybierzmiejsce(gra, pwierszgracz, pkolumnagracz, pwierszkomputer, pkolumnakomputer);

		if (gra[(*pwierszgracz)][(*pkolumnagracz)] == ' ')
		{
			gra[(*pwierszgracz)][(*pkolumnagracz)] = 'X';
			break;
		}
		else
			puts("Bledny ruch!");
		system("cls");
	}
	system("cls");
}

void wybierzmiejsce(char** gra, int* pwierszgracz, int* pkolumnagracz, int* pwierszkomputer, int* pkolumnakomputer)
{
	char ch;
	tab(gra, R * (*pwierszgracz) + (*pkolumnagracz), R * (*pwierszkomputer) + (*pkolumnakomputer));

	while ((ch = getch()) != ENTER)
	{
		if (ch == KLAWISZFUNSTRZALKI || ch == KLAWISZFUNNUMPAD)
			klawisz(pwierszgracz, pkolumnagracz);
	
		else
			puts("zly przycisk");

		system("cls");
		tab(gra, R * (*pwierszgracz) + (*pkolumnagracz), R * (*pwierszkomputer) + (*pkolumnakomputer));
	}
}

void klawisz(int* pwierszgracz, int* pkolumnagracz)
{
	switch (getch())
	{
	case GORA://up
		if ((*pwierszgracz) > 0)
			(*pwierszgracz)--;
		break;
	
	case DOL://down
		if ((*pwierszgracz) < (R-1))
			(*pwierszgracz)++;
		break;
	
	case LEWO://left
		if ((*pkolumnagracz) > 0)
			(*pkolumnagracz)--;
		break;
	
	case PRAWO://right
		if ((*pkolumnagracz) < (R-1))
			(*pkolumnagracz)++;
		break;
	}
}

void ruchkomputer(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet)
{
	int flaga = 0;
	int zagranie = 0;
	int licznik = 0;
	int* pzagranie = &zagranie;

	if ((*pwiersz) == (R+1) || (*pkolumna) == (R + 1))
	{
		wylosuj(gra, pwiersz, pkolumna);
		return;
	}

	WstawDoZapPoz(gra,pwiersz,pkolumna,pflagapriorytet);
}

void wylosuj(char** gra, int* pwiersz, int* pkolumna)
{

	while (1)
	{
		(*pwiersz) = rand() % R;
		(*pkolumna) = rand() % R;
		
		if (gra[(*pwiersz)][(*pkolumna)] == ' ')
		{
			gra[(*pwiersz)][(*pkolumna)] = 'O';
			return;
		}
	}
}

void ZapPoz(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet)
{
	int maxlicznik = 0;
	ZapPozXY4(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
	ZapPozXY3(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
	ZapPozXY2(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
	ZapPozXY(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
	ZapPozX(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
	ZapPozY(gra, pwiersz, pkolumna, pflagapriorytet, &maxlicznik);
}

void WstawDoZapPoz(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet)
{
	int zagranie= 0;
	ZapPoz(gra, pwiersz, pkolumna, pflagapriorytet);

	if ((*pflagapriorytet) != 2)
		KomputerObrona(gra, &zagranie, pwiersz, pkolumna);

	if (zagranie == 1)
		(*pflagapriorytet) = 0;
	
	else
	{
		if ((*pflagapriorytet) == 0)
			ustawO(gra, pwiersz, pkolumna);

		WstawDoNowPoz(gra, pwiersz, pkolumna);
		(*pflagapriorytet) = 0;
	}	
}

void WstawDoNowPoz(char** gra, int* pwiersz, int* pkolumna)
{
	int i = 0;
	int j = -1;
	while (1)
	{
		if (gra[(*pwiersz)][(*pkolumna)] == ' ')
		{
			gra[(*pwiersz)][(*pkolumna)] = 'O';
			break;
		}

		else
		{
			ZnajdzO(&i, &j, gra);
			ustawO(gra, &i, &j);
		}

		if (i == 20)
		{
			wylosuj(gra, &i, &j);
			break;
		}
	}
}

void ZnajdzO(int* i, int* j, char** gra)
{
	(*j)++;
	for ((*i); (*i) < R; (*i)++)
	{
		for ((*j); (*j) < R; (*j)++)
		{
			if (gra[(*i)][(*j)] == 'O')
				return;
		}
		(*j) = 0;
	}
}

void ustawO(char** gra, int* pwiersz, int* pkolumna)
{
	if (((*pwiersz) - 1 > -1) && gra[(*pwiersz) - 1][(*pkolumna)] == ' ') //wstawianie w wierszu nad
		(*pwiersz) = (*pwiersz) - 1;
			
	else if (((*pwiersz) + 1 < R) && gra[(*pwiersz) + 1][(*pkolumna)] == ' ') //wstawianie w wierszu pod
		(*pwiersz) = (*pwiersz) + 1;
			
	else if (((*pkolumna) + 1 < R) && gra[(*pwiersz)][(*pkolumna) + 1] == ' ') //wstawianie w nastepnej kolumnie
		(*pkolumna) = (*pkolumna) + 1;
			
	else if (((*pkolumna) - 1 > -1) && gra[(*pwiersz)][(*pkolumna) - 1] == ' ') //wstawianie w poprzedniej kolumnie
		(*pkolumna) = (*pkolumna) - 1;	
}

void reset(int* licznik, int* wolne_miejsce, int* prio, int* wiersz, int* kolumna,int* pom, int* pom2)
{
	*licznik = *wolne_miejsce = *prio=*pom=*pom2 = 0;
	*wiersz = (R + 1);
	*kolumna = (R + 1);
}

void krzyzyk(int* wolne_miejsce, int* licznik, int* prio)
{
	*wolne_miejsce = *prio = *licznik = 0;
}

void kolko(int* wolne_miejsce, int* licznik)
{
	(*wolne_miejsce)++;
	(*licznik)++;

}

void ZapPozXYspacja(char** gra, int licznik, int* prio, int* pom, int* pom2, int i, int j, int* wiersz, int* kolumna, int* wolne_miejsce)
{
	if (licznik > 1 && gra[j + 1][i - 1] == 'O')
	{
		*prio = 1;
		*pom = j;
		*pom2 = i;
	}

	*wiersz = j;
	*kolumna = i;
	(*wolne_miejsce)++;

}

void UstawLinieXY(char** gra, int j, int i, int* wolne_miejsce, int* licznik, int* prio, int pom, int pom2, int* wiersz, int* kolumna, int stala)
{
	if (*wiersz == (R + 1))
	{
		*wiersz = j - 1;
		*kolumna = i + 1;
	}
	if (*prio == 1)
	{
		*wiersz = pom;
		*kolumna = pom2;
	}
	if (j < 18 && i < 18 - stala)
	{
		if (gra[j - 1][i + 1] == 'O')
			(*licznik)++;
		if (gra[j - 2][i + 2] == 'O')
			(*licznik)++;
	}
}
void ZapPozXY(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i, j, licznik, prio, pom, pom2, wolne_miejsce, wiersz, kolumna;
	for (int stala = 0; stala < 16; stala++) // 19 1 18 2
	{
		reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
		j = 19;
		for (i = stala; i < R; i++)
		{
			if (gra[j][i] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[j][i] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozXYspacja(gra, licznik, &prio, &pom, &pom2, i, j, &wiersz, &kolumna, &wolne_miejsce);		
			if ((licznik > 1 && wolne_miejsce > 4) && ((*maxlicznik) < licznik))
			{
				UstawLinieXY(gra, j, i, &wolne_miejsce, &licznik, &prio, pom, pom2, &wiersz, &kolumna, stala);
				(*maxlicznik) = licznik;
				ZapiszLinie(wiersz, kolumna, licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
			}
			if ((*pflagapriorytet) == 2)
				return;
			if ((licznik!=0 && j < 16) && gra[j + 4][i-4] == 'O')
				licznik--;
			j--;
		}
	}
}

void UstawLinieXY2(char** gra, int j, int i, int* wolne_miejsce, int* licznik, int* prio, int pom, int pom2, int* wiersz, int* kolumna, int stala)
{
	if (*wiersz == (R + 1))
	{
		*wiersz = i + 1;
		*kolumna = j - 1;
	}

	if (*prio == 1)
	{
		*wiersz = pom;
		*kolumna = pom2;
	}

	if (i < 18 && j < 18 - stala)
	{
		if (gra[i + 1][j - 1] == 'O')
			(*licznik)++;
		if (gra[i + 2][j - 2] == 'O')
			(*licznik)++;
	}
}

void ZapPozXY2spacja(char** gra, int licznik, int* prio, int* pom, int* pom2, int i, int j, int* wiersz, int* kolumna, int* wolne_miejsce)
{
	*wiersz = i;
	*kolumna = j;
	(*wolne_miejsce)++;

	if (licznik > 1 && gra[i - 1][j + 1] == 'O')
	{
		*prio = 1;
		*pom = i;
		*pom2 = j;
	}

}

void ZapPozXY2(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i,j, licznik, prio, pom, pom2, wolne_miejsce, wiersz, kolumna;
	for (int stala = 19; stala > 3; stala--) // 0 18, 1 17
	{
		reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
		i = 0;
		for (j = stala; j > -1; j--)
		{
			if (gra[i][j] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[i][j] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozXY2spacja(gra, licznik, &prio, &pom, &pom2, i, j, &wiersz, &kolumna, &wolne_miejsce);
			if ((licznik > 1 && wolne_miejsce > 4) && ((*maxlicznik) < licznik))
			{
				(*maxlicznik) = licznik;
				UstawLinieXY2(gra, j, i, &wolne_miejsce, &licznik, &prio, pom, pom2, &wiersz, &kolumna, stala);
				ZapiszLinie(wiersz, kolumna, licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);	
			}
			if ((*pflagapriorytet) == 2)
				return;
			if ((licznik != 0 && i > 3) && gra[i-4][j + 4] == 'O')
				licznik--;
			i++;
		}
	}
}

void ZapPozXY3spacja(char** gra, int licznik, int* prio, int* pom, int* pom2, int i, int j, int* wiersz, int* kolumna, int* wolne_miejsce)
{
	if (licznik > 1 && gra[i - 1][j - 1] == 'O')
	{
		*prio = 1;
		*pom = i;
		*pom2 = j;
	}

	*wiersz = i;
	*kolumna = j;
	(*wolne_miejsce)++;

}

void UstawLinieXY3(char** gra, int j, int i, int* wolne_miejsce, int* licznik,  int* prio, int pom, int pom2, int* wiersz, int* kolumna, int stala)
{
	if (*wiersz == (R + 1))
	{
		*wiersz = i + 1;
		*kolumna = j + 1;
	}

	if (*prio == 1)
	{
		*wiersz = pom;
		*kolumna = pom2;
	}

	if (i < 18 && j < 18 - stala)
	{
		if (gra[i + 1][j + 1] == 'O')
			(*licznik)++;
		if (gra[i + 2][j + 2] == 'O')
			(*licznik)++;
	}
}

void ZapPozXY3(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i, j, licznik, prio, pom, pom2, wolne_miejsce, wiersz, kolumna;
	for (int stala = 0; stala < 16; stala++) // 01 12
	{
		reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
		i = 0;
		for (j = stala; j < R; j++)
		{
			if (gra[i][j] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[i][j] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozXY3spacja(gra, licznik, &prio, &pom, &pom2, i, j, &wiersz, &kolumna, &wolne_miejsce);
			if ((licznik > 1 && wolne_miejsce > 4) && ((*maxlicznik) < licznik))
			{
				(*maxlicznik) = licznik;
				UstawLinieXY3(gra, i,j,  &wolne_miejsce, &licznik,  &prio, pom, pom2, &wiersz, &kolumna, stala);
				ZapiszLinie(wiersz,kolumna,  licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);	
			}
			if ((*pflagapriorytet) == 2)
				return;
			if ((j > 3 && i > 3) && (licznik != 0 && gra[i-4][j - 4] == 'O'))
				licznik--;
			i++;
		}
	}
}
void ZapPozXY4(char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i, j, licznik, prio, pom, pom2, wolne_miejsce, wiersz, kolumna;
	for (int stala = 0; stala < 16; stala++) // 10 21
	{
		reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
		i = 0;
		for (j = stala; j < R; j++)
		{
			if (gra[j][i] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[j][i] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozXY3spacja(gra, licznik, &prio, &pom, &pom2, j,i,  &wiersz, &kolumna, &wolne_miejsce);
			
			if (licznik > 1 && wolne_miejsce > 4 && ((*maxlicznik) < licznik))
			{
				(*maxlicznik) = licznik;
				UstawLinieXY3(gra, j, i, &wolne_miejsce, &licznik, &prio, pom, pom2, &wiersz, &kolumna, stala);
				ZapiszLinie(wiersz, kolumna, licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				if ((*pflagapriorytet) == 2)
					return;
				reset(&licznik, &wolne_miejsce, &prio, &wiersz, &kolumna, &pom, &pom2);
			}
			if ((licznik != 0 && i > 3) && gra[j - 4][i-4] == 'O')
				licznik--;
			i++;
		}	
	}
}

void ZapiszLinie(int wiersz, int i, int licznik, char** gra, int* pwiersz, int* pkolumna, int* pflagapriorytet)
{
	(*pwiersz) = wiersz;
	(*pkolumna) = i;
	(*pflagapriorytet) = 1;

	if (licznik > 3)
		(*pflagapriorytet) = 2;
}

void ZapPozYspacja(char** gra, int licznik, int* prio, int* pom, int i, int j, int* wiersz, int* wolne_miejsce)
{
	if (licznik > 1 && gra[j - 1][i] == 'O')
	{
		*prio = 1;
		*pom = j;
	}

	*wiersz = j;
	(*wolne_miejsce)++;

}

void UstawLinieY(char** gra, int j, int i, int* wolne_miejsce, int* licznik,  int* prio, int pom, int* wiersz)
{
	if (*wiersz == (R + 1))
		*wiersz = j + 1;

	if (*prio == 1)
		*wiersz = pom;

	if (j < 18)
	{
		if (gra[j + 1][i] == 'O')
			licznik++;
		if (gra[j + 2][i] == 'O')
			licznik++;
	}
}

void ZapPozY(char** gra, int* pwiersz, int* pkolumna,int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i, j, licznik, prio, pom, wolne_miejsce, wiersz;
	for (i = 0; i < R; i++) // szukanie 2 "O" w wierszach
	{
		reset(&licznik, &wolne_miejsce, &prio, &wiersz,&wiersz,&pom,&pom);
		for (j = 0; j < R; j++)
		{
			if (gra[j][i] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[j][i] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozYspacja(gra, licznik, &prio, &pom, i,j, &wiersz, &wolne_miejsce);
			
			if ((licznik > 1 && wolne_miejsce > 4) && ((*maxlicznik) < licznik))
			{
				(*maxlicznik) = licznik;
				UstawLinieY(gra, j, i, &wolne_miejsce, &licznik,  &prio, pom,&wiersz);
				ZapiszLinie(wiersz, i, licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				if ((*pflagapriorytet) == 2)
					return;
				reset(&licznik, &wolne_miejsce, &prio, &wiersz, &wiersz,&pom,&pom);
			}
			if ((licznik != 0 && j>3) && gra[j-4][i]=='O')
				licznik--;
		}
	}
}

void ZapPozXspacja(char** gra, int licznik, int* prio, int* pom, int i, int j, int* kolumna, int* wolne_miejsce)
{
	if (licznik > 1 && gra[i][j - 1] == 'O')
	{
		*prio = 1;
		*pom = j;
	}

	*kolumna = j;
	(*wolne_miejsce)++;

}

void UstawLinieX(char** gra, int j, int i, int* wolne_miejsce, int* licznik, int* prio, int pom, int* kolumna)
{
	if (*prio == 1)
		*kolumna = pom;

	if (j < 18)
	{
		if (gra[i][j + 1] == 'O')
			(*licznik)++;
		if (gra[i][j + 2] == 'O')
			(*licznik)++;
	}

}

void ZapPozX(char** gra, int* pwiersz, int* pkolumna,int* pflagapriorytet, int* maxlicznik)
{
	if ((*pflagapriorytet) == 2)
		return;
	int i, j, licznik, prio, pom, wolne_miejsce, kolumna;
	for (i = 0; i < R; i++) // szukanie 2 "O" w wierszach
	{
		reset(&licznik, &wolne_miejsce, &prio, &kolumna, &kolumna, &pom, &pom);
		for (j = 0; j < R; j++)
		{
			if (gra[i][j] == 'O')
				kolko(&wolne_miejsce, &licznik);
			else if (gra[i][j] == 'X')
				krzyzyk(&wolne_miejsce, &licznik, &prio);
			else
				ZapPozXspacja(gra, licznik, &prio, &pom, i, j, &kolumna, &wolne_miejsce);
			
			if ((licznik > 1 && wolne_miejsce > 4) && ((*maxlicznik) < licznik))
			{
				(*maxlicznik) = licznik;
				UstawLinieX(gra, j, i, &wolne_miejsce, &licznik, &prio, pom, &kolumna);
				ZapiszLinie(i, kolumna, licznik, gra, pwiersz, pkolumna, pflagapriorytet);
				if ((*pflagapriorytet) == 2)
					return;
				reset(&licznik, &wolne_miejsce, &prio, &kolumna, &kolumna, &pom, &pom);
			}
			if ((licznik != 0 && j>3) && gra[i][j-4] == 'O')
				licznik--;
		}
	}
}


void KomputerObrona(char** gra, int* pzagranie, int* pwiersz, int* pkolumna)
{
  	int czterywlinii = 0;
	int* pczterywlinii = &czterywlinii;

	KomputerObronaX(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);
	KomputerObronaY(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);
	KomputerObronaSkos(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);
	KomputerObronaSkos2(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);
	KomputerObronaSkos3(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);
	KomputerObronaSkos4(gra, pzagranie, pwiersz, pkolumna, pczterywlinii);

	if (gra[(*pwiersz)][(*pkolumna)] == ' ')
	{
		(*pzagranie) = 1;
		gra[(*pwiersz)][(*pkolumna)] = 'O';
	}
}

void xzero(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x)
{
	if (gra[j][i] == 'X')
	{
		if ((i != 0 && j != 0) && gra[j - 1][i - 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}

		if ((i != 0 && j != 0) && gra[j - 1][i - 1] == ' ')
		{
			*miejsce = j - 1;
			*miejsce2 = i - 1;
		}
		*x = 1;
	}
}

void xjeden(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x, int* przerwa, int stala)
{
	if (gra[j][i] == 'X')
	{
		if ((j != 19 && i != 19 - stala) && gra[j + 1][i + 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}
	}

	else if (gra[j][i] == 'O' || (*przerwa == 1 && gra[j][i] == ' '))
		reset(licznik, przerwa, x, miejsce, miejsce2, x, flaga);

	else if (gra[j][i] == ' ' && *przerwa == 0)
	{
		*miejsce = j;
		*miejsce2 = i;
		*przerwa = 1;
	}
}

void Zapiszmiejsce(int* miejsce, int* miejsce2, int i, int j, char** gra, int* czterywlinii, int* flaga, int* pwiersz, int* pkolumna, int licznik)
{
	if (*miejsce == (R + 1))
	{
		*miejsce2 = i + 1;
		*miejsce = j + 1;
	}
	if (*miejsce > (R - 1))
		return;

	if (gra[*miejsce][*miejsce2] == ' ' && (*czterywlinii) != 1)
	{
		(*pwiersz) = *miejsce;
		(*pkolumna) = *miejsce2;
		if (licznik == 4 || *flaga == 0)
			(*czterywlinii) = 1;
		if (j != 19 && gra[j + 1][i + 1] == 'X')
			*flaga = 0;
	}
}

void KomputerObronaSkos(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i,j,x,przerwa,licznik,flaga,miejsce,miejsce2;
	for (int stala = 0; stala < 16; stala++) // 10 21
	{	
		reset(&licznik, &przerwa, &i, &miejsce, &miejsce2, &x, &flaga);
		for (j = stala; j < R; j++)
		{
			if (x == 0)
				xzero(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x);
			else
				xjeden(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x, &przerwa, stala);
				
			if (licznik > 2)
				Zapiszmiejsce(&miejsce, &miejsce2, i, j, gra, czterywlinii, &flaga, pwiersz, pkolumna,licznik);
			i++;
		}
	}
}

void KomputerObronaSkos2(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i, j, x, przerwa, licznik, flaga, miejsce, miejsce2;

	for (int stala = 0; stala < 16; stala++) // 10 21
	{
		reset(&licznik, &przerwa, &i, &miejsce, &miejsce2, &x, &flaga);
		for (j = stala; j < R; j++)
		{
			if (x == 0)
				xzero(gra, i, j, &flaga, &licznik, &miejsce2, &miejsce, &x);
			else
				xjeden(gra, i, j, &flaga, &licznik, &miejsce2, &miejsce, &x, &przerwa, stala);

			if (licznik > 2)
				Zapiszmiejsce( &miejsce2,&miejsce, j,i, gra, czterywlinii, &flaga, pwiersz,pkolumna,  licznik);
			i++;
		}
	}
}

void xzero2(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x)
{
	if (gra[j][i] == 'X')
	{
		if (i != 0 && gra[j + 1][i - 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}

		if (i != 0 && gra[j + 1][i - 1] == ' ')
		{
			*miejsce = j + 1;
			*miejsce2 = i - 1;
		}
		*x = 1;
	}
}

void xjeden2(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x, int* przerwa, int stala)
{
	if (gra[j][i] == 'X')
	{
		if ((j != 0 && i != stala) && gra[j - 1][i + 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}
	}

	else if (gra[j][i] == 'O' || (*przerwa == 1 && gra[j][i] == ' '))
		reset(licznik, przerwa,x, miejsce, miejsce2, x, flaga);

	else if (gra[j][i] == ' ' && *przerwa == 0)
	{
		*miejsce = j;
		*miejsce2 = i;
		*przerwa = 1;
	}
}

void Zapiszmiejsce2(int* miejsce, int* miejsce2, int i, int j, char** gra, int* czterywlinii, int* flaga, int* pwiersz, int* pkolumna, int licznik)
{
	if (*miejsce == (R + 1))
	{
		*miejsce2 = i + 1;
		*miejsce = j - 1;
	}

	if (*miejsce > (R - 1))
		return;

	if (gra[*miejsce][*miejsce2] == ' ' && (*czterywlinii) != 1)
	{
		(*pwiersz) = *miejsce;
		(*pkolumna) = *miejsce2;
		if (licznik == 4 || *flaga == 0)
			(*czterywlinii) = 1;
		if (j != 0 && gra[j - 1][i + 1] == 'X')
			*flaga = 0;
	}
}

void KomputerObronaSkos3(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i, j, x, przerwa, licznik, flaga, miejsce, miejsce2;
	for (int stala = 19; stala > 3; stala--) // 18 0 17 1
	{
		reset(&licznik, &przerwa, &i, &miejsce, &miejsce2, &x, &flaga);
		for (j = stala; j > -1; j--)
		{
			if (x == 0)
				xzero2(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x);
			else
				xjeden2(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x, &przerwa, stala);	
			if (licznik > 2)
				Zapiszmiejsce2(&miejsce, &miejsce2, i, j, gra, czterywlinii, &flaga, pwiersz, pkolumna, licznik);
			i++;
		}
	}
}

void xzero3(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x)
{
	if (gra[j][i] == 'X')
	{
		if (j != 19 && gra[j + 1][i - 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}

		if (j != 19 && gra[j + 1][i - 1] == ' ')
		{

			*miejsce = j + 1;
			*miejsce2 = i - 1;
		}
		*x = 1;
	}
}

void xjeden3(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* miejsce2, int* x, int* przerwa, int stala)
{

	if (gra[j][i] == 'X')
	{
		if ((j != stala && i != 19) && gra[j - 1][i + 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}
	}

	else if (gra[j][i] == 'O' || (*przerwa == 1 && gra[j][i] == ' '))
		reset(licznik, przerwa, x, miejsce, miejsce2, x, flaga);

	else if (gra[j][i] == ' ' && *przerwa == 0)
	{
		*miejsce = j;
		*miejsce2 = i;
		*przerwa = 1;
	}

}

void Zapiszmiejsce3(int* miejsce, int* miejsce2, int i, int j, char** gra, int* czterywlinii, int* flaga, int* pwiersz, int* pkolumna, int licznik)
{
	if (*miejsce == (R + 1))
	{
		*miejsce2 = i + 1;
		*miejsce = j - 1;
	}

	if (*miejsce > (R - 1))
		return;

	if (gra[*miejsce][*miejsce2] == ' ' && (*czterywlinii) != 1)
	{
		(*pwiersz) = *miejsce;
		(*pkolumna) = *miejsce2;
		if (licznik == 4 || *flaga == 0)
			(*czterywlinii) = 1;
		if (j != 0 && gra[j - 1][i + 1] == 'X')
			*flaga = 0;
	}
}

void KomputerObronaSkos4(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i, j, x, przerwa, licznik, flaga, miejsce, miejsce2;
	for (int stala = 0; stala < 16; stala++) // 19 1 18 2
	{
		j = 19;
		reset(&licznik, &przerwa, &x, &miejsce, &miejsce2, &x, &flaga);
		for (i = stala; i < R; i++)
		{
			if (x == 0)
				xzero3(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x);
			else
				xjeden3(gra, j, i, &flaga, &licznik, &miejsce, &miejsce2, &x, &przerwa, stala);		
			if (licznik > 2)
				Zapiszmiejsce3(&miejsce, &miejsce2, i, j, gra, czterywlinii, &flaga, pwiersz, pkolumna, licznik);
			j--;
		}
	}
}

void xzeroY(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* x)
{
	if (gra[j][i] == 'X')
	{
		if (j != 0 && gra[j - 1][i] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}

		if (j != 0 && gra[j - 1][i] == ' ')
			*miejsce = j - 1;

		*x = 1;
	}
}

void xjedenY(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* x, int* przerwa)
{
	
	if (gra[j][i] == 'X')
	{
		if (j != 19 && gra[j + 1][i] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}
	}

	else if (gra[j][i] == 'O' || (*przerwa == 1 && gra[j][i] == ' '))
		reset(licznik, przerwa, x, miejsce, miejsce, x, flaga);

	else if (gra[j][i] == ' ' && *przerwa == 0)
	{
		*miejsce = j;
		*przerwa = 1;
	}
}

void ZapiszmiejsceY(int* miejsce, int i, int j, char** gra, int* czterywlinii, int* flaga, int* pwiersz, int* pkolumna, int licznik)
{
	if (licznik > 2)
	{
		if (*miejsce == (R + 1))
			*miejsce = j + 1;
		if (*miejsce > (R - 1))
			return;

		if (gra[*miejsce][i] == ' ' && (*czterywlinii) != 1)
		{
			if (licznik == 4 || *flaga == 0)
				(*czterywlinii) = 1;
			(*pwiersz) = *miejsce;
			(*pkolumna) = i;
			if (j != 19 && gra[j + 1][i] == 'X')
				*flaga = 0;
		}
	}
}

void KomputerObronaY(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i, j, x, przerwa, licznik, flaga, miejsce;
	for ( i = 0; i < R; i++) // kolumny
	{	
		reset(&licznik, &przerwa, &x, &miejsce,&miejsce, &x, &flaga);
		for (j = 0; j < R; j++)
		{
			if (x == 0)
				xzeroY(gra, j, i, &flaga, &licznik, &miejsce,&x);
			else
				xjedenY(gra, j, i, &flaga, &licznik, &miejsce, &x, &przerwa);
			if (licznik > 2)
				ZapiszmiejsceY(&miejsce, i, j, gra, czterywlinii, &flaga, pwiersz, pkolumna, licznik);
		}	
	}
}

void xzeroX(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* x)
{
	if (gra[j][i] == 'X')
	{
		if (i != 0 && gra[j][i - 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}

		if (i != 0 && gra[j][i - 1] == ' ')
			*miejsce = i - 1;

		*x = 1;
	}
}

void xjedenX(char** gra, int j, int i, int* flaga, int* licznik, int* miejsce, int* x, int* przerwa)
{
	if (gra[j][i] == 'X')
	{
		if (i != 19 && gra[j][i + 1] != 'O')
		{
			*flaga = 1;
			(*licznik)++;
		}
	}

	else if (gra[j][i] == 'O' || (*przerwa == 1 && gra[j][i] == ' '))
		reset(licznik, przerwa, x, miejsce, miejsce, x, flaga);

	else if (gra[j][i] == ' ' && *przerwa == 0)
	{
		*miejsce = i;
		*przerwa = 1;
	}
}

void ZapiszmiejsceX(int* miejsce, int i, int j, char** gra, int* czterywlinii, int* flaga, int* pwiersz, int* pkolumna, int licznik)
{

	if (*miejsce == (R + 1))
		*miejsce = i + 1;
	if (*miejsce > (R - 1))
		return;
	if (gra[j][*miejsce] == ' ' && (*czterywlinii) != 1)
	{
		if (licznik == 4 || *flaga == 0)
			(*czterywlinii) = 1;

		(*pwiersz) = j;
		(*pkolumna) = *miejsce;
		if (i != 19 && gra[j][i + 1] == 'X')
			*flaga = 0;
	}
}

void KomputerObronaX(char** gra, int* pzagranie, int* pwiersz, int* pkolumna, int* czterywlinii)
{
	if ((*czterywlinii) == 1)
		return;
	int i, j, x, przerwa, licznik, flaga, miejsce;
	for (j = 0; j < R; j++) // kolumny
	{
		reset(&licznik, &przerwa, &x, &miejsce, &miejsce, &x, &flaga);
		for (i = 0; i < R; i++)
		{
			if (x == 0)
				xzeroX(gra, j, i, &flaga, &licznik, &miejsce, &x);
			else
				xjedenX(gra, j, i, &flaga, &licznik, &miejsce, &x, &przerwa);
			if (licznik > 2)
				ZapiszmiejsceX(&miejsce, i, j, gra, czterywlinii, &flaga, pwiersz, pkolumna, licznik);
		}
	}
}

int SprawdzCzyWygrana(char** gra)
{
	int wygrana = 0;
	wygrana = SprawdzCzyWygranaX(gra);
	wygrana = SprawdzCzyWygranaO(gra, wygrana);

	if (wygrana != 0)
	{
		komunikat(wygrana, gra);
		return 1;
	}

	return 0;
}

int SprawdzCzyWygranaX(char** gra)
{
	int wygrana=0;
	int* pwygrana = &wygrana;

	SprawdzCzyWygranaXSkos(gra, pwygrana);
	SprawdzCzyWygranaXSkos2(gra, pwygrana);
	SprawdzCzyWygranaXSkos3(gra, pwygrana);
	SprawdzCzyWygranaXSkos4(gra, pwygrana);
	SprawdzCzyWygranaXX(gra, pwygrana);
	SprawdzCzyWygranaXY(gra, pwygrana);
	
	return wygrana;
}

void SprawdzCzyWygranaXSkos3(char** gra, int* pwygrana)
{
	int i = 0;
	int j;
	int licznik = 0;
	for (int stala = 19; stala > 3; stala--) // 18 0 17 1
	{
		for (j = stala; j > -1; j--)
		{
			if (gra[j][i] == 'X')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
			i++;
		}

		i = 0;
		licznik = 0;
	}
}

void SprawdzCzyWygranaOSkos3(char** gra, int* pwygrana)
{
	int i = 0;
	int j;
	int licznik = 0;
	for (int stala = 19; stala > 3; stala--) // 18 0 17 1
	{
		for (j = stala; j > -1; j--)
		{
			if (gra[j][i] == 'O')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}
			i++;
		}

		i = 0;
		licznik = 0;
	}
}

void SprawdzCzyWygranaXSkos4(char** gra, int* pwygrana)
{
	int i = 0;
	int j = 19;
	int licznik = 0;

	for (int stala = 0; stala < 16; stala++) // 19 1 18 2
	{
		for (i = stala; i < R; i++)
		{
			if (gra[j][i] == 'X')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
			j--;
		}

		j = 19;
		licznik = 0;		
	}
}

void SprawdzCzyWygranaOSkos4(char** gra, int* pwygrana)
{
	int i = 0;
	int j = 19;
	int licznik = 0;
	for (int stala = 0; stala < 16; stala++) // 19 1 18 2
	{
		for (i = stala; i < R; i++)
		{
			if (gra[j][i] == 'O')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}
			j--;
		}

		j = 19;
		licznik = 0;

	}
}

void SprawdzCzyWygranaXSkos(char** gra, int* pwygrana)
{
	int i=0;
	int licznik = 0;
	int j;
	for (int stala = 0; stala < 16; stala++) 
	{
		for (j = stala; j < R; j++)
		{
			if (gra[i][j] == 'X')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
			i++;
		}
		i = 0;
		licznik = 0;
	}
}

void SprawdzCzyWygranaXSkos2(char** gra, int* pwygrana)
{
	int licznik = 0;
	int i;
	int j = 0;
	for (int stala = 0; stala < 16; stala++) // kolumny
	{
		for (i = stala; i < R; i++)
		{
			if (gra[i][j] == 'X')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
			
			j++;
		}
		j = 0;
		licznik = 0;
	}

}

void SprawdzCzyWygranaXX(char** gra, int* pwygrana)
{
	int licznik = 0;
	for (int i = 0; i < R; i++) // wierszami
	{
		for (int j = 0; j < R; j++)
		{
			if (gra[j][i] == 'X')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
			
		}

		licznik = 0;
	}
}

void SprawdzCzyWygranaXY(char** gra, int* pwygrana)
{
	int licznik = 0;

	for (int i = 0; i < R; i++) // kolumnami
	{
		for (int j = 0; j < R; j++)
		{
			if (gra[i][j] == 'X')
				licznik++;
			else
				licznik=0;

			if (licznik == 5)
			{
				(*pwygrana) = 1;
				return;
			}
		}

		licznik = 0;
	}
}

int SprawdzCzyWygranaO(char** gra, int wygranaX)
{
	if (wygranaX == 1)
		return 1;

	int wygrana=0;
	int* pwygrana = &wygrana;
	SprawdzCzyWygranaOSkos(gra, pwygrana);
	SprawdzCzyWygranaOSkos2(gra, pwygrana);
	SprawdzCzyWygranaOSkos3(gra, pwygrana);
	SprawdzCzyWygranaOSkos4(gra, pwygrana);
	SprawdzCzyWygranaOX(gra, pwygrana);
	SprawdzCzyWygranaOY(gra, pwygrana);
	
	return wygrana;
}

void SprawdzCzyWygranaOSkos(char** gra, int* pwygrana)
{
	int i = 0;
	int licznik = 0;
	int j;
	for (int stala = 0; stala < 16; stala++)
	{
		for (j = stala; j < R; j++)
		{
			if (gra[i][j] == 'O')
				licznik++;
			else
				licznik = 0;
			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}
			i++;
		}
		i = 0;
		licznik = 0;
	}
}

void SprawdzCzyWygranaOSkos2(char** gra, int* pwygrana)
{
	int licznik = 0;
	int i;
	int j = 0;
	for (int stala = 0; stala < 16; stala++) // kolumny
	{
		for (i = stala; i < R; i++)
		{
			if (gra[i][j] == 'O')
				licznik++;
			else
				licznik = 0;

			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}

			j++;
		}
		j = 0;
		licznik = 0;
	}
}

void SprawdzCzyWygranaOX(char** gra, int* pwygrana)
{
	int licznik = 0;
	for (int i = 0; i < R; i++) // wierszami
	{
		for (int j = 0; j < R; j++)
		{
			if (gra[j][i] != 'O')
				licznik=0;
			else
				licznik++;

			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}
		}
		licznik = 0;
	}
}

void SprawdzCzyWygranaOY(char** gra, int* pwygrana)
{
	int licznik = 0;

	for (int i = 0; i < R; i++) // kolumnami
	{
		for (int j = 0; j < R; j++)
		{
			if (gra[i][j] != 'O')
				licznik = 0;
			else
				licznik++;

			if (licznik == 5)
			{
				(*pwygrana) = 2;
				return;
			}
		}
		licznik = 0;
	}
}

void ZapiszDoPliku(element* head)
{
	element* pisz = head;

	FILE* file = fopen("historia.bin", "ab");
	if(file)
	{ 
		while (pisz)
		{
			fwrite(&pisz, sizeof(struct historia), 1, file);
			pisz = pisz->pnext;
		}
		fclose(file);
	}
}

element* wyczyscliste(element* head)
{
	element* pom = head;

	while (pom)
	{
		element* next = pom->pnext;
		
		free(pom->kto_sie_ruszyl);
		free(pom);
		pom = next;
	}
	head = NULL;
	return head;
}

char** wyczyscplansze(char** gra)
{
	
	for (int i = 0; i < R; i++)
		free(gra[i]);

	free(gra);
	gra = 0;

	return gra;
}