#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "ui.h"

//GLOBAL VARIABLES
int cartID[15];
int cartQuantity[15];
int cartCount=0;
//categories ---MEN---WOMEN---KIDS---
clothingItem men[5] = {
    {4,"Shirt",1200,10},
    {2,"Jeans",2500,10},
    {1,"Hoodie",3000,10},
    {3,"Shirt",1800,10},
    {5,"Jacket",4000,10}
};
clothingItem women[5] = {
    {8,"Shirt",1200,10},
    {7,"Dress",3500,10},
    {10,"Jeans",2200,10},
    {6,"Kurti",1500,10},
    {9,"Scarf",1800,10}
};
clothingItem kids[5] = {
    {13,"Jeans",1200,10},
    {12,"Hoodie",2000,10},
    {15,"T-Shirt",800,10},
    {11,"Jacket",2500,10},
    {14,"Frocks",2000,10}
};
//INPUT VALIDATION FUNCTION
int getValidChoice(int min, int max) {
    int choice;
    while (1){
    printf("\n%s%s  ➤ %sEnter your choice (%d-%d): ", C_BOLD, C_YELLOW, C_RESET, min, max);
    int r = scanf("%d", &choice);
    if (r == EOF){
        ui_error("\nInput ended. Exiting.\n");
        exit(1);
    }
    if (r != 1){
        ui_error("Invalid input!\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF){
        // Discard invalid characters from the input buffer
        }
    }
    else if (choice < min || choice > max){
        ui_error("Out of range! Please try again\n");
    }
    else{
        return choice;
    }
}
}
// DISPLAYING FUNCTION FOR ALL THREE CATEGORIES
void f2DisplayItems(clothingItem items[], int size, char category[])
{
    char title[40];
    snprintf(title, sizeof(title), "%s CATEGORY", category);
    ui_section(title, C_MAGENTA);
    printf("%s%s%-6s %-14s %-12s %-8s%s\n", C_BOLD, C_CYAN, "ID", "ITEM", "PRICE", "STOCK", C_RESET);
    ui_line();
    for (int i = 0; i < size; i++){
        printf("%-6d %-14s %-12.2f %s%-8d%s\n",
               items[i].id,
               items[i].name,
               items[i].price,
               items[i].stock == 0 ? C_RED : (items[i].stock <= 3 ? C_YELLOW : C_GREEN),
               items[i].stock, C_RESET);
    }
    ui_line();
}
//BUBBLE SORTING FUNCTION
void f2SortItems(clothingItem items[], int size)
{
    clothingItem temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (items[j].id > items[j + 1].id)
            {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}
//BINARY SEARCH FUNCTION
int f2SearchItemById(clothingItem items[], int low, int high, int id)
{
    if (low > high)
    {
        return -1;
    }
    int mid = (low + high) / 2;

    if (items[mid].id == id)
    {
        return mid;
    }
    else if (id < items[mid].id){
        return f2SearchItemById(items, low, mid - 1, id);
    }
    else
    {
        return f2SearchItemById(items, mid + 1, high, id);
    }
}
void runfloor2() {
    int choice;
    int category=0;
    int subChoice;
    //ENTERING SECOND FLOOR
    ui_header("👕  FLOOR 2 : CLOTHING SHOP  👗", C_MAGENTA);
do{
    ui_section("MAIN MENU", C_MAGENTA);
    ui_item(1, "Men Category",       C_BLUE);
    ui_item(2, "Women Category",     C_MAGENTA);
    ui_item(3, "Kids Category",      C_YELLOW);
    ui_item(4, "Exit The Shop",      C_RED);
    choice=getValidChoice(1,4);
    switch (choice)
    {
    case 1:
        f2DisplayItems(men,5,"MEN");
        category=1;
        break;
    case 2:
        f2DisplayItems(women,5,"WOMEN");
        category=2;
        break;
    case 3:
        f2DisplayItems(kids,5,"KIDS");
        category=3;
        break; 
    default:
    ui_info("Exiting shop. Thanks for visiting!\n");
        break;
    }
    
    if(choice>=1 && choice<=3) {
    do {
    ui_section("SUB MENU", C_CYAN);
    ui_item(1, "Sort Items By ID",                  C_CYAN);
    ui_item(2, "Search Item By ID And Add To Cart", C_GREEN);
    ui_item(3, "View Cart And Checkout",            C_YELLOW);
    ui_item(4, "Go Back To Main Menu",              C_RED);
    subChoice = getValidChoice(1, 4);
    
switch (subChoice) {
            case 1:
                if (category == 1) {
                    f2SortItems(men,5);
                    f2DisplayItems(men,5,"MEN");
                } 
                else if (category == 2) {
                    f2SortItems(women,5);
                    f2DisplayItems(women,5,"WOMEN");
                }
                else if (category == 3) {
                    f2SortItems(kids,5);
                    f2DisplayItems(kids,5,"KIDS");
                }
            break;
            case 2:
            {
                int id, index, quantity;
                if (category == 1){
                    f2SortItems(men, 5);
                }
                else if (category == 2){
                    f2SortItems(women, 5);
                }
                else if (category == 3)
                {
                    f2SortItems(kids, 5);
                }
                do{
                    printf("\n%s  Enter item ID (1-15) or 16 to exit%s", C_CYAN, C_RESET);
                    id = getValidChoice(1, 16);
                    if (id != 16){
                        index = -1;
                        if (category == 1){
                            index = f2SearchItemById(men, 0, 4, id);
                            if (index != -1){
                                ui_success("Item Found!\n");
                                printf("Name: %s\n", men[index].name);
                                printf("Price: %.2f\n", men[index].price);
                                printf("Stock: %d\n", men[index].stock);
                                printf("%s  Enter quantity%s", C_CYAN, C_RESET);
                                quantity = getValidChoice(1, 10);
                                if (quantity <= men[index].stock){
                                    if (cartCount < 15){
                                        cartID[cartCount] = men[index].id;
                                        cartQuantity[cartCount] = quantity;
                                        cartCount++;
                                        men[index].stock -= quantity;
                                        ui_success("Item added to cart!\n");
                                    }
                                    else{
                                        ui_error("Cart is full!\n");
                                    }
                                }
                                else{
                                    ui_error("Not enough stock!\n");
                                }
                            }
                        }
                        else if (category == 2){
                            index = f2SearchItemById(women, 0, 4, id);
                            if (index != -1){
                            ui_success("Item Found!\n");
                            printf("Name: %s\n", women[index].name);
                            printf("Price: %.2f\n", women[index].price);
                            printf("Stock: %d\n", women[index].stock);
                            printf("%s  Enter quantity%s", C_CYAN, C_RESET);
                            quantity = getValidChoice(1, 10);
                            if (quantity <= women[index].stock){
                                if (cartCount < 15){
                                    cartID[cartCount] = women[index].id;
                                    cartQuantity[cartCount] = quantity;
                                    cartCount++;
                                    women[index].stock -= quantity;
                                    ui_success("Item added to cart!\n");
                                }
                                else{
                                    ui_error("Cart is full!\n");
                                }
                            }
                            else{
                                ui_error("Not enough stock!\n");
                            }
                        }
                    }
                    else if (category == 3){
                        index = f2SearchItemById(kids, 0, 4, id);
                        if (index != -1){
                            ui_success("Item Found!\n");
                            printf("Name: %s\n", kids[index].name);
                            printf("Price: %.2f\n", kids[index].price);
                            printf("Stock: %d\n", kids[index].stock);
                            printf("%s  Enter quantity%s", C_CYAN, C_RESET);
                            quantity = getValidChoice(1, 10);
                            if (quantity <= kids[index].stock){
                                if (cartCount < 15){
                                    cartID[cartCount] = kids[index].id;
                                    cartQuantity[cartCount] = quantity;
                                    cartCount++;
                                    kids[index].stock -= quantity;
                                    ui_success("Item added to cart!\n");
                                }
                                else{
                                    ui_error("Cart is full!\n");
                                }
                            }
                            else{
                                ui_error("Not enough stock!\n");
                            }
                        }
                    }
                    if (index == -1){
                        ui_error("Item not found!\n");
                    }
                }
            } while (id != 16);
            ui_info("Done searching.\n");
            break;
        }
            case 3:
            {
                int i, j,checkoutChoice;
                float total = 0;
                if (cartCount == 0){
                    ui_warn("Your cart is empty!\n");
                    break;
                }
                else{
                    ui_section("YOUR CART", C_YELLOW);
                    for (i = 0; i < cartCount; i++){
                        for (j = 0; j < 5; j++){
                            if (cartID[i] == men[j].id){
                                printf("\n  %sItem:%s %s   %sPrice:%s %.2f   %sQty:%s %d   %sSubtotal:%s %.2f\n", C_BOLD, C_RESET, men[j].name, C_BOLD, C_RESET, men[j].price, C_BOLD, C_RESET, cartQuantity[i], C_BOLD, C_RESET, men[j].price * cartQuantity[i]);
                                total += men[j].price * cartQuantity[i];
                            }
                        }
                        for (j = 0; j < 5; j++){
                            if (cartID[i] == women[j].id){
                                printf("\n  %sItem:%s %s   %sPrice:%s %.2f   %sQty:%s %d   %sSubtotal:%s %.2f\n", C_BOLD, C_RESET, women[j].name, C_BOLD, C_RESET, women[j].price, C_BOLD, C_RESET, cartQuantity[i], C_BOLD, C_RESET, women[j].price * cartQuantity[i]);
                                total += women[j].price * cartQuantity[i];
                            }
                        }
                        for (j = 0; j < 5; j++){
                            if (cartID[i] == kids[j].id){
                                printf("\n  %sItem:%s %s   %sPrice:%s %.2f   %sQty:%s %d   %sSubtotal:%s %.2f\n", C_BOLD, C_RESET, kids[j].name, C_BOLD, C_RESET, kids[j].price, C_BOLD, C_RESET, cartQuantity[i], C_BOLD, C_RESET, kids[j].price * cartQuantity[i]);
                                total += kids[j].price * cartQuantity[i];
                            }
                        }
                    }
                    ui_line();
                    printf("  %s%sGRAND TOTAL: %.2f%s\n", C_BOLD, C_GREEN, total, C_RESET);

                }
                ui_section("CHECKOUT", C_YELLOW);
                ui_item(1, "CONFIRM PURCHASE", C_GREEN);
                ui_item(2, "CANCEL PURCHASE",  C_RED);
                checkoutChoice = getValidChoice(1,2);
                if(checkoutChoice==1){
                    ui_success("Purchase confirmed! Thank you for shopping.\n");
                    cartCount=0;
                }
                else{
                    ui_warn("Purchase cancelled!\n");
                }
                break;
              
            }
            case 4:
            ui_info("Returning to main menu...\n");
            break;
        }
}while(subChoice != 4);
}
}while(choice!=4);


 return;
}
