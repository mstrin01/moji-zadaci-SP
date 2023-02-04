#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Napisati program koji iz dvije datoteke (jedna sadrži ocjenu 1. kolokvija,a druga ocjenu 2. kolokvija) kreira
vezanu listu studenata koji su položili ispit i ta se nova vezana lista slaže po ocjenama. Naèin pretvorbe
bodova u ocjenu je dan u tablici.
	Bodovi		Ocjena
	50 – 59.99%  2
	60 – 73.99%  3
	74 – 86.99%  4
	87 - 100     5
*/


struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char ime[40];
	char prezime[40];
	float bodovi;
	position next;
}lista;

position inicijalizacija(position);
int citajDat(position, char*);
int pretvoriBodove(float);
int unesiUListu(position, char*, char*, float);
int ispis(position);
int polozeniIspit(position, position, position);

int main()
{
	position k1 = NULL, k2 = NULL, head = NULL;
	char kol1[40] = { 0 }, kol2[40] = { 0 };
	
	k1 = inicijalizacija(k1);
	k2 = inicijalizacija(k2);
	head = inicijalizacija(head); //head liste gdje su oni koji su polozili ispit

	printf("Unesi ime datoteke gdje su rezultati 1.kolokvija: \n");
	scanf(" %s", kol1);
	printf("\nUnesi ime datoteke gdje su rezultati 2.kolokvija: \n");
	scanf(" %s", kol2);

	citajDat(k1, kol1);
	citajDat(k2, kol2);
	
	printf("\nPRVI KOLOKVIJ: \n");
	ispis(k1->next);
	printf("\nDRUGI KOLOKVIJ: \n");
	ispis(k2->next);

	printf("\nPOLOZILI ISPIT: \n");
	polozeniIspit(head, k1, k2);
	ispis(head->next);

	return 0;
}

int ispis(position p)
{
	if (p == NULL)
		printf("Lista je prazna!\n");

	while (p != NULL)
	{
		printf("%s %s %.2f\n", p->ime, p->prezime, p->bodovi);
		p = p->next;
	}

	return 0;
}

int polozeniIspit(position p, position k1, position k2)
{
	position q = NULL;
	int ocjena = 0;
	float ukBodovi = 0;
	k1 = k1->next;
	k2 = k2->next;

	while (k1 != NULL)
	{
		if (k1->bodovi >= 50 && k2->bodovi >= 50)
		{
			ukBodovi = (k1->bodovi + k2->bodovi) / 2;
			ocjena = pretvoriBodove(ukBodovi);

			q = inicijalizacija(q);
			strcpy(q->ime, k1->ime);
			strcpy(q->prezime, k1->prezime);
			q->bodovi = ocjena;

			q->next = p->next;
			p->next = q;

		}
		k1 = k1->next;
		k2 = k2->next;
	}

	return 0;
}



int unesiUListu(position p, char* ime, char* prezime, float bodovi)
{
	position q = NULL;
	q = inicijalizacija(q);

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->bodovi = bodovi;

	q->next = p->next;
	p->next = q;


	return 0;
}


int pretvoriBodove(float bodovi)
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


int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char ime[40] = { 0 }, prezime[40] = { 0 };
	float bodovi = 0.0;
	int ocjena = 0;

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %f", ime, prezime, &bodovi);
		unesiUListu(p, ime, prezime, bodovi);

	}

	fclose(fp);

	return 0;
}


position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(lista));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->bodovi = 0.0;

	p->next = NULL;

	return p;

}