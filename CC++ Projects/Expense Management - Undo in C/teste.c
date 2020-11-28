#include "teste.h"
#include "MyList.h"
#include "service.h"
#include <string.h>
#include <stdlib.h>

void testSet()
{
	MyList* l = createEmpty();
	int poz=0;
	Expense* e1 = createExpense(1,2,"altele");
	Expense* e2 = createExpense(2, 3, "altele");
	Expense* e3 = createExpense(2, 3, "mancare");
	add(l, e1);
	ElemType* e4 = getExpense(l, 0);
	assert(equals(e4, e1));
	assert(equals(l->elems[0], e1));
	setType(l, 0, "internet");
	assert(strcmp(getType(l->elems[0]), "internet") == 0);
	add(l, e2);
	assert(search(l, e2) == 1);
	assert(search(l, e3) == -1);
	
	destroyExpense(e3);
	destroyListExpense(l);
}

void testValidate()
{
	Expense* e1 = createExpense(-1, 2, "altele");
	assert(validate(e1) == 1);
	Expense* e2 = createExpense(1, 2, "");
	assert(validate(e2) == 3);
	Expense* e3 = createExpense(1, 2, "a");
	assert(validate(e3) == 4);
	assert(getSum(e3) == 2);

	destroyExpense(e3);
	destroyExpense(e2);
	destroyExpense(e1);
}

void testsrvDeleteExpense()
{
	ExpenseService* srv = createService();
	int day = -1;
	int sum = 2;
	char* type = "altele";
	assert(srvDeleteExpense(srv, day, sum, type) == 1);
	day = 8;
	assert(srvDeleteExpense(srv, day, sum, type)==1);
	addExpense(srv, day, sum, type);
	assert(srvDeleteExpense(srv, day, sum, type) == 0);

	destroyService(srv);
}

void testFilterExpensesNew()
{
	ExpenseService* srv = createService();
	int day = 1;
	int sum = 2;
	char type[10];
	strcpy(type, "altele");
	addExpense(srv, day, sum, type);
	day = 1;
	sum = 3;
	strcpy(type,"altele");
	addExpense(srv, day, sum, type);
	int suma = 3;
	MyList* filtered = filterExpensesNew(srv, suma);
	assert(equals(filtered->elems[0],getExpense(srv->allExpenses,0))==1);

	destroyListExpense(filtered);
	destroyService(srv);
}

void testAll()
{
	testSet();
	testValidate();
	testsrvDeleteExpense();
	testFilterExpensesNew();
}