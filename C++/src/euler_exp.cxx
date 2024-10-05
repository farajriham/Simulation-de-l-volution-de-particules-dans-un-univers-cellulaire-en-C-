/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <cstdlib>
#include <iostream>

double* euler_exp(int N_h,double u_init,double inf_vect,double sup_vect);
double exp_calc(double x_prev,double h,double u_prev);
double phi(double x,double u_x);


int main()
{
    double* u;
    double u_init= 1;
    double inf_vect=0;
    double sup_vect=15;
    int N_h;
    std::cout << "Entrez le nombre de points : ";
    std::cin >> N_h;
    u= euler_exp(N_h,u_init,inf_vect,sup_vect);
    int j;
    for(j=0;j<=N_h;j++)
        std::cout << u[j] << std::endl;

    return 0;
}

double phi(double x,double u_x){
    return (2*x*u_x);
}

double exp_calc(double x_prev,double h,double u_prev){
    return (h*phi(x_prev,u_prev)+u_prev);
}


double* euler_exp(int N_h,double u_init,double inf_vect,double sup_vect){
    double* absc;
    double h= (sup_vect-inf_vect)/N_h;
    absc=(double*)calloc(N_h+1,sizeof(double*));
    int i;
    for(i=0;i<=N_h;i++)
        absc[i]=inf_vect+i*h;

    double* u;
    u=(double *)calloc(N_h+1,sizeof(double));
    u[0]=u_init;
    int j;
    for(j=1;j<=N_h;j++)
        u[j]=h*phi(absc[j-1],u[j-1])+u[j-1];
    return (u);
}
