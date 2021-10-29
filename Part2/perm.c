#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { FALSE, TRUE} bool;

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

typedef struct Dbloc
{
    Liste list;
    struct Dbloc *suivant;
} Dbloc;

typedef Dbloc *Dliste;

void initVide(Liste *L)
{
    *L = NULL;
}

void initVide2(Dliste *l)
{
    *l = NULL;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

bool estVide2(Dliste l)
{
    return l == NULL ;
}


int premier(Liste l)
{
    return l->nombre;
}

Liste premier2(Dliste l)
{
    return l->list;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste)malloc(sizeof(Bloc));
    tmp->nombre = x;
    tmp->suivant = l;
    return tmp;
}

Dliste ajoute2(Liste x, Dliste l)
{
    Dliste tmp = (Dliste)malloc(sizeof(Dbloc));
    tmp->list = x;
    tmp->suivant = l;
    return tmp;
}

void empile(int x, Liste *L)
{
    *L = ajoute(x, *L);
}

Liste suite(Liste l)
{
    return l->suivant;
}

Dliste suite2(Dliste l)
{
    return l->suivant;
}

void depile(Liste *L)
{
    Liste tmp = *L;
    *L = suite(*L);
    free(tmp);
}

Dliste concat(Dliste l1, Dliste l2)
{
    if (l1 == NULL)
        return l2;
    else
        return ajoute2(premier2(l1), concat(suite2(l1), l2));
}

Dliste AETTL(int x, Dliste l)
{
    if (l == NULL)
    {
        Dliste *p;
        initVide2(p);
        return *p;
    }
    else
        return ajoute2(
            ajoute(x, premier2(l)),
            AETTL(x, suite2(l)));
}

Dliste ATP(int x, Liste l)
{
    if (l == NULL)
    {
        Liste *p;
        Dliste *q;
        initVide(p);
        initVide2(q);
        ajoute(x, *p);
        return ajoute2(*p, *q);
    }
    else
        return ajoute2(
            ajoute(x, l),
            AETTL(premier(l), ATP(x, suite(l))));
}

Dliste ATLTP(int x, Dliste l)
{
    if (l == NULL)
    {
        Liste *p;
        Dliste *q;
        initVide(p);
        initVide2(q);
        return ajoute2(*p, *q);
    }
    else
        return concat(ATP(x, premier2(l)), ATLTP(x, suite2(l)));
}

Dliste Permutations(int n)
{
    if (n == 0)
    {
        Liste *p;
        Dliste *q;
        initVide(p);
        initVide2(q);
        return ajoute2(*p, *q);
    }
    else
    {
        return ATLTP(n, Permutations(n - 1));
    }
}

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}

void affiche_rec2(Dliste l)
{
    if(estVide2(l))
        printf("\n");
    else
    {
        affiche_rec(premier2(l));
        affiche_rec2(suite2(l));
    }
}

int main()
{   
    Dliste p = Permutations(1);
    affiche_rec2(p);
    return 0;
}