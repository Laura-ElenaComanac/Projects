#pragma once
///begin - added to activate memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>
///end - added to activate memory leak detection
#include <stdio.h>

#include "entitati.h"
#include "MyList.h"
#include "service.h"

void undoUI(ExpenseService* srv);

void run();

int readInt();

int modifyExpenseValue(ExpenseService* srv, int poz, int call);

int modifyDay(ExpenseService* srv, int poz);
int modifySum(ExpenseService* srv, int poz);
int modifyType(ExpenseService* srv, int poz);

void deleteExpense(ExpenseService* srv);

MyList* filterExpenses(ExpenseService* srv, int call);

int trySorting(ExpenseService* srv, int call, int order);

void readNewExpense(ExpenseService* srv);

void runAllTests();

void ui_sortExpense(ExpenseService* srv);

void ui_filterExpenses(ExpenseService* srv);
