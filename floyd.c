#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_OF_PROCESSORS 4

void generate_adjacency_matrix(int matrix[][1000],int matrix_size) {
  int i,j;
  for(i = 0; i < matrix_size; i++)
    for(j = 0; j < matrix_size; j++)
      matrix[i][j] = 0;

  for(i = 1; i < matrix_size; i++)
    for(j = 0; j < i; j++) {
      matrix[i][j] = rand() % 10;
      matrix[j][i] = 99;
    }
}

int min(int a,int b) {
  return a < b ? a : b;
}

void improved_floyd(int matrix[][1000], int matrix_size, int step)  {
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

    for (i = start; i <= end; i++)
      for (j = 0; j < matrix_size; j++)
        matrix[i][j] = min(matrix[i][j], matrix[i][step] + matrix[step][j]);
  }
}

void compute_shortest_path(int matrix[][1000], int matrix_size) {
  int step;
  for (step = 0; step < matrix_size; step++)
    improved_floyd(matrix, matrix_size, step);
}

void execute_floyd_algorithm_and_time_it(int matrix[][1000], int matrix_size) {
  clock_t begin, end;
  double cpu_time = 0;

  begin = clock();
  compute_shortest_path(matrix,matrix_size);
  end = clock();
  cpu_time = (double)(end - begin) / CLOCKS_PER_SEC;
  cpu_time = cpu_time / NUM_OF_PROCESSORS;

  FILE *fp = fopen("./perf_result","a");
  fprintf(fp, "%d --> %f\n", matrix_size, cpu_time);
  fclose(fp);
}

void print_matrix_to_file(int matrix[][1000], int matrix_size) {
  int i, j;
  FILE *fp = fopen("./floyds.dot","w");
  for(i = 0;i < matrix_size; i++) {
    for(j = 0;j < matrix_size; j++)
      fprintf(fp, "%d ", matrix[i][j]);
    fprintf(fp, "\n");
  }

  fclose(fp);
}

int main(int argc, char* argv[]) {
  int matrix[1000][1000], matrix_size;

  matrix_size = atoi(argv[1]);
  generate_adjacency_matrix(matrix, matrix_size);
  execute_floyd_algorithm_and_time_it(matrix, matrix_size);
  print_matrix_to_file(matrix, matrix_size);

  return 0;
}
