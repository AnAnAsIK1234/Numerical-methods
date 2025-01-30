#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 100
void Gauss(double **list, int main_elem)
{
    int t;
    if (main_elem < n)
    {

//                       1 шаг  
        if(list[main_elem][main_elem] == 0)
        {
            for (int p = main_elem + 1; p < n; p++)
                if (list[p][main_elem] != 0)
                {
                    for (int i = main_elem; i < n + 1; i++)
                    {
                        t = list[p][i];
                        list[p][i] = list[main_elem][i];
                        list[main_elem][i] = t;
                    }
                }
        }

//                       2 шаг
        long double h = list[main_elem][main_elem];
        if (h == 0)
        {
            printf("матрица вырождена!\n");
            exit(1);
        }
        for (int j = n; j >= main_elem; j--)
            list[main_elem][j] /= h;

//                       3 шаг

        for (int i = main_elem + 1; i < n; i++)
            for (int j = n; j >= main_elem; j--)
                list[i][j] -= list[main_elem][j] * list[i][main_elem];
//                       4 шаг
        Gauss(list, main_elem + 1);
    }
}
void back(double **list, double *ans_list)
{
    int h = n - 1;
    while (h >= 0)
    {
        ans_list[h] = list[h][n];
        for (int i = n - 1; i > h; i--)
            ans_list[h] -= list[h][i]*ans_list[i];
        h--;
    }
}
void create_matrix(double **mass)
{
    mass[0][0] = 1;
    mass[n - 1][n - 1] = 1;
    for (int i = 1; i < n; i++)
        mass[0][i] = 0;
    for (int i = 0; i < n - 1; i++)
        mass[n - 1][i] = 0;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
            mass[i][j] = 0;
        mass[i][i] = 2;
        mass[i][i-1] = -1;
        mass[i][i+1] = -1;
    }
}
double f(int i)
{
    if (i == (n - 1))
        return (double)1/12;
    else
        return ((double)i/(n - 1)) * ((double)i/(n - 1)) * ((double)1/(n - 1)) * ((double)1/(n - 1));
}
double norm(double *x1, double *x2)
{
    double ans = 0;
    for (int i = 0; i < n + 1; i++)
        ans += x1[i] * x2[i];
    return sqrt(ans);
}
int main()
{

    double **list = malloc(n * sizeof(double*));
    double **A = malloc(n * sizeof(double*));
    double *save_f = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        list[i] = malloc((n + 1) * sizeof(double*));
        A[i] = malloc((n + 1) * sizeof(double*));
    }
        
    create_matrix(list);
    create_matrix(A);
    for (int i = 0; i < n; i++)
    {
        list[i][n] = f(i);
        save_f[i] = list[i][n];
    }
    double* ans_list = malloc(n * sizeof(double));
    Gauss(list, 0);
    back(list, ans_list);


    double Ab[n];
    for (int i = 0; i < n; i++)
    {
        Ab[i] = 0;
        for (int j = 0; j < n; j++)
            Ab[i] += A[i][j] * ans_list[j];
    }
    double ans_norm[n];
    for (int i = 0; i < n; i++)
        ans_norm[i] = Ab[i] - save_f[i];  
    printf("\nx0 = %f\n", ans_list[0]);
    for (int i = 1; i < n/4 +1; i++)
        printf("x%d = %f\tx%d = %f\tx%d = %f\tx%d = %f\n", i, ans_list[i], i + n/4, ans_list[i + n/4], i + n/2, ans_list[i + n/2], i + 3*n/4, ans_list[i+3*n/4]);
    printf("\n||r|| = ||Ab - f|| = %f\n\n", norm(ans_norm, ans_norm));
    
    for (int i = 0; i < n; i++)
    {
        free(list[i]);
        free(A[i]);
    }
        
    free(list);free(ans_list);free(A);free(save_f);
}
