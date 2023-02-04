#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Napisati program koji za tri razlièita predmeta èita ime i prezime studenta te njegovu ocjenu.Podaci o
svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
ispisati je.
a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri predmeta.
b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
studenata, sadrži i njihovu prosjeènu ocjenu iz ta tri predmeta.
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista 
{
	char ime[40];
	char prezime[40];
	int bodovi;
	position next;

}lista;

position inicijalizacija(position);
int citajDat(position, char*);
position stvoriListu(position, char*, char*, int);
int ispisListe(position);
int poloziliSvaTri(position,position,position,position);
int oslobodiMemoriju(position);

int main()
{
	position hrv = NULL, mat = NULL, eng = NULL, svaTri=NULL;
	char datHrv[40] = { 0 }, datMat[40] = { 0 }, datEng[40] = { 0 };


	hrv = inicijalizacija(hrv);
	mat = inicijalizacija(mat);
	eng = inicijalizacija(eng);
	svaTri = inicijalizacija(svaTri);

	printf("Unesi ime datoteke - hrvatski: \n");
	scanf(" %s", datHrv);

	printf("Unesi ime datoteke - matematika: \n");
	scanf(" %s", datMat);

	printf("Unesi ime datoteke - engleski: \n");
	scanf(" %s", datEng);

	citajDat(hrv, datHrv);
	citajDat(mat, datMat);
	citajDat(eng, datEng);

	printf("\nHrvatski: \n");
	ispisListe(hrv->next);
	printf("\nMatematika: \n");
	ispisListe(mat->next);
	printf("\nEngleski: \n");
	ispisListe(eng->next);

	printf("\nPolozili sva tri predmeta: \n");
	poloziliSvaTri(svaTri, hrv, mat, eng);
	ispisListe(svaTri->next);

	oslobodiMemoriju(hrv);
	oslobodiMemoriju(mat);
	oslobodiMemoriju(eng);
	oslobodiMemoriju(svaTri);

	puts("\n");
	ispisListe(hrv->next);
	ispisListe(mat->next);
	ispisListe(eng->next);
	ispisListe(svaTri->next);

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
}


int poloziliSvaTri(position svaTri, position hrv, position mat, position eng)
{
	position noviEl = NULL;

	hrv = hrv->next;
	mat = mat->next;
	eng = eng->next;

	while (hrv != NULL)
	{
		if (hrv->bodovi >= 50 && mat->bodovi >= 50 && eng->bodovi >= 50)
		{
			noviEl = inicijalizacija(noviEl);
			strcpy(noviEl->ime, hrv->ime);
			strcpy(noviEl->prezime, hrv->prezime);
			noviEl->bodovi = (hrv->bodovi + mat->bodovi + eng->bodovi) / 3;

			noviEl->next = svaTri->next;
			svaTri->next = noviEl;
		}
		hrv = hrv->next;
		mat = mat->next;
		eng = eng->next;
		
	}


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


position stvoriListu(position p, char* imeStud, char* prezimeStud, int bodoviStud)
{
	position q = NULL;
	q = inicijalizacija(q);

	strcpy(q->ime, imeStud);
	strcpy(q->prezime, prezimeStud);
	q->bodovi = bodoviStud;
	
	q->next = p->next;
	p->next = q;

	return p;
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
	p->bodovi = 0;
	p->next = NULL;

	return p;
}

int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char imeStud[40] = { 0 }, prezimeStud[40] = { 0 };
	int bodoviStud = 0;

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %d", imeStud, prezimeStud, &bodoviStud);
		p = stvoriListu(p, imeStud, prezimeStud, bodoviStud);
	}

	fclose(fp);
	
	return 0;
}
