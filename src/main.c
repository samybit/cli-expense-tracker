#include <stdio.h>
#include "transaction.h"

int main()
{
    printf("--- Expense Tracker Debug ---\n");

    // Manually create a transaction to test our struct
    Transaction t1 = create_transaction(1, "2023-10-01", 150.50, EXPENSE, "Food", "Groceries at market");
    Transaction t2 = create_transaction(2, "2023-10-02", 2000.00, INCOME, "Salary", "October Paycheck");

    // Print them out
    print_transaction(&t1);
    print_transaction(&t2);

    return 0;
}