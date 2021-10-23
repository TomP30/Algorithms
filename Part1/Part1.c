#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/*************************************************/
/*                                               */
/*                   Fonctions                   */
/*                                               */
/*************************************************/
int factorial (int n)
{
    if (n==0) return 1;
    else return n * factorial(n - 1);
}

double exp(double epsilon)
{
    double e = 1;
    int incr = 1;
    while ((1./factorial(incr+1)) > epsilon)
    {
        e += 1./factorial(incr);
        incr ++;
    }
    return e;
}

float Puissance_fl(float x, int n)
{
    if (n<0) return 1./Puissance_fl(x,-n);
    else if (n==0) return 1.;
    else
    {
        if (x==0) return 0.;
        else return x * Puissance_fl(x,n-1);
    }
}
double Puissance_db(double x, int n)
{
    int k;
    double res = 1.;
    if (n<0)
    {
        k = -n;
        while (k>0)
        {
            res *= x;
            k--;
        }
        return 1/res;
    }
    else if (n==0) return 1.;
    else
    {
        k = n;
        while (k>0)
        {
            res *= x;
            k--;
        }
    }
    return res;

}

double DL(double epsilon)
{
    return exp(0.000001) * (1 - (1./2)*epsilon + (11/24)*epsilon*epsilon 
    - (7/16)*epsilon*epsilon*epsilon 
    + (2447/5760)*epsilon*epsilon*epsilon*epsilon 
    - (959/2304)*epsilon*epsilon*epsilon*epsilon*epsilon);
}

int Ack_ite(int m,int n)
{
    if (m==0) return n+1;
    else
    {
        int r = 1;
        for (int i=1;i<=n+1;i++)
        {
            r = Ack_ite(m-1,r);
        }
        return r;
    }
}

int Ack_rec(int m, int n)
{
    if (m == 0) return n + 1;
    else if (n == 0) return Ack_rec(m-1,1);
    else return Ack_rec(m-1,Ack_rec(m,n-1));
}

double X_rec(int n)
{
    if (n==0) return 1;
    else 
    {
        float x = X_rec(n-1);
        return x + 1./x;
    }
}

double X_ite(int n)
{
    double x = 1;
    while (n>0)
    {
        x = x + 1/x;
        n--;
    }
    return x;
}


/*************************************************/
/*                                               */
/*               Main ; Tests                    */
/*                                               */
/*************************************************/

int main (int argc, char** argv)
{
    assert(factorial(4) == 24);
    assert(factorial(0)==factorial(1));

    double e = exp(0.000001);
    printf("exp(1) à 10^-6 pres : %f\n\n",e);

    printf("(1.1)^10 = %f (double) \n", Puissance_db(1.1,10) );
    printf("(1.1)^10 = %f (float) \n",Puissance_fl(1.1,10));
    printf("(1.1)^10 = %f (développement limité) \n\n",DL(0.1));

    printf("(1.01)^100 = %f (double) \n", Puissance_db(1.01,100) );
    printf("(1.01)^100 = %f (float) \n",Puissance_fl(1.01,100));
    printf("(1.01)^100 = %f (développement limité) \n\n",DL(0.01));

    printf("(1.001)^1000 = %f (double) \n", Puissance_db(1.001,1000) );
    printf("(1.001)^1000 = %f (float) \n",Puissance_fl(1.001,1000));
    printf("(1.001)^1000 = %f (développement limité) \n\n",DL(0.001));

    printf("(1.00001)^100000 = %f (double) \n", Puissance_db(1.00001,100000) );
    printf("(1.00001)^100000 = %f (float) \n",Puissance_fl(1.00001,100000));
    printf("(1.00001)^100000 = %f (développement limité) \n\n",DL(0.00001));

    printf("X100 = %f (récursif); X100 = %f (itératif) \n",X_rec(100),X_ite(100));
}