#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

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
        // If the file to not exist on the very first run
        return;
    }

    int file_count = 0;

    // 1. Read the number of transactions
    if (fread(&file_count, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        return;
    }

    // 2. Ensure dynamic array has enough capacity before reading
    while (list->capacity < file_count)
    {
        list->capacity *= 2;
        list->items = (Transaction *)realloc(list->items, list->capacity * sizeof(Transaction));
        if (list->items == NULL)
        {
            printf("Memory allocation failed during load!\n");
            exit(1);
        }
    }

    // 3. Read the struct data directly into our allocated memory
    if (file_count > 0)
    {
        fread(list->items, sizeof(Transaction), file_count, file);
        list->count = file_count;
    }

    fclose(file);
    printf("Loaded %d transactions from file.\n", list->count);
}