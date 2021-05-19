#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

void matmul(matrix *result, matrix *x, matrix *y) {
	assert(x->shape[1] == y->shape[0]);
	assert(result->shape[0] == x->shape[0] && result->shape[1] == y->shape[1]);

	for (int i = 0; i < x->shape[0]; i++) {
		for (int j = 0; j < y->shape[1]; j++) {
			result->array[i][j] = 0;

			for (int a = 0; a < x->shape[1]; a++) {
				result->array[i][j] += x->array[i][a] * y->array[a][j];
			}
		}
	}
}

void element_wise(matrix *result, matrix *x, matrix *y, char operation) {

	assert(result->shape[0] == x->shape[0] && result->shape[1] == x->shape[1]);

	char broadcast;

	if (x->shape[0] == y->shape[0] && x->shape[1] == y->shape[1]) broadcast = 'n';
	else if (x->shape[0] == y->shape[0] && y->shape[1] == 1) broadcast = 'c';
	else if (x->shape[1] == y->shape[1] && y->shape[0] == 1) broadcast = 'r';
	else printf("ELEMENT WISE ERROR\n");

	for (int i = 0; i < x->shape[0]; i++) {
		for (int j = 0; j < x->shape[1]; j++) {
			switch (broadcast) {
			case 'n':
				switch (operation) {
				case '+': result->array[i][j] = x->array[i][j] + y->array[i][j]; break;
				case '*': result->array[i][j] = x->array[i][j] * y->array[i][j]; break;
				case '-': result->array[i][j] = x->array[i][j] - y->array[i][j]; break;
				}
				break;

			case 'c':
				switch (operation) {
				case '+': result->array[i][j] = x->array[i][j] + y->array[i][0]; break;
				case '*': result->array[i][j] = x->array[i][j] * y->array[i][0]; break;
				case '-': result->array[i][j] = x->array[i][j] - y->array[i][0]; break;
				}
				break;

			case 'r':
				switch (operation) {
				case '+': result->array[i][j] = x->array[i][j] + y->array[0][j]; break;
				case '*': result->array[i][j] = x->array[i][j] * y->array[0][j]; break;
				case '-': result->array[i][j] = x->array[i][j] - y->array[0][j]; break;
				}
				break;
			}
		}
	}
}


void print_matrix(matrix *mat) {
	printf("[");
	for (int i = 0; i < mat->shape[0]; i++) {
		printf("[");
		for (int j = 0; j < mat->shape[1]; j++) {
			printf("%lf, ", mat->array[i][j]);
		}
		printf("\b\b]\n");
	}
	printf("SHAPE: (%d, %d)\n", mat->shape[0], mat->shape[1]);
	printf("\n");
}

matrix *create_matrix_rand(const int h, const int w) {
	matrix *result = malloc(sizeof(matrix));
	assert(result != NULL);
	result->shape[0] = h;
	result->shape[1] = w;
	result->array = malloc(h * sizeof(double));
	for (int i = 0; i < h; i++) {
		result->array[i] = malloc(w * sizeof(double));
		for (int j = 0; j < w; j++) {
			result->array[i][j] = rand() % 10;
		}
	}
	return result;
}

matrix *create_matrix_zeros(const int h, const int w) {
	matrix *result = malloc(sizeof(matrix));
	assert(result != NULL);
	result->shape[0] = h;
	result->shape[1] = w;
	result->array = malloc(h * sizeof(double));
	for (int i = 0; i < h; i++) {
		result->array[i] = malloc(w * sizeof(double));
		for (int j = 0; j < w; j++) {
			result->array[i][j] = 0;
		}
	}
	return result;
}

matrix *create_weights(const int h, const int w) {
	matrix *weights = malloc(sizeof(matrix));
	assert(weights != NULL);
	weights->shape[0] = h; weights->shape[1] = w;

	weights->array = malloc(h * sizeof(double *));
	assert(weights->array != NULL);

	for (int i = 0; i < h; i++) {
		weights->array[i] = malloc(w * sizeof(double));
		assert(weights->array[i] != NULL);

		for (int j = 0; j < w; j++) {
			weights->array[i][j] = GaussianSample() * sqrt(2.0 / w);
		}
	}
	return weights;
}

void transpose(matrix *result, matrix *a) {
	assert(result->shape[0] == a->shape[1] && result->shape[1] == a->shape[0]);

	for (int i = 0; i < result->shape[0]; i++) {
		for (int j = 0; j < result->shape[1]; j++) {
			result->array[i][j] = a->array[j][i];
		}
	}

}

void scale(matrix *result, matrix *a, double factor) {
	assert(result->shape[0] == a->shape[0] && result->shape[1] == a->shape[1]);

	for (int i = 0; i < result->shape[0]; i++) {

		for (int j = 0; j < result->shape[1]; j++) {
			result->array[i][j] = factor * (a->array[i][j]);
		}
	}
}

void free_matrix(matrix *a) {
	if (a != NULL) {
		//printf("%d\t%d\n",a->shape[0], a->shape[1]);
		for (int i = 0; i < a->shape[0]; i++) {
			if (a->array[i] != NULL) free(a->array[i]);
		}
		if (a->array != NULL) free(a->array);
		if (a != NULL) free(a);
	}
}

void cpy_matrix(matrix *result, matrix *a) {
	assert(result->shape[0] == a->shape[0] && result->shape[1] == a->shape[1]);

	for (int i = 0; i < a->shape[0]; i++) {
		for (int j = 0; j < a->shape[1]; j++) {
			result->array[i][j] = a->array[i][j];
		}
	}
}
