#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define m 60
/*
Napisati program koji iz datoteke (ime se unosi u programu) èita podatke o ljudima i kafiæima u kojima su ti ljudi bili.
Za 2: Izgraditi vezanu listu u kojoj su elementi složeni po nazivu kafiæa. Ispisati je, a za traženi kafiæ ispisati koliko
ga je ljudi posjetilo i koji su to ljudi.
*/


struct _lista;
typedef struct _lista* position;
typedef struct _lista {
	char ime[m];
	char prezime[m];
	char nazivKafica[m];
	position next;
}Lista;


position Inicijalizacija(position);
int citajDat(position, char*);
int stvoriListu(position, char*, char*, char*);
int ispisListe(position);
int traziPoKaficu(position, char*);
int oslobodiMemoriju(position);
int main()
{
	position head = NULL;
	head = Inicijalizacija(head);

	char imeDat[m] = "kaf.txt";
	char odabraniKafic[m];
	

	citajDat(head, imeDat);
	ispisListe(head->next);
	
	printf("\nUnesi naziv kafica: \n");
	scanf(" %s", odabraniKafic);
	traziPoKaficu(head, odabraniKafic);

	printf("\n OSLOBADANJE MEMORIJE...\n");
	oslobodiMemoriju(head);
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

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	strcpy(p->nazivKafica, "");
	p->next = NULL;

	return p;
}
int citajDat(position p, char* imeDat)
{
	FILE* fp = NULL;
	char ime[m], prezime[m], imeKafica[m];

	fp = fopen(imeDat, "r");
	if (!fp)
		return -1;

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %s", ime, prezime, imeKafica);
		stvoriListu(p, ime, prezime, imeKafica);
	}
	fclose(fp);
	return 0;
}
int stvoriListu(position p, char* ime, char* prezime, char* imeKafica)
{
	position q = NULL;
	q = Inicijalizacija(q);

	while (p->next != NULL && strcmp(p->next->nazivKafica, imeKafica) > 0)
		p = p->next;

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	strcpy(q->nazivKafica, imeKafica);

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
		printf("%s %s %s\n", p->ime, p->prezime, p->nazivKafica);
		p = p->next;
	}
	return 0;
}
int traziPoKaficu(position p, char* odabraniKafic) 
{
	int brojac = 0;
	
	while (p->next!= NULL)
	{
		if (strcmp(p->next->nazivKafica, odabraniKafic) == 0)
		{
			
			printf("%s %s\n", p->next->ime, p->next->prezime);
			++brojac;
			
		}
		p = p->next;
		
	}
	printf("%d ljudi je posjetilo %s \n", brojac, odabraniKafic);

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
}