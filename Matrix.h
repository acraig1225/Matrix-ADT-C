/*************************************************************************************************************************************
*	File: Matrix.h
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa2
**************************************************************************************************************************************/

#ifndef _MATRIX_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct MatrixObj* Matrix;

//Constructors-Destructors************************************************************************************************************
Matrix newMatrix(int n);								//Returns a reference to a new nXn Matrix object in the zero state.										
void freeMatrix(Matrix* pM);							//Frees heap memory associated with *pM, sets *pM to NULL.

//Access Functions********************************************************************************************************************
int size(Matrix M);										//Return the size of square Matrix M.
int NNZ(Matrix M);										//Return the number of non-zero elements in M.
int equals(Matrix A, Matrix B);							//Return true (1) if matrices A and B are equal, false (0) otherwise.

//Manipulation Procedures*************************************************************************************************************
void makeZero(Matrix M);								//Re-sets M to the zero Matrix.
void changeEntry(Matrix M, int i, int j, double x);		//Changes the ith row, jth column of M to the value x.
														//Preconditon: 1<=i<=size(M), 1<=j<=size(M)

//Matrix Arithmetic Operations********************************************************************************************************
Matrix copy(Matrix A);									//Returns a reference to a new Matrix object having the same entries as A.
Matrix transpose(Matrix A);								//Returns a reference to a new Matrix object representing the transpose of A.
Matrix scalarMult(double x, Matrix A);					//Returns a reference to a new Matrix object representing xA.
Matrix sum(Matrix A, Matrix B);							//Returns a reference to a new Matrix object representing A+B.
														//Precondition: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);						//Returns a reference to a new Matrix object representing A-B.
														//Precondition: size(A)==size(B)
Matrix product(Matrix A, Matrix B);						//Returns a reference to a new Matrix object representing AB
														//Precondition: size(A)==size(B)
void printMatrix(FILE* out, Matrix M);					//Prints a string representation of Matrix M to filestream out. Zero rows
														//are not printed. Each non-zero is represented as one line consisting
														//of the row number, followed by a colon, a space, then a space separated
														//list of pairs "(col, val)" giving the column numbers and non-zero values
														//in that row. The double val will be rounded to 1 decimal point.


#endif