/********************************************************************************************************************
*	File: Matrix.c
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa2
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

//Entry Implementation************************************************************************************************************
typedef struct EntryObj
{
	int column;
	double value;
} EntryObj;

typedef struct EntryObj* Entry;


Entry newEntry(int c, double v)
{
	Entry E = malloc(sizeof(EntryObj));
	E->column = c;
	E->value = v;
	return (E);
}

void freeEntry(Entry* pE)
{
	if(*pE != NULL && pE != NULL)
	{
		free(*pE);
		*pE = NULL;
	}
}

//Helper Functions************************************************************************************************************
//Description: Computes the vector dot product of two matrix rows represented by Lists P and Q.
double vectorDot(List P, List Q)
{
	double result = 0;
	Entry E = NULL;
	Entry F = NULL;
	moveFront(P);
	moveFront(Q);

	while( (index(P) != -1) && (index(Q) != -1) )
	{
		E = (Entry)get(P);
		F = (Entry)get(Q);
		if(E->column == F->column)
		{
			result += (E->value * F->value);
			moveNext(P);
			moveNext(Q);
		}
		else if(E->column < F->column)
		{
			moveNext(P);
		}
		else
		{
			moveNext(Q);
		}
	}
	return result;
}

//Description: Computes the vector sum of two matrix rows represented by Lists P and Q.
List vectorSum(List P, List Q)
{
	List R = newList();
	Entry E = NULL;
	Entry pE;
	Entry qE;
	double result;
	moveFront(P);
	moveFront(Q);
	
	while( (index(P) != -1) && (index(Q) != -1) )		//traverse each list comparing values until you reach the end of one
	{
		pE = (Entry)get(P);
		qE = (Entry)get(Q);

		if(pE->column == qE->column)
		{
			result = pE->value + qE->value;
			if(result != 0)
			{
				E = newEntry(pE->column, result);
				append(R, E);				
			}
			moveNext(P);
			moveNext(Q);
		}
		else if(pE->column < qE->column)
		{
			E = newEntry(pE->column, pE->value);
			append(R, E);
			moveNext(P);
		}
		else
		{
			E = newEntry(qE->column, qE->value);
			append(R, E);
			moveNext(Q);
		}
	}


	if(index(P) != -1)			//catch any remaining values in P and Q
	{
		while(index(P) != -1)
		{
			pE = (Entry)get(P);
			E = newEntry(pE->column, pE->value);
			append(R, E);
			moveNext(P);
		}
	}
	else if(index(Q) != -1)
	{
		while(index(Q) != -1)
		{
			qE = (Entry)get(Q);
			E = newEntry(qE->column, qE->value);
			append(R, E);
			moveNext(Q);
		}
	}
	
	return (R);
}

//Description: Computes the vector difference of two matrix rows represented by Lists P and Q.
List vectorDiff(List P, List Q)
{
	List R = newList();
	Entry E = NULL;
	Entry pE;
	Entry qE;
	moveFront(P);
	moveFront(Q);

	while( (index(P) != -1) && (index(Q) != -1) )		//traverse each list comparing values until you reach the end of one
	{
		pE = (Entry)get(P);
		qE = (Entry)get(Q);

		if(pE->column == qE->column)
		{
			if(pE->value - qE->value != 0)
			{
				E = newEntry(pE->column, (pE->value - qE->value));
				append(R, E);
			}
			moveNext(P);
			moveNext(Q);
		}
		else if(pE->column < qE->column)
		{
			E = newEntry(pE->column, pE->value);
			append(R, E);
			moveNext(P);
		}
		else
		{
			E = newEntry(qE->column, qE->value * -1);
			append(R, E);
			moveNext(Q);
		}
	}

	if(index(P) != -1)			//catch any remaining values in P and Q
	{
		while(index(P) != -1)
		{
			pE = (Entry)get(P);
			E = newEntry(pE->column, pE->value);
			append(R, E);
			moveNext(P);
		}
	}
	else if(index(Q) != -1)
	{
		while(index(Q) != -1)
		{
			qE = (Entry)get(Q);
			E = newEntry(qE->column, qE->value * -1);
			append(R, E);
			moveNext(Q);
		}
	}

	return (R);
}


typedef struct MatrixObj
{
	int size;
	int NNZ;
	List *rows;
} MatrixObj;

//Constructors-Destructors************************************************************************************************************
Matrix newMatrix(int n)
{
	int i;
	Matrix M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->NNZ = 0;
	M->rows = calloc(n, sizeof(List));
	for(i = 0; i < n; i++)
	{
		M->rows[i] = newList();
	}
	return (M);
}															

void freeMatrix(Matrix* pM)
{
	if(*pM != NULL && pM != NULL)
	{
		int i;
		Entry E = NULL;
		for(i = 0; i < size(*pM); i++)
		{
			if(length((*pM)->rows[i]) != 0)
			{
				moveFront((*pM)->rows[i]);
				while(index((*pM)->rows[i]) != -1)
				{				
					E = get((*pM)->rows[i]);
					freeEntry(&E);
					moveNext((*pM)->rows[i]);
				}
			}
			freeList(&(*pM)->rows[i]);	
			free((*pM)->rows[i]);
		}
		free((*pM)->rows);
		free(*pM);
		*pM = NULL;
	}
}					

//Access Functions********************************************************************************************************************
//Description: Return the size of square Matrix M.
int size(Matrix M)
{
	if(M == NULL)
	{
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	return (M->size);
}

//Description: Return the number of non-zero elements in M.										
int NNZ(Matrix M)
{
	if(M == NULL)
	{
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	return (M->NNZ);
}									

//Description: Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
	if(A == NULL || B == NULL)
	{
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);		
	}

	if(size(A) != size(B))
	{
		return 0;
	}

	int i;
	Entry E = NULL;
	Entry F = NULL;
	for(i = 0; i < size(A); i++)
	{	
		if(length(A->rows[i]) != length(B->rows[i]))
		{
			return 0;
		}

		moveFront(A->rows[i]);
		moveFront(B->rows[i]);

		while( (index(A->rows[i]) != -1) && (index(B->rows[i]) != -1) )
		{
			E = (Entry)get(A->rows[i]);
			F = (Entry)get(B->rows[i]);
			if( (E->column != F->column) || (E->value != F->value) )
			{
				return 0;
			}
			moveNext(A->rows[i]);
			moveNext(B->rows[i]);
		}
	}

	return 1;
}						

//Manipulation Procedures*************************************************************************************************************
//Description: Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
	if(M == NULL)
	{
		printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	int i;
	Entry E = NULL;
	for(i = 0; i < size(M); i++)
	{
		if(length(M->rows[i]) != 0)
		{
			moveFront(M->rows[i]);
			while(index(M->rows[i]) != -1)
			{				
				E = get(M->rows[i]);
				freeEntry(&E);
				moveNext(M->rows[i]);
			}
			clear(M->rows[i]);
		}
	}
	M->NNZ = 0;
}

//Description: Changes the ith row, jth column of M to the value x.
//Preconditon: 1<=i<=size(M), 1<=j<=size(M)
//Cases:
//	Case 1: Mij = 0, x = 0
//		Do nothing
//	Case 2: Mij != 0, x = 0
//		Delete an Entry
//	Case 3: Mij = 0, x != 0
//		Insert a new Entry
//	Case 4: Mij != 0, x != 0
//		Overwrite existing Entry
void changeEntry(Matrix M, int i, int j, double x)
{
	if(M == NULL)
	{
		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(i < 1 || i > size(M))
	{
		printf("Matrix Error: calling changeEntry() on an out of bounds element\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1 || j > size(M))
	{
		printf("Matrix Error: calling changeEntry() on an out of bounds element\n");
		exit(EXIT_FAILURE);
	}

	Entry E = NULL;

	if(length(M->rows[i - 1]) == 0)							//check to see if list is empty
	{
		if(x != 0)
		{
			E = newEntry(j, x);
			prepend(M->rows[i - 1], E);
			M->NNZ++;
		}
	}
	else												//list not empty
	{
		moveFront(M->rows[i - 1]);					
		while(index(M->rows[i - 1]) != -1 && (((Entry)get(M->rows[i - 1]))->column < j) ) //look to see if entry already exists
		{
			moveNext(M->rows[i - 1]);		
		}

		if(index(M->rows[i - 1]) == -1)		//does not exist
		{
			if(x != 0)						//do nothing if x = 0
			{
				E = newEntry(j, x);
				append(M->rows[i - 1], E);
				M->NNZ++;
			}
		}
		else if (((Entry)get(M->rows[i - 1]))->column == j)		//does exist
		{
			if(x == 0)											//if x = 0 delete entry
			{
				E = (Entry)get(M->rows[i - 1]);
				freeEntry(&E);
				delete(M->rows[i - 1]);
				M->NNZ--;
				E = NULL;
			}
			else												//else change the value of the entry to x
			{
				E = (Entry)get(M->rows[i - 1]);
				E->value = x;
			}
		}
		else		//if an entry with a higher column number is found, insert a new entry before if x != 0											
		{
			if(x != 0)											
			{
				E = newEntry(j, x);
				insertBefore(M->rows[i - 1], E);
				M->NNZ++;
			}
			
		}

	}
}


//Matrix Arithmetic operations********************************************************************************************************
//Description: Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
	if(A == NULL)
	{
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	int i;
	Matrix C = newMatrix(size(A));
	Entry E;

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0)
		{
			moveFront(A->rows[i]);
			while(index(A->rows[i]) != -1)
			{
				E = (Entry)get(A->rows[i]);
				changeEntry(C, i + 1, E->column, E->value);
				moveNext(A->rows[i]);
			}
		}
	}
	return(C);
}									

//Description: Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A)
{
	if(A == NULL)
	{
		printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	
	int i;
	Matrix T = newMatrix(size(A));
	Entry E;

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0)
		{
			moveFront(A->rows[i]);
			while(index(A->rows[i]) != -1)
			{
				E = (Entry)get(A->rows[i]);
				changeEntry(T, E->column, i + 1, E->value);
				moveNext(A->rows[i]);
			}
		}
	}
	return (T);
}								

//Description: Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
	if(A == NULL)
	{
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}

	int i;
	Matrix xA = newMatrix(size(A));
	Entry E = NULL;

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0)
		{
			moveFront(A->rows[i]);
			while(index(A->rows[i]) != -1)
			{
				E = get(A->rows[i]);
				changeEntry(xA, i + 1, E->column, (E->value * x));
				moveNext(A->rows[i]); 
			}
		}
	}
	return (xA);
}					

//Description: Returns a reference to a new Matrix object representing A+B.
//Precondition: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)		
{
	if(A == NULL || B == NULL)
	{
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B))
	{
		printf("Matrix Error: calling sum() on Matricies of different sizes\n");
		exit(EXIT_FAILURE);
	}
	if(A == B)
	{
		Matrix C = scalarMult(2, A);
		return(C);
	}

	int i;
	Matrix C = newMatrix(size(A));
	List L;

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0 || length(B->rows[i]) != 0)
		{
			L = vectorSum(A->rows[i], B->rows[i]);
			freeList(&C->rows[i]);
			C->rows[i] = L;
			C->NNZ += length(L);
		}

	}

	return(C);
}

//Description: Returns a reference to a new Matrix object representing A-B.
//Precondition: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
	if(A == NULL || B == NULL)
	{
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B))
	{
		printf("Matrix Error: calling diff() on Matricies of different sizes\n");
		exit(EXIT_FAILURE);
	}

	int i;
	Matrix C = newMatrix(size(A));
	List L;

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0 || length(B->rows[i]) != 0)
		{
			L = vectorDiff(A->rows[i], B->rows[i]);
			freeList(&C->rows[i]);
			C->rows[i] = L;
			C->NNZ += length(L);
		}
	}

	return(C);
}

//Description: Returns a reference to a new Matrix object representing AB.
//Precondition: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
	if(A == NULL || B == NULL)
	{
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B))
	{
		printf("Matrix Error: calling product() on Matricies of different sizes\n");
		exit(EXIT_FAILURE);
	}

	int i;
	int j;
	double dotProd;
	Matrix C = newMatrix(size(A));
	Matrix T = transpose(B);

	for(i = 0; i < size(A); i++)
	{
		if(length(A->rows[i]) != 0)
		{
			for(j = 0; j < size(A); j++)
			{
				dotProd = vectorDot(A->rows[i], T->rows[j]);
				changeEntry(C, i + 1, j + 1, dotProd);
			}
		}	
	}

	freeMatrix(&T);
	return(C);
}


//Description: Prints a string representation of Matrix M to filestream out. Zero rows
//are not printed. Each non-zero is represented as one line consisting
//of the row number, followed by a colon, a space, then a space separated
//list of pairs "(col, val)" giving the column numbers and non-zero values
//in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M)
{
	Entry E = NULL;
	int i;

	if(M == NULL)
	{
		printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		printf("Matrix Error: calling printMatrix() on NULL FILE reference\n");
		exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < size(M); i++)
	{
		if(length(M->rows[i]) != 0)
		{
			moveFront(M->rows[i]);
			fprintf(out, "%d: ", i + 1);
			while(index(M->rows[i]) != -1)
			{
				E = get(M->rows[i]);
				fprintf(out, "(%d, %0.1f) ", E->column, E->value);
				moveNext(M->rows[i]);
			}
			fprintf(out, "\n");			
		}
	}
}
