#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int n;
double A(int i, double **mass){
    return mass[i][i - 1];
}
double B(int i, double **mass){
    return mass[i][i + 1];
}
double C(int i, double **mass){
    return -mass[i][i];
}
double alpha(int i, double **mass){ 
    if (i == 1)
        return -mass[0][1];
    else
        return B(i - 1, mass)/(C(i - 1, mass) - A(i - 1, mass) * alpha(i - 1, mass));
}
double f(int i);
double beta(int i, double **mass){ 
    if (i == 1)
        return f(0);
    else  
        return (-f(i - 1) + A(i - 1, mass) * beta(i - 1, mass)) / (C(i - 1, mass) - A(i - 1, mass) * alpha(i - 1, mass));
}
double f(int i)
{
    if (i == n)
        return (double)1/12;
    else
        return ((double)i/n) * ((double)i/n) * ((double)1/n) * ((double)1/n);
}
double x(int i, double **mass, double* alpha_m, double* beta_m){
    if (i == n)
        return (-mass[n][n - 1] * beta_m[n] + f(n)) / (1 + mass[n][n - 1] * alpha_m[n]);
    else
        return (alpha_m[i + 1] * x(i + 1, mass, alpha_m, beta_m) + beta_m[i + 1]);
}
void create_matrix(int n, double **mass)
{
    mass[0][0] = 1;
    mass[n][n] = 1;
    for (int i = 1; i < n + 1; i++)
        mass[0][i] = 0;
    for (int i = 0; i < n; i++)
        mass[n][i] = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
            mass[i][j] = 0;
        mass[i][i] = 2;
        mass[i][i-1] = -1;
        mass[i][i+1] = -1;
    }
}
double norm(double *x1, double *x2, int n)
{
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += x1[i] * x2[i];
    return sqrt(ans);
}
int main()
{
    printf("Введите n: ");
    scanf("%d", &n);
    double **mass = malloc(sizeof(double*) * (n+1));
    for (int i = 0; i < n+1; i++)
        mass[i] = malloc(sizeof(double) * (n+1));
    create_matrix(n, mass);
    double *alpha_m = malloc(sizeof(double) * (n+1));
    double *beta_m = malloc(sizeof(double) * (n+1));
    for (int i = 1; i < n+1; i++)
    {
        alpha_m[i] = alpha(i, mass);    
        beta_m[i] = beta(i, mass);
    }
    double *value_x = malloc(sizeof(double) * (n+1 + 1));
    for (int i = 0; i < n+1; i++)
        value_x[i] = x(i, mass, alpha_m, beta_m);

    FILE* python_file = fopen("python_file.txt2", "w+");
    fprintf(python_file, "%d", n + 1);
    fprintf(python_file, "%c", '\n');
    for (int i = 0; i < n + 1; i++)
    {
        fprintf(python_file, "%f", value_x[i]);
        if (i != n)
            fprintf(python_file, "%c", '\n');
    }
    fclose(python_file);

    printf("\nрешения:\n\n");  

    printf("x0 = %f\n", value_x[0]);
    for (int i = 1; i < n/4 +1; i++)
        printf("x%d = %f\tx%d = %f\tx%d = %f\tx%d = %f\n", i, value_x[i], i + n/4, value_x[i + n/4], i + n/2, value_x[i + n/2], i + 3*n/4, value_x[i+3*n/4]);
    printf("\n");

    double *diff = malloc(sizeof(double) * (n+1));
    for (int i = 0; i < n+1; i++)
    {
        double t = 0;
        for (int j = 0; j < n+1; j++)
            t += mass[i][j] * value_x[j];

        diff[i] = t - f(i);
    }
    printf("\n||r|| = ||Ab - f|| = %f\n\n", norm(diff, diff, n+1));
    for (int i = 0; i < n+1; i++)
        free(mass[i]);
    free(mass); free(value_x); free(alpha_m); free(beta_m); free(diff);
}