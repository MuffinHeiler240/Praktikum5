//
// Created by jgreive on 20.12.2024.
//

#include "matrix.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct matrix_struct {
    unsigned short n;
    unsigned short m;
    double **data;
} matrix_struct;


matrix createMatrix(unsigned short n, unsigned short m) {
    unsigned short i;
    size_t total_size = sizeof(matrix_struct) + sizeof(double *) * n + sizeof(double) * n * m;
    matrix_struct *matrix = (matrix_struct *)calloc(1, total_size);

    matrix->n = n;
    matrix->m = m;

    double **row_ptrs = (double **)(matrix + 1);
    double *data_start = (double *)(row_ptrs + n);

    for (i = 0; i < n; i++) {
        row_ptrs[i] = data_start + i * m;
    }

    matrix->data = row_ptrs;
    return matrix;
}

void rmMatrix(matrix a) {
    if (a) {
        free(a);
    }
}


unsigned short rows(matrix a) {
    return a->n;
}

unsigned short cols(matrix a) {
    return a->m;
}

double** data(matrix a) {
    return a->data;
}

double getEntry(matrix a, unsigned short r, unsigned short c) {
    if (r >= a->n || c >= a->m) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    return a->data[r][c];
}

void setEntry(matrix a, unsigned short r, unsigned short c, double v) {
    if (r >= a->n || c >= a->m) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    a->data[r][c] = v;
}


matrix matrixDotMatrix(matrix a, matrix b) {
    unsigned short i,j,k;
    register double temp = 0;
    if (a->m != b->n) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    matrix c = createMatrix(a->n, b->m);
    for (i = 0; i < a->n; i++) {
        for ( j = 0; j < b->m; j++) {
            for ( k = 0; k < a->m; k++) {
                 temp += a->data[i][k] * b->data[k][j];
            }
            c->data[i][j] = temp;
            temp = 0;
        }
    }
    return c;
}

matrix matrixPlusMatrix(matrix a, matrix b) {
    unsigned short i,j;
    if (a->n != b->n || a->m != b->m) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    matrix c = createMatrix(a->n, a->m);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->m; j++) {
            c->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return c;
}

vector matrixDotVector(matrix a, vector x) {
    unsigned short i,j;
    register double temp = 0;
    if (a->m != size(x)) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    vector y = createVector(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->m; j++) {
            temp += a->data[i][j] * getValue(x,j);
        }
        setValue(y,i,temp);
        temp = 0;
    }
    return y;
}

