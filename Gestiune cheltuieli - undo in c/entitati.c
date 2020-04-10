#include "entitati.h"

/*
Create a new Expense
*/
Expense* createExpense(int day, int sum, char type[]) {
    Expense* rez = malloc(sizeof(Expense));
    //size_t nrC = strlen(type) + 1;
    rez->type = malloc(sizeof(char) * 50);
    strcpy(rez->type, type);
    rez->day = day;
    rez->sum = sum;

    return rez;
}

/*
Dealocate memory occupied by Expense
*/
void destroyExpense(Expense* e) {

    free(e->type);
    free(e);
}

/*
Create a deep copy for the expense
*/

Expense* copyExpense(Expense* e) {

    return createExpense(e->day, e->sum, e->type);

}

int validate(Expense* e) {

    if (e->day <= 0 || e->day > 31)
        return 1;

    if (e->sum < 0)
        return 2;

    if (strlen(e->type) == 0)
        return 3;
    /// heck
    if (strcmp(e->type, "mancare") == 0 || strcmp(e->type, "internet") == 0 || strcmp(e->type, "telefon") == 0
        || strcmp(e->type, "imbracaminte") == 0 || strcmp(e->type, "altele") == 0)
        return 0;
    else
        return 4;
}

int getSum(Expense* e)
{
    return e->sum;
}

int getType(Expense* e)
{
    return e->type;
}

void testCreateDestroy() {
    ///creare cheltuiala
    Expense* e = createExpense(1, 200, "mancare");
    assert(e->day == 1);
    assert(e->sum == 200);
    assert(strcmp(e->type, "mancare") == 0);

    ///distrugere cheltuiala
    destroyExpense(e);
}