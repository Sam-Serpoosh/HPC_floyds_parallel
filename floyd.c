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

void new_floyds(int matrix[][1000], int matrix_size, int step)  {
  int i, j;
  #pragma omp parallel default(none) shared(matrix, matrix_size, step) private(i, j)
  {
    int num_of_threads = omp_get_num_threads();
    int thread_id = omp_get_thread_num();
    int block_size = matrix_size / num_of_threads;
    int start = thread_id * block_size;
    int end = start + block_size - 1;

    if (thread_id == num_of_threads - 1)
      end = matrix_size - 1;
    
    for (i = start; i <= end; i++) {
      for (j = 0; j < matrix_size; j++) {
        matrix[i][j] = min(matrix[i][j], matrix[i][step] + matrix[step][j]);
      }
    }
  }
}

void new_floyds_caller(int matrix[][1000], int matrix_size) {
  int k;
  for (k = 0; k < matrix_size; k++)
    new_floyds(matrix, matrix_size, k);
}

void floyds(int a[][1000],int n) {
  int i,j,k;
  for(k = 0;k < n ; k++) {
    #pragma omp parallel default(none) shared(a, n, k) private(i, j)
    {
      for(i = 0;i < n; i++) {
        for(j = 0;j < n ; j++) {
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
  new_floyds_caller(a,n);
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
