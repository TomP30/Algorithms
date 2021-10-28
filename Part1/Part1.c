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

float puissance_float_rec(float x, int n)
{
    if (n < 0)
        return 1. / puissance_float_rec(x, -n);
    else if (n == 0)
        return 1.;
    else
    {
        if (x == 0)
            return 0.;
        else
            return x * puissance_float_rec(x, n - 1);
    }
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
    else if (n == 0)
        return 1.;
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

double puisBis(double x, int n, int acc)
{
    if (n == 0)
        return acc;
    else
        return puisBis(x, n - 1, x * acc);
}

double puisTerm(double x, int n)
{
    if (x = 0.)
        return 0.;
    else
    {
        if (n < 0)
            return 1 / puisBis(x, -n, 1);
        else
            return puisBis(x, n, 1);
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
    printf("e à 10^-6 près : %f\n\n", expo(10));

    printf("(1.1)^10 = %f (double) \n", puissance_double_it(1.1, 10));
    printf("(1.1)^10 = %f (float) \n", puissance_float_rec(1.1, 10));
    printf("(1.1)^10 = %f (développement limité) \n\n", DL(0.1));

    printf("(1.01)^100 = %f (double) \n", puissance_double_it(1.01, 100));
    printf("(1.01)^100 = %f (float) \n", puissance_float_rec(1.01, 100));
    printf("(1.01)^100 = %f (développement limité) \n\n", DL(0.01));

    printf("(1.001)^1000 = %f (double) \n", puissance_double_it(1.001, 1000));
    printf("(1.001)^1000 = %f (float) \n", puissance_float_rec(1.001, 1000));
    printf("(1.001)^1000 = %f (développement limité) \n\n", DL(0.001));

    printf("(1.00001)^100000 = %f (double) \n", puissance_double_it(1.00001, 100000));
    printf("(1.00001)^100000 = %f (float) \n", puissance_float_rec(1.00001, 100000));
    printf("(1.00001)^100000 = %f (développement limité) \n\n", DL(0.00001));

    for (int k = 0; k <= 4; k++) {
        printf("%d\n", ack_it_rec(k));
        printf("%d\n", ack_rec(k));
    }

    printf("X100 = %f (récursif); X100 = %f (itératif) \n", X_rec(100), X_ite(100));
}