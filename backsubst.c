#include "backsubst.h"
#include "mat_io.h"
#include <stdio.h>

int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    int i, j;
    int rows = mat->r;
    int cols = mat->c;

    for (i = rows - 1; i >= 0; i--) {
        x->data[i][0] = b->data[i][0];

        for (j = i + 1; j < cols; j++) {
            x->data[i][0] -= mat->data[i][j] * x->data[j][0];
        }

        if (mat->data[i][i] == 0.0) {
            fprintf(stderr, "Błąd! Dzielenie na zero. \n");
            return 1; 
        }

        x->data[i][0] /= mat->data[i][i];
    }

    return 0;
}
