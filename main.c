#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int res;
    Matrix *A = readFromFile(argc > 1 ? argv[1] : "A.txt");
    Matrix *b = readFromFile(argc > 2 ? argv[2] : "b.txt");
    Matrix *x;

    if (A == NULL || b == NULL) {
        fprintf(stderr, "Błąd! Nie udało się wczytać macierzy A lub wektora b.\n");
        return -1;
    }

    printf("Macierz A:\n");
    printToScreen(A);

    printf("Wektor b:\n");
    printToScreenB(b);

        res = eliminate(A, b);
        x = createMatrix(A->c, 1);

        if (x != NULL) {
            res = backsubst(x, A, b);

            printf("Wektor wynikowy x:\n");
            printToScreenB(x);

            freeMatrix(x);
        } else {
            fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        }

    freeMatrix(A);
    freeMatrix(b);

    return 0;
}
