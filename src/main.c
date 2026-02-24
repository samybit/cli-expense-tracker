#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "transaction.h"
#include "utils.h"
#include "utils.h"
#include "storage.h"

int main()
{
    TransactionList my_list;
    init_transaction_list(&my_list, 2); // Start with a small capacity to test realloc quickly

    const char *DATA_FILE = "data/transactions.dat";

    // --- LOAD ON STARTUP ---
    load_transactions(&my_list, DATA_FILE);

    // Calculate the next ID to use based on loaded data
    int current_id = 1;
    if (my_list.count > 0)
    {
        current_id = my_list.items[my_list.count - 1].id + 1;
    }

    int choice = 0;
    char buffer[10];

    while (choice != 3)
    {
        printf("\n=== Expense Tracker ===\n");
        printf("1. Add Transaction\n");
        printf("2. List Transactions\n");
        printf("3. Delete Transaction\n");
        printf("4. Exit (and Save)\n");
        printf("Choose an option: ");

        read_string(buffer, sizeof(buffer));
        choice = atoi(buffer);

        if (choice == 1)
        {
            char date[15], category[50], desc[100];
            double amount;
            int type_choice;

            printf("Enter date (YYYY-MM-DD): ");
            read_string(date, sizeof(date));

            printf("Enter amount: ");
            amount = read_double();

            printf("Enter type (0 for INCOME, 1 for EXPENSE): ");
            read_string(buffer, sizeof(buffer));
            type_choice = atoi(buffer);
            TransactionType type = (type_choice == 0) ? INCOME : EXPENSE;

            printf("Enter category (e.g., Food, Salary): ");
            read_string(category, sizeof(category));

            printf("Enter description: ");
            read_string(desc, sizeof(desc));

            Transaction new_t = create_transaction(current_id++, date, amount, type, category, desc);
            add_transaction(&my_list, new_t);
            printf("Transaction added successfully!\n");
        }
        else if (choice == 2)
        {
            print_all_transactions(&my_list);
        }
        else if (choice == 3)
        {
            printf("Enter the ID of the transaction to delete: ");
            read_string(buffer, sizeof(buffer));
            int id_to_delete = atoi(buffer);

            delete_transaction(&my_list, id_to_delete);
        }
        else if (choice != 4)
        {
            printf("Invalid choice. Please try again.\n");
        }
    }

    // --- SAVE BEFORE EXIT ---
    save_transactions(&my_list, DATA_FILE);

    // Memory cleanup
    free_transaction_list(&my_list);
    printf("Goodbye!\n");

    return 0;
}