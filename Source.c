#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)

//Napisati program koji za tri razlièita predmeta èita ime i prezime studenta te njegovu ocjenu.Podaci o
//svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
//ispisati je.
//a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri
//predmeta.
//b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
//studenata, sadrži i njihovu prosjeènu ocjenu iz ta tri predmeta.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define m 60

struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char ime[m];
	char prezime[m];
	int bodovi;
	position next;
}Lista;

position Inicijalizacija(position);
int citajDat(position, char*);
int stvoriListu(position, char*, char*, int);
int ispisListe(position);
int poloziliSvaTri(position, position, position, position);
int main()
{
	position hrv = NULL, mat = NULL, eng = NULL, svaTri = NULL;
	char hrvDat[m] = "h.txt", matDat[m] = "m.txt", engDat[m] = "e.txt";

	hrv = Inicijalizacija(hrv);
	mat = Inicijalizacija(mat);
	eng = Inicijalizacija(mat);
	svaTri = Inicijalizacija(svaTri);

	citajDat(hrv, hrvDat);
	citajDat(mat, matDat);
	citajDat(eng, engDat);

	printf("HRVATSKI: \n");
	ispisListe(hrv->next);
	puts("\n");

	printf("MATEMATIKA: \n");
	ispisListe(mat->next);
	puts("\n");

	printf("ENGLESKI: \n");
	ispisListe(eng->next);
	puts("\n");

	printf("POLOZILE SVA TRI PREDMETA: \n");
	poloziliSvaTri(svaTri, hrv, mat, eng);
	ispisListe(svaTri->next);
	puts("\n");

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
	p->bodovi = 0;
	p->next = NULL;

	return p;
}
int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char imeSt[m], prezimeSt[m];
	int bodoviSt;
	
	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %d", imeSt, prezimeSt, &bodoviSt);
		stvoriListu(p, imeSt, prezimeSt, bodoviSt);
	}

	return 0;
}
int stvoriListu(position p, char* imeSt, char* prezimeSt, int bodoviSt)
{
	position q = NULL;
	q = Inicijalizacija(q);

	strcpy(q->ime, imeSt);
	strcpy(q->prezime, prezimeSt);
	q->bodovi = bodoviSt;

	q->next = p->next;
	p->next = q;

	return 0;
}
int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna!\n");
	}
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->bodovi);
		p = p->next;
	}
	return 0;
}

int poloziliSvaTri(position svaTri, position hrv, position mat, position eng)
{
	position q = NULL;
	hrv = hrv->next;
	mat = mat->next;
	eng = eng->next;

	while (hrv != NULL) //!! da je bilo hrv->next!=NULL onda ne bi zadnji element u listi printalo!
	{
		if (hrv->bodovi >= 50 && mat->bodovi >= 50 && eng->bodovi >= 50)
		{
			q = Inicijalizacija(q);
			strcpy(q->ime, hrv->ime);
			strcpy(q->prezime, hrv->prezime);
			q->bodovi = 0;
			q->next = svaTri->next;
			svaTri->next = q;
		}
		hrv = hrv->next;
		mat = mat->next;
		eng = eng->next;
	}
	return 0;
}