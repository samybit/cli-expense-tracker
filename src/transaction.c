#include <stdio.h>
#include <string.h>
#include "transaction.h"

Transaction create_transaction(int id,
                               char *date,
                               double amount,
                               TransactionType type,
                               char *category,
                               char *description)
{
    Transaction t;

    t.id = id;
    t.amount = amount;
    t.type = type;

    // Safe string copying
    // We copy up to sizeof(buffer) - 1 to leave room for the null terminator
    strncpy(t.date, date, sizeof(t.date) - 1);
    t.date[sizeof(t.date) - 1] = '\0'; // Ensure it is null-terminated

    strncpy(t.category, category, sizeof(t.category) - 1);
    t.category[sizeof(t.category) - 1] = '\0';

    strncpy(t.description, description, sizeof(t.description) - 1);
    t.description[sizeof(t.description) - 1] = '\0';

    return t;
}

void print_transaction(const Transaction *t)
{
    printf("ID: %d | Date: %s | Amount: %.2f | Type: %s | Cat: %s | Desc: %s\n",
           t->id,
           t->date,
           t->amount,
           (t->type == INCOME) ? "INCOME" : "EXPENSE",
           t->category,
           t->description);
}