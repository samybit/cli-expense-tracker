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

void delete_transaction(TransactionList *list, int id)
{
    int found_index = -1;

    // 1. Search array: Find the index of the transaction with the matching ID
    for (int i = 0; i < list->count; i++)
    {
        if (list->items[i].id == id)
        {
            found_index = i;
            break;
        }
    }

    // If we finished the loop and found_index is still -1, the ID doesn't exist
    if (found_index == -1)
    {
        printf("Transaction with ID %d not found.\n", id);
        return;
    }

    // 2. Shift elements: Move everything after the found index one step to the left
    for (int i = found_index; i < list->count - 1; i++)
    {
        list->items[i] = list->items[i + 1];
    }

    // Decrease the total count since we removed an item
    list->count--;
    printf("Transaction ID %d deleted successfully.\n", id);

    // 3. Resize memory: Give memory back if we have way too much empty space.
    // We only shrink if capacity is larger than our starting size (2),
    // and we are using less than 1/4th of the allocated space.
    if (list->capacity > 2 && list->count <= list->capacity / 4)
    {
        list->capacity /= 2;

        // realloc works for shrinking too!
        list->items = (Transaction *)realloc(list->items, list->capacity * sizeof(Transaction));

        if (list->items == NULL && list->capacity > 0)
        {
            printf("Memory reallocation failed during shrink!\n");
            exit(1);
        }
    }
}

void monthly_summary(const TransactionList *list, int target_year, int target_month)
{
    double total_income = 0.0;
    double total_expense = 0.0;
    int match_count = 0;

    printf("\n--- Summary for %04d-%02d ---\n", target_year, target_month);
    printf("%-12s | %-10s | %-9s | %-15s\n", "Date", "Amount", "Type", "Category");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < list->count; i++)
    {
        Transaction *t = &list->items[i];
        int year, month, day;

        // Parse the "YYYY-MM-DD" string into integer variables
        if (sscanf(t->date, "%d-%d-%d", &year, &month, &day) == 3)
        {

            // Filter by the requested month and year
            if (year == target_year && month == target_month)
            {
                printf("%-12s | %-10.2f | %-9s | %-15s\n",
                       t->date,
                       t->amount,
                       (t->type == INCOME) ? "INCOME" : "EXPENSE",
                       t->category);

                // Calculate totals
                if (t->type == INCOME)
                {
                    total_income += t->amount;
                }
                else
                {
                    total_expense += t->amount;
                }
                match_count++;
            }
        }
    }

    if (match_count == 0)
    {
        printf("No transactions found for this month.\n");
    }
    else
    {
        printf("----------------------------------------------------\n");
        printf("Total Income:  +%.2f\n", total_income);
        printf("Total Expense: -%.2f\n", total_expense);
        printf("Net Balance:    %.2f\n", total_income - total_expense);
    }
    printf("----------------------------------------------------\n");
}

// === Sorting logic ===
// Helper function to swap two transactions in memory
void swap_transactions(Transaction *a, Transaction *b)
{
    Transaction temp = *a;
    *a = *b;
    *b = temp;
}

// The core of QuickSort: placing the pivot in its final sorted position
int partition(Transaction *arr, int low, int high, SortType sort_type)
{
    Transaction pivot = arr[high]; // Choose the last element as pivot
    int i = (low - 1);             // Index of the smaller element

    for (int j = low; j <= high - 1; j++)
    {
        int should_swap = 0;

        // Determine if current element is smaller than the pivot based on user choice
        if (sort_type == SORT_BY_AMOUNT)
        {
            if (arr[j].amount < pivot.amount)
            {
                should_swap = 1;
            }
        }
        else if (sort_type == SORT_BY_DATE)
        {
            if (strcmp(arr[j].date, pivot.date) < 0)
            {
                should_swap = 1;
            }
        }

        // If it belongs before the pivot, move the boundary and swap
        if (should_swap)
        {
            i++;
            swap_transactions(&arr[i], &arr[j]);
        }
    }
    // Place the pivot in its correct position
    swap_transactions(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// The recursive sorting engine
void quicksort(Transaction *arr, int low, int high, SortType sort_type)
{
    if (low < high)
    {
        // pi is the partitioning index, arr[pi] is now in the right place
        int pi = partition(arr, low, high, sort_type);

        // Recursively sort elements before and after partition
        quicksort(arr, low, pi - 1, sort_type);
        quicksort(arr, pi + 1, high, sort_type);
    }
}

// The public wrapper function we call from main.c
void sort_transactions(TransactionList *list, SortType sort_type)
{
    if (list->count > 1)
    {
        quicksort(list->items, 0, list->count - 1, sort_type);
        printf("Transactions sorted successfully.\n");
    }
    else
    {
        printf("Not enough transactions to sort.\n");
    }
}