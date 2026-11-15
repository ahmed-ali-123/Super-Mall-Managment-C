#include <stdio.h>
#include "common.h"
#include "ui.h"

void floor3Menu(void) {
    int mainChoice = 0;

    do {
        ui_header("🍔  FLOOR 3 : FOOD COURT  🍕", C_YELLOW);
        ui_item(1, "Place a Snack Order",         C_YELLOW);
        ui_item(2, "Back to Super Mall Main Menu", C_RED);
        ui_line();

        mainChoice = getValidInt(UI_PROMPT("Enter your choice (1-2): "));

        switch (mainChoice) {
            case 1: {
                int snackTypes, quantity, i;
                char choice;
                float totalBill = 0.0;

                ui_section("RESTAURANT MENU", C_YELLOW);
                printf("  %s%sB%s  Burger         %sRs. 200%s\n", C_BOLD, C_YELLOW, C_RESET, C_GREEN, C_RESET);
                printf("  %s%sF%s  French Fries   %sRs. 50%s\n",  C_BOLD, C_YELLOW, C_RESET, C_GREEN, C_RESET);
                printf("  %s%sP%s  Pizza          %sRs. 500%s\n", C_BOLD, C_YELLOW, C_RESET, C_GREEN, C_RESET);
                printf("  %s%sS%s  Sandwiches     %sRs. 150%s\n", C_BOLD, C_YELLOW, C_RESET, C_GREEN, C_RESET);
                ui_line();

                snackTypes = getValidInt(UI_PROMPT("How many types of snacks (1-4)? "));

                if (snackTypes < 1 || snackTypes > 4) {
                    ui_error("Invalid number of items! Choose between 1 and 4 types.\n");
                    break;
                }

                for (i = 1; i <= snackTypes; i++) {
                    printf("\n%s%s  Item %d%s\n", C_BOLD, C_CYAN, i, C_RESET);
                    printf("%s", UI_PROMPT("Choice (B/F/P/S): "));
                    if (scanf(" %c", &choice) != 1) {
                        ui_error("Input ended. Returning to menu.\n");
                        return;
                    }
                    { int c; while ((c = getchar()) != '\n' && c != EOF) { } }

                    quantity = getValidInt(UI_PROMPT("Enter Quantity: "));

                    if (quantity <= 0) {
                        ui_warn("Invalid quantity! Skipping this item.\n");
                        continue;
                    }

                    switch (choice) {
                        case 'B': case 'b':
                            totalBill += 200 * quantity;
                            ui_success("Added: %d x Burger = Rs. %d\n", quantity, 200 * quantity);
                            break;
                        case 'F': case 'f':
                            totalBill += 50 * quantity;
                            ui_success("Added: %d x French Fries = Rs. %d\n", quantity, 50 * quantity);
                            break;
                        case 'P': case 'p':
                            totalBill += 500 * quantity;
                            ui_success("Added: %d x Pizza = Rs. %d\n", quantity, 500 * quantity);
                            break;
                        case 'S': case 's':
                            totalBill += 150 * quantity;
                            ui_success("Added: %d x Sandwiches = Rs. %d\n", quantity, 150 * quantity);
                            break;
                        default:
                            ui_error("Invalid choice! Item not added to order.\n");
                            break;
                    }
                }

                ui_line();
                printf("  %s%sTOTAL CHARGES:%s %s%sRs. %.2f%s\n",
                       C_BOLD, C_WHITE, C_RESET, C_BOLD, C_GREEN, totalBill, C_RESET);
                ui_line();
                break;
            }

            case 2:
                ui_info("Returning to Super Mall Main Menu...\n");
                break;

            default:
                ui_error("Invalid selection! Please enter 1 or 2.\n");
                break;
        }
    } while (mainChoice != 2);
}
