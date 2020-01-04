/********************************************************************************************************************
*  File: ListTest.c
*  Name: Andrew Craig
*  CruzID: acraig1
*  Assignment: pa2
*********************************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[])
{
   List A = newList();
   List B = newList();
   int i;
   int j;
   int* x = calloc(1000, sizeof(int));
  
   //Store 0-1000 in A
   //Store 1000-0 in B
   for(i = 0; i < 1000; i++)
   {
      x[i]= i;
      append(A, &x[i]);
      prepend(B, &x[i]);
   }

   //Print the contents of A and its number of elements
   printf("List A has %d elements\n", length(A));
   moveFront(A);
   printf("A:\n");
   while(index(A) != -1)
   {
      printf("%d ", *(int*)get(A));
      j++;
      if(j == 25) //just for formatting purposes
      {
         printf("\n");
         j = 0;
      }
      moveNext(A);
   }

   printf("\n");
   j = 0;

   //Print the contents of B and its number of elements
   printf("List B has %d elements\n", length(B));
   moveFront(B);
   printf("B:\n");
   while(index(B) != -1)
   {
      printf("%d ", *(int*)get(B));
      j++;
      if(j == 25) //just for formatting purposes
      {
         printf("\n");
         j = 0;
      }
      moveNext(B);
   }
   printf("\n");

   //Delete the front and back elements of A until only 10 elements remain
   moveFront(A);
   while(length(A) > 10)
   {
      deleteFront(A);
      if(length(A) != 0)
         deleteBack(A);
   }

   //Print the remaining contents of A
   moveFront(A);
   printf("A: ");
   while(index(A) != -1)
   {
      printf("%d ", *(int*)get(A));
      moveNext(A);
   }
   printf("\n");

   //Print the remaining contents of A in reverse
   moveBack(A);
   printf("A: ");
   while(index(A) != -1)
   {
      printf("%d ", *(int*)get(A));
      movePrev(A);
   }
   printf("\n");

   //Move the cursor of A to the 5th element and then delete it
   moveFront(A);
   while(index(A) != 4)
   {
      moveNext(A);
   }
   delete(A);

   //Print the remaining contents of A
   moveFront(A);
   printf("A: ");
   while(index(A) != -1)
   {
      printf("%d ", *(int*)get(A));
      moveNext(A);
   }
   printf("\n");

   //Insert 1 & 2 before and after the first element in A
   moveFront(A);
   insertBefore(A, &x[1]);
   insertAfter(A, &x[2]);

   //Insert 9 & 10 before and after the last element in A
   moveBack(A);
   insertBefore(A, &x[9]);
   insertAfter(A, &x[10]);

   //Print the new contents of A
   moveFront(A);
   printf("A: ");
   while(index(A) != -1)
   {
      printf("%d ", *(int*)get(A));
      moveNext(A);
   }
   printf("\n");

   //Print the first element in A, delete the first element, and then print the new first element of A
   printf("Front(A): %d\n", *(int*)front(A));
   deleteFront(A);
   printf("Front(A): %d\n", *(int*)front(A));

   //Print the last element in A, delete the last element, and then print the new last element of A
   printf("Back(A): %d\n", *(int*)back(A));
   deleteBack(A);
   printf("Back(A): %d\n", *(int*)back(A));

   //Clear B and then check to see if there are any remaining elements
   clear(B);
   if(length(B) != 0)
   {
      moveFront(B);
      printf("B: ");
      while(index(B) != -1)
      {
         printf("%d ", *(int*)get(B));
         moveNext(B);
      }
      printf("\n");
   }
   else
   {
      printf("List is empty\n");
   }

   free(x);
   freeList(&A);
   freeList(&B);

   return(0);
}

