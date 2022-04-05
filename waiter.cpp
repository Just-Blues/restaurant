#include "declarations.h"

Waiter::Waiter()
{
	name = "Basic";
	head = NULL;
	numberOfAssignedTables = 0;
	bill = 0;
}

Waiter::Waiter(const char* nam)
{
	name = nam;
	head = NULL;
	numberOfAssignedTables = 0;
	bill = 0;
}

void Waiter::removeAllTables()
{
	tableNode* etr = head;
	while (etr)
	{
		etr = etr->next;
		delete head;
		head = etr;
	}
}

Waiter::~Waiter()
{
	removeAllTables();
}

float Waiter::serveClients(const menuNode* menu, int numberOfDishes)
{
	//menuNode* ptr = menu;
	tableNode* etr = head;
	//float* fun = new float;
	float fun = 0;
	//float aux = 0;
	while (etr)
	{
		if (etr->table->getisFree() == false)
		{
			const menuNode* ptr = menu;
			etr->table->placeOrder(ptr, numberOfDishes);
			cout << "-----------------" << endl;
			//ptr->meal->printDish();
			bill = prepareMeal(ptr, etr->table->getOrders());
			fun = bill + fun;
			etr->table->wasPaid(bill);
			etr->table->changePaymentStatus();
			//aux = aux + bill;
			bill = 0;
		}
		etr = etr->next;
	}
	cout << "---------------------------" << endl;
	cout << "Money waiter made = " << fun << endl;
	cout << "---------------------------" << endl;
	return fun;
}

float Waiter::prepareMeal(const menuNode* menu, const char** food)
{
	cout << "The problem = " << *menu->meal->getPrice() << endl;
	float price = 0;
	int i = 0;
	const menuNode* etr = menu;
	while (food[i] != NULL)
	{
		if (!strcmp(etr->meal->getName(), food[i]))
		{
			//cout << etr << endl;
			//etr->meal->printDish();
			//cout << "Price = " << price << endl;
			price = price + *etr->meal->getPrice();
			i++;
		}
		if (etr->next == NULL)
		{
			etr = menu;
		}
		else
		{
			etr = etr->next;
		}
	}
	etr = menu;
	//cout <<"Final Price = " << price << endl;
	return price;
}

void Waiter::assignTable(Table* tabl)
{
	tableNode* etr = new tableNode;
	etr->next = head;
	etr->table = tabl;
	head = etr;
	numberOfAssignedTables++;
}

void Waiter::changePriority()
{
	tableNode* curr, *nex;
	curr = head;
	nex = head->next;
	for (int i = numberOfAssignedTables - 1; i >= 0; i--)
	{
		curr = head;
		nex = head->next;
		for (int j = 0; j < numberOfAssignedTables - 1; j++)
		{
			if (curr->table->getisFree() == true && nex->table->getisFree() == false)
			{
				swap(curr->table, nex->table);
			}
			curr = nex;
			nex = nex->next;
		}
	}
}

Table* Waiter::findFree() //or return last possible
{
	tableNode* etr = head;
	Table* aux = NULL;
	while (etr)
	{
		if (etr->table->getisFree())
		{
			return etr->table;
		}
		else
			etr = etr->next;
	}
	etr = head;
	while (etr->next)
	{
		etr = etr->next;
	}
	aux = etr->table;
	return aux;
}

void Waiter::removeAssignedTable()
{
	tableNode* etr = head;
	tableNode* temp = new tableNode;
	tableNode* curr = new tableNode;
	tableNode* prev = new tableNode;
	curr = head;

	Table* aux = new Table;
	aux = this->findFree();

	if (aux->getisFree() == true)
	{
		if (etr->table->getisFree() == true)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		while (etr->table->getisFree() != true)
		{
			etr = etr->next;
			prev = curr;
			curr = curr->next;
		}
		prev->next = curr->next;

		numberOfAssignedTables--;
	}
	else
	{
		cout << "This waiter has no free tables, can't remove any tables" << endl;
	}
}

void Waiter::removeLast()
{
	tableNode* current = new tableNode;
	tableNode* previous = new tableNode;
	current = head;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	//tail = previous;
	previous->next = NULL;
	delete current;

	numberOfAssignedTables--;
}

bool Waiter::isInTheZone(Table* tabl)
{
	tableNode* etr = head;

	while (etr)
	{
		if (etr->table == tabl)
		{
			return true;
		}
		etr = etr->next;
	}
	return false;
}

void Waiter::printWaiter()
{

	cout << "----------" << endl;
	cout << endl;
	cout << name << " - Number of assigned tables: " << numberOfAssignedTables << endl;
	cout << endl;
	tableNode* etr = head;
	while (etr)
	{
		etr->table->printTable();
		etr = etr->next;
	}
}
