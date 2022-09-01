#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#define m 60

/*
Napisati program koji iz datoteke èita stringove (mogu biti imena i mora ih biti min. 10) i
stvara vezanu listu elemenata sortiranih po abecedi
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char stringovi[m];
	position next;
}Lista;

position Inicijalizacija(position);
int citajDat(position, char*);
int stvoriListu(position, char*);
int ispisListe(position);
int main()
{
	position head = NULL;
	char imeDat[m] = "popisImena.txt";
	head = Inicijalizacija(head);
	
	citajDat(head, imeDat);
	ispisListe(head->next);

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
	strcpy(p->stringovi, "");
	p->next = NULL;

	return p;

}
int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char procitano[m];

	fp = fopen(imeDat, "r");
	if (fp == NULL)
	{
		printf("Greska!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s", procitano);
		stvoriListu(p, procitano);
	}
	fclose(fp);
}
int stvoriListu(position p, char* procitano)
{
	position q = NULL;
	q = Inicijalizacija(q);

	while (p->next != NULL && strcmp(p->next->stringovi, procitano) < 0)
		p = p->next;

	strcpy(q->stringovi, procitano);
	q->next = p->next;
	p->next = q;

	return 0;
}
int ispisListe(position p)
{
	while (p != NULL)
	{
		printf("%s \t", p->stringovi);
		p = p->next;
	}
	return 0;
}