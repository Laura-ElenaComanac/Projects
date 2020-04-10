#include "MyList.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
Create an empty list
*/
MyList* createEmpty() {

    MyList* rez = (MyList*)malloc(sizeof(MyList));
    rez->lungime = 0;
    rez->capacitate = 2;
    rez->elems = (ElemType*)malloc(sizeof(ElemType) * rez->capacitate);
    return rez;
}

void destroyListExpense(MyList* l)
{
    destroy(l, destroyExpense);
}

/*
Destroy the list of expenses
*/
void destroy(MyList* l, DestroyFunction destFct) {
    ///dealocate expenses
    for (int i = 0; i < l->lungime; i++)
    {
        ElemType p = l->elems[i];
        destFct(p);
    }
    free(l->elems);
    free(l);
}

/*
returns an element from the list
poz - position of the element to be returned, needs to be valid
return element on the given position
*/
ElemType* get(MyList* l, int poz) {

    return l->elems[poz];
}

/*
retun number of elements in the list
*/
int size(MyList* l) {
    return l->lungime;
}

/*
check if we have enough capacity
allocate more memory otherwise
*/
void enoughSpace(MyList* l) { //resize

    if (l->lungime < l->capacitate)
        return; /// there is enough space

    ///allocate more memory
    int newCapacity = l->capacitate *= 2;
    ElemType* newElems = malloc(sizeof(ElemType) * newCapacity);
    ///copy elements
    for (int i = 0; i < l->lungime; i++)
        newElems[i] = l->elems[i];

    ///delete old vector
    free(l->elems);
    l->elems = newElems;
    l->capacitate = newCapacity;
}


void deleteFromList(MyList* l, int poz, DeleteFunction destFct) {
    /*
    int newCap = l -> capacitate;
    ElemType* newElems = malloc(sizeof(ElemType) * newCap);
    ///now we copy the elements except the one that we wish to delete
    int j = -1; ///counter for the new array
    for(int i = 0; i < l -> lungime; i++)
        if ( i == poz)
            continue;
        else {
            j++;
            newElems[j] = l -> elems[i];
        }
    //delete the elem and the old elem vector
    free(l -> elems);
    l -> elems = newElems;
    l -> capacitate = newCap;
    l -> lungime--;
    */
    ElemType p = l->elems[poz];
    destFct(p);
    for (int i = poz; i < l->lungime; i++)
        l->elems[i] = l->elems[i + 1];
    l->lungime--;
}


/*
Add an element to the list
*/
void add(MyList* l, ElemType* e) {

    enoughSpace(l);
    l->elems[l->lungime] = e;
    l->lungime++;
}

///sets the day for an element at the given index
void setDay(MyList* l, int poz, int day) {
    Expense** inter = l->elems;
    inter[poz]->day = day;
}

///sets the sum for an element at the given index
void setSum(MyList* l, int poz, int sum) {
    Expense** inter = l->elems;
    inter[poz]->sum = sum;
}

///sets the type for an element at the given index
void setType(MyList* l, int poz, char* tip) {
    Expense** inter = l->elems;
    strcpy(inter[poz]->type, tip);
}

///checks if an expense is equal to another
int equals(Expense* e1, Expense* e2) {

    return e1->day == e2->day && e1->sum == e2->sum && (strcmp(e1->type, e2->type) == 0);

}

/// returns the index of an element, -1 if the element cannot be found in the list
int search(MyList* l, ElemType* e) {
    int i = 0;
    for (i = 0; i < l->lungime; i++) {
        if (equals(l->elems[i], e))
            return i;
    }
    return -1;
}
///compares to expenses by sum
///1 if e1 < e2, 0 otherwise
int cmpSum(Expense* e1, Expense* e2) {
    if (e1->sum < e2->sum)
        return 1;
    else
        return 0;
}

///compares to expenses by type
///1 if e1 < e2, 0 otherwise
int cmpType(Expense* e1, Expense* e2) {
    if (strcmp(e1->type, e2->type) < 0)
        return 1;
    else
        return 0;
}


///Sorts the list of expenses by either the type or sum in the given order
void sortExpense(MyList* l, int (*orderingFunction)(Expense* e1, Expense* e2), int order) {
    int i, j;
    ElemType* left;
    ElemType* right;
    for (i = 0; i < l->lungime - 1; ++i) {
        for (j = i + 1; j < l->lungime; ++j) {
            left = get(l, i);
            right = get(l, j);
            if (!orderingFunction(left, right) && order == 1) {
                swapp(l, i, j);
            }
            else
                if (orderingFunction(left, right) && order == 2)
                    swapp(l, i, j);
        }
    }
}

///Swaps the elements at index i and j
void swapp(MyList* l, int i, int j) {
    Expense* aux;
    aux = l->elems[i];
    l->elems[i] = l->elems[j];
    l->elems[j] = aux;
}

/*
duplicate the list
"shallow copy"
*/
MyList* copyList(MyList* l) {

    MyList* newList = createEmpty();
    for (int i = 0; i < size(l); i++) {
        ElemType* e = get(l, i);
        add(newList, copyExpense(e));
    }
    return newList;
}
void testCreateList() {

    MyList* l = createEmpty();
    assert(size(l) == 0);
    destroy(l, destroyExpense);

}

void testIterateList() {

    MyList* l = createEmpty();
    add(l, createExpense(31, 2000, "mancare"));
    add(l, createExpense(1, 2000, "internet"));
    assert(size(l) == 2);

    Expense* e = get(l, 0);

    assert(strcmp(e->type, "mancare") == 0);
    assert(e->day == 31);

    e = get(l, 1);
    assert(e->sum == 2000);

    destroy(l, destroyExpense);
}

void testCopyList() {

    MyList* l = createEmpty();
    add(l, createExpense(31, 200, "mancare"));
    add(l, createExpense(1, 200, "internet"));

    MyList* l2 = copyList(l);

    assert(size(l2) == 2);

    Expense* e = get(l, 0);
    Expense* e2 = get(l2, 0);

    assert(strcmp(e->type, e2->type) == 0);
    assert(e->day == e2->day);

    destroy(l, destroyExpense);
    destroy(l2, destroyExpense);
}

void testResize() {

    MyList* l = createEmpty();

    for (int i = 0; i < 10; i++)
        add(l, createExpense(31, 200, "mancare"));

    assert(size(l) == 10);

    destroy(l, destroyExpense);
}
