#ifndef _MAT_IO_H
#define _MAT_IO_H

typedef struct _Matrix {
    int r, c;
    double **data;
} Matrix;

Matrix *readVectorFromFile(char *fname); 
Matrix *readSquareMatrixFromFile(char *fname) ; 


void printToScreen(Matrix *mat);
void printToScreenB(Matrix *mat); 
Matrix *createMatrix(int r, int c);
void freeMatrix(Matrix *mat);



double det(Matrix *mat);
double detRecursive(Matrix *mat); 
Matrix *createMinor(Matrix *mat, int row, int col); 


#endif
