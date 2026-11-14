# Super Mall Management System

## Project Description
The Super Mall Management System is a console-based application developed using the C programming language for the Programming Fundamentals course. It manages parking, grocery inventory, food court operations, and mall analytics.

## Group Members:
1	Muqaddas	CT-26270
2	Aleena Salman	CT-26260
3	Ahmed Ali	CT-26290
4	Syeda Rania Irfan	CT-26258

## Features
- Parking management
- Grocery inventory management
- Add, update, search, and display grocery items
- Food court management
- Mall analytics
- Input validation

## How to Compile and Run

### Compile

```bash
gcc main.c system_utils.c "parking (1).c" "manage_grocery (3).c" "floor2analytics (4).c" food_court.c -o supermall
```

### Run on Windows

```powershell
.\supermall.exe
```

## Sample Input and Output

### Sample Input
```text
Enter your choice: 1
```

### Sample Output
```text
SUPER MALL MANAGEMENT SYSTEM

1. Parking Management
2. Grocery Management
3. Food Court Management
4. Mall Analytics
5. Exit

Enter your choice:
```

## PF Concepts Used

- Variables and Data Types
- Conditional Statements
- Loops
- Functions
- Arrays
- Structures
- Pointers
- Dynamic Memory Allocation (malloc, realloc, free)
- Recursion
- Searching and Sorting

## Folder Structure
```text
Super-Mall-Management-C/
│
├── README.md
└── source_code/
    ├── main.c
    ├── common.h
    ├── ui.h
    ├── system_utils.c
    ├── parking (1).c
    ├── manage_grocery (3).c
    ├── floor2analytics (4).c
    └── food_court.c
```

## Project Information

- Course: Programming Fundamentals
- Language: C
- Interface: Command Line Interface (CLI)
- Compiler: GCC

Developed as a group project.
