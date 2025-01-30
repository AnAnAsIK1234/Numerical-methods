#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 11


long double deg(long double x, int n)
{
    long double ans = 1;
    for (int i = 0; i < n; i++)
        ans *= x;
    return ans;
}

long double norm(long double *x1, long double *x2)
{
    long double ans = 0;
    for (int i = 0; i < N; i++)
        ans += x1[i] * x2[i];
    return sqrtl(ans);
}

void Gauss(long double **list) 
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int k = i + 1; k < N; k++) 
        {
            long double h = list[k][i] / list[i][i];
            for (int j = 0; j <= N; j++)
                list[k][j] = list[k][j] - h * list[i][j];
        }
    }
}

void back(long double **list, long double **A) 
{
    long double x[N];
    for (int i = N - 1; i >= 0; i--) 
    {
        x[i] = list[i][N] / list[i][i];
        for (int j = i - 1; j >= 0; j--)
            list[j][N] -= list[j][i] * x[i];  
    }

    FILE* f = fopen("python_file.txt1", "w+");
    fprintf(f, "%d", N);
    fprintf(f, "%c", '\n');
    for (int i = 0; i < N; i++)
    {
        fprintf(f, "%Lf", x[i]);
        if (i != N - 1)
            fprintf(f, "%c", '\n');
    }
    fclose(f);

    printf("\nРешение:\n");
    for (int i = 0; i < N; i++)
        printf("x%d = %Lf\n", i+1, x[i]);

    printf("\n");
    long double *Ab = malloc(sizeof(long double) * N);
    for (int i = 0; i < N; i++)
    {
        Ab[i] = 0;
        for (int j = 0; j < N; j++)
            Ab[i] += A[i][j] * x[j];
    }
    long double *ans_norm = malloc(sizeof(long double) * N);
    for (int i = 0; i < N; i++)
        ans_norm[i] = Ab[i] - A[i][N];  
    printf("\n||r|| = ||Ab - f|| = %Lf\n", norm(ans_norm, ans_norm));
    free(ans_norm);free(Ab);
}


int main() 
{
    long double **list = malloc(sizeof(long double*) * N);
    long double **A = malloc(sizeof(long double*) * N);
    for (int i = 0; i < N; i++)
    {
        list[i] = malloc(sizeof(long double) * (N+1));
        A[i] = malloc(sizeof(long double) * (N+1));
    }
    for (int l = 0; l < N; l++)
    {
        for (int k = 0; k < N; k++)
        {
            list[l][k] = 0;
            for (int m = 0; m <= 50; m++)
                list[l][k] += deg((double)m/10, l + k);
            A[l][k] = list[l][k];
        }
    }
    for (int l = 0; l < N; l++)
    {
        list[l][N] = 0;
        for (int m = 0; m <= 50; m++)
            list[l][N] += deg((long double)m/10, l) * ( (long double)m/10 + (long double)m/20 * sin(4 * ((long double)m/10)) );
        A[l][N] = list[l][N];
    }
    Gauss(list);
    back(list, A);

    for (int i = 0; i < N; i++)
    {free(list[i]); free(A[i]);}
    free(list); free(A);
}