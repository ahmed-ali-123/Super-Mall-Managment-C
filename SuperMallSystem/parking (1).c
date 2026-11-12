/*Basement Parking
 * Compile with the group's files:
 *     gcc main.c system_utils.c parking.c grocery.c analytics.c -o supermall*/

#include <stdio.h>
#include "ui.h"
#define PARKING_ROWS  5
#define PARKING_COLS  8

#define PARKING_FILE  "parking.dat"
#define SLOT_FREE     0
#define SLOT_OCCUPIED 1
#define SYMBOL_FREE     "\033[92m[ ]\033[0m "
#define SYMBOL_OCCUPIED "\033[91m[X]\033[0m "
#define LEGEND_TEXT     "\033[92m[ ]\033[0m = free    \033[91m[X]\033[0m = occupied"

static int parking[PARKING_ROWS][PARKING_COLS];
//prototypes:
void initParkingGrid(void);
void displayParkingGrid(void);
int  parkVehicle(void);
int  releaseParkingSlot(void);
int  saveParkingData(void);
void parkingMenu(void);
//private helper
static int getParkingInput(const char *label, int min, int max);
 
static int getParkingInput(const char *label, int min, int max)
{
    int value;
    int result;
    int c;

    while (1) {
        printf("%s%s  ➤ %sEnter %s (%d-%d): ", C_BOLD, C_YELLOW, C_RESET, label, min, max);
        result = scanf("%d", &value);       //result is 1 if a number was read

        if (result == EOF) {
            return -1;                     
        }

        //throw away anything left on the line 
        while ((c = getchar()) != '\n' && c != EOF) {}

        if (result != 1) {
            ui_error("Invalid input. Please enter a number.\n");
        } else if (value < min || value > max) {
            ui_error("Out of range. Enter a number from %d to %d.\n", min, max);
        } else {
            return value;                   //good number: give it back 
        }
    }
}
void initParkingGrid(void)
{
    int i, j;
    int ok = 1;
    int temp[PARKING_ROWS][PARKING_COLS];
    FILE *fp = fopen(PARKING_FILE, "r");

    // Start with an empty grid. 
    for (i = 0; i < PARKING_ROWS; i++) {
        for (j = 0; j < PARKING_COLS; j++) {
            parking[i][j] = SLOT_FREE;
        }
    }

    if (fp == NULL) {
        return;                             
    }
    for (i = 0; i < PARKING_ROWS && ok; i++) {
        for (j = 0; j < PARKING_COLS && ok; j++) {
            if (fscanf(fp, "%d", &temp[i][j]) != 1 ||
                (temp[i][j] != SLOT_FREE && temp[i][j] != SLOT_OCCUPIED)) {
                ok = 0;
            }
        }
    }
    fclose(fp);

    if (ok) {
        for (i = 0; i < PARKING_ROWS; i++) {
            for (j = 0; j < PARKING_COLS; j++) {
                parking[i][j] = temp[i][j];
            }
        }
        ui_success("Parking data loaded from %s.\n", PARKING_FILE);
    } else {
        ui_warn("%s is damaged. Starting with an empty garage.\n", PARKING_FILE);
    }
}

void displayParkingGrid(void)
{
    int i, j;
    int freeCount = 0;

    ui_header("🚗  BASEMENT PARKING  🚗", C_BLUE);

    //Columns
    printf("%s      ", C_CYAN);
    for (j = 0; j < PARKING_COLS; j++) {
        printf(" C%d ", j + 1);
    }
    printf("%s", C_RESET);
    printf("\n");

    //Rows
    for (i = 0; i < PARKING_ROWS; i++) {
        printf("  %sR%d%s  ", C_CYAN, i + 1, C_RESET);
        for (j = 0; j < PARKING_COLS; j++) {
            if (parking[i][j] == SLOT_OCCUPIED) {
                printf(SYMBOL_OCCUPIED);
            } else {
                printf(SYMBOL_FREE);
                freeCount++;
            }
        }
        printf("\n");
    }

    ui_line();
    printf("  %s\n", LEGEND_TEXT);
    printf("  %sFree slots:%s %s%d%s / %d\n", C_BOLD, C_RESET, C_GREEN, freeCount, C_RESET, PARKING_ROWS * PARKING_COLS);
}
int parkVehicle(void)
{
    int row, col;

    displayParkingGrid();
    row = getParkingInput("row", 1, PARKING_ROWS);
    if (row == -1) return 0;
    col = getParkingInput("column", 1, PARKING_COLS);
    if (col == -1) return 0;

    if (parking[row - 1][col - 1] == SLOT_OCCUPIED) {
        ui_error("Slot R%d-C%d is already occupied.\n", row, col);
        return 0;
    }

    parking[row - 1][col - 1] = SLOT_OCCUPIED;
    ui_success("Vehicle parked at slot R%d-C%d.\n", row, col);
     saveParkingData();
    return 1;
}
int releaseParkingSlot(void)
{
    int row, col;

    displayParkingGrid();
    row = getParkingInput("row", 1, PARKING_ROWS);
    if (row == -1) return 0;
    col = getParkingInput("column", 1, PARKING_COLS);
    if (col == -1) return 0;

    if (parking[row - 1][col - 1] == SLOT_FREE) {
        ui_warn("Slot R%d-C%d is already empty.\n", row, col);
        return 0;
    }

    parking[row - 1][col - 1] = SLOT_FREE;
    ui_success("Slot R%d-C%d released.\n", row, col);
    saveParkingData();
    return 1;
}
int saveParkingData(void)
{
    int i, j;
    FILE *fp = fopen(PARKING_FILE, "w");

    if (fp == NULL) {
        ui_error("Could not save parking data to %s.\n", PARKING_FILE);
        return 0;
    }

    for (i = 0; i < PARKING_ROWS; i++) {
        for (j = 0; j < PARKING_COLS; j++) {
            fprintf(fp, "%d ", parking[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 1;
}

void parkingMenu(void)
{
    int choice = 0;

    initParkingGrid();

    do {
        ui_header("🚗  BASEMENT PARKING MENU", C_BLUE);
        ui_item(1, "View parking grid", C_BLUE);
        ui_item(2, "Park a vehicle",    C_GREEN);
        ui_item(3, "Release a slot",    C_YELLOW);
        ui_item(4, "Back to main menu", C_RED);
        ui_line();

        choice = getParkingInput("choice", 1, 4);
        if (choice == -1) {
            choice = 4;          //input ended: leave safely
        }

        switch (choice) {
        case 1:
            displayParkingGrid();
            break;
        case 2:
            parkVehicle();
            break;
        case 3:
            releaseParkingSlot();
            break;
        case 4:
            ui_info("Returning to main menu...\n");
            break;
        }
    } while (choice != 4);
}
