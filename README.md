# Super Mall Management System

## 1. Project Description

The **Super Mall Management System** is a console-based application developed using the C programming language as part of the Programming Fundamentals course at NED University.

The system manages different operations of a shopping mall, including parking management, grocery inventory, food court operations, and mall analytics.

## 2. Group Members

| No. | Student Name | Roll Number |
|---|---|---|
| 1 | Muqaddas | CT-26270 |
| 2 | Ahmed Ali | CT-26290 |
| 3 | Aleena Salman | CT-26260 |
| 4 | Syeda Rania Irfan | CT-26258 |

## 3. Features

### Parking Management
- Display parking slots.
- Park vehicles.
- Release parking slots.
- Manage parking availability.

### Grocery Management
- Add grocery items.
- Update grocery stock.
- Display grocery inventory.
- Search grocery items.
- Dynamic inventory management.

### Food Court Management
- Manage food court operations.

### Mall Analytics
- Sort brand information.
- Search for brands.
- Calculate discounts using recursion.

### Input Validation
- Validate user input.
- Handle invalid menu choices.
- Prevent incorrect data entry.

## 4. How to Compile and Run

### Requirements
- GCC Compiler
- Visual Studio Code
- C Programming Environment

### Compile

Open the terminal inside the source code folder and compile:

```bash
gcc main.c system_utils.c "parking (1).c" "manage_grocery (3).c" "floor2analytics (4).c" food_court.c -o supermall
```

### Run on Windows

```powershell
.\supermall.exe
```

### Run on Linux

```bash
./supermall
```

**Note:** Ensure the filenames match the actual files in the Source Code folder.

## 5. Sample Input and Output

### Sample Input

```text
Enter your choice: 1
```

### Sample Output

```text
================================
   SUPER MALL MANAGEMENT SYSTEM
================================

1. Parking Management
2. Grocery Management
3. Food Court Management
4. Mall Analytics
5. Exit

Enter your choice:
```

*Sample output is illustrative; actual output depends on the program.*

## 6. Programming Fundamentals Concepts Used

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
- Input Validation

## 7. Folder Structure

```text
Super-Mall-Management-C/
│
├── Flowchart/
│
├── Screenshots/
│
├── Source Code/
│   └── SuperMallSystem_new/
│       ├── main.c
│       ├── common.h
│       ├── ui.h
│       └── Other source files
│
├── CT175_CCAReport_SuperMallSystemfinal.pdf
│
└── README.md
```

## 8. Project Information

- **Project:** Super Mall Management System
- **Course:** Programming Fundamentals (PF)
- **Course Code:** CT-175
- **University:** NED University
- **Programming Language:** C
- **Interface:** Command Line Interface (CLI)
- **Compiler:** GCC
- **Project Type:** Group Project

---

Developed as part of the Programming Fundamentals course.
