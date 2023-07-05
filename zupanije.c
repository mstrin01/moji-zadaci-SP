#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
Procitati datoteku i stvoriti listu koja sadrzi imena ljudi i njihove zupanije. 
Zatim pronaci zupaniju koja ima najvise
stanovnika, ispisati koliko ih je i koji su stanovnici. */


struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char ime[30];
	char prezime[30];
	char zupanija[50];
	position next;
}lista;

position inicijalizacija();
int citajDat(position);
int stvoriListu(position, char*, char*, char*);
int ispis(position);
int provjera(position);
int traziLjudePoZup(position, char*);

int main()
{
	position head = NULL;
	head = inicijalizacija();

	citajDat(head);
	ispis(head->next);
	
	puts("\n");
	provjera(head);

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

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	strcpy(p->zupanija, "");
	p->next = NULL;

	return p;
}

int citajDat(position p)
{
	FILE* fp = NULL;
	char ime[30], prezime[30], zup[50];

	fp = fopen("z.txt", "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %s", ime, prezime, zup);
		stvoriListu(p, ime, prezime, zup);
	}
	fclose(fp);

	return 0;
}
int stvoriListu(position p, char* ime, char* prezime, char* zup)
{
	position q = NULL;
	q = inicijalizacija();

	while (p->next != NULL && strcmp(p->next->zupanija, zup) < 0)
		p = p->next;

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	strcpy(q->zupanija, zup);

	q->next = p->next;
	p->next = q;

	return 0;
}
int ispis(position p)
{
	if (p == NULL)
	{
		printf("LISTA JE PRAZNA!\n");
		return 1;
	}

	while (p != NULL)
	{
		printf("%s %s %s\n", p->ime, p->prezime, p->zupanija);
		p = p->next;
	}

	return 0;
}

int provjera(position p)
{
	int brojac = 0, maxBrojac = 0;
	position current=NULL, prev=NULL, temp = NULL;
	char trZup[50] = { 0 };

	p = p->next;
	prev = p;
	current = prev->next;

	while (current != NULL)
	{
		brojac = 0;
		temp = current;
		

		while (temp != NULL && strcmp(temp->zupanija, current->zupanija) == 0)
		{
			++brojac;
			temp = temp->next;
		}

		if (brojac > maxBrojac)
		{
			maxBrojac = brojac;
			strcpy(trZup, current->zupanija);
		}

		prev = current;
		current = current->next;
	}

	printf("Najvise stanovnika (%d) ima %s\n", maxBrojac, trZup);
	traziLjudePoZup(p, trZup);

	return 0;
}

int traziLjudePoZup(position p, char* trZup)
{

	while (p != NULL)
	{
		if (strcmp(p->zupanija, trZup) == 0)
		{
			printf("%s %s\n", p->ime, p->prezime);
		}
		p = p->next;
	}


	return 0;
}
