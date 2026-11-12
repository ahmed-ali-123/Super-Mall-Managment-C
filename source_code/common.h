#ifndef COMMON_H
#define COMMON_H


// 1. SHARED STRUCTURES

typedef struct {
    int id;
    char name[50];       
    float price;
    int stock;

} GroceryItem;

typedef struct {
    int id;
    char name[50];  
    float price;
    float stock;
} clothingItem;


// 2. FUNCTIONS


// --- Member 1: System Utilities  ---
int getValidInt(char *prompt);
float getValidFloat(char *prompt);
void saveSystemData(void);
void loadSystemData(void);

 //---for floor 3
 void floor3Menu();


// --- Member 2: Basement Parking Functions ---
void parkingMenu(void);

// --- Member 3: Floor 1 Grocery Functions ---
void Grocery_Menu(void);

 
// --- Member 4: Analytics Desk Functions ---
//---for floor 2
void runfloor2(void);
 


#endif
