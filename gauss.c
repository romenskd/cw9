#include "gauss.h"
#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

int eliminate(Matrix *mat, Matrix *b) {
    int i, j, k;
    int rows = mat->r;
    int cols = mat->c;

    for (k = 0; k < rows - 1; k++) {
        if (mat->data[k][k] == 0.0) {
            fprintf(stderr, "\nElement diagonalny o indeksach %dx%d jest równy 0.\n\n", k+1, k+1);

            
            int swap_row = -1;
            for (i = k + 1; i < rows; i++) {
                if (mat->data[i][k] != 0.0) {
                    swap_row = i;
                    break;
                }
            }

            if (swap_row == -1) {
                fprintf(stderr, "Błąd! Nie można znaleźć wiersza do wymiany.\n");
                return 1;
            }

            
            for (j = 0; j < cols; j++) {
                double temp = mat->data[k][j];
                mat->data[k][j] = mat->data[swap_row][j];
                mat->data[swap_row][j] = temp;
            }

            
            double temp_b = b->data[k][0];
            b->data[k][0] = b->data[swap_row][0];
            b->data[swap_row][0] = temp_b;
        }

        for (i = k + 1; i < rows; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];

            for (j = k; j < cols; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0;
}

