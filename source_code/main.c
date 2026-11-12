#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "ui.h"

void displayMainMenu(void) {
    ui_header("🏬  SUPER MALL MANAGEMENT SYSTEM  🏬", C_CYAN);
    printf("%s  Main Menu%s\n", C_GRAY, C_RESET);
    ui_line();
    ui_item(1, "🚗  Basement Parking System",        C_BLUE);
    ui_item(2, "🛒  Floor 1: Grocery Department",    C_GREEN);
    ui_item(3, "👕  Floor 2: Clothing & Categories", C_MAGENTA);
    ui_item(4, "🍔  Floor 3: Food Court",            C_YELLOW);
    ui_item(5, "⚙   System Settings / Save & Load",  C_CYAN);
    ui_item(6, "🚪  Exit System",                    C_RED);
    ui_line();
}

int main(void) {
    int choice = 0;

    ui_init();
    ui_clear();
    loadSystemData();

    while (1) {
        displayMainMenu();
        choice = getValidInt(UI_PROMPT("Enter your choice (1-6): "));

        switch (choice) {
            case 1:
                ui_info("Directing to Basement Parking...\n");
                parkingMenu();
                break;
            case 2:
                ui_info("Directing to Grocery Department...\n");
                Grocery_Menu();
                break;
            case 3:
                ui_info("Directing to Floor 2 & Categories...\n");
                runfloor2();
                break;
            case 4:
                ui_info("Directing to Floor 3: Food Court...\n");
                floor3Menu();
                break;
            case 5:
                ui_section("System Settings", C_CYAN);
                saveSystemData();
                break;
            case 6:
                saveSystemData();
                printf("\n%s%s  Thank you for visiting Super Mall. Goodbye! 👋%s\n\n",
                       C_BOLD, C_CYAN, C_RESET);
                return 0;
            default:
                ui_error("Invalid selection! Please enter a number between 1 and 6.\n");
                break;
        }
    }
    return 0;
}
