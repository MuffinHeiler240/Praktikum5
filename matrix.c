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
    matrix a = (matrix) malloc(sizeof(matrix_struct));
    a->n = n;
    a->m = m;
    a->data = (double **) calloc(n, sizeof(double *));
    for (i = 0; i < n; i++) {
        a->data[i] = (double *) calloc(m, sizeof(double));
    }
    return a;
}

void rmMatrix(matrix a) {
    unsigned short i;
    for ( i = 0; i < a->n; i++) {
        free(a->data[i]);
    }
    free(a->data);
    free(a);
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
    if (a->m != b->n) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    matrix c = createMatrix(a->n, b->m);
    for (i = 0; i < a->n; i++) {
        for ( j = 0; j < b->m; j++) {
            for ( k = 0; k < a->m; k++) {
                c->data[i][j] += a->data[i][k] * b->data[k][j];
            }
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

vector createVectorWithOne(unsigned short n) {
    vector v = createVector(n);
    unsigned short i;
    for (i = 0; i < n; i++) {
        setValue(v,i,1);
    }
    return v;
}

vector matrixDotVector(matrix a, vector x) {
    unsigned short i,j;
    double temp = 0;
    if (a->m != size(x)) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    vector y = createVectorWithOne(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->m; j++) {
            temp += a->data[i][j] * getValue(x,j);
        }
        setValue(y,i,temp);
        temp = 0;
    }
    return y;
}

