#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define m 60

/* Iz datoteke èitaju rijeèi i spremaju u vezanu listu na naèin da se rijeèi slažu po abecednom redu
obrnutom od abecednog reda.Zatim ispisati tu vezanu listu.*/

struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char rijeci[m];
	position next;
}Lista;

position Inicijalizacija(position);
int citajDatoteku(position, char*);
int stvoriListu(position, char*);
int ispisListe(position);
int oslobodiMemoriju(position);

int main()
{
	position head = NULL;
	head = Inicijalizacija(head);

	char imeDat[m] = "rijecii.txt";
	citajDatoteku(head, imeDat);
	ispisListe(head->next);

	printf("\n\nOslobadjanje memorije...\n");
	oslobodiMemoriju(head);
	puts("\n");
	ispisListe(head->next);

	return 0;
}

position Inicijalizacija(position p)
{
	p = (position)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->rijeci, "");
	p->next = NULL;

	return p;
}
int citajDatoteku(position p, char* imeDat)
{
	FILE* fp = NULL;
	char str[m];

	fp = fopen(imeDat, "r");
	if (fp==NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s", str);
		stvoriListu(p, str);

	}
	fclose(fp);

	return 0;
}
int stvoriListu(position p, char* str)
{
	position q = NULL;
	q = Inicijalizacija(q);

	while (p->next != NULL && strcmp(p->next->rijeci, str) > 0)
		p = p->next;
	
	strcpy(q->rijeci, str);
	q->next = p->next;
	p->next = q;


	return 0;
}
int ispisListe(position p)
{
	if (p == NULL)
	{
		printf("LISTA JE PRAZNA!\n");
	}

	while (p != NULL)
	{
		printf("%s \t", p->rijeci);
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
	p = p->next;

	return 0;
}