#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "utils.h"

void save_transactions(const TransactionList *list, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error: Could not open file %s for saving.\n", filename);
        return;
    }

    // 1. Write the number of transactions first
    fwrite(&list->count, sizeof(int), 1, file);

    // 2. Write the entire array of structs in one single command
    if (list->count > 0)
    {
        fwrite(list->items, sizeof(Transaction), list->count, file);
    }

    fclose(file);
    printf("Successfully saved %d transactions.\n", list->count);
}

void load_transactions(TransactionList *list, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return;
    }

    int file_count = 0;

    // 1. Check if fread actually read 1 item successfully
    if (fread(&file_count, sizeof(int), 1, file) != 1)
    {
        fprintf(stderr, "Warning: Data file is empty or unreadable.\n");
        fclose(file);
        return;
    }

    // 2. Prevent massive memory allocations from corrupted files
    if (file_count < 0 || file_count > 100000)
    {
        fprintf(stderr, "Error: Data file is corrupted (invalid transaction count: %d).\n", file_count);
        fclose(file);
        return;
    }

    while (list->capacity < file_count)
    {
        list->capacity *= 2;
        Transaction *temp = (Transaction *)realloc(list->items, list->capacity * sizeof(Transaction));
        if (temp == NULL)
        {
            fprintf(stderr, "Critical Error: Out of memory during file load!\n");
            exit(EXIT_FAILURE);
        }
        list->items = temp;
    }

    if (file_count > 0)
    {
        // 3. Ensure the file actually contains as much data as it claims
        size_t read_items = fread(list->items, sizeof(Transaction), file_count, file);
        if (read_items != (size_t)file_count)
        {
            fprintf(stderr, "Warning: File size mismatch. Expected %d, got %zu. File may be truncated.\n", file_count, read_items);
        }
        list->count = read_items; // Only accept what we actually successfully read
    }

    fclose(file);
    printf("Loaded %d transactions from file.\n", list->count);
}

void export_to_csv(const TransactionList *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, COLOR_RED "Error: Could not open %s for exporting." COLOR_RESET "\n", filename);
        return;
    }

    // 1. Write the standard CSV header
    fprintf(file, "ID,Date,Amount,Type,Category,Description\n");

    // 2. Iterate through the array and write each row
    for (int i = 0; i < list->count; i++)
    {
        Transaction *t = &list->items[i];

        // We wrap category and description in quotes to prevent user-entered
        // commas from breaking the CSV columns.
        fprintf(file, "%d,%s,%.2f,%s,\"%s\",\"%s\"\n",
                t->id,
                t->date,
                t->amount,
                (t->type == INCOME) ? "INCOME" : "EXPENSE",
                t->category,
                t->description);
    }

    fclose(file);
    printf(COLOR_GREEN "Successfully exported %d transactions to %s" COLOR_RESET "\n", list->count, filename);
}