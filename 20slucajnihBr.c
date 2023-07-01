#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
/*
Napisati program koji generira 20 sluèajnih brojeva iz opsega 100 – 150 i njih spremiti u vezanu listu i
svakom od njih dodijeliti redni broj od 0-19.
a) Nakon toga treba generirati pet sluèajnih brojeva iz opsega 0-19 (voditi raèuna da se ne pojavi
isti broj više puta) i elemente gornje liste s tim rednim brojem postaviti na poèetak liste. Ispisati
te brojeve te novu listu s rednim brojevima.
*/

#define GG 150
#define DG 100

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	int redni;
	position next;
}lista;

position inicijalizacija(position);
int generirajBrojeve(position);
int stvoriListu(position, int,int);
int ispis(position);
int generirajRedne(position);
int nadjiRedne(position, int);


int main()
{
	srand(time(NULL));

	position head = NULL;
	head = inicijalizacija(head);
	

	generirajBrojeve(head);
	ispis(head->next);


	generirajRedne(head);
	puts("\n");
	ispis(head->next);

	return 0;
}

position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(lista));
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


int generirajBrojeve(position p)
{
	int i = 0, broj = 0;

	do
	{
		broj = rand() % (GG - DG + 1) + DG;
		stvoriListu(p, broj,i);
		++i;

	} while (i < 20);


	return 0;
}

int stvoriListu(position head, int broj, int redni)
{
	position q = NULL;
	q = inicijalizacija(q);

	while (head->next != NULL)
		head = head->next;

	q->broj = broj;
	q->redni = redni;

	q->next = head->next;
	head->next = q;

	return 0;
}

int ispis(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return -1;
	}

	while (p != NULL)
	{
		printf("%d. %d \n", p->redni, p->broj);
		p = p->next;
	}

	return 0;
}

int generirajRedne(position head)
{
	int redni = 0, i = 0, prisutan=0;
	position p = NULL;
	printf("\nREDNI BROJEVI: \n");
	do
	{
		redni = rand() % (19 - 0 + 1);
		while (p != NULL)
		{
			if (p->redni == redni)
			{
				prisutan = 1;
				break;
			}
			p = p->next;
		}
		if (prisutan != 1)
		{
			nadjiRedne(head, redni);
			++i;
			printf("\n %d \n", redni);
		}
		
		
	
	} while (i < 5);


	return 0;
}

int nadjiRedne(position head, int redni)
{
	position curr = NULL, p = NULL;
	curr = inicijalizacija(curr); //nadjeni redni za prebacivanje na pocetak
	p = head;

	while (p->next != NULL && p->next->redni != redni)
		p = p->next;

	if (p->next == NULL)
		return 0; //nije pronadjen redni broj

	curr = p->next;
	p->next = curr->next;
	curr->next = head->next;	
	head->next = curr;

	return 1;
	
}