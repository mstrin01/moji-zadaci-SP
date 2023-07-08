#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _lista;
typedef struct _lista* Pozicija;
typedef struct _lista
{
    int broj;
    int redni;
    Pozicija next;
} Lista;

Pozicija inicijalizacija()
{
    Pozicija p = (Pozicija)malloc(sizeof(Lista));
    if (!p)
    {
        printf("Inicijalizacija neuspjesna!\n");
        return NULL;
    }

    p->broj = 0;
    p->redni = 0;
    p->next = NULL;

    return p;
}

void generirajBr(Pozicija p)
{
    int brojac = 0;
    int br = 0;

    do
    {
        br = rand() % (150 - 100 + 1) + 100;
        Pozicija q = inicijalizacija();
        while (p->next != NULL)
            p = p->next;
        q->broj = br;
        q->redni = brojac;
        q->next = p->next;
        p->next = q;
        brojac++;

    } while (brojac < 20);
}

void ispis(Pozicija p)
{
    if (p == NULL)
    {
        printf("Lista je prazna.\n");
        return;
    }

    while (p != NULL)
    {
        printf("%d. %d\n", p->redni, p->broj);
        p = p->next;
    }
}

int generirajRedni()
{
    int br = 0;
    br = rand() % 20;
    return br;
}

void prebaciNaPocetak(Pozicija head, int redni)
{
    if (head->next == NULL || head->next->redni == redni)
    {
        return;
    }

    Pozicija prethodni = head;
    Pozicija trenutni = head->next;

    while (trenutni != NULL)
    {
        if (trenutni->redni == redni)
        {
            prethodni->next = trenutni->next;
            trenutni->next = head->next;
            head->next = trenutni;
            return;
        }

        prethodni = trenutni;
        trenutni = trenutni->next;
    }
}

void oslobodiMemoriju(Pozicija p)
{
    if (p == NULL)
    {
        return;
    }

    oslobodiMemoriju(p->next);
    free(p);
}

int main()
{
    srand(time(NULL));
    Pozicija head = inicijalizacija();
    generirajBr(head);

    printf("Originalna lista:\n");
    ispis(head->next);

    printf("\nGeneriranje 5 slucajnih rednih brojeva:\n");
    int i;
    for (i = 0; i < 5; i++)
    {
        int redni = generirajRedni();
        printf("%d\n", redni);
        prebaciNaPocetak(head, redni);
    }

    printf("\nNova lista:\n");
    ispis(head->next);

    oslobodiMemoriju(head);

    return 0;
}
