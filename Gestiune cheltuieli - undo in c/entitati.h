#pragma once
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
    int day, sum;
    char* type;
} Expense;

/*
Create new Expense
*/
Expense* createExpense(int day, int sum, char type[]);

/*
Dealocate memory occupied by Expense
*/
void destroyExpense(Expense* e);

void testCreateDestroy();

int validate(Expense* e);

int getSum(Expense* e);

int getType(Expense* e);

Expense* copyExpense(Expense* e);
