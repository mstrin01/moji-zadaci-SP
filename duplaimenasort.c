#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>

#define m 60
#define GG 199
#define DG 100

/*
Napisati program koji iz datoteke èita prezime i ime studenta i svakom studentu se dodjeljuje jedinstveni(!) ID u
opsegu od 100 do 199. Od dobivenih podataka se gradi lista sortirana po ID-u. Ispisati listu.
Iz liste ukloniti sve one osobe cije se ime ponavlja u listi, tako da ostane samo jedna osoba tog imena.
Ispisati novu listu.
*/


struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char ime[m];
	char prezime[m];
	int id;
	position next;
}Lista;

position Inicijalizacija(position);
int citajDat(position, char*);
int stvoriListu(position, char*, char*, int);
int Generiraj();
int ispisListe(position);
int izbrisiDuplikate(position);
int main()
{
	srand(time(NULL));

	position head = NULL;
	head = Inicijalizacija(head);

	char imeDat[m] = "stud.txt";

	citajDat(head, imeDat);

	ispisListe(head->next);

	printf("\nLista nakon brisanja duplikata: \n");
	izbrisiDuplikate(head);
	ispisListe(head->next);

	return 0;
}

int izbrisiDuplikate(position p)
{
	position temp = NULL, trenutni = NULL;
	trenutni = p;

	if (trenutni == NULL)
		return;

	while (trenutni->next != NULL)
	{
		if (strcmp(trenutni->ime, trenutni->next->ime) == 0)
		{
			temp = trenutni->next;
			trenutni->next = trenutni->next->next;
			free(temp);
		}
		else
			trenutni = trenutni->next;

	}

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

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->id = 0;
	p->next = NULL;

	return p;
}
int citajDat(position p, char* imeDat)
{
	char imeStud[m], prezimeStud[m];
	int IDstud = 0;
	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", imeStud, prezimeStud);
		IDstud = Generiraj();
		stvoriListu(p, imeStud, prezimeStud, IDstud);

	}
	fclose(fp);

	return 0;
}
int stvoriListu(position p, char* imeStud, char* prezimeStud, int IDstud)
{
	position q = NULL;
	q = Inicijalizacija(q);

	while (p->next != NULL && strcmp(p->next->ime,imeStud) <= 0)
		p = p->next;

	if (p->id != IDstud)
	{
		strcpy(q->ime, imeStud);
		strcpy(q->prezime, prezimeStud);
		q->id = IDstud;

		q->next = p->next;
		p->next = q;
	}
	else
		return -1;

	return 0;
}
int Generiraj()
{
	int randBr = 0;
	randBr = rand() % (GG - DG + 1) + DG;


	return randBr;
}
int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
	}

	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->id);
		p = p->next;
	}

	return 0;
}