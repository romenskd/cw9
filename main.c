#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int res;
    Matrix *A = readFromFile(argc > 1 ? argv[1] : "A.txt");   //czytamy plik jako 1 argument - macierz 
    Matrix *b = readFromFile(argc > 2 ? argv[2] : "b.txt");   //czyamy plik jako 2 argument - wektor 
    Matrix *x;

    if (A == NULL || b == NULL) {   //ubezpieczenie 
        fprintf(stderr, "Błąd! Nie udało się wczytać macierzy A lub wektora b.\n");
        return -1;
    }

    printf("Macierz A:\n");
    printToScreen(A);

    printf("Wektor b:\n");
    printToScreen(b);
    
    
    double determinant = det(A);

    //w przypadku gdy macierz osobliwa 
    if (determinant == 0.0) {     
        fprintf(stderr, "Błąd! Macierz jest osobliwa. Nie można zastosować eliminacji Gaussa.\n");
        freeMatrix(A);
        freeMatrix(b);
        return -1;
    }
     
    
    res = eliminate(A, b);    //liczymy wektor wynikowy 
    x = createMatrix(A->c, 1);  //tworzymy wektor wynikowy 
 
    if (x != NULL) {     //ubezpieczenie 
        
        res = backsubst(x, A, b);
        printf("Wektor wynikowy x:\n");
        printToScreen(x);

        freeMatrix(x);
    } else {
        fprintf(stderr, "Błąd! Nie udalo sie utworzyć wektora wynikowego x.\n");
    }

    freeMatrix(A);
    freeMatrix(b);

    return 0;
}
