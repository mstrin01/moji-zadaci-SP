#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#define m 60
/*Napisati program koji iz dvije datoteke (jedna sadrži ocjenu 1. kolokvija,a druga ocjenu 2. kolokvija) kreira 
vezanu listu studenata koji su položili ispit i ta se nova vezana lista slaže po ocjenama. Naèin pretvorbe 
bodova u ocjenu je dan u tablici

Bodovi Ocjena
50 – 59.99% 2
60 – 73.99% 3
74 – 86.99% 4
87 - 100%	5

*/


struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char ime[m];
	char prezime[m];
	int ocjena;
	position next;
}Lista;

position Inicijalizacija(position);
int citajDat(position, char*);
int stvoriListu(position, char*, char*, int);
int bodoviUOcjenu(int);
int ispisListe(position);
int poloziliIspit(position, position, position);
int listaPolozenih(position,position,position,int);
int oslobodiMemoriju(position);
int main()
{
	position head1 = NULL, head2 = NULL, headIspit = NULL;

	head1 = Inicijalizacija(head1);
	head2 = Inicijalizacija(head2);
	headIspit = Inicijalizacija(headIspit);

	char dat1[m] = "kol1.txt";
	char dat2[m] = "kol2.txt";

	citajDat(head1, dat1);
	citajDat(head2, dat2);

	printf("\n PRVI KOLOKVIJ: \n");
	ispisListe(head1->next);
	printf("\n DRUGI KOLOKVIJ: \n");
	ispisListe(head2->next);

	printf("\n POLOZILI: \n");
	poloziliIspit(head1, head2, headIspit);
	ispisListe(headIspit->next);

	puts("\n");
	printf("... OSLOBADANJE MEMORIJE ... \n");
	oslobodiMemoriju(head1);
	oslobodiMemoriju(head2);
	oslobodiMemoriju(headIspit);
	ispisListe(head1->next);
	ispisListe(head2->next);
	ispisListe(headIspit->next);


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
	p->ocjena = 0;
	p->next = NULL;
	return p;

}
int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char imeStud[m], prezimeStud[m];
	int bodovi,ocjena;

	fp = fopen(imeDat, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %d", imeStud, prezimeStud, &bodovi);
		ocjena=bodoviUOcjenu(bodovi);
		stvoriListu(p, imeStud, prezimeStud, ocjena);
	}
	fclose(fp);

	return 0;
}

int stvoriListu(position p, char* imeStud, char* prezimeStud, int ocjenaStud)
{
	position q = NULL;
	q = Inicijalizacija(q);

	strcpy(q->ime, imeStud);
	strcpy(q->prezime, prezimeStud);
	q->ocjena = ocjenaStud;
	
	q->next = p->next;
	p->next = q;

	return 0;
}
int bodoviUOcjenu(int bodovi)
{
	if (bodovi < 50)
		return 1;
	else if (bodovi >= 50 && bodovi < 60)
		return 2;
	else if (bodovi >= 60 && bodovi < 74)
		return 3;
	else if (bodovi >= 74 && bodovi < 87)
		return 4;
	else
		return 5;
}

int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
	}
	while (p != NULL)
	{
		printf("%s %s %d \n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return 0;
}

int poloziliIspit(position kol1, position kol2, position ispit)
{
	int ukupnaOcjena = 0;
	while (kol1 != NULL)
	{
		if (kol1->ocjena >= 2 && kol2->ocjena >= 2)
		{
			ukupnaOcjena = (kol1->ocjena + kol2->ocjena) / 2;
			listaPolozenih(kol1,kol2,ispit,ukupnaOcjena);
		}
		kol1 = kol1->next;
		kol2 = kol2->next;
	}

	return 0;
}

int listaPolozenih(position kol1,position kol2,position ispit,int ukupnaOcjena)
{
	position q = NULL;
	q = Inicijalizacija(q);

	while (ispit->next != NULL && ispit->next->ocjena > ukupnaOcjena)
		ispit=ispit->next;


	strcpy(q->ime, kol1->ime);
	strcpy(q->prezime, kol1->prezime);
	q->ocjena = ukupnaOcjena;
	
	q->next = ispit->next;
	ispit->next = q;

	return 0;
}

int oslobodiMemoriju(position p)
{
	position temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}