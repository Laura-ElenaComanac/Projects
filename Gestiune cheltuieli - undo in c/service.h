#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "MyList.h"

typedef struct {
    MyList* allExpenses;
    MyList* undoListOfLists;
}ExpenseService;

void undoService(ExpenseService* srv);

void testUndoService();

void listCopy(MyList** listaDestinatie, MyList* listaSursa);

/*
Create a new Service
*/
ExpenseService* createService();


/*
Destroy the service to free the memory
*/
void destroyService(ExpenseService* srv);


/*
Add an expense
*/
int addExpense(ExpenseService* srv, int day, int sum, char* type);

/*
Delete an expense
*/
int srvDeleteExpense(ExpenseService* srv, int day, int sum, char* type);

/*
Function that gets all the expenses matching a substring,
or simply the entire list if the argument is NULL
*/
MyList* getAllExpenses(ExpenseService* srv, char* typeSubstring);

MyList* filterExpensesNew(ExpenseService* srv, int suma);

ElemType* getExpense(MyList* l, int poz);

/*
Tests
*/
void testAddExpense();
void testDeleteExpense();
void testModifyExpense();
void testSorting();
void testFilterExpense();
