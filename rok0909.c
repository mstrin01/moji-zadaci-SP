#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>


/* 9.9.21.
Napisati program koji iz datoteke èita imena studenata. Nakon što se proèita ime jednog studenta dodijeli mu se ocjena iz predmeta
(sluèajna vrijednost od 1 do 5) i sprema se u vezanu listu sortirano prema ocjenama od najvece prema najmanjoj. Ispiši listu.
Za 2: sluèajno generirati jednu ocjenu i izbrisati sve studente s tom ocjenom. Ispisati listu.
Za 3: sortirati ne samo po ocjeni, veæ i po prezimenu i imenu.
*/

#define GG 5
#define DG 1
#define m 60

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char ime[m];
	char prezime[m];
	int ocjena;
	position next;
}Lista;

position Inicijalizacija(position);
int citajDatoteku(position, char*);
int Generiraj();
int kreirajListu(position,char*,char*,int);
int ispisListe(position);
int brisiStudente(position, int);
int main()
{
	srand(time(NULL));
	position head = NULL;
	int slucajnaOcjena = 0;
	head = Inicijalizacija(head);

	char imeDat[m] = "popisStud.txt";
	citajDatoteku(head, imeDat);
	ispisListe(head->next);

	puts("\n");
	printf("...Bira se slucajno odabrana ocjena za brisanje...\n");
	slucajnaOcjena = Generiraj();
	printf("Slucajno odabrana ocjena -> %d\n", slucajnaOcjena);
	puts("\n");
	printf("...Brisanje studenata s tom ocjenom...\n");
	puts("\n");
	printf("Lista nakon brisanja izgleda ovako: \n");
	brisiStudente(head,slucajnaOcjena);
	ispisListe(head->next);


	
	return 0;

}

position Inicijalizacija(position p)
{
	p = (position)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska u inicijalizaciji!\n");
		return NULL;
	}

	strcpy(p->ime,"");
	strcpy(p->prezime,"");
	p->ocjena = 0;
	p->next = NULL;

	return p;
}

int citajDatoteku(position p, char* imeDat)
{
	char imeStud[m] = { 0 }, prezimeStud[m] = { 0 };
	int ocjenaStud = 0;

	FILE* fp = NULL;
	fp = fopen(imeDat, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp," %s %s",imeStud,prezimeStud);
		ocjenaStud = Generiraj();
		kreirajListu(p, imeStud, prezimeStud, ocjenaStud);
	}

	fclose(fp);

	return 0;
}

int Generiraj()
{
	int randomOcjena = 0;
	randomOcjena = rand() % (GG - DG + 1) + DG;

	return randomOcjena;
}

int kreirajListu(position p, char* imeStud, char* prezimeStud, int ocjenaStud)
{
	position q = NULL;
	q = Inicijalizacija(q);

	

	while (p->next
		!= NULL && p->next->ocjena > ocjenaStud)
	{
		p = p->next;
	}
	strcpy(q->ime, imeStud);
	strcpy(q->prezime, prezimeStud);
	q->ocjena = ocjenaStud;

	q->next = p->next;
	p->next = q;

	return 0;
}

int ispisListe(position p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return 0;
}

int brisiStudente(position p, int ocjenaZaBrisanje)
{
	position temp = NULL;
	while (p->next != NULL)
	{
		if (p->next->ocjena == ocjenaZaBrisanje)
		{
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		else
			p = p->next;
	}
	return 0;
}