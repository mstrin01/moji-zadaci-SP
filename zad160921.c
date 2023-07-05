#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Napisati program koji generira 30 slucajnih brojeva u opsegu od 50 do 70 i sprema ih u 
vezanu listu u sortiranom redoslijedu. Ispisati listu na ekran, 
a zatim pronaci koja se vrijednost ponavlja najveci broj puta i obrisati sva ponavljanja.

*/

#define GG 70
#define DG 50

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}lista;

position inicijalizacija();
int generirajBr(position);
int stvoriListu(position, int);
int ispis(position);
int obrisi(position);

int main()
{
	position head = NULL;
	int trazeniBroj = 0;
	head = inicijalizacija();

	generirajBr(head);
	ispis(head->next);

	puts("\n");
	obrisi(head);
	ispis(head->next);
	return 0;
}

position inicijalizacija()
{
	position p = NULL;
	p = (position)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	p->broj = 0;
	p->next = NULL;

	return p;
}
int generirajBr(position p)
{
	int i = 0, br = 0;
	do
	{
		br = rand() % (GG - DG + 1) + DG;
		stvoriListu(p, br);
		++i;

	} while (i < 30);
	
	return 0;
}

int stvoriListu(position p, int br)
{
	position q = NULL;
	q = inicijalizacija();

	while (p->next != NULL && p->next->broj < br)
		p = p->next;

	q->broj = br;
	q->next = p->next;
	p->next = q;

	return 0;
}

int ispis(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return 1;
	}

	while (p != NULL)
	{
		printf("%d\n", p->broj);
		p = p->next;
	}

	return 0;
}

int obrisi(position p)
{
	int maxCount = 0;
	int najcescaVrijednost = 0;
	position current = p->next;
	position prev = p;

	// Pronaði najèešæe ponavljajuæu vrijednost i njezin broj pojavljivanja
	while (current != NULL)
	{
		int vrijednost = current->broj;
		position temp = current;
		int count = 0;

		while (temp != NULL && temp->broj == vrijednost)
		{
			count++;
			temp = temp->next;
		}

		if (count > maxCount)
		{
			maxCount = count;
			najcescaVrijednost = vrijednost;
		}

		prev = current;
		current = current->next;
	}

	// Obriši sve pojave najèešæe ponavljajuæe vrijednosti
	current = p->next;
	prev = p;

	while (current != NULL)
	{
		if (current->broj == najcescaVrijednost)
		{
			position temp = current;
			prev->next = current->next;
			current = prev->next;
			free(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}

	return 0;
}