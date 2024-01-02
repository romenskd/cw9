#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *readSquareMatrixFromFile(char *fname) {
    int n, ir, ic;
    FILE *fin = fopen(fname, "r");
    Matrix *mat = NULL;

    if (fin != NULL) {
        fscanf(fin, "%d", &n);
        
        mat = createMatrix(n, n);

        if (mat != NULL) {
            for (ir = 0; ir < n; ir++)
                for (ic = 0; ic < n; ic++)
                    fscanf(fin, "%lf", &(mat->data[ir][ic]));
        } else {
            fprintf(stderr, "Problem creating a square matrix of size %d for data from file: %s\n", n, fname);
        }

        fclose(fin);
    } else {
        fprintf(stderr, "Cannot open the file named: %s\n", fname);
    }

    return mat;
}

Matrix *readVectorFromFile(char *fname) {
    int n, ir;
    FILE *fin = fopen(fname, "r");
    Matrix *vec = NULL;

    if (fin != NULL) {
        fscanf(fin, "%d", &n);
        vec = createMatrix(n, 1);

        if (vec != NULL) {
            for (ir = 0; ir < n; ir++)
                fscanf(fin, "%lf", &(vec->data[ir][0]));
        } else {
            fprintf(stderr, "Problem creating a vector of size %d for data from file: %s\n", n, fname);
        }

        fclose(fin);
    } else {
        fprintf(stderr, "Cannot open the file named: %s\n", fname);
    }

    return vec;
}

void printToScreen(Matrix *mat) {
    int i, j;
    printf("[ \n");
    for (i = 0; i < mat->r; i++) {
        printf("  ");
        for (j = 0; j < mat->c; j++) {
            printf("%f ", mat->data[i][j]);
        }
        printf("; \n");
    }
    printf("]\n");
}

void printToScreenB(Matrix *mat) {
    int i, j;
    printf("[ \n");
    for (i = 0; i < mat->r; i++) {
        printf("  ");
        printf("%f ", mat->data[i][0]);
        printf("; \n");
    }
    printf("]\n");
}

Matrix *createMatrix(int r, int c) {
    int i;
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    if (mat != NULL) {
        mat->r = r;
        mat->c = c;
        mat->data = (double **)malloc(sizeof(double *) * r);
        for (i = 0; i < r; i++) {
            mat->data[i] = (double *)malloc(sizeof(double) * c);
        }
    }

    return mat;
}

void freeMatrix(Matrix *mat) {
    int i;
    for (i = 0; i < mat->r; i++)
        free(mat->data[i]);
    free(mat->data);
    free(mat);
}

