#ifndef STORAGE_H
#define STORAGE_H

#include "transaction.h"

// Pass the filename so the functions are reusable
void save_transactions(const TransactionList *list, const char *filename);
void load_transactions(TransactionList *list, const char *filename);

void export_to_csv(const TransactionList *list, const char *filename);

#endif