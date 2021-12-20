/*************************************************/
/*                                               */
/*              INIT                             */
/*                                               */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

typedef struct bloc_image
{ 
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;
typedef bloc_image *image ;


/*************************************************/
/*                                               */
/*           Briques de base                     */
/*                                               */
/*************************************************/

image Construit_Blanc()
{
    image i = NULL ;

}

image Construit_Noir()
{
    image i = (image) malloc(sizeof(bloc_image));
    i->fils[0] = NULL ;
    i->fils[1] = NULL ;
    i->fils[2] = NULL ;
    i->fils[3] = NULL ;
    i->toutnoir = 1;
    return i;
}

image Construit_Composee(image ihg, image ihd, image ibg, image ibd)
{
    image i = Construit_Noir();
    i->toutnoir = 0;
    i->fils[0] = ihg;
    i->fils[1] = ihd;
    i->fils[2] = ibg;
    i->fils[3] = ibd;
}

image Copie(image i)
{
    image copy = NULL;
    if (TestNoir(i)){
        copy = Construit_Noir();
    }
    else if (NOT(TestBlanc(i))){
        copy = Construit_Composee(Copie(i->fils[0]),Copie(i->fils[1]),Copie(i->fils[2]),Copie(i->fils[3]));
    }
    return copy;
}

void RendMemoire(image* i)
{
    if (TestNoir(*i))
    {
        free(*i);
        *i = NULL;
    }
    else if (NOT(TestBlanc(*i)))
    {
        RendMemoire(&(*i)->fils[0]);
        RendMemoire(&(*i)->fils[1]);
        RendMemoire(&(*i)->fils[2]);
        RendMemoire(&(*i)->fils[3]);
        free(*i);
        *i = NULL;
    }
}

image Lecture();
/*************************************************/
/*                                               */
/*                 Prédicats                     */
/*                                               */
/*************************************************/


bool TestNoir(image i)
{
    return i->toutnoir == 1 
    AND i->fils[0] == NULL 
    AND i->fils[1] == NULL 
    AND i->fils[2] == NULL 
    AND i->fils[3] == NULL;
}
bool TestBlanc(image i)
{
    return i == NULL;
}


bool EstNoir(image i)
{
    return TestNoir(i)
    OR(EstNoir(i->fils[0]) 
        AND EstNoir(i->fils[1]) 
        AND EstNoir(i->fils[2]) 
        AND EstNoir(i->fils[3]));
}
bool EstBlanc(image i)
{
    return TestBlanc(i)
    OR(EstBlanc(i->fils[0]) 
        AND EstBlanc(i->fils[1]) 
        AND EstBlanc(i->fils[2]) 
        AND EstBlanc(i->fils[3]));
}

bool UnionNoire (image i1, image i2);

/*************************************************/
/*                                               */
/*                 Affichage                     */
/*                                               */
/*************************************************/


void Affiche_Normal_SansRL(image i)
{
    if (TestBlanc(i)) printf("B ");
    else if (TestNoir(i)) printf("N ");
    else
    {
        printf("+ ");
        Affiche_Normal_SansRL(i->fils[0]);
        Affiche_Normal_SansRL(i->fils[1]);
        Affiche_Normal_SansRL(i->fils[2]);
        Affiche_Normal_SansRL(i->fils[3]);
    }
}


void Affiche_Normal(image i)
{
    Affiche_Normal_SansRL(i);
    printf("\n");
}
void Bis_Affiche_Prof(image i,int p)
{
    if (TestBlanc(i)) printf("B%d ",p);
    else if (TestNoir(i)) printf("N%d ",p);
    else
    {
        printf("+%d ",p);
        Bis_Affiche_Prof(i->fils[0],p+1);
        Bis_Affiche_Prof(i->fils[1],p+1);
        Bis_Affiche_Prof(i->fils[2],p+1);
        Bis_Affiche_Prof(i->fils[3],p+1);
    }
}

void Affiche_Prof(image i)
{
    Bis_Affiche_Prof(i,0);
    printf("\n");
}


/*************************************************/
/*                                               */
/*             Aire et Image grise               */
/*                                               */
/*************************************************/


void BisAire(image i,int* Noir,int* Total)
{
    if (TestBlanc(i)) (*Total)++;
    else if (TestNoir(i))
    {
        (*Noir)++;
        (*Total)++;
    }
    else{
        BisAire(i->fils[0],Noir,Total);
        BisAire(i->fils[1],Noir,Total);
        BisAire(i->fils[2],Noir,Total);
        BisAire(i->fils[3],Noir,Total);
    }
}

double Aire(image i)
{
    int Noir,Total = 0;
    BisAire(i,&Noir,&Total);
    return (Noir*1.0)/Total;
}


void BisGrise(image i,int* cpt)
{
    if (NOT(TestNoir(i) OR TestBlanc(i)))
    {
        if (Aire(i)<=2./3 AND Aire(i)>=1./3) (*cpt)++;
        BisGrise(i->fils[0],cpt);
        BisGrise(i->fils[1],cpt);
        BisGrise(i->fils[2],cpt);
        BisGrise(i->fils[3],cpt);
    }
}

int CompteSousImagesGrises(image i)
{
    int cpt = 0;
    BisGrise(i,&cpt);
    return cpt;
}

void Negatif(image *i)
{
    if (TestBlanc(*i)){
        RendMemoire(i);
        *i = Construit_Noir();
    }
    else if (TestNoir(*i)){
        RendMemoire(i);
        *i = Construit_Blanc();
    }
    else {
        Negatif((*i)->fils[0]);
        Negatif((*i)->fils[1]);
        Negatif((*i)->fils[2]);
        Negatif((*i)->fils[3]);
    }
}