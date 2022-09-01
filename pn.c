#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#define MAX 256
#define DG 50
#define GG 80

/*Napisati program koji generira sluèajne brojeve u opsegu od 50 - 80. Ukoliko je generirani broj paran
sprema se u vezanu listu parnih brojeva i to u padajuæem redoslijedu(od najveæeg prema najmanjem).
Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, takoðer u padajuæem redoslijedu.Niti
jedna vezana lista ne smije sadržavati dva ista elementa.Unos traje sve dok obje liste ne sadrže 10
elemenata.Treba ispisivati koji se broj generira i na kraju ispisati obje liste.*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}Lista;


position Inicijalizacija(position);
int Generiraj(position, position);
int vracaRandomBroj();
int ispisListe(position);
int stvoriListu(position, int, int*);
int main()
{
	srand(time(NULL));
	
	position headParni = NULL;
	position headNeparni = NULL;

	headParni = Inicijalizacija(headParni);
	headNeparni = Inicijalizacija(headNeparni);

	Generiraj(headParni, headNeparni);
	printf("Lista parnih brojeva: \n");
	ispisListe(headParni->next);
	puts("\n");
	printf("Lista neparnih brojeva: \n");
	ispisListe(headNeparni->next);
	


	return 0;
}

position Inicijalizacija(position p)
{
	p = (position)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->next = NULL;

	return p;
}

int ispisListe(position p)
{
	while (p != NULL)
	{
		printf("%d\n", p->broj);
		p = p->next;
	}
	return 0;
}
int Generiraj(position headParni, position headNeparni)
{
	int brojac_parni = 0, brojac_neparni = 0;
	int slucajniBroj = 0;
	int kraj = 1;

	do {
		slucajniBroj = vracaRandomBroj();
		printf("Slucajni broj: %d \n", slucajniBroj);
		if (slucajniBroj % 2 == 0 && brojac_parni < 10)
		{
			stvoriListu(headParni, slucajniBroj, &brojac_parni);
		}
		else if (slucajniBroj % 2 != 0 && brojac_neparni < 10)
		{
			stvoriListu(headNeparni, slucajniBroj, &brojac_neparni);
		}
		else if (brojac_parni == 10 && brojac_neparni == 10)
		{
			kraj = 0;
		}
		

	} while (kraj);

	return 0;
}
int vracaRandomBroj()
{
	int randBr = 0;
	randBr = rand() % (GG - DG + 1) + DG;
	return randBr;

}
int stvoriListu(position p, int slucajniBr, int* brojac)
{
	position noviEl = NULL;
	noviEl = Inicijalizacija(noviEl);
	while (p->next != NULL && p->next->broj >= slucajniBr)
	{
		p = p->next;
	}
	if (p->broj != slucajniBr)
	{
		noviEl->broj = slucajniBr;
		++(*brojac);

		noviEl->next = p->next;
		p->next = noviEl;
	}
	else
	{
		return -1;

	}
	
	return 0;
}