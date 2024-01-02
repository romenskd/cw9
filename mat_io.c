#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"
#include <math.h>


Matrix *createMinor(Matrix *mat, int row, int col) {    
    //alokacja pamieci dla macierzy dopelniajacej 
    int minorRows = mat->r - 1;
    int minorCols = mat->c - 1;
    Matrix *minor = createMatrix(minorRows, minorCols);

    if (minor != NULL) {
        int minorRow = 0, minorCol = 0;
        for (int i = 0; i < mat->r; i++) {  // skopijowanie elemetow z oryginalnej macierzy 
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

// Rekurencyjna funkcja do obliczania wyznacznika 
double detRecursive(Matrix *mat) {
    if (mat->r == 1 && mat->c == 1) {   //jesli macierz 1*1 to zwracamy jedyny element 
        return mat->data[0][0];
    }

    if (mat->r == 2 && mat->c == 2) {   //jesli macierz 2*2 
        return mat->data[0][0] * mat->data[1][1] - mat->data[0][1] * mat->data[1][0];
    }

    double determinant = 0.0;
    int sign = 1;
    
    //iteracja przez pierwszy wiersz macierzy dla obliczenia wyznacznika 
    for (int j = 0; j < mat->c; j++) {
        Matrix *minor = createMinor(mat, 0, j);
        if (minor != NULL) {

            //uzywamy Laplaca do rekurencyjnego oblicznia wyznacznika
            determinant += sign * mat->data[0][j] * detRecursive(minor);    
            sign = -sign;                                                  
            freeMatrix(minor);
        }
    }

    return determinant;
}


double det(Matrix *mat) {
    //sprawdzamy czy macierz jest kwadratowa 
    if(mat->r != mat->c){          
        fprintf(stderr, "Macierz nie jest kwadratowa \n");
        exit(EXIT_FAILURE); 
    } else {
        return detRecursive(mat);
    }   
}



Matrix *readFromFile(char *fname) {
    int r, c, ir, ic;
    FILE *fin = fopen(fname, "r");
    Matrix *mat = NULL;

    if (fin != NULL) {
        fscanf(fin, "%d %d", &r, &c); //skanowanie pierwszych dwoch znakow (rozmiar macierzy )
        
        mat = createMatrix(r, c); //tworzenie macierzy

        if (mat != NULL) {      //wczytujemy info z pliku wejsciowego 
            for (ir = 0; ir < r; ir++)
                for (ic = 0; ic < c; ic++)
                    fscanf(fin, "%lf", &(mat->data[ir][ic]));

            fgetc(fin); //ignorujemy znak nowej linii 
        } else {
            fprintf(stderr, "Problem z utworzeniem macierzy z pliku: %s\n", fname);
        }

        fclose(fin);
    } else {
        fprintf(stderr, "Nie mogę otworzyć plik %s\n", fname);
    }

    return mat;
}

//funkcja wypisujaca macierz 
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

//funkcja do tworzenia macierzy 
Matrix *createMatrix(int r, int c) {
    int i;
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));  //przydzielenie pamieci 
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

//funckcja zwalniajaca pamiec 
void freeMatrix(Matrix *mat) {
    int i;
    for (i = 0; i < mat->r; i++)
        free(mat->data[i]);
    free(mat->data);
    free(mat);
}

