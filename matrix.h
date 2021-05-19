#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct matrix {
	unsigned int shape[2];
	double **array;
} matrix;

void print_matrix(matrix *mat);
matrix *create_matrix_rand(const int h, const int w);
matrix *create_matrix_zeros(const int h, const int w);
matrix *create_weights(const int h, const int w);
void cpy_matrix(matrix *result, matrix *a);
void matmul(matrix *result, matrix *x, matrix *y);
void element_wise(matrix *result, matrix *x, matrix *y, char operation);
void transpose(matrix *result, matrix *a);
void scale(matrix *result, matrix *a, double factor);
void free_matrix(matrix *a);

#endif
