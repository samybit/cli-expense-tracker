# Terminal Expense Tracker 📊
[![C/C++ CI with Make](https://github.com/samybit/cli-expense-tracker/actions/workflows/make.yml/badge.svg)](https://github.com/samybit/cli-expense-tracker/actions/workflows/make.yml)

A robust, memory-safe command-line personal finance manager written entirely in C. 

This project was built to demonstrate core computer science principles, including manual dynamic memory management, defensive programming, and binary file I/O operations.

## ✨ Features

* **Dynamic Memory Allocation:** Uses `malloc` and `realloc` to scale the transaction list infinitely while shrinking arrays upon deletion to conserve RAM.
* **Defensive Programming:** Strict input validation utilizing `strtol` and `strtod` to prevent crashes from invalid data types, alongside safeguards against corrupted binary data files.
* **Binary File Persistence:** Fast, automated saving and loading of structs directly to/from disk using `fwrite` and `fread`.
* **Custom QuickSort:** Manually implemented recursive QuickSort algorithm to order transactions by date or amount.
* **Data Analysis:** Generates calculated monthly summaries isolating net balances.

## 🛠️ Project Structure

```text
cli-expense-tracker/
├── .github/
│   └── workflows/
│       └── make.yml         # "C/C++ CI with Make" workflow
├── src/
│   ├── main.c               # Application loop and interactive menu
│   ├── transaction.c        # Data models, QuickSort, and array management
│   ├── storage.c            # Binary File I/O operations
│   └── utils.c              # Safe string parsing and validation wrappers
├── data/
│   └── transactions.dat     # Auto-generated binary storage file
└── Makefile                 # Compilation instructions
```

## 🚀 Compilation & Installation

**Prerequisites:** You must have a C compiler (like `gcc`) and `make` installed on your system.

1. Clone the repository:
   ```bash
   git clone https://github.com/samybit/cli-expense-tracker.git
   cd cli-expense-tracker
   ```

2. Compile the project using the provided Makefile:
   ```bash
   make
   ```

3. Run the executable:
   ```bash
   ./expense_tracker
   ```

## 💻 Usage Examples

Upon running `./expense_tracker`, you will be greeted with an interactive terminal menu.

**Adding a Transaction:**
```text
Choose an option: 1
Enter date (YYYY-MM-DD): 2026-02-24
Enter amount: 150.50
Enter type (0 for INCOME, 1 for EXPENSE): 1
Enter category: Groceries
Enter description: Weekly food shopping
Transaction added successfully!
```

**Viewing the Monthly Summary:**
```text
Choose an option: 4
Enter Year (e.g., 2023): 2026
Enter Month (1-12): 2

--- Summary for 2026-02 ---
Date         | Amount     | Type      | Category       
----------------------------------------------------
2026-02-24   | 150.50     | EXPENSE   | Groceries      
----------------------------------------------------
Total Income:  +0.00
Total Expense: -150.50
Net Balance:    -150.50
----------------------------------------------------
```

## 🧹 Cleanup
To remove the compiled object files and the executable, run:
```bash
make clean
```
*(Note: This will not delete your saved `transactions.dat` data file).*
