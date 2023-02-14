#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define GG (199)
#define DG (100)

/*Program cita iz datoteke ime i prezime studenta, te svakom dodijeli jedinstven ID u opsegu 100-199 (broj se ne smije ponavljati!).
Od dobivenih podataka, lista se gradi po ID-u koristeci sortirani unos. Ispisati listu.
Izbrisati sve one osobe cije se ime ponavlja i to tako da ostane samo jedna osoba tog imena. Ispisati novu listu.*/

struct _student;
typedef struct _student* position;
typedef struct _student
{
	char ime[40];
	char prezime[40];
	int id;
	position next;
}student;

position inicijalizacija(position);
int citajDat(position, char*);
int generiraj();
int stvoriListu(position, char*, char*, int);
int ispis(position);
int izbrisiPonavljanaImena(position);
int oslobodiMemoriju(position);

int main()
{
	srand(time(NULL));
	position head = NULL;
	char imeDat[40] = { 0 };

	head = inicijalizacija(head);

	citajDat(head, imeDat);
	ispis(head->next);

	printf("\nLista nakon brisanja duplih imena...\n");
	izbrisiPonavljanaImena(head);
	ispis(head->next);

	printf("\nOSLOBODI MEMORIJU...\n");
	oslobodiMemoriju(head);
	ispis(head->next);

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


int izbrisiPonavljanaImena(position p)
{
	position p1 = NULL, p2 = NULL, temp = NULL;

	p1 = p; //p1=head

	while (p1 != NULL && p1->next != NULL)
	{
		p2 = p1;

		while (p2->next != NULL)
		{
			if (strcmp(p1->ime, p2->next->ime) == 0)
			{
				temp = p2->next;
				p2->next = temp->next;
				free(temp);
			}
			else
				p2 = p2->next;
		}
		p1 = p1->next;
	}


	return 0;
}


int generiraj()
{
	int broj = 0;
	broj = rand() % (GG - DG + 1) + DG;
	return broj;
}

int ispis(position p)
{
	if (p == NULL)
	{
		printf("Prazna lista!\n");
		return NULL;
	}

	while (p != NULL)
	{
		printf("%d %s %s\n", p->id, p->ime, p->prezime);
		p = p->next;
	}

	return 0;
}

int stvoriListu(position p, char* ime, char* prezime, int id)
{
	position q = NULL;
	
	while (p->next != NULL && p->next->id <= id)
	{
		p = p->next;
	}

	if (p->id != id)
	{
		q = inicijalizacija(q);
		strcpy(q->ime, ime);
		strcpy(q->prezime, prezime);
		q->id = id;
		q->next = p->next;
		p->next = q;
	}
	else
		return -1;

	return 0;
}


int citajDat(position p, char* imeDat)
{
	char ime[40] = { 0 }, prezime[40] = { 0 };
	int id = 0;

	FILE* fp = NULL;

	printf("Unesi ime datoteke: ");
	scanf(" %s", imeDat);
	puts("\n");

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", ime, prezime);
		id = generiraj();
		stvoriListu(p, ime, prezime, id);

	}
	fclose(fp);
	return 0;
}

position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(student));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->id = 0;
	p->next = NULL;

	return p;
}
