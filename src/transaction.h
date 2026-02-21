#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>

// 1. Define the type of transaction
typedef enum
{
    INCOME,
    EXPENSE
} TransactionType;

// 2. Define the Transaction struct
typedef struct
{
    int id;                // Unique ID for finding/deleting
    char date[11];         // "YYYY-MM-DD" + null terminator = 11 bytes
    double amount;         // double is standard for simple math, though not perfect for finance
    TransactionType type;  // INCOME or EXPENSE
    char category[50];     // e.g., "Food", "Salary" Max 49 chars
    char description[100]; // Description of the transaction
} Transaction;

// 3. Define a container for our dynamic array
typedef struct
{
    Transaction *items; // Pointer to the first transaction in memory
    int count;          // How many transactions we currently have
    int capacity;       // How many we have allocated memory for
} TransactionList;

// Function Prototypes - Promises that we will implement these in .c file
Transaction create_transaction(int id,
                               char *date,
                               double amount,
                               TransactionType type,
                               char *category,
                               char *description);

void print_transaction(const Transaction *t);

#endif