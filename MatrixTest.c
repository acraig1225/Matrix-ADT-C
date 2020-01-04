/********************************************************************************************************************
*	File: MatrixTest.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa2
*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
     
int main()
{
	int n = 1000000;
	int i;
	int j;
	int k = 1;
	Matrix A = newMatrix(1000000);
	Matrix B;
	Matrix C = newMatrix(5);
	Matrix D;
	Matrix E;
	Matrix F;
	Matrix G = newMatrix(5);
	Matrix H;
	Matrix I;

	//Store values in the corners and in the middle of A.
	changeEntry(A, 1, 1, -72384);
	changeEntry(A, 1, n, 934856);
	changeEntry(A, n, 1, 4343.46478);
	changeEntry(A, n, n, 0.123156);
	changeEntry(A, n/2, n/2, n/2);

	//Print the contents of A its size and the number of non-zero elements.
	fprintf(stdout, "A is a %d x %d Matrix and has %d non-zero entries:\n", size(A), size(A), NNZ(A));
	printMatrix(stdout, A);
	fprintf(stdout, "\n");

	//Copy A to B and see if they are equal.
	B = copy(A);
	printf("%s\n", equals(A, B)?"true":"false");

	//Remove an element from A and see if it is still equal to B.
	changeEntry(A, n/2, n/2, 0);
	printf("%s\n", equals(A, B)?"true":"false");

	//Fill C with values 1 - 25
	for(i = 1; i <= size(C); i++)
	{
		for(j = 1; j <= size(C); j++)
		{
			changeEntry(C, i, j, k);
			k++;
		}	
	}
	printMatrix(stdout, C);
	fprintf(stdout, "\n");

	//Take the transpose of C
	D = transpose(C);
	printMatrix(stdout, D);
	fprintf(stdout, "\n");

	//Take the transpose of D and see if equal to C
	E = transpose(D);
	printf("%s\n", equals(C,E)?"true":"false");

	//Multipy C by 2.5
	F = scalarMult(2.5, C);
	printMatrix(stdout, F);
	fprintf(stdout, "\n");

	//Fill G with values 26 - 50.
	k = 26;
	for(i = 1; i <= size(G); i++)
	{
		for(j = 1; j <= size(G); j++)
		{
			changeEntry(G, i, j, k);
			k++;
		}	
	}
	printMatrix(stdout, G);
	fprintf(stdout, "\n");

	//C + G
	H = sum(C, G);
	printMatrix(stdout, H);
	fprintf(stdout, "\n");
	freeMatrix(&H);

	//C + (G * -1)
	H = scalarMult(-1, G);
	I = sum(C, H);
	printMatrix(stdout, I);
	fprintf(stdout, "\n");
	freeMatrix(&H);

	//G - c
	H = diff(G, C);
	printMatrix(stdout, H);
	fprintf(stdout, "\n");
	freeMatrix(&H);

	//G * C
	H = product(G, C);
	printMatrix(stdout, H);
	fprintf(stdout, "\n");
	freeMatrix(&H);	

	//Make C into the zerio matrix.
	//Multiply G by C.
	//Check to see if H has any remaining entries afterards.
	makeZero(C);
	H = product(G, C);
	if(NNZ(H) != 0)
	{
		fprintf(stdout, "H is a %d x %d Matrix and has %d non-zero entries:\n", size(H), size(H), NNZ(H));
		printMatrix(stdout, H);
	}
	else
	{
		fprintf(stdout, "Matrix is empty\n");
	}
	
	fprintf(stdout, "\n");


	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);

	return(0);
}
