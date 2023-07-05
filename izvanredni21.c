#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* radi, ali upis u datoteku ima i prethodno izvedene liste, + nisam trecu listu
Napisati program koji generira dvije vezane liste na naèin da u svaku upiše po 10 sluèajno generiranih brojeva u 
opsegu od 0 do 20. U jednoj listi ne smije biti ponavljanja vrijednosti. Ispisati obje liste na ekran.
Iz ove dvije liste kreirati treæu koja sadrži samo one vrijednosti koje se ponavljaju u obje liste
i upisati je u datoteku.
*/

#define GG 20
#define DG 0

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
int provjera(position, position, position);
int trazi(int, position);
int upis(int);

int main()
{
	position head1 = NULL, head2=NULL, head3=NULL;
	head1 = inicijalizacija();
	head2 = inicijalizacija();
	head3 = inicijalizacija();

	generirajBr(head1);
	generirajBr(head2);

	printf("PRVA LISTA: \n");
	ispis(head1->next);

	printf("DRUGA LISTA: \n");
	ispis(head2->next);

	provjera(head3, head1, head2);

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
	int br = 0, i = 0;

	do {
		br = rand() % (GG - DG + 1) + DG;
		if (stvoriListu(p, br) != 1)
			++i;
	} while (i < 10);
}

int stvoriListu(position p, int br)
{
	position q = NULL;
	q = inicijalizacija();

	while (p->next != NULL && p->next->broj <= br)
		p = p->next;

	if (p->broj != br)
	{
		q->broj = br;
		q->next = p->next;
		p->next = q;
	}
	else
		return 1;

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

int provjera(position p3, position p1, position p2)
{
	//trazenje po prvoj listi
	p1 = p1->next;
	while (p1 != NULL)
	{
		if (trazi(p1->broj,p2) == 1 && trazi(p1->broj,p3)!=1)
			upis(p1->broj);
		
		p1 = p1->next;
		
	}

	//trazenje po drugoj listi
	p2 = p2->next;
	while (p2 != NULL)
	{
		if (trazi(p2->broj, p1) == 1 && trazi(p2->broj,p3)!=1)
			upis(p2->broj);
		p2 = p2->next;
	}

	return 0;
}
int trazi(int br,position p)
{
	while (p != NULL)
	{
		if (p->broj == br)
			return 1;
		p = p->next;
	}
	return 0;

}
int upis(int br)
{
	FILE* fp = NULL;
	
	fp = fopen("dat.txt", "a");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}
	
	fprintf(fp, "%d\n", br);
	fclose(fp);
	
	return 0;
}