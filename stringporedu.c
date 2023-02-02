#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Napisati program koji iz datoteke cita stringove (mogu biti imena i mora ih biti min. 10) i
stvara vezanu listu elemenata sortiranih po abecedi.
*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char stringovi[60];
	position next;
}lista;

position inicijalizacija(position);
int citajDatoteku(position, char*);
int unesiUListu(position, char*);
int ispisListe(position);
int oslobodiMemoriju(position);

int main() 
{
	position head = NULL;
	char imeDat[60] = { 0 };

	head = inicijalizacija(head);
	
	citajDatoteku(head, imeDat);
	ispisListe(head->next);

	printf("\nOslobadjanje memorije...\n");
	oslobodiMemoriju(head);
	ispisListe(head->next);

	return 0;

}

position inicijalizacija(position p)
{
	p = (position)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	strcpy(p->stringovi, "");
	p->next = NULL;

	return p;
}

int citajDatoteku(position p, char* imeDat)
{
	char imena[60] = { 0 };
	FILE* fp = NULL;

	printf("Unesi ime datoteke iz koje ces procitati imena: ");
	scanf(" %s", imeDat);

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s ", imena);
		unesiUListu(p, imena);
	}

	fclose(fp);
	return 0;
}
int unesiUListu(position p, char* imena)
{
	position q = NULL;
	q = inicijalizacija(q);

	while (p->next != NULL && strcmp(p->next->stringovi, imena) < 0)
	{
		p = p->next;
	}

	strcpy(q->stringovi, imena);
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
		printf("%s \n", p->stringovi);
		p = p->next;
	}

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
