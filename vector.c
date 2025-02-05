//
// Created by jgreive on 20.12.2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

typedef struct vector_struct {
    unsigned short n;
    double *data;
} vector_struct;


vector createVector(unsigned short n) {
    vector v;
    v = (vector) calloc(1, sizeof(vector_struct) + n * sizeof(double));
    if(v) {
        v->n = n;
        v->data = (double *) (v + 1);
    }
    return v;
}

void rmVector(vector v) {
    if (v) {
        free(v);
    }
}

unsigned short size(vector v) {
    return v->n;
}

double* values(vector v) {
    return v->data;
}

double getValue(vector v, unsigned short j) {
    if( j >= v->n) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    return v->data[j];
}

void setValue(vector v, unsigned short j, double value) {
    if( j >= v->n) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    v->data[j] = value;
}

double vectorDotVector(vector a, vector b) {
    unsigned short i;
    double c = 0;

    if (a->n != b->n) {
        printf("Error: vector dimensions do not match\n");
        exit(-1);
    }

    for (i = 0; i < a->n;i++) {
        c += a->data[i] * b->data[i];
    }
    return c;
}

vector vectorPlusVector(vector a, vector b) {
    unsigned short i;
    vector c = createVector(a->n);

    if (a->n != b->n) {
        printf("Error: vector dimensions do not match\n");
        exit(-1);
    }

    for (i = 0; i < a->n; i++) {
        c->data[i] = a->data[i] + b->data[i];
    }
    return c;
}