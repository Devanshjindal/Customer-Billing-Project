#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct menu
{
	char item[50];
	char type[50];
	float price;
	int discount;
};

struct bill
{
	char item[50];
	char type[50];
	float price;
	int discount;
	int quantity;
};

void display_menu(struct menu list[], int n);
void add_item(struct menu list[], struct bill order[], int n, int* o_index);
void delete_item(struct bill order[], int* o_index);
void apply_discount(struct bill order[], int o_index);
void payment_mode(struct bill order[], int o_index);

int main()
{
	struct menu list[10];
	strcpy(list[0].item, "Veg_meal");
	strcpy(list[0].type, "meal");
	list[0].price = 100;
	list[0].discount = 10;
	
	strcpy(list[1].item, "Non-Veg_meal");
	strcpy(list[1].type, "meal");
	list[1].price = 150;
	list[1].discount = 15;
	
	strcpy(list[2].item, "Coffee");
	strcpy(list[2].type, "drink");
	list[2].price = 50;
	list[2].discount = 5;
	
	strcpy(list[3].item, "Tea");
	strcpy(list[3].type, "drink");
	list[3].price = 30;
	list[3].discount = 3;
	
	strcpy(list[4].item, "Burger");
	strcpy(list[4].type, "snack");
	list[4].price = 70;
	list[4].discount = 7;
	
	strcpy(list[5].item, "French_fries");
	strcpy(list[5].type, "snack");
	list[5].price = 60;
	list[5].discount = 6;

	int n = 6;
	struct bill order[20];
	int o_index = -1;
	int choice = 0;
	do
	{
		printf("\n1. Display Menu\n2. Add Item\n3. Delete Item\n4. Apply Discount\n5. Payment Mode\n6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				display_menu(list, n);
				break;
			case 2:
				add_item(list, order, n, &o_index);
				break;
			case 3:
				delete_item(order, &o_index);
				break;
			case 4:
				apply_discount(order, o_index);
				break;
			case 5:
				payment_mode(order, o_index);
				break;
			case 6:
				printf("Thank you for visiting.\n");
				break;
			default:
				printf("Invalid choice.\n");
		}
	}
	while(choice != 6);
	return 0;
}

void display_menu(struct menu list[], int n)
{
	printf("\nItems available on the menu:\n");
	printf("Item\t\tType\t\tPrice\n");
	for(int i=0; i<n; i++)
	{
		printf("%-16s%15s%.2f\n", list[i].item, list[i].type, list[i].price);
	}
}

void add_item(struct menu list[], struct bill order[], int n, int* o_index)
{
	int found = 0;
	char name[50];
	printf("Enter the item name: ");
	scanf("%s", name);
	for(int i=0; i<n; i++)
	{
		if(strcmp(name, list[i].item) == 0)
		{
			found = 1;
			printf("Enter quantity: ");
			scanf("%d", &order[++(*o_index)].quantity);
			strcpy(order[*o_index].item, list[i].item);
			strcpy(order[*o_index].type, list[i].type);
			order[*o_index].price = list[i].price;
			order[*o_index].discount = list[i].discount;
			printf("Item added to the order.\n");
			break;
		}
	}
	
	if(found == 0)
	{
		printf("Item not found.\n");
	}
}

void delete_item(struct bill order[], int* o_index)
{
	if(*o_index == -1)
	{
		printf("No items in the order.\n");
		return;
	}
	char name[50];
	printf("Enter the item name: ");
	scanf("%s", name);
	int found = 0;
	for(int i=0; i<=*o_index; i++)
	{
		if(strcmp(name, order[i].item) == 0)
		{
			found = 1;
			for(int j=i; j<*o_index; j++)
			{
				strcpy(order[j].item, order[j+1].item);
				strcpy(order[j].type, order[j+1].type);
				order[j].price = order[j+1].price;
				order[j].discount = order[j+1].discount;
				order[j].quantity = order[j+1].quantity;
			}
			(*o_index)--;
			printf("Item deleted from the order.\n");
			break;
		}
	}
	if(found == 0)
	{
		printf("Item not found.\n");
	}
}
void apply_discount(struct bill order[], int o_index)
{
	if(o_index == -1)
	{
		printf("No items in the order.\n");
		return;
	}
	for(int i=0; i<=o_index; i++)
	{
		if(order[i].discount != 0)
		{
			float discount = order[i].price * order[i].discount / 100.0;
			order[i].price -= discount;
			printf("%d%% discount applied on %s.\n", order[i].discount, order[i].item);
		}
	}
}

void payment_mode(struct bill order[], int o_index)
{
	if(o_index == -1)
	{
		printf("No items in the order.\n");
		return;
	}
	float total = 0;
	printf("Item\t\tType\t\tPrice\t\tQuantity\n");
	for(int i=0; i<=o_index; i++)
	{
		printf("%-15s%-15s%.2f\t\t%d\n", order[i].item, order[i].type, order[i].price, order[i].quantity);
		total += order[i].price * order[i].quantity;
	}
	printf("Total: %.2f\n", total);
	char mode[10];
	printf("Enter payment mode (cash/card): ");
	scanf("%s", mode);
	if(strcmp(mode, "cash") == 0)
	{
		float cash;
		printf("Enter cash amount: ");
		scanf("%f", &cash);
		if(cash < total)
		{
			printf("Insufficient cash.\n");
		}
		else
		{
			float change = cash - total;
			printf("Change: %.2f\n", change);
			printf("Payment successful.\n");
			o_index = -1;
		}
	}
	else if(strcmp(mode, "card") == 0)
	{
		printf("Payment successful.\n");
		o_index = -1;
	}
	else
	{
		printf("Invalid payment mode.\n");
	}
}
