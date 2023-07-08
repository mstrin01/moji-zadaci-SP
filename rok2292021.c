#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Napisati program koji generira dvije vezane liste na naèin da u svaku upiše po 10 sluèajno
generiranih brojeva u
opsegu od 0 do 20. U jednoj listi ne smije biti ponavljanja vrijednosti. Ispisati obje liste na ekran.
Iz ove dvije liste kreirati treæu koja sadrži samo one vrijednosti koje se ponavljaju u obje liste
i upisati je u datoteku.
*/

#define gg 20
#define dg 0

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int broj;
	position next;
}lista;

position inicijalizacija();
int genBr(position);
int stvoriListu(position,int);
int ispis(position);
int provjera(position, position, position);
int novaLista(position, int);

int main()
{
	srand(time(NULL));
	position head = NULL, head1 = NULL, head2 = NULL;
	head = inicijalizacija();
	head1 = inicijalizacija();
	head2 = inicijalizacija();

	genBr(head1);
	genBr(head2);

	printf("Prva lista: \n");
	ispis(head1->next);
	printf("\nDruga lista: \n");
	ispis(head2->next);

	puts("");
	printf("\nTreca lista: \n");
	provjera(head, head1, head2);
	ispis(head->next);
	printf("\nOtvori bb.txt!\n");

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
int genBr(position p)
{
	int br = 0, i = 0;
	do
	{
		br = rand() % (gg - dg + 1) + dg;
		if (stvoriListu(p, br) != 1)
			++i;

	} while (i < 10);

}
int stvoriListu(position p, int br)
{
	position temp = NULL, q = NULL;
	q = inicijalizacija();

	temp = p->next;
	while (temp != NULL)
	{
		if (temp->broj == br)
		{
			free(q);
			return 1;
		}
		temp = temp->next;
	}

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
		return -2;
	}

	while (p != NULL)
	{
		printf("%d\n", p->broj);
		p = p->next;
	}
	return 0;
}
int provjera(position nova, position p1, position p2)
{
	position start = NULL;
	start = p2->next;
	p1 = p1->next;
	p2 = p2->next;

	while(p1!=NULL)
	{ 
		while (p2 != NULL)
		{
			if (p1->broj == p2->broj)
			{
				novaLista(nova, p1->broj);
				upis(p1->broj);
			}
			p2 = p2->next;
		}
		p1 = p1->next;
		p2 = start;
	}

	return 0;

}
int novaLista(position p, int br)
{
	position q = NULL;
	q = inicijalizacija();

	q->broj = br;
	q->next = p->next;
	p->next = q;

	return 0;
}
int upis(int br)
{
	FILE* fp = NULL;
	fp = fopen("bb.txt", "a");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return 1;
	}

	fprintf(fp, " %d\n", br);
	fclose(fp);

	return 0;
}