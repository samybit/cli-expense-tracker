#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// Initialize the dynamic array
void init_transaction_list(TransactionList *list, int initial_capacity)
{
    list->capacity = initial_capacity;
    list->count = 0;
    // Allocate memory for 'initial_capacity' number of Transactions
    list->items = (Transaction *)malloc(list->capacity * sizeof(Transaction));

    if (list->items == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Exit program if we can't get memory
    }
}

// Add an item, growing the array if needed
void add_transaction(TransactionList *list, Transaction t)
{
    // Check if we need more room
    if (list->count >= list->capacity)
    {
        list->capacity *= 2; // Double the capacity
        list->items = (Transaction *)realloc(list->items, list->capacity * sizeof(Transaction));

        if (list->items == NULL)
        {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
    }

    // Add the new transaction at the current count index, then increment count
    list->items[list->count] = t;
    list->count++;
}

// Print formatted table
void print_all_transactions(const TransactionList *list)
{
    printf("\n%-5s | %-12s | %-10s | %-9s | %-15s | %-20s\n",
           "ID", "Date", "Amount", "Type", "Category", "Description");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < list->count; i++)
    {
        Transaction *t = &list->items[i];
        printf("%-5d | %-12s | %-10.2f | %-9s | %-15s | %-20s\n",
               t->id,
               t->date,
               t->amount,
               (t->type == INCOME) ? "INCOME" : "EXPENSE",
               t->category,
               t->description);
    }
    printf("----------------------------------------------------------------------------------\n");
}

// Clean up memory when done
void free_transaction_list(TransactionList *list)
{
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}