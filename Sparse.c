/********************************************************************************************************************
*	File: Sparse.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa2
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Matrix.h"


int main(int argc, char* argv[])
{
	//Check for appropriate number of arguments. 
	if(argc != 3)
	{
		fprintf(stderr, "Sparse Error: incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	//Open up input and output files.
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	//Check to see if the files were successfully opened.
	if(in == NULL)
	{
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int n;
	int a;
	int b;
	int i;
	int row;
	int col;
	double value;

	//Find the first 3 values found in the input file and assign them to n, a, and b.
	//n = size of each matrix
	//a = number of non-zero elements in matrix A
	//b = number of non-zero elements in matrix B
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &a);
	fscanf(in, "%d", &b);

	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix C;
	Matrix D;
	Matrix E;
	Matrix F;
	Matrix G;
	Matrix H;
	Matrix I;
	Matrix J;

	//Each line will represent a particular entry in the Matrix.
	//Grab each row, column, and value from each line and enter them into matrix A until you've taken 'a' entries.
	//Repeat the process for Matrix B

	for(i = 0; i < a; i++)
	{
		fscanf(in, "%d", &row);
		fscanf(in, "%d", &col);
		fscanf(in, "%lf", &value);
		changeEntry(A, row, col, value);
	}

	for(i = 0; i < b; i++)
	{
		fscanf(in, "%d", &row);
		fscanf(in, "%d", &col);
		fscanf(in, "%lf", &value);
		changeEntry(B, row, col, value);
	}
	
	//A & NNZ(A)
	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);
	fprintf(out, "\n");

	//B & NNZ(B)
	fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);
	fprintf(out, "\n");

	//Scalar Mult
	C = scalarMult(1.5, A);
	fprintf(out, "(1.5) * A =\n");
	printMatrix(out, C);
	fprintf(out, "\n");

	//A+B
	D = sum(A, B);
	fprintf(out, "A + B =\n");
	printMatrix(out, D);
	fprintf(out, "\n");

	//A+A
	E = sum(A, A);
	fprintf(out, "A + A =\n");
	printMatrix(out, E);
	fprintf(out, "\n");

	//B-A
	F = diff(B, A);
	fprintf(out, "B - A =\n");
	printMatrix(out, F);
	fprintf(out, "\n");

	//A-A
	G = diff(A, A);
	fprintf(out, "A - A =\n");
	printMatrix(out, G);
	fprintf(out, "\n");

	//transpose(A)
	H = transpose(A);
	fprintf(out, "Transpose(A) =\n");
	printMatrix(out, H);
	fprintf(out, "\n");

	//A*B
	I = product(A, B);
	fprintf(out, "A * B =\n");
	printMatrix(out, I);
	fprintf(out, "\n");
	
	//B*B
	J = product(B, B);
	fprintf(out, "B * B =\n");
	printMatrix(out, J);
	fprintf(out, "\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);

	fclose(in);
	fclose(out);

	return(0);
}