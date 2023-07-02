#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
Napisati program koji iz datoteke sub1.txt cita listu studenata koji su polozili
taj predmet. U 2. vezanu listu procitati studente iz sub2.txt.
Kreirati 3. vezanu listu u kojoj ce biti studenti koji su prosli samo jedan predmet.
Studenti u 3. listi moraju biti sortirani po abecedi. Ispisati listu.
*/

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
    char ime[20];
    pozicija next;
} lista;

pozicija inicijalizacija(pozicija);
int procitajDat(pozicija, char*);
int unosUListu(pozicija, char*);
int ispis(pozicija);
int novaLista(pozicija, char*);
pozicija trazi(pozicija, char*);
int provjera(pozicija, pozicija, pozicija);

int main()
{
    pozicija head1 = NULL;
    pozicija head2 = NULL;
    pozicija head3 = NULL;

    char imedat1[20] = { 0 };
    char imedat2[20] = { 0 };

    head1 = inicijalizacija(head1);
    head2 = inicijalizacija(head2);
    head3 = inicijalizacija(head3);

    procitajDat(head1, imedat1);
    procitajDat(head2, imedat2);
    puts("ISPIS LISTA:\n");
    ispis(head1->next);
    puts("");
    ispis(head2->next);
    printf("\nPOLOZILI SAMO JEDAN:\n");

    provjera(head1->next, head2->next, head3);
    ispis(head3->next);

    return 0;
}

pozicija inicijalizacija(pozicija p)
{
    p = (pozicija)malloc(sizeof(lista));
    if (!p)
    {
        printf("Greska u inicijalizaciji!\n");
        return NULL;
    }

    strcpy(p->ime, "");
    p->next = NULL;

    return p;
}

int procitajDat(pozicija p, char* imedat)
{
    FILE* fp = NULL;
    char name[20] = { 0 };

    printf("Unesi ime datoteke za citanje podataka:\n");
    scanf(" %s", imedat);

    fp = fopen(imedat, "r");

    while (fscanf(fp, " %s", name) == 1)
    {
        unosUListu(p, name);
    }

    fclose(fp);
    return 0;
}

int unosUListu(pozicija p, char* name)
{
    pozicija q = NULL;
    q = inicijalizacija(q);

    strcpy(q->ime, name);
    q->next = p->next;
    p->next = q;

    return 0;
}

int ispis(pozicija p)
{
    if (p == NULL)
    {
        printf("LISTA JE PRAZNA!\n");
        return 0;
    }

    while (p != NULL)
    {
        printf(" %s\n", p->ime);
        p = p->next;
    }

    return 0;
}

pozicija trazi(pozicija p, char* name)
{
    while (p != NULL)
    {
        if (strcmp(p->ime, name) == 0)
            return p;
        else
            p = p->next;
    }

    return NULL;
}

int provjera(pozicija p1, pozicija p2, pozicija p3)
{
    pozicija start1 = p1;
    pozicija start2 = p2;

    // Provjera studenata iz prve liste
    while (p1 != NULL)
    {
        if (trazi(p2, p1->ime) == NULL && trazi(p3, p1->ime) == NULL)
        {
            novaLista(p3, p1->ime);
        }
        p1 = p1->next;
    }

    // Provjera studenata iz druge liste
    while (p2 != NULL)
    {
        if (trazi(start1, p2->ime) == NULL && trazi(p3, p2->ime) == NULL)
        {
            novaLista(p3, p2->ime);
        }
        p2 = p2->next;
    }

    return 0;
}

int novaLista(pozicija p, char* name)
{
    pozicija q = NULL;
    q = inicijalizacija(q);

    while (p->next != NULL && strcmp(p->next->ime, name) < 0)
    {
        p = p->next;
    }

    strcpy(q->ime, name);
    q->next = p->next;
    p->next = q;

    return 0;
}