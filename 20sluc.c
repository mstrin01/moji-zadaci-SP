#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*Napisati program koji generira 20 sluèajnih brojeva iz opsega 100 – 150 i njih spremiti u vezanu listu i 
svakom od njih dodijeliti redni broj od 0-19. 
a) Nakon toga treba generirati pet sluèajnih brojeva iz opsega 0-19 (voditi raèuna da se ne pojavi 
isti broj više puta) i elemente gornje liste s tim rednim brojem postaviti na poèetak liste. Ispisati 
te brojeve te novu listu s rednim brojevima. */

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	int broj;
	int redni;
	pozicija next;
}lista;

pozicija inicijalizacija(pozicija);
int generirajBr(pozicija,int,int);
int unosUListu(pozicija, int, int);
int ispis(pozicija);
int slucajniRBr(pozicija);
int unosRednih(pozicija, int);
int ispisRednih(pozicija);
int staviNaPocetak(pozicija, pozicija);


int main()
{
	srand(time(NULL));
	pozicija head = NULL;
	pozicija headredni = NULL;

	int nasumicnibr = 0, rednibr = 0;
	int i = 0;

	head = inicijalizacija(head);
	headredni = inicijalizacija(headredni);

	generirajBr(head, nasumicnibr, rednibr);
	printf("20 SLUCAJNIH BROJEVA:\n");
	ispis(head->next);

	printf("\n5 SLUCAJNIH REDNIH BROJEVA:\n");
	do
	{
		slucajniRBr(headredni);
		i++;
		
	} while (i < 5);

	ispisRednih(headredni->next);

	printf("Pomicanje liste: \n");
	staviNaPocetak(head, headredni);
	ispis(head->next);
	return 0;
}

pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->redni = 0;
	p->next = NULL;
	return p;
}

int generirajBr(pozicija p, int nasumicni, int redni)
{

	for (redni = 0; redni < 21; redni++)
	{
		nasumicni = rand() % (120 - 100 + 1) + 100;
		unosUListu(p, nasumicni, redni);
	}

	return 0;
}

int unosUListu(pozicija p, int nasumicni, int rbr)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	while (p->next!=NULL)
	{
		p = p->next;
	}
	q->broj = nasumicni;
	q->redni = rbr;
	q->next = p->next;
	p->next = q;
	return 0;
}

int ispis(pozicija p)
{
	if (p == NULL)
		printf("Lista je prazna!\n");

	while (p != NULL)
	{
		printf("%d. %d\n", p->redni, p->broj);
		p = p->next;
	}
	return 0;
}

int slucajniRBr(pozicija pr) //headrednih
{
	int br = 0;
	int provjera = 0; // za provjeru je li uneseni redni u listi
	br= rand() % (19 - 0 + 1) + 0;

	provjera=unosRednih(pr, br);
	if (provjera == 1)
	{
		slucajniRBr(pr);
	}
	return 0;
}

int unosRednih(pozicija pr, int br)
{
	pozicija start = pr->next;
	pozicija q = NULL;
	q = inicijalizacija(q);


	while (pr->next != NULL)
	{

		if (pr->next->redni != br) //ako je razlicit od onoga u listi, iterira dalje kroz listu za provjeru
		{
			pr = pr->next;
		}
		else
		{
			printf("Broj je u listi!\n");
			return 1; //gore vraca varijabli provjera da je 1 sto znaci da se gore poziva novo generiranje slucajnog broja!
		}
	}
	q->redni = br;
	q->next = pr->next;
	pr->next = q;

	return 0;	
}

int ispisRednih(pozicija p)
{
	if (p == NULL)
		printf("Lista je prazna!\n");

	while (p != NULL)
	{
		printf("%d\n", p->redni);
		p = p->next;
	}
	return 0;
}

int staviNaPocetak(pozicija headBrojevi, pozicija headRedni)
{
	pozicija prev = NULL, current = NULL, prvipravi = NULL;
	pozicija originalnihead = NULL, start=NULL;

	start = headBrojevi; //kad krenemo ispocetka iterirat kroz listu
	prvipravi = headBrojevi->next; //inicijalni prvi (ne onaj u novom stanju)
	originalnihead = headBrojevi; // na njega preusmjeravamo novopridošlice (tj one redne brojeve koji su generirani za pomicanje)
	headRedni = headRedni->next;

	while (headRedni != NULL)
	{
		while (headBrojevi != NULL)
		{
			if (headBrojevi->next->redni == headRedni->redni)
			{
				prev = headBrojevi;
				current = prev->next;
				prev->next = current->next;

				current->next = originalnihead->next;
				originalnihead->next = current;
			}
			else
			{
				headBrojevi = headBrojevi->next;
			}

		}
		headBrojevi = start;
		headRedni = headRedni->next;
	}

	return 0;
}
