#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Napisati program koji iz datoteke èita dio teksta, rijeè po rijeè i unosi u binarno stablo pretraživanja
(maksimalna duljina rijeèi 1024 znaka). Ispisati binarno stablo na „inorder“ naèin.
Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve rijeèi koje poèinju samoglasnikom, a u
drugoj sve rijeèi koje poèinju suglasnikom. Rijeèi zapisane u datotekama moraju biti sortirane po abecedi.
*/

struct _stablo;
typedef struct _stablo* pok;
typedef struct _stablo {
	char rijec[1024];
	pok left;
	pok right;
}stablo;

pok inicijalizacija(pok);
int citajDat(pok, char*);
pok unesiUStablo(pok, char*);
int inorderIspis(pok);
int provjera(pok, char*,char*);
int upisiUDat(pok, char*);

int main()
{
	pok root = NULL;
	char imeDat[40] = { 0 };
	char dat1[40] = { 0 }, dat2[40] = { 0 };

	root = inicijalizacija(root);

	printf("Unesi ime datoteke iz koje citas, dat. za samoglasnike i za suglasnike: \n");
	scanf(" %s %s %s", imeDat,dat1,dat2);

	citajDat(root, imeDat);
	inorderIspis(root);
	provjera(root, dat1, dat2);

	return 0;
}

int provjera(pok p, char* dat1_samogl, char* dat2_sugl)
{
	if (p == NULL)
		return NULL;
	
	p->left = provjera(p->left, dat1_samogl, dat2_sugl);

	if (p->rijec[0] == 'a' || p->rijec[0] == 'e' || p->rijec[0] == 'i' || p->rijec[0] == 'o' || p->rijec[0] == 'u')
	{
		upisiUDat(p, dat1_samogl);
	}

	else
	{
		upisiUDat(p, dat2_sugl);
	}


	p->right = provjera(p->right, dat1_samogl, dat2_sugl);

	return 0;
}

int upisiUDat(pok p, char* imeDat)
{
	FILE* fp = NULL;
	fp = fopen(imeDat, "a+");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	fprintf(fp," %s\n", p->rijec);

	return 0;
}


int inorderIspis(pok p)
{
	if (p == NULL)
		return NULL;

	inorderIspis(p->left);
	printf("%s\n", p->rijec);		
	inorderIspis(p->right);
	
	return 0;
}

pok unesiUStablo(pok p, char* rijeciIzDat)
{
	if (p == NULL)
	{
		p = inicijalizacija(p);
		strcpy(p->rijec, rijeciIzDat);
	}

	else if (strcmp(rijeciIzDat, p->rijec) > 0)
		p->right = unesiUStablo(p->right, rijeciIzDat);
	else if (strcmp(rijeciIzDat, p->rijec) < 0)
		p->left = unesiUStablo(p->left, rijeciIzDat);

	return p;
}


int citajDat(pok p, char* imeDat)
{
	FILE* fp = NULL;
	char rijeciIzDat[1024] = { 0 };

	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s", rijeciIzDat);
		p = unesiUStablo(p, rijeciIzDat);
	}
	fclose(fp);
	return 0;
}


pok inicijalizacija(pok p)
{
	p = (pok)malloc(sizeof(stablo));
	if (!p)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->rijec, "");
	p->right = NULL;
	p->left = NULL;

	return p;
}
