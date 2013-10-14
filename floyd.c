#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void adjacency_matrix(int a[][1000],int n) {
  int i,j;
  for(i = 0; i < n; i++)
    for(j = 0; j <= n; j++)
      a[i][j] = 0;

  for(i = 1; i < n; i++)
    for(j = 0; j < i; j++) {
      a[i][j] = rand() % 10;
      a[j][i] = 99;
    }
}

int min(int a,int b) {
  return a < b ? a : b;
}

void floyds(int a[][1000],int n) {
  int i,j,k;
  for(k = 0;k < n ; k++) {
    #pragma omp parallel for private(i, j)
    for(i = 0;i < n; i++) {
      for(j = 0;j < n ; j++) {
        #pragma omp critical
        {
          a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        }
      }
    }
  }
}

void execute_floyd_algorithm_and_time_it(int a[][1000], int n) {
  clock_t begin, end;
  double cpu_time = 0;

  begin = clock();
  floyds(a,n);
  end = clock();
  cpu_time = (double)(end - begin) / CLOCKS_PER_SEC;

  FILE *fp = fopen("./perf_result.dot","a");
  fprintf(fp, "%f\n", cpu_time);
  fclose(fp);
}

int main(int argc, char* argv[]) {
  int a[1000][1000],n,i,j;
  FILE *fp = fopen("./floyds.dot","w");

  n = atoi(argv[1]);
  adjacency_matrix(a,n);
  execute_floyd_algorithm_and_time_it(a, n);

  for(i = 0;i < n; i++) {
    for(j = 0;j < n; j++)
      fprintf(fp, "%d ", a[i][j]);
    fprintf(fp, "\n");
  }

  fclose(fp);

  return 0;
}
