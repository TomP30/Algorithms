
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

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


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*         2. LISTES-PILES ET FILES              */
/*                                               */
/*************************************************/

bool ZeroEnDeuxiemePosition (Liste l)
{
    if (estVide(l) || estVide(suite(l))) return FALSE;
    else return (suite(l))->nombre == 0;
}

bool QueDesZeros (Liste l)
{
    if (estVide(l)) return TRUE;
    else return (l->nombre == 0) && QueDesZeros(suite(l));  
}

int Compte0Initiaux_rec(Liste l)
{
    if (estVide(l)) return 0;
    else
    {
        if (premier(l)==0) return 1 + Compte0Initiaux_rec(suite(l));
        else return 0;
    }
}

int Compte0Initiaux_iter(Liste l)
{
    Liste copy = l;
    int cpt = 0;
    while (NOT(estVide(copy)) && (copy->nombre == 0))
    {
        cpt ++;
        copy = copy->suivant;
    }
    return cpt;
}

int Bis_C0I_1 (Liste l, int acc)
{
    if (estVide(l)) return acc;
    else
    {
        if (premier(l)==0) return Bis_C0I_1(suite(l), acc+1);
        else return acc;
    }
}

int Compte0Initiaux_term1(Liste l)
{
    return Bis_C0I_1(l,0);
}

void Bis_C0I_2(Liste l, int* acc)
{
    if (estVide(l)) return;
    else
    {
        if (premier(l)==0){
            (*acc)=(*acc) +1 ;
            Bis_C0I_2(suite(l),acc);
        };
    }
}

int Compte0Initiaux_term2(Liste l)
{
    int acc = 0;
    Bis_C0I_2(l, &acc);
    return acc;
}

void BisIT(Liste l1, Liste l2, Liste* lsave)
{
    if (NOT(estVide(l1)||estVide(l2))){
        if (premier(l1)>premier(l2)) BisIT(l1,suite(l2),lsave);
        else if (premier(l1)<premier(l2)) BisIT(suite(l1),l2,lsave);
        else 
        {
            BisIT(suite(l1),suite(l2),lsave);
            empile(premier(l1),lsave);
        }
    }
}

Liste IntersectionTriee(Liste l1, Liste l2)
{
    Liste save;
    initVide(&save);
    BisIT(l1, l2, &save);
    return save;
}

void ElimineKPremiersX(Liste* l, int k, int x)
{
    if (NOT(estVide(*l)))
    {
        if (k!=0)
        {
            if (premier(*l)==x)
            {
                depile(l);
                return ElimineKPremiersX(l,k-1,x);
            }else
            {
                return ElimineKPremiersX(&(*l)->suivant,k,x);
            }
        }
    }
}

void Bis_EKDX(Liste* l,int* k,int x)
{
    if (NOT(estVide(*l)))
    {
        Bis_EKDX(&(*l)->suivant,k,x);
        if ((*k)>0 && premier(*l)==x)
        {
            (*k)=(*k)-1;
            depile(l);
        }
    }
}

void ElimineKDerniersX(Liste *l, int k, int x)
{
    Bis_EKDX(l,&k,x);
}


// File


typedef Liste* File;

void initFileVide(File* f)
{
    *f = NULL;
}

void ajouteFile(int x, File *f)
{
    Bloc* tmp = (Bloc*) malloc(sizeof(Bloc)) ;
    tmp->nombre = x;
    if (f == NULL)
    {
        tmp->suivant = tmp ;
        *f = &tmp->suivant;
        **f = tmp;
    }else
    {
        tmp->suivant = **f ;
        **f = tmp;
        *f = &tmp->suivant;
    }
    
    
}

/*void sortir(int x, File* f)
{
    if (x == (**f)->nombre)
    {
        depile(**f);
    }else
    {
        File save = *f;
        save = (**f)->suivant;
        while(*f != save)
        {
            if (x == (**save).nombre)
            {
                depile(*save);
            }
        }
    }
}*/

void printFile (File f)
{
    Liste L2 = *f;
    Liste L1 = L2;
    printf("%d ", premier(L2));
    L2 = suite(L2);
    while(L2 != L1)
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}
/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    //Fonctions relatives aux 0
    Liste l, g, zeros;

        initVide (&l) ;
        initVide (&g) ;
        initVide(&zeros) ;

             empile(0, &l) ;      //l = [0,0,1,2,4,0]
             empile(4, &l) ;
             empile(2, &l) ;
             empile(1, &l) ;
             empile(0, &l) ;
             empile(0, &l) ;

             empile(3, &g) ;     //g = [0,1,0,3,4,3]
             empile(4, &g) ;
             empile(3, &g) ;
             empile(0, &g) ;
             empile(1, &g) ;
             empile(0, &g) ;

             empile(0, &zeros) ;//zeros = [0,0,0,0,0,0]
             empile(0, &zeros) ;
             empile(0, &zeros) ;
             empile(0, &zeros) ;
             empile(0, &zeros) ;
             empile(0, &zeros) ;

        assert(ZeroEnDeuxiemePosition(l));
        assert(NOT(ZeroEnDeuxiemePosition(g)));
        assert(ZeroEnDeuxiemePosition(zeros));

        assert(QueDesZeros(zeros));
        assert(NOT(QueDesZeros(l)));
        assert(NOT(QueDesZeros(g)));

        assert(Compte0Initiaux_rec(l)==2);
        assert(Compte0Initiaux_rec(g)==1);
        assert(Compte0Initiaux_rec(zeros)==6);

        assert(Compte0Initiaux_iter(l)==2);
        assert(Compte0Initiaux_iter(g)==1);
        assert(Compte0Initiaux_iter(zeros)==6);

        assert(Compte0Initiaux_term1(l)==2);
        assert(Compte0Initiaux_term1(g)==1);
        assert(Compte0Initiaux_term1(zeros)==6);

        assert(Compte0Initiaux_term2(l)==2);
        assert(Compte0Initiaux_term2(g)==1);
        assert(Compte0Initiaux_term2(zeros)==6);

        ElimineKDerniersX(&l,2,0);
        printf("[0,1,2,4] ");
        affiche_rec(l);
        ElimineKPremiersX(&g,1,3);
        printf("[0,1,0,4,3] ");
        affiche_rec(g);

    VideListe(&l);
    VideListe(&g);
    VideListe(&zeros);

    // Intersection Triée

    Liste l1,l2, l3;
    initVide(&l1);
    initVide(&l2);
    initVide(&l3);

        empile(4,&l1);
        empile(4,&l1);
        empile(3,&l1);
        empile(2,&l1);
        empile(2,&l1);
        empile(2,&l1);
        empile(1,&l1);
        empile(1,&l1);

        empile(8,&l2);
        empile(7,&l2);
        empile(6,&l2);
        empile(5,&l2);
        empile(5,&l2);
        empile(4,&l2);
        empile(3,&l2);
        empile(1,&l2);

        empile(8,&l3);
        empile(7,&l3);
        empile(6,&l3);
        empile(4,&l3);
        empile(3,&l3);
        empile(3,&l3);
        empile(2,&l3);
        empile(2,&l3);

        Liste m1=IntersectionTriee(l1,l1);
        printf("IT l1,l1 :");
        affiche_rec(m1);

        Liste m2=IntersectionTriee(l2,l1);
        printf("IT l2,l1 :");
        affiche_rec(m2);

        Liste m3=IntersectionTriee(l2,l3);
        printf("IT l2,l3 :");
        affiche_rec(m3);

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&m1);
    VideListe(&m2);
    VideListe(&m3);

    File f;

    initFileVide (&f);
    ajouteFile(1,&f);
    ajouteFile(2,&f);
    ajouteFile(3,&f);
    ajouteFile(4,&f);
    ajouteFile(5,&f);
    //printFile(f);

    return 0;
}





