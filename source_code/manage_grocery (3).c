#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ui.h"
void Grocery_Menu(void);
void Manage_GroceryItem(void);
void Update_GroceryStock(void);
void Display_GroceryItem(void);
void Search_GroceryItem(void); 
void Reset_GroceryItem(void);   
int *groc_ID = NULL ,*groc_Quantity= NULL;
char (*groc_Name)[50] = NULL;
float *groc_Price= NULL;
int count=0,capacity=0;
	
void Grocery_Menu(void)
{   
    int option;
    do{
	ui_header("🛒  FLOOR 1 : GROCERY DEPARTMENT", C_GREEN);
    ui_item(1, "Manage Grocery Items",      C_GREEN);
    ui_item(2, "Update Grocery Stock",      C_GREEN);
    ui_item(3, "Display Grocery Inventory", C_CYAN);
    ui_item(4, "Search Grocery Item",       C_CYAN);
    ui_item(5, "Reset Grocery Items",       C_YELLOW);
    ui_item(6, "Exit to main menu",         C_RED);
    ui_line();
    printf(UI_PROMPT("Enter your choice (1-6): "));
    scanf("%d",&option);
    switch(option)
	{
    	case 1 : {
		         Manage_GroceryItem();
    	         break;
    	         }
    	case 2 : {
    		     Update_GroceryStock();
			     break;
		         }
		case 3 : {
			     Display_GroceryItem();
			     break;
		         }
        case 4 : {
        	     Search_GroceryItem(); 
			     break;
		         }
	    case 5:  {
	    	     Reset_GroceryItem();
			     break;
		         } 
		case 6 : {
			      ui_info("Returning to main menu...\n");
			      break;
		         }
	}    	
	}while(option!=6);
}

void Manage_GroceryItem(void)
{

      int choice,g_id,g_quantity,i,dup=0;
      char g_name[50];
      float g_price;
    do
	{
      ui_section("Manage Grocery Items", C_GREEN);
      ui_item(1, "Add an item",    C_GREEN);
      ui_item(2, "Remove an item", C_YELLOW);
      ui_item(3, "Go back",        C_RED);
      printf(UI_PROMPT("Enter your choice: "));
      scanf("%d",&choice);
      switch (choice)
      {
	    case 1 :
		{
			dup=0;
      	    printf(UI_PROMPT("Enter an item id: "));
      	    scanf("%d",&g_id);
      	    for(i=0;i<count;i++)
      	    {
      		   if(groc_ID[i] == g_id)
      		   {
      		     dup=1;
      		     break;
		       }
	        }
	        if(dup)
	         {
	         	ui_error("ID already exists!\n");
	         	break;
			 }
		printf(UI_PROMPT("Enter item name: "));
		scanf("%s",&g_name);
		printf(UI_PROMPT("Enter item quantity: "));
		scanf("%d",&g_quantity);
		printf(UI_PROMPT("Enter item price: "));
		scanf("%f",&g_price);
		if(g_id <= 0 || g_price < 0 || g_quantity < 0)
		{
			ui_error("Invalid input!\n");
			break;
		}
		int newcap;
		//condition for checking space
		if(capacity == 0)
		 newcap=2;
		else
		{newcap=2*capacity;}
		//memory allocation of new variables
		int *newid = malloc(newcap * sizeof(int));
        int *newquantity = malloc(newcap * sizeof(int));
        char (*newname)[50] = malloc(newcap * sizeof(*newname));
        float *newprice = malloc(newcap * sizeof(float)); 
		//addition of memory
		newid=realloc(groc_ID,newcap*sizeof(int));
		groc_ID=newid;
		newname=realloc(groc_Name,newcap*sizeof(*groc_Name));
		groc_Name=newname;
		newquantity=realloc(groc_Quantity,newcap*sizeof(int));
		groc_Quantity=newquantity;
		newprice=realloc(groc_Price,newcap*sizeof(float));
		groc_Price=newprice;
		//saving the input
		groc_ID[count] = g_id;
		for(i=0;i<50;i++)
		{
			groc_Name[count][i]=g_name[i];
			if(g_name[i]=='\0')
			break;
		}
		groc_Price[count]= g_price;
		groc_Quantity[count]=g_quantity;
		count=count+1;
		ui_success("Grocery item added successfully\n");
	    break;
		}
	    case 2 :
	    	{
	    		int index=-1,j;
	    		printf(UI_PROMPT("Enter item ID to remove: "));
	    		scanf("%d",&g_id);
	    		for(i=0;i<count;i++)
	    		{
	    			if(groc_ID[i] == g_id)
	    			{
					 index=i;
	    			 break;
	    		    }
				}
				if(index == -1)
				{
				 ui_error("Item does not exist\n");
				 break;
				}
				for(i=index;i<count-1;i++)
				{
					groc_ID[i]=groc_ID[i+1];
					groc_Quantity[i]=groc_Quantity[i+1];
					groc_Price[i]=groc_Price[i+1];
					for(j=0;j<50;j++)
					{
						groc_Name[i][j]=groc_Name[i+1][j];
					}
				}
				ui_success("Grocery item removed successfully\n");
				count=count-1;
				break;
			}
		case 3 : {
			      break;
		         }
		default : ui_error("Invalid option entered\n");
		          break;
	   }
	}while(choice != 3);
}

void Update_GroceryStock(void)
{
	int g_id,index,choice,quantity,i;
	do
	{
	    index=-1;
		printf(UI_PROMPT("Enter Item ID: "));
		scanf("%d",&g_id);
		if(g_id <= 0)
		{
			ui_error("Invalid ID input\n");
			break;
		}
		for(i=0;i<count;i++)
		{
			if(groc_ID[i]==g_id)
			{
				index=i;
				break;
			}
		}
		
        if (index==-1)
        {
         int back;
         ui_error("Grocery not found!\n");
         ui_item(1, "Try another ID", C_GREEN);
         ui_item(2, "Go back to menu", C_RED);
         printf(UI_PROMPT("Enter choice: "));
         scanf("%d", &back);
         if (back==1)
         break;
         else if (back==2)
         continue;
         else
         {
          ui_error("Invalid choice!\n");
          break;
          }
        }
		else
		{
		 ui_section("Update Stock", C_GREEN);
		 printf("  %sItem Name:%s %s\n", C_BOLD, C_RESET, groc_Name[index]);
         printf("  %sCurrent Quantity:%s %s%d%s\n", C_BOLD, C_RESET, C_CYAN, groc_Quantity[index], C_RESET);
         printf("\n");
         ui_item(1, "Add Stock",    C_GREEN);
         ui_item(2, "Reduce Stock", C_YELLOW);
         ui_item(3, "Go back",      C_RED);
         printf(UI_PROMPT("Enter your choice: "));
         scanf("%d",&choice);
         switch(choice)
         {
         	case 1:{
			
                    printf(UI_PROMPT("Enter quantity to add: "));
                    scanf("%d", &quantity); 
                    if(quantity <=0)
                    {
                     ui_error("Enter a positive quantity!\n");
                     break;
                    }
                    groc_Quantity[index]+=quantity;
                    ui_success("Stock added successfully!\n");
                    break;
                   }
            case 2 :{
				    printf(UI_PROMPT("Enter quantity to reduce: "));
                    scanf("%d", &quantity); 
                    if(quantity <=0)
                    {
                     ui_error("Enter a positive quantity!\n");
                     break;
                    }
                    if (quantity>groc_Quantity[index])
                    {
                        ui_error("Insufficient stock!\n");
                        break;
                    }
                    groc_Quantity[index] -= quantity;
                    ui_success("Stock reduced successfully!\n");
                    break;
                    }
            case 3 :{
                    ui_info("Returning to menu...\n");                 
				    break;
			        }
		}
		}	
	}while(choice != 3);
}

void Display_GroceryItem(void)
{
    int i,total_Quantity,choice;
    do
    {
        total_Quantity=0;
        if (count == 0)
        {
            ui_warn("Grocery inventory is empty!\n");
        }
        else
        {
            ui_section("GROCERY INVENTORY", C_GREEN);
            printf("%s%s%-10s %-20s %-10s %-12s %-15s%s\n", C_BOLD, C_CYAN, "ID", "Name", "Quantity", "Price", "Status", C_RESET);
            ui_line();
            for (i = 0; i < count; i++)
            {
                printf("%-10d %-20s %-10d %-12.2f ",
                       groc_ID[i],
                       groc_Name[i],
                       groc_Quantity[i],
                       groc_Price[i]);
                if (groc_Quantity[i] == 0)
                    printf("%s%-15s%s\n", C_RED, "Out of Stock", C_RESET);
                else if (groc_Quantity[i] <= 5)
                    printf("%s%-15s%s\n", C_YELLOW, "Low Stock", C_RESET);
                else
                    printf("%s%-15s%s\n", C_GREEN, "Available", C_RESET);
                total_Quantity += groc_Quantity[i];
            }
            ui_line();
            printf("  %sTotal grocery items:%s %d\n", C_BOLD, C_RESET, count);
            printf("  %sTotal quantity in stock:%s %d\n", C_BOLD, C_RESET, total_Quantity);
        }      
    do
    {
           printf("\n");
           ui_item(1, "Display Inventory Again", C_GREEN);
           ui_item(2, "Back to menu",            C_RED);
           printf(UI_PROMPT("Enter your choice: "));
           if (scanf("%d", &choice) != 1)
           {
             ui_error("Invalid input!\n");
             return;
           }
           if (choice != 1 && choice != 2)
           {
            ui_error("Invalid option! Please enter 1 or 2.\n");
           }
           } while (choice != 1 && choice != 2);
    }while(choice == 1);
}
void Search_GroceryItem(void)
{
    int id,index,i,choice;
    do
    {
        index=-1;
        printf(UI_PROMPT("Enter grocery item ID: "));
        scanf("%d",&id);
        if(id <= 0)
        {
         ui_error("Invalid ID input!\n");
         return ;
        }
        for (i = 0;i<count;i++)
        {
            if (groc_ID[i]==id)
            {
                index=i;
                break;
            }
        }
        if (index==-1)
        {
         int back;
         ui_error("Grocery not found!\n");
         break;
        }
        {
            ui_section("Item Found", C_GREEN);
            printf("  %sItem ID:%s         %d\n",C_BOLD, C_RESET, groc_ID[index]);
            printf("  %sItem Name:%s       %s\n",C_BOLD,C_RESET,groc_Name[index]);
            printf("  %sQuantity:%s        %d\n",C_BOLD,C_RESET,groc_Quantity[index]);
            printf("  %sPrice per item:%s  %.2f\n",C_BOLD,C_RESET,groc_Price[index]);
            printf("  %sTotal value:%s     %s%.2f%s\n",C_BOLD,C_RESET,C_GREEN,groc_Quantity[index]*groc_Price[index],C_RESET);
        }
         do
        {
            printf("\n");
            ui_item(1, "Search Another Item", C_GREEN);
            ui_item(2, "Back to menu",        C_RED);
            printf(UI_PROMPT("Enter your choice: "));
            scanf("%d",&choice);
            if (choice != 1)
            {
                return;
            }
            if (choice != 1 && choice != 2)
                ui_error("Invalid option! Enter 1 or 2.\n");
        } while(choice != 1 && choice != 2);
    }while(choice == 1);
} 
void Reset_GroceryItem(void)
{
	int option;
do{
	
    ui_section("Reset Grocery Items", C_YELLOW);
    ui_item(1, "Reset all grocery items", C_YELLOW);
    ui_item(2, "Return to menu",          C_RED);
    printf(UI_PROMPT("Enter your choice: "));
    scanf("%d",&option);
    switch(option)
    {
    	case 1 :{
	               free(groc_ID);
                   free(groc_Name);
                   free(groc_Quantity);
                   free(groc_Price);
                   groc_ID = NULL;
                   groc_Name = NULL;
                   groc_Quantity = NULL;
                   groc_Price = NULL;
                   count = 0;
                   capacity = 0;
                   ui_success("Grocery has been reset successfully!\n");
    	           break;
		        }
		case 2 : break;
		default :{	      
		          ui_error("Invalid input\n");
		          break;
	             }
	}
  }while(option!=2);
}

  

