#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Napisati program koji èita iz datoteka podatke o studentima i ispitima, te kreira dvije vezane liste
struct _Student{char *sifra_studenta; char *ime; char *prezime; char *sifra_ispita;struct _Student
*Next;};
struct _Ispit {char *sifra_ispita; char *naziv; struct _Ispit *Next;};
Potrebno je ispisati koliko je studenata položilo svaki pojedini ispit (po nazivu ispita), te nabrojati koji su
to studenti
*/

struct _student;
typedef struct _student* position;
typedef struct _student
{
	char ime[40];
	int sifraStud;
	int sifraIspit;
	position next;
}student;

struct _ispit;
typedef struct _ispit* pok;
typedef struct _ispit
{
	int sifraIspit;
	char nazivIspita[40];
	pok next;
}ispit;

position inic_stud(position);
pok inic_ispit(pok);
int citajDat_stud(position, char*);
int citajDat_ispit(pok, char*);
int listaStudenata(position, int, char*, int);
int listaIspita(pok, int, char*);
int ispisStud(position);
int ispisIspit(pok);
int provjera(position, pok);

int main()
{
	pok head_ispit = NULL;
	position head_stud = NULL;

	char dat_ispit[40] = { 0 }, dat_stud[40] = { 0 };

	head_ispit = inic_ispit(head_ispit);
	head_stud = inic_stud(head_stud);

	citajDat_ispit(head_ispit, dat_ispit);
	citajDat_stud(head_stud, dat_stud);

	printf("\nLISTA STUDENATA: \n");
	ispisStud(head_stud->next);
	puts("\n");
	printf("\nLISTA ISPITA: \n");
	ispisIspit(head_ispit->next);

	printf("\n");
	provjera(head_stud, head_ispit);


	return 0;
}

int provjera(position s, pok i)
{
	int brojac = 0;
	position start = NULL;
	start = s;
	s = s->next;
	i = i->next;

	while (i!=NULL)
	{
		printf("\nPredmet %s su polozili: \n", i->nazivIspita);
		while (s!=NULL)
		{
			if (i->sifraIspit == s->sifraIspit)
			{
				++brojac;
				printf("%s \n", s->ime);
			}
			s = s->next;
		}
		printf("Ukupno njih: %d \n", brojac);
		s = start;
		i = i->next;
		brojac = 0;
	}
	return 0;
}


int ispisStud(position p)
{
	if (p == NULL)
		printf("Lista je prazna!\n");

	while (p != NULL)
	{
		printf("%d %s %d\n", p->sifraStud, p->ime, p->sifraIspit);
		p = p->next;
	}

	return 0;
}
int ispisIspit(pok p)
{
	if (p == NULL)
		printf("Lista je prazna!\n");

	while (p != NULL)
	{
		printf("%d %s\n", p->sifraIspit, p->nazivIspita);
		p = p->next;
	}
	return 0;
}


int listaStudenata(position p, int sifraStud, char* imeStud, int sifraIspita)
{
	position q = NULL;
	q = inic_stud(q);

	while (p->next != NULL && p->next->sifraIspit < sifraIspita)
		p = p->next;

	strcpy(q->ime, imeStud);
	q->sifraIspit = sifraIspita;
	q->sifraStud = sifraStud;

	q->next = p->next;
	p->next = q;

	return 0;
}
int listaIspita(pok p, int sifraIspita, char* nazivIspita)
{
	pok q = NULL;
	q = inic_ispit(q);

	while (p->next != NULL && p->next->sifraIspit < sifraIspita)
		p = p->next;

	strcpy(q->nazivIspita, nazivIspita);
	q->sifraIspit = sifraIspita;

	q->next = p->next;
	p->next = q;

	return 0;
}

int citajDat_stud(position p, char* dat1)
{
	FILE* fp1 = NULL;
	char imeStud[40] = { 0 };
	int sifraStud = 0, sifraIspit = 0;

	printf("Unesi ime datoteke (studenti): ");
	scanf(" %s", dat1);
	puts("\n");

	fp1 = fopen(dat1, "r");
	if (!fp1)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp1))
	{
		fscanf(fp1, " %d %s %d", &sifraStud, imeStud, &sifraIspit);
		listaStudenata(p, sifraStud, imeStud, sifraIspit);
	}

	fclose(fp1);

	return 0;
}

int citajDat_ispit(pok p, char* dat2)
{
	FILE* fp = NULL;
	char nazivIspita[40] = { 0 };
	int sifraIspit = 0;

	printf("Unesi ime datoteke (ispit): ");
	scanf(" %s", dat2);
	puts("\n");

	fp = fopen(dat2, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d %s", &sifraIspit, nazivIspita);
		listaIspita(p, sifraIspit, nazivIspita);
	}

	fclose(fp);
	return 0;
}

position inic_stud(position p)
{
	p = (position)malloc(sizeof(student));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	strcpy(p->ime, "");
	p->sifraIspit = 0;
	p->sifraStud = 0;
	p->next = NULL;

	return p;
}
pok inic_ispit(pok p)
{
	p = (pok)malloc(sizeof(ispit));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	strcpy(p->nazivIspita, "");
	p->sifraIspit = 0;
	p->next = NULL;

	return p;
}
