#include "declarations.h"
#include <time.h>
#include <stdlib.h>

Dish::Dish()
{
	type = NULL;
	name = NULL;
	price = new float;
	*price = 0;
}

Dish::Dish(const char* ty, float pri, const char* nam)
{
	type = ty;
	name = nam;
	price = new float;
	*price = pri;
}

void Dish::printDish()
{
	cout << type << " " << name << " " << *price << endl;
}

Table::Table()
{
	orders = NULL;
	numberOfSeats = 4;
	numberOfTakenSeats = 0;
	Free = true;
	Paid = true;
}

Table::Table(int numberOfChairs)
{
	orders = NULL;
	numberOfSeats = numberOfChairs;
	numberOfTakenSeats = 0;
	Free = true;
	Paid = true;
}

void Table::printOrder()
{
	int i = 0;
	if (orders != NULL)
	{
		cout << "Orders of this table: " << "(" << orders << ")" << endl;
		while (orders[i] != NULL)
		{
			cout << orders[i] << endl;
			i++;
		}
	}
	else
	{
		cout << "There are no orders" << endl;
	}
}

void Table::wasPaid(float price)
{
	if (price > 0)
	{
		Paid = false;
	}
	else
	{
		Paid = true;
	}
}

void Table::placeOrder(const menuNode* menu, int numberOfDishes)
{
	const menuNode* etr = menu;
	int kek = numberOfDishes;
	int siz = 3 * numberOfTakenSeats;
	orders = 0;
	orders = new const char*[siz];
	int a, b, c;
	int d = 0;
	srand(time(NULL));
	for (int x = 0; x < numberOfTakenSeats; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			a = rand() % (kek)+1;
			b = rand() % (kek)+1;
			c = rand() % (kek)+1;
		}
		for (int i = 0; i < a; i++)
		{
			if (etr->next == NULL)
			{
				etr = menu;
			}
			else
			{
				etr = etr->next;
			}
		}
		orders[d] = new char[32];
		orders[d] = etr->meal->getName();
		d++;
		etr = menu;
		for (int i = 0; i < b; i++)
		{
			if (etr->next == NULL)
			{
				etr = menu;
			}
			else
			{
				etr = etr->next;
			}
		}
		orders[d] = new char[32];
		orders[d] = etr->meal->getName();
		d++;
		etr = menu;
		for (int i = 0; i < c; i++)
		{
			if (etr->next == NULL)
			{
				etr = menu;
			}
			else
			{
				etr = etr->next;
			}
		}
		orders[d] = new char[32];
		orders[d] = etr->meal->getName();
		d++;
		etr = menu;
	}
	orders[d] = new char[32];
	orders[d] = NULL;
	//return orders;
}

void Table::printTable()
{
	cout << "---" << endl;
	cout << "Number of seats: " << numberOfSeats << " || Number of taken seats: " << numberOfTakenSeats << endl;
	if (Free == true)
	{
		cout << "Status: FREE, ";
	}
	else if (Free == false)
	{
		cout << "Status: HOSTING, ";
	}
	if (Paid == true)
	{
		cout << "HAS BEEN PAID" << endl;
	}
	else if (Paid == false)
	{
		cout << "NOT PAID" << endl;
	}
	printOrder();

}

void Table::copyTable(Table &tabl)
{
	this->Free = tabl.Free;
	this->Paid = tabl.Paid;
	this->orders = tabl.orders;
	this->numberOfSeats = tabl.numberOfSeats;
	this->numberOfTakenSeats = tabl.numberOfTakenSeats;
}

void Table::deleteOrder()
{
	orders = NULL;
}

void Table::changeStatus()
{
	if (Free == true)
	{
		Free = false;
	}
	else if (Free == false)
	{
		Free = true;
	}
}

void Table::changePaymentStatus()
{
	if (Paid == true)
	{
		Paid = false;
	}
	else if (Paid == false)
	{
		Paid = true;
	}
}
