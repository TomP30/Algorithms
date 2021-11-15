#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/*************************************************/
/*                                               */
/*                   Fonctions                   */
/*                                               */
/*************************************************/


/*
int fact_bis(int n, int acc)
{
    if (n == 0)
        return acc;
    else
        return fact_bis(n - 1, acc * n);
}

int fact_term(int n)
{
    return fact_bis(n, 1);
}
*/

double abso(double x) {
    if (x < 0) return -x;
    else return x;
}

double expo(int N)
{
    double e = 1;
    int incr = 1;
    int fact = 1;
    while (incr < N)
    {
        e += 1. / fact;
        incr++;
        fact *= incr;
    }
    return e;
}

double puissance_double_it(double x, int n)
{
    int k;
    double res = 1.;
    if (n < 0)
    {
        k = -n;
        while (k > 0)
        {
            res *= x;
            k--;
        }
        return 1 / res;
    }
    else
    {
        k = n;
        while (k > 0)
        {
            res *= x;
            k--;
        }
    }
    return res;
}

float puissance_float_it(float x, int n)
{
    int k;
    float res = 1.;
    if (n < 0)
    {
        k = -n;
        while (k > 0)
        {
            res *= x;
            k--;
        }
        return 1 / res;
    }
    else
    {
        k = n;
        while (k > 0)
        {
            res *= x;
            k--;
        }
    }
    return res;
}

double puissance_rec_bis(double x, int n)
{
    if (n==0) return 1.;
    else return x * puissance_rec_bis(x, n - 1);
}

double puissance_rec(double x, int n)
{
    if (n < 0)
        return 1. / puissance_rec_bis(x, -n);
    else if (n == 0)
        return 1.;
    else
    {
        if (x == 0.)
            return 0.;
        else
            return puissance_rec_bis(x, n);
    }
}

double puissance_parite(double x, int n) {
    if (n == 0) return 1;
    else {
        double p = puissance_parite(x,n/2);
        if (n % 2 == 0) return p*p;
        else return p*p*x;
    }
}

double puisBis(double x, int n, int acc)
{
    if (n == 0)
        return acc;
    else
        return puisBis(x, n - 1, x * acc);
}

double puisTerm(double x, int n)
{
    if (n<0) return 1/puisBis(x, -n, 1);
    else if (n == 0) return 1;
    else 
    {
        if (x == 0) return 0;
        else return puisBis( x, n,1);
    }
}
double DL(double epsilon)
{
    return expo(10) * (1 - (1. / 2) * epsilon 
    + (11 / 24) * epsilon * epsilon 
    - (7 / 16) * epsilon * epsilon * epsilon 
    + (2447 / 5760) * epsilon * epsilon * epsilon * epsilon 
    - (959 / 2304) * epsilon * epsilon * epsilon * epsilon * epsilon);
}

int ack_it_rec_bis(int m, int n)
{
    if (m == 0)
        return n + 1;
    else
    {
        int r = 1;
        for (int i = 1; i <= n + 1; i++)
        {
            r = ack_it_rec_bis(m - 1, r);
        }
        return r;
    }
}

int ack_it_rec(int m) {
    return ack_it_rec_bis(m,0);
}

int ack_rec_bis(int m, int n)
{
    if (m == 0)
        return n + 1;
    else {
        if (n == 0)
            return ack_rec_bis(m - 1, 1);
        else
            return ack_rec_bis(m - 1, ack_rec_bis(m, n - 1));
    }
}

int ack_rec(int m) {
    return ack_rec_bis(m,0);
}

double X_rec(int n)
{
    if (n == 0)
        return 1;
    else
    {
        double x = X_rec(n - 1);
        return x + 1. / x;
    }
}

double X_ite(int n)
{
    double x = 1;
    while (n > 0)
    {
        x = x + 1 / x;
        n--;
    }
    return x;
}


/*************************************************/
/*                                               */
/*               Main ; Tests                    */
/*                                               */
/*************************************************/

int main(int argc, char **argv)
{
    double e = expo(30);
    printf("e à 10^-10 près : %.10f\n\n", e);

    //On teste la précision des doubles et float qu'une seule fois et on voit que double est plus précis -> on utilise que des double à présent
    printf("(1.00001)^100000  taux d'erreur = %.10e (double) \n", abso(e - puissance_double_it(1.00001, 100000)));
    printf("(1.00001)^100000  taux d'erreur = %.10e (float) \n\n", abso(e - puissance_float_it(1.00001, 100000)));

    //Les temps de calcul des affichages suivants sont dans une valeur arbitraire, permettant une comparaison
    clock_t t1 = clock();
    printf("(1.1)^10  taux d'erreur = %.10e (itératif),             temps de calcul : %.10f \n", abso(e - puissance_double_it(1.1, 10)),abso(clock()-t1)* 1000 / CLOCKS_PER_SEC);
    clock_t t2 = clock();
    printf("(1.1)^10  taux d'erreur = %.10e (récursif),             temps de calcul : %.10f \n", abso(e - puissance_rec(1.1, 10)),abso(clock()-t2)* 1000 / CLOCKS_PER_SEC);
    clock_t t3 = clock();
    printf("(1.1)^10  taux d'erreur = %.10e (parité),               temps de calcul : %.10f \n", abso(e - puissance_parite(1.1, 10)),abso(clock()-t3)* 1000 / CLOCKS_PER_SEC);
    clock_t t4 = clock();
    printf("(1.1)^10  taux d'erreur = %.10e (réc terminal),         temps de calcul : %.10f \n", abso(e - puisTerm(1.1, 10)),abso(clock()-t4)* 1000 / CLOCKS_PER_SEC);
    clock_t t5 = clock();
    printf("(1.1)^10  taux d'erreur = %.10e (développement limité), temps de calcul : %.10f \n\n", abso(e - DL(0.1)),abso(clock()-t5)* 1000 / CLOCKS_PER_SEC);

    t1 = clock();
    printf("(1.01)^100  taux d'erreur = %.10e (itératif),             temps de calcul : %.10f \n", abso(e - puissance_double_it(1.01, 100)),abso(clock()-t1)* 1000 / CLOCKS_PER_SEC);
    t2 = clock();
    printf("(1.01)^100  taux d'erreur = %.10e (récursif),             temps de calcul : %.10f \n", abso(e - puissance_rec(1.01, 100)),abso(clock()-t2)* 1000 / CLOCKS_PER_SEC);
    t3 = clock();
    printf("(1.01)^100  taux d'erreur = %.10e (parité),               temps de calcul : %.10f \n", abso(e - puissance_parite(1.01, 100)),abso(clock()-t3)* 1000 / CLOCKS_PER_SEC);
    t4 = clock();
    printf("(1.01)^100  taux d'erreur = %.10e (réc terminal),         temps de calcul : %.10f \n", abso(e - puisTerm(1.01, 100)),abso(clock()-t4)* 1000 / CLOCKS_PER_SEC);
    t5 = clock();
    printf("(1.01)^100  taux d'erreur = %.10e (développement limité), temps de calcul : %.10f \n\n", abso(e - DL(0.01)),abso(clock()-t5)* 1000 / CLOCKS_PER_SEC);

    t1 = clock();
    printf("(1.001)^1000  taux d'erreur = %.10e (itératif),             temps de calcul : %.10f \n", abso(e - puissance_double_it(1.001, 1000)),abso(clock()-t1)* 1000 / CLOCKS_PER_SEC);
    t2 = clock();
    printf("(1.001)^1000  taux d'erreur = %.10e (récursif),             temps de calcul : %.10f \n", abso(e - puissance_rec(1.001, 1000)),abso(clock()-t2)* 1000 / CLOCKS_PER_SEC);
    t3 = clock();
    printf("(1.001)^1000  taux d'erreur = %.10e (parité),               temps de calcul : %.10f \n", abso(e - puissance_parite(1.001, 1000)),abso(clock()-t3)* 1000 / CLOCKS_PER_SEC);
    t4 = clock();
    printf("(1.001)^1000  taux d'erreur = %.10e (réc terminal),         temps de calcul : %.10f \n", abso(e - puisTerm(1.001, 1000)),abso(clock()-t4)* 1000 / CLOCKS_PER_SEC);
    t5 = clock();
    printf("(1.001)^1000  taux d'erreur = %.10e (développement limité), temps de calcul : %.10f \n\n", abso(e - DL(0.001)),abso(clock()-t5)* 1000 / CLOCKS_PER_SEC);

    t1 = clock();
    printf("(1.00001)^10000  taux d'erreur = %.10e (itératif),             temps de calcul : %.10f \n", abso(e - puissance_double_it(1.00001, 100000)),abso(clock()-t1)* 1000 / CLOCKS_PER_SEC);
    t2 = clock();
    printf("(1.00001)^10000  taux d'erreur = %.10e (récursif),             temps de calcul : %.10f \n", abso(e - puissance_rec(1.00001, 100000)),abso(clock()-t2)* 1000 / CLOCKS_PER_SEC);
    t3 = clock();
    printf("(1.00001)^10000  taux d'erreur = %.10e (parité),               temps de calcul : %.10f \n", abso(e - puissance_parite(1.00001, 100000)),abso(clock()-t3)* 1000 / CLOCKS_PER_SEC);
    t4 = clock();
    printf("(1.00001)^10000  taux d'erreur = %.10e (réc terminal),         temps de calcul : %.10f \n", abso(e - puisTerm(1.00001, 100000)),abso(clock()-t4)* 1000 / CLOCKS_PER_SEC);
    t5 = clock();
    printf("(1.00001)^10000  taux d'erreur = %.10e (développement limité), temps de calcul : %.10f \n\n", abso(e - DL(0.00001)),abso(clock()-t5)* 1000 / CLOCKS_PER_SEC);

    for (int k = 0; k <= 4; k++) {
        printf("%d ", ack_it_rec(k));
        //printf("%d ", ack_rec(k));
    }
    printf("\n\n");

    printf("X100 = %f (récursif); X100 = %f (itératif) \n", X_rec(100), X_ite(100));
}