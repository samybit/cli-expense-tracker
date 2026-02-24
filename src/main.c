#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "transaction.h"
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

    while (choice != 7)
    {
        printf("\n" COLOR_CYAN "=== Expense Tracker ===" COLOR_RESET "\n");
        printf(COLOR_CYAN "1." COLOR_RESET " Add Transaction\n");
        printf(COLOR_CYAN "2." COLOR_RESET " List Transactions\n");
        printf(COLOR_CYAN "3." COLOR_RESET " Delete Transaction\n");
        printf(COLOR_CYAN "4." COLOR_RESET " Monthly Summary\n");
        printf(COLOR_CYAN "5." COLOR_RESET " Sort Transactions\n");
        printf(COLOR_CYAN "6." COLOR_RESET " Export to CSV\n");
        printf(COLOR_CYAN "7." COLOR_RESET " Exit (and Save)\n");

        printf(COLOR_CYAN "Choose an option: " COLOR_RESET);

        // Ensure the user enters a number
        if (!read_int(&choice))
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        read_string(buffer, sizeof(buffer));
        choice = atoi(buffer);

        if (choice == 1)
        {
            // --- ADD TRANSACTION ---
            char date[15], category[50], desc[100];
            double amount;
            int type_choice;

            printf("Enter date (YYYY-MM-DD): ");
            read_string(date, sizeof(date));

            printf("Enter amount: ");
            // Ensure the user enters a valid positive number
            while (!read_double(&amount) || amount < 0)
            {
                printf("Invalid amount. Please enter a valid positive number: ");
            }

            printf("Enter type (0 for INCOME, 1 for EXPENSE): ");
            // Ensure the user enters 0 or 1
            while (!read_int(&type_choice) || (type_choice != 0 && type_choice != 1))
            {
                printf("Invalid input. Enter 0 for INCOME or 1 for EXPENSE: ");
            }
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
            // --- LIST TRANSACTIONS ---
            print_all_transactions(&my_list);
        }
        else if (choice == 3)
        {
            // --- DELETE TRANSACTION ---
            printf("Enter the ID of the transaction to delete: ");
            read_string(buffer, sizeof(buffer));
            int id_to_delete = atoi(buffer);

            delete_transaction(&my_list, id_to_delete);
        }
        else if (choice == 4)
        {
            // --- MONTHLY SUMMARY ---
            printf("Enter Year (e.g., 2023): ");
            read_string(buffer, sizeof(buffer));
            int target_year = atoi(buffer);

            printf("Enter Month (1-12): ");
            read_string(buffer, sizeof(buffer));
            int target_month = atoi(buffer);

            monthly_summary(&my_list, target_year, target_month);
        }
        else if (choice == 5)
        {
            // --- SORTING ---
            printf("Sort by:\n");
            printf("1. Date\n");
            printf("2. Amount\n");
            printf("Choose an option: ");

            read_string(buffer, sizeof(buffer));
            int sort_choice = atoi(buffer);

            if (sort_choice == 1)
            {
                sort_transactions(&my_list, SORT_BY_DATE);
                print_all_transactions(&my_list);
            }
            else if (sort_choice == 2)
            {
                sort_transactions(&my_list, SORT_BY_AMOUNT);
                print_all_transactions(&my_list);
            }
            else
            {
                printf("Invalid sorting choice.\n");
            }
        }
        else if (choice == 6)
        {
            // --- CSV LOGIC ---
            export_to_csv(&my_list, "expense_report.csv");
        }
        else if (choice != 7)
        {
            // --- INVALID CHOICE ---
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