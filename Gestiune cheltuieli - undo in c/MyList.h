#pragma once
#include "entitati.h"

typedef void* ElemType;

typedef void (*DestroyFunction)(ElemType*);

typedef void (*DeleteFunction)(ElemType*);

typedef struct {
    ElemType* elems;
    int lungime;
    int capacitate;

}MyList; //repository

/*
Check if two expenses are identical
*/
int equals(Expense* e1, Expense* e2);

/*
Search for an elem in the list, returns the position
*/
int search(MyList* l, ElemType* e);

/*
Deletes the element from the position poz
*/
void deleteFromList(MyList* l, int poz, DeleteFunction* destFct);

/*
Create an empty list
*/
MyList* createEmpty();

void destroyListExpense(MyList* l);

/*
Destroy the list
*/
void destroy(MyList* l, DestroyFunction destFct);

/*
Get an element from the list
poz - position of the element, needs to be valid
return element on the given position
*/
ElemType* get(MyList* l, int poz);

/*
Modify the element on the given pozition
return the overwrited element
*/
ElemType* set(MyList* l, int poz, Expense* p);

/*
  return number of elements in the list
*/
int size(MyList* l);

/*
  Add element into the list
  post: element is added to the end of the list
*/
void add(MyList* l, ElemType* el);

/*
  Make a shallow copy of the list
  return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l);

/*
Swap two items in the list
*/
void swapp(MyList* l, int i, int j);

/*
Sort the list on a parameter
*/
void sortExpense(MyList* l, int (*orderingFunction)(Expense* e1, Expense* e2), int order);

int cmpSum(Expense* e1, Expense* e2);
int cmpType(Expense* e1, Expense* e2);

void setDay(MyList* l, int poz, int day);
void setSum(MyList* l, int poz, int sum);
void setType(MyList* l, int poz, char* type);

void testCreateList();
void testIterateList();
void testCopyList();
void testResize();


