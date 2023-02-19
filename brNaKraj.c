#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GG 50
#define DG 30

/*
Napisati program koji generira 30 slucajnih brojeva u opsegu od 30 do 50. Brojeve treba spremiti u
vezanu listu u sortiranom redoslijedu. Ispisati listu.
Za 2: Pitati korisnika da unese jedan broj i sve elemente s tim brojem pomaknuti na kraj vezane liste.
Ispisati novu listu.
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}lista;

position inicijalizacija(position);
int generiranje(position);
int stvoriListu(position, int);
int ispis(position);
int pomicanjeListe(position);
int staviNaKraj(position,int);
int nadjiZadnji(position);
position pronadjiBr(position, int);

int main()
{
	srand(time(NULL));

	int slucajniBr = 0;
	position head = NULL;

	head = inicijalizacija(head);
	generiranje(head);
	ispis(head->next);

	printf("Odaberi broj: \n");
	scanf(" %d",&slucajniBr);
	printf("\nNova lista:  \n");
	
	staviNaKraj(head,slucajniBr);
	ispis(head->next);

	return 0;
}


int nadjiZadnji(position p)
{
	if (p == NULL)
		return NULL;

	while (p->next != NULL)
		p = p->next;

	return p;
}


int staviNaKraj(position p, int br)
{
	position q = NULL, zadnji = NULL;
	position prev = NULL, current = NULL;

	prev = p;
	current = prev->next;
	zadnji = nadjiZadnji(p);

	while (current != zadnji)
	{
		if (current->broj == br)
		{
			prev->next = current->next;
			
			current->next = zadnji->next;
			zadnji->next = current;

		}
		else if (current->broj!=br)
		{
			prev = current;
			current = prev->next;
		}
		
		current = prev->next;
	}

	return 0;
}


int ispis(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
		return NULL;
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
	
	while (p->next != NULL && p->next->broj <= br)
		p = p->next;

	q = inicijalizacija(q);
	q->broj = br;
	q->next = p->next;
	p->next = q;

	return 0;
}

int generiranje(position p)
{
	int br = 0, i = 0;

	do {
		
		br = rand() % (GG - DG + 1) + DG;
		stvoriListu(p, br);
		++i;

	} while (i < 30);

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