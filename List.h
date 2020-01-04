/********************************************************************************************************************
*	File: List.h
*	Name: Andrew Craig
*	CruzID: acraig1
*	Assignment: pa2
*********************************************************************************************************************/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//Constructors-Destructors*******************************************************************************************
List newList(void);						//Creates and returns a new empty List.
void freeList(List* pL);				//Frees all heap memory associated with *pL, and sets *pL to NULL.

//Access Functions***************************************************************************************************
int length(List L);						//Returns the number of elements in List L.
int index(List L);						//Returns index of cursor element if defined, -1 otherwise.
void* front(List L);					//Returns front element of List L.
										//Precondition: length() > 0
void* back(List L);						//Returns back element of List L.
										//Precondition: length() > 0
void* get(List L);						//Returns cursor element of List L.
										//Precondition: length() > 0 & index() >= 0

//Manipulation Procedures********************************************************************************************
void clear(List L);						//Resets List L to its original empty state.
void moveFront(List L);					//If List L is non-empty, sets the cursor under the front element,
										//otherwise does nothing.
void moveBack(List L);					//If List L is non-empty, sets the cursor under the last element,
										//otherwise does nothing.
void movePrev(List L);					//If the cursor is defined and not at the front, move the cursor one
										//step towards the front of List L; if the cursor is defined and at
										//the front, cursor becomes undefined; if cursor is undefined do nothing.
void moveNext(List L);					//If the cursor is defined and not at back, move cursor one step towards
										//the back of List L; if the cursor is defined and at the back, the
										//cursor becomes undefined; if the cursor is undefined do nothing
void prepend(List L, void* data);		//Insert new element into List L. If L is non-empty, insertion takes
										//place before front element.
void append(List L, void* data);		//Insert new element into List L. If L is non-empty, insertion takes
										//place after back element.
void insertBefore(List L, void* data);	//Insert new element before cursor.
										//Precondition: length() > 0 & index() >= 0
void insertAfter(List L, void* data);	//Insert new element after cursor.
										//Precondition: length() > 0 & index() >= 0
void deleteFront(List L);				//Deletes the front element of List L.
										//Precondition: length() > 0
void deleteBack(List L);				//Deletes the back element of List L.
										//Precondition: length() > 0
void delete(List L);					//Delete cursor element, making the cursor undefined.
										//Precondition: length() > 0 & index() >= 0

#endif