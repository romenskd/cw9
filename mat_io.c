#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"
#include <math.h>

double det(Matrix *mat);


Matrix *createMinor(Matrix *mat, int row, int col) {
    int minorRows = mat->r - 1;
    int minorCols = mat->c - 1;
    Matrix *minor = createMatrix(minorRows, minorCols);

    if (minor != NULL) {
        int minorRow = 0, minorCol = 0;
        for (int i = 0; i < mat->r; i++) {
            if (i == row) continue;

            minorCol = 0;
            for (int j = 0; j < mat->c; j++) {
                if (j == col) continue;

                minor->data[minorRow][minorCol] = mat->data[i][j];
                minorCol++;
            }

            minorRow++;
        }
    }

    return minor;
}

double detRecursive(Matrix *mat) {
    if (mat->r == 1 && mat->c == 1) {
        return mat->data[0][0];
    }

    if (mat->r == 2 && mat->c == 2) {
        return mat->data[0][0] * mat->data[1][1] - mat->data[0][1] * mat->data[1][0];
    }

    double determinant = 0.0;
    int sign = 1;

    for (int j = 0; j < mat->c; j++) {
        Matrix *minor = createMinor(mat, 0, j);
        if (minor != NULL) {
            determinant += sign * mat->data[0][j] * detRecursive(minor);
            sign = -sign;
            freeMatrix(minor);
        }
    }

    return determinant;
}

int isSingular(Matrix *mat) {
    if (mat->r != mat->c) {
        fprintf(stderr, "Błąd! Macierz nie jest kwadratowa.\n");
        return 1; 
    }
    double determinant = det(mat);
    if (determinant == 0.0) {
        fprintf(stderr, "Błąd! Macierz jest osobliwa.\n");
        return 1; 
    }

    return 0; 
}

double det(Matrix *mat) {
    if (mat->r != mat->c) {
        fprintf(stderr, "Błąd! Macierz nie jest kwadratowa.\n");
        return NAN; 
    }

    return detRecursive(mat);
}



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

