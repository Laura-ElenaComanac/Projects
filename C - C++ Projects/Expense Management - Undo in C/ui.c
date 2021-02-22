#include "ui.h"
#include "service.h"
#include "teste.h"

void undoUI(ExpenseService* srv)
{
    undoService(srv);
}

int readInt() {
    int c, cmd;
    if (scanf("%d", &cmd) != 1) {
        printf("Va rugam introduceti doar o singura cifra!\n");
        while ((c = getchar()) != EOF && c != '\n');
        cmd = -1;
    }
    return cmd;
}

/*
A function that filteres the list on a given creteria,
taken from the user, and returns the filtered list
*/
MyList* filterExpenses(ExpenseService* srv, int call) {

    switch (call) {
    case 1: {
        int day;
        printf("Introduceti ziua: ");
        scanf("%d", &day);
        return filterByDay(srv, day);
        break;
    }
    case 2: {
        int sum;
        printf("Introduceti suma: ");
        scanf("%d", &sum);
        return filterBySum(srv, sum);
        break;
    }
    case 3: {
        int c;
        char type[30];
        while ((c = getchar()) != EOF && c != '\n');
        printf("Introduceti tipul: ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\r\n")] = '\0';
        return getAllExpenses(srv, type);
        break;
    }
    default:
        break;
    }
}

void deleteExpense(ExpenseService* srv) {
    printf("Introduceti campul cerut urmat de tasta ENTER!\n");
    int day, sum;
    char type[30];

    ///day
    printf("Introduceti ziua: ");
    day = readInt();
    ///sum
    printf("Suma: ");
    sum = readInt();
    ///type
    printf("Tipul cheltuielii: ");
    int c;
    while ((c = getchar()) != EOF && c != '\n');
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\r\n")] = '\0';
    printf("\n");
    if (srvDeleteExpense(srv, day, sum, type) == 0)
        printf("Sters cu succes\n");
    else
        printf("Nu s-a putut efectua stergerea\n");
}

void readNewExpense(ExpenseService* srv) {

    printf("Introduceti campul cerut urmat de tasta ENTER!\n");
    int day, sum;
    char type[30];

    ///day
    printf("Introduceti ziua: ");
    day = readInt();
    ///sum
    printf("Suma: ");
    sum = readInt();
    ///type
    printf("Tipul cheltuielii: ");
    int c;
    while ((c = getchar()) != EOF && c != '\n');
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\r\n")] = '\0';
    printf("\n");
    int code = addExpense(srv, day, sum, type);
    switch (code) {
    case 0: {
        printf("Adaugat cu succes\n");
        break;
    }
    case 1: {
        printf("Ziua este invaldia!\n");
        break;
    }
    case 2: {
        printf("Suma trebuie sa fie pozitiva\n");
        break;
    }
    case 3: {
        printf("Tipul trebuie sa fie: mancare, telefon, internet sau altele\n");
        break;
    }
    default: {
        printf("Tipul trebuie sa fie: mancare, telefon, internet sau altele\n");
        break;
    }
    }

}

///modify day
int modifyDay(ExpenseService* srv, int poz)
{
    int day, c;
    printf("Introduceti noua valoarea pentru zi: ");

    if (scanf("%d", &day) != 1) {
        while ((c = getchar()) != EOF && c != '\n');
        day = -1;
    }
    if (day == -1)
        return 1;
    Expense* e = createExpense(day, 200, "mancare");
    int errorCode = validate(e);
    if (errorCode)
        return errorCode;

    MyList* copySrvAllExpenses = copyList(srv->allExpenses);
    add(srv->undoListOfLists, copySrvAllExpenses);
    setDay(srv->allExpenses, poz, day);
    return 0;
}
///modify sum

int modifySum(ExpenseService* srv, int poz)
{
    int sum, c;
    printf("Introduceti noua valoarea pentru suma: ");
    if (scanf("%d", &sum) != 1) {
        while ((c = getchar()) != EOF && c != '\n');
        sum = -1;
    }
    if (sum == -1)
        return 1;

    Expense* e = createExpense(1, sum, "mancare");
    int errorCode = validate(e);
    if (errorCode)
        return errorCode;

    MyList* copySrvAllExpenses = copyList(srv->allExpenses);
    add(srv->undoListOfLists, copySrvAllExpenses);
    setSum(srv->allExpenses, poz, sum);
    return 0;
}
///modify type
int modifyType(ExpenseService* srv, int poz)
{
    printf("Tipul cheltuielii: ");
    int c;
    char type[30];
    while ((c = getchar()) != EOF && c != '\n');
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\r\n")] = '\0';
    Expense* e = createExpense(1, 1, type);
    int errorCode = validate(e);
    if (errorCode)
        return errorCode;

    MyList* copySrvAllExpenses = copyList(srv->allExpenses);
    add(srv->undoListOfLists, copySrvAllExpenses);
    setType(srv->allExpenses, poz, type);
    return 0;
}
/*
Function that tries to change a value of an expense
input : the position of the object to be modified, and an int from 1 to 3 with the meaning of which value to be changed
output: 0 if succesful, !=0 otherwise
*/
int modifyExpenseValue(ExpenseService* srv, int poz, int call) {

    int errorCode = 0;
    switch (call) {
    case 1: {
        errorCode = modifyDay(srv, poz);
        break;
    }
    case 2: {
        errorCode = modifySum(srv, poz);
        break;
    }
    case 3: {
        errorCode = modifyType(srv, poz);
        break;
    }
    default:
        break;
    }
    return errorCode;
}
/*
Function that checks if sorting call is ok and calls the ordering function from the repo
*/
int trySorting(ExpenseService* srv, int call, int order) {
    if (order != 1 && order != 2) {
        printf("Criteriul de sortare este invalid, se efectueaza sortare crescatoare.\n");
        order = 1;
    }
    switch (call) {
    case 1: {
        sortExpense(srv->allExpenses, cmpSum, order);
        break;
    }
    case 2: {
        sortExpense(srv->allExpenses, cmpType, order);
        break;
    }
    default:
        return 1;
        break;
    }
    return 0;
}


void runAllTests() 
{
    testUndoService();
    testListOfLists();
    testCreateDestroy();
    testCreateList();
    testIterateList();
    testCopyList();
    testAddExpense();
    testDeleteExpense();
    testModifyExpense();
    testResize();
    testSorting();
    testFilterExpense();
    testAll();
}

void printAllExpenses(MyList* l) {

    printf("Cheltuieli: \n");
    for (int i = 0; i < size(l); i++) {
        Expense* e = get(l, i);
        printf("Ziua: %d, Suma: %d, Tipul: %s\n", e->day, e->sum, e->type);
    }

}

void showAll(ExpenseService* srv) {

    MyList* allExpenses = getAllExpenses(srv, NULL);
    printAllExpenses(allExpenses);
    destroy(allExpenses,destroyExpense);

}

void modifyExpense(ExpenseService* srv) {

    int poz, call;
    printf("Introduceti pozitia elementului pe care doriti sa il modificati: ");
    poz = readInt();

    printf("Introduceti cifra corespunzatoare modificarii pe care doriti sa o faceti: \n1.Ziua\n2.Suma\n3.Tipul\nAlegere: ");
    call = readInt();

    if (call > 3 || call < 1) {
        printf("Valoare introdusa nu este corecta.");
        return;
    }
    int code = modifyExpenseValue(srv, poz, call);
    if (code != 0)
        printf("Valoarea introdusa nu este specifica campului care doriti sa il actualizati.\n");

}

void ui_sortExpense(ExpenseService* srv) {

    int call, order;
    printf("Introduceti cifra corespunzatoare criteriului dupa care doriti sa se realizeze sortarea.\n1.Suma\n2.Tip\nAlegere: ");
    call = readInt();
    printf("1.Crescator\n2.Descrescator\nAlegere: ");
    order = readInt();
    int code = trySorting(srv, call, order);
    if (code == 0)
        printf("Succes!\n");
}

void ui_filterExpensesNew(ExpenseService* srv) {
    int suma;
    printf("Introduceti suma pentru care doriti sa filtrati produsele cu suma mai mica decat valoarea data: ");
    scanf("%d", &suma);
    MyList* filtered = filterExpensesNew(srv, suma);
    printAllExpenses(filtered);
    destroy(filtered, destroyExpense);
}

void ui_filterExpenses(ExpenseService* srv) {
    int call;
    printf("Introduceti cifra corespunzatoare criteriului dupa care doriti sa se efectueze filtarea.\n1.Ziua\n2.Suma\n3.Tipul\nAlegere: ");
    call = readInt();
    if (call < 1 || call > 3) {
        printf("Cifra introdusa nu corespunde nici unei variante.\n");
        return;
    }
    MyList* filtered = filterExpenses(srv, call);
    printAllExpenses(filtered);
    destroy(filtered,destroyExpense);
}


void run() {
    printf("1: Adaugare\n2:Modificare\n3:Sterge\n4:Filtrare\n5:Sortare\n6:Afisare lista\n9:Exit\n10:Undo\n11:Filtrare noua\n");
    int cmd = 0;
    printf("Introduceti numarul corespunzator comenzii care doriti sa o efectuati: \n");

    ExpenseService* srv = createService();

    while (cmd != 12) {
        printf(">>>>");
        cmd = readInt();
        if (cmd == -1)
            continue;
        printf("\n");
        switch (cmd) {

        case 1: {
            readNewExpense(srv);
            break;
        }
        case 2: {
            modifyExpense(srv);
            break;
        }
        case 3: {
            deleteExpense(srv);
            break;
        }
        case 4: {
            ui_filterExpenses(srv);
            break;
        }
        case 5: {
            ui_sortExpense(srv);
            break;
        }
        case 6: {
            showAll(srv);
            break;
        }
        case 9: {
            printf("Sfarsitul executiei...\n");
            cmd = 12;
            break;
        }
        case 10: {
            undoUI(srv);
            printf("Succes!\n");
            break;
        }
        case 11: {
            ui_filterExpensesNew(srv);
            //printf("Succes!\n");
            break;
        }
        default:
            printf("Comanda invalida!\n");
        }
    }
    destroyService(srv);
}
