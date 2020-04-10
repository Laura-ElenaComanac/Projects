#include "service.h"

void undoService(ExpenseService* srv)
{
    listCopy(&srv->allExpenses, srv->undoListOfLists->elems[srv->undoListOfLists->lungime - 1]);
    //destroy(srv->undoListOfLists->elems[srv->undoListOfLists->lungime - 1], destroyListExpense);
    deleteFromList(srv->undoListOfLists,srv->undoListOfLists->lungime - 1,destroyListExpense);
}

void testUndoService()
{
    ExpenseService* srv = createService();
    addExpense(srv, 1, 2, "mancare");
    assert(srv->undoListOfLists->lungime == 1);
    undoService(srv);
    assert(srv->undoListOfLists->lungime == 0);
    destroyService(srv);
}

void listCopy(MyList** listaDestinatie, MyList* listaSursa)
{
    destroy(*listaDestinatie, destroyExpense);
    *listaDestinatie = copyList(listaSursa);
}

/*
Add an expense
*/
int addExpense(ExpenseService* srv, int day, int sum, char* type) 
{
    Expense* e = createExpense(day, sum, type);
    int errorCode = validate(e);

    if (errorCode) {
        destroyExpense(e);
        return errorCode;
    }
    MyList* copySrvAllExpenses = copyList(srv->allExpenses);
    add(srv->undoListOfLists, copySrvAllExpenses);
    add(srv->allExpenses, e);
    //destroyExpense(e);
    return 0; /// all ok
}

int srvDeleteExpense(ExpenseService* srv, int day, int sum, char* type) 
{
    Expense* e = createExpense(day, sum, type);
    int errorCode = validate(e);

    if (errorCode) {
        destroyExpense(e);
        return errorCode;
    }
    int i = search(srv->allExpenses, e);
    if (i == -1) {
        destroyExpense(e);
        return 1;
    }
    else {
        MyList* copySrvAllExpenses = copyList(srv->allExpenses);
        add(srv->undoListOfLists, copySrvAllExpenses);
        deleteFromList(srv->allExpenses, i, destroyExpense);
        destroyExpense(e);
        return 0;
    }
}

/*
Create a service
*/
ExpenseService* createService() {

    ExpenseService* rez = (ExpenseService*)malloc(sizeof(ExpenseService));
    rez->allExpenses = createEmpty();
    rez->undoListOfLists = createEmpty();
    return rez;
}
/*
Destroy a service
*/
void destroyService(ExpenseService* srv) {

    destroy(srv->allExpenses,destroyExpense);
    destroy(srv->undoListOfLists, destroyListExpense);
    free(srv);

}

/*
Returns a list of all the expenses, filtered by type
Returns the entire list if type is NULL
*/
MyList* getAllExpenses(ExpenseService* srv, char* typeSubstring) {
    if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
        return copyList(srv->allExpenses);
    }


    MyList* rez = createEmpty();
    //Expense** elems = 
    //rez->elems = (Expense*)rez->elems;
    for (int i = 0; i < size(srv->allExpenses); i++) {
        Expense* e = get(srv->allExpenses, i);
        if (strstr(e->type, typeSubstring) != NULL)
            add(rez, copyExpense(e));
    }
    return rez;
}
/*
Filters the list by the given sum
return the filtered list
*/
MyList* filterBySum(ExpenseService* srv, int summ) {
    MyList* rez = createEmpty();
    for (int i = 0; i < size(srv->allExpenses); i++) {
        Expense* e = get(srv->allExpenses, i);
        if (e->sum == summ)
            add(rez, copyExpense(e));
    }
    return rez;
}

/*
Filters the list by the given day
returns the filtered list
*/
MyList* filterByDay(ExpenseService* srv, int dayy) {
    MyList* rez = createEmpty();
    for (int i = 0; i < size(srv->allExpenses); i++) {
        Expense* e = get(srv->allExpenses, i);
        if (e->day == dayy)
            add(rez, copyExpense((e)));

    }
    return rez;
}
/*
returns an element from the list
poz - position of the element to be returned, needs to be valid
return element on the given position
*/
ElemType* getExpense(MyList* l, int poz) {

    return l->elems[poz];
}

/*
A function that filteres the list on a given creteria,
taken from the user, and returns the filtered list
*/
MyList* filterExpensesNew(ExpenseService* srv, int suma) 
{
    MyList* filter = createEmpty();
    for (int i = 0; i < srv->allExpenses->lungime; i++)
    {
        Expense* e = getExpense(srv->allExpenses, i);
        if (getSum(e) < suma)
            add(filter, copyExpense(e));
    }
    return filter;
}


void testAddExpense() {
    ExpenseService* srv = createService();

    assert(addExpense(srv, 31, 200, "mancare") == 0);
    assert(addExpense(srv, 1, -10, "internet") == 2);
    assert(addExpense(srv, 1, 200, "internet") == 0);

    MyList* filtered = getAllExpenses(srv, NULL);
    assert(size(filtered) == 2);
    destroy(filtered,destroyExpense);

    filtered = getAllExpenses(srv, "mancare");
    assert(size(filtered) == 1);
    destroy(filtered, destroyExpense);

    filtered = getAllExpenses(srv, "internet");
    assert(size(filtered) == 1);
    destroy(filtered, destroyExpense);

    filtered = getAllExpenses(srv, "telefon");
    assert(size(filtered) == 0);
    destroy(filtered, destroyExpense);

    destroyService(srv);
}

void testDeleteExpense() {

    ExpenseService* srv = createService();
    assert(addExpense(srv, 31, 200, "mancare") == 0);
    assert(addExpense(srv, 1, 200, "internet") == 0);

    MyList* filtered = getAllExpenses(srv, NULL);
    assert(size(filtered) == 2);

    deleteFromList(filtered, 1, destroyExpense);
    assert(size(filtered) == 1);

    Expense* e = createExpense(31, 200, "mancare");

    assert(equals(e, filtered->elems[0]));
    destroy(filtered, destroyExpense);
    destroyExpense(e);
    destroyService(srv);

}

void testFilterExpense() {

    ExpenseService* srv = createService();
    assert(addExpense(srv, 31, 200, "mancare") == 0);
    assert(addExpense(srv, 1, 500, "internet") == 0);

    MyList* filtered = getAllExpenses(srv, NULL);
    assert(size(filtered) == 2);

    MyList* rez = filterByDay(srv, 31);
    Expense* e = createExpense(31, 200, "mancare");
    assert(equals(e, rez->elems[0]));
    destroy(rez, destroyExpense);
    destroyExpense(e);
    e = createExpense(1, 500, "internet");
    rez = filterBySum(srv, 500);
    assert(equals(e, rez->elems[0]));
    destroyExpense(e);
    destroy(rez, destroyExpense);
    destroyService(srv);
    destroy(filtered, destroyExpense);
}

void testModifyExpense() {
    ExpenseService* srv = createService();
    assert(addExpense(srv, 31, 200, "internet") == 0);

    MyList* filtered = getAllExpenses(srv, NULL);
    assert(size(filtered) == 1);
    destroy(filtered, destroyExpense);

    filtered = getAllExpenses(srv, "internet");
    setDay(filtered, 0, 31);
    setSum(filtered, 0, 300);

    Expense* e = createExpense(31, 300, "internet");
    assert(equals(e, filtered->elems[0]));
    destroyExpense(e);
    destroy(filtered, destroyExpense);
    destroyService(srv);
}

void testSorting() {
    ExpenseService* srv = createService();
    assert(addExpense(srv, 31, 500, "mancare") == 0);
    assert(addExpense(srv, 1, 200, "internet") == 0);

    MyList* filtered = getAllExpenses(srv, NULL);
    assert(size(filtered) == 2);
    destroy(filtered, destroyExpense);

    trySorting(srv, 1, 1);
    MyList* filter = getAllExpenses(srv, NULL);
    //filter->elems = *(Expense**)filter->elems;
    Expense** intermediar = filter->elems;
    assert(intermediar[0]->sum == 200);
    destroy(filter, destroyExpense);

    trySorting(srv, 1, 2);
    filter = getAllExpenses(srv, NULL);
    //filter->elems = (Expense*)filter->elems;
    intermediar = filter->elems;

    assert(intermediar[0]->sum == 500);
    destroy(filter, destroyExpense);
    assert(addExpense(srv, 20, 150, "mancare") == 0);

    trySorting(srv, 2, 1);
    filter = getAllExpenses(srv, NULL);
    intermediar = filter->elems;

    assert(size(filter) == 3);
    assert(strcmp(intermediar[0]->type, "internet") == 0);
    assert(strcmp(intermediar[1]->type, "mancare") == 0);
    assert(strcmp(intermediar[2]->type, "mancare") == 0);

    destroy(filter, destroyExpense);
    destroyService(srv);
}


void testListOfLists()
{
    MyList* list = createEmpty();
    add(list, createExpense(1, 3, "internet"));
    add(list, createExpense(2, 5, "mancare"));
    assert(size(list) == 2);

    MyList* undoList = createEmpty();

    MyList* list2 = createEmpty();

    add(undoList, copyList(list));
    assert(size(undoList) == 1);
    add(undoList, copyList(list2));
    assert(size(undoList) == 2);

    destroy(list,destroyExpense);
    destroy(list2, destroyExpense);
    destroy(undoList, destroyListExpense);
}
