#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
Napisati program koji generira 15 sluèajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu
listu, po redoslijedu generiranja, a ne sortirano. U listi ne smije biti duplih vrijednosti.
a) Potrebno je pronaæi minimalnu i maksimalnu vrijednost, te iz njih izraèunati srednju vrijednost
((min+max)/2) i nakon toga sve vrijednosti koje su veæe od srednje prebaciti na kraj liste. Ispisati
minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu.
*/

#define GG 120
#define DG 100

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}lista;

position inicijalizacija(position);
int generiraj(position);
int stvoriListu(position, int);
int ispisListe(position);
int pronadjiMin(position);
int pronadjiMax(position);
int novaLista(position, int);
position nadjiZadnji(position);

int main()
{
	srand(time(NULL));
	position head = NULL, novaHead = NULL;
	int min = 0, max = 0, srednja = 0;

	head = inicijalizacija(head);
	novaHead = inicijalizacija(novaHead);

	generiraj(head);
	ispisListe(head->next);

	min = pronadjiMin(head->next);
	printf("\nNajmanji element: %d\n", min);

	max = pronadjiMax(head->next);
	printf("\nNajveci element: %d\n", max);

	srednja = (min + max) / 2;
	printf("\nSrednja vrijednost: %d\n", srednja);

	novaLista(head, srednja);
	ispisListe(head->next);

	return 0;
}

position nadjiZadnji(position p)
{
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

int novaLista(position p, int srednja)
{
	position current = NULL, zadnji = NULL, prev = NULL, noviZadnji = NULL, head = NULL;

	head = p;
	prev = p;
	current = p->next;

	zadnji = nadjiZadnji(p); //3
	noviZadnji = zadnji;

	while (current != zadnji)
	{
		if (current->broj > srednja)
		{
			prev->next = current->next;

			noviZadnji->next = current;
			current->next = NULL;
			noviZadnji = current;
		}
		else 
		{
			prev = current;
			current = current->next;
		}
		current = prev->next;
	}
	
	if (current == zadnji)
	{
		if (current->broj > srednja)
		{
			prev->next = current->next;

			noviZadnji->next = current;
			current->next = NULL;
			noviZadnji = current;
		}

	}

	return 0;
}


int pronadjiMax(position p)
{
	int max = 0;
	position current = NULL;
	current = p;

	if (p == NULL)
		printf("Lista je prazna!\n");
	
	else
	{
		max = p->broj;
		
		while (current != NULL)
		{
			if (current->broj > max)
			{
				max = current->broj;
			}
			current = current->next;
		}
	
	}

	return max;
}

int pronadjiMin(position p)
{
	int min = 0;

	position current = NULL;
	current = p;

	if (p == NULL)
	{
		printf("Lista je prazna!\n");
	}

	else 
	{
		min = p->broj;
		while (current != NULL)
		{
			if (current->broj < min)
			{
				min = current->broj;
			}
			current = current->next;
		}
	}

	return min;
}


int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
	}

	while (p != NULL)
	{
		printf("%d\n", p->broj);
		p = p->next;
	}

	return 0;
}


int stvoriListu(position p, int br)
{
	position q = NULL;
	q = inicijalizacija(q);

	if (p->next == NULL)
	{
		q->broj = br;
		q->next = p->next;
		p->next = q;
	}
	else {
		while (p->next != NULL)
		{
			if (p->broj != br)
			{
				p = p->next;
			}
			else
			{
				printf("Broj vec postoji!\n");
				return 1;
			}

		}
		if (p->broj != br)
		{
			q->broj = br;
			q->next = p->next;
			p->next = q;
		}
		else
		{
			printf("Broj vec postoji!\n");
			return 1;
		}
		
	}
	

	return 0;

}


int generiraj(position p)
{
	int br = 0, i = 0;
	int povratna = 0;

	do {

		br = rand() % (GG - DG + 1) + DG;
		povratna=stvoriListu(p, br);
		if (povratna != 1)
		{
			++i;
		}
		

	} while (i < 15);

	return 0;
}


position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->next = NULL;

	return p;
}