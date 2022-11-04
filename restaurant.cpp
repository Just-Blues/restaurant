#include "declarations.h"

Restaurant::Restaurant()
{
	Waiterhead = NULL;
	Menuhead = NULL;
	moneyMade = 0;
	numberOfClients = 0;
	numberOfTables = 0;
	numberOfWaiters = 0;
	numberOfDishes = 0;
}

Restaurant::~Restaurant()
{
	menuNode* etr = Menuhead;
	while (etr)
	{
		etr = etr->next;
		delete Menuhead;
		Menuhead = etr;
	}
	waiterNode* ptr = Waiterhead;
	while (ptr)
	{
		fireWaiter(ptr->waiter->getName());
		ptr = ptr->next;
	}
}

void Restaurant::printRestaurant()
{
	cout << "--------------------------------------" << endl;
	cout << "Number of waiters: " << numberOfWaiters << endl;
	cout << "Number of dishes: " << numberOfDishes << endl;
	cout << "Number of tables: " << numberOfTables << endl;
	cout << "Number of customers inside: " << numberOfClients << endl;
	waiterNode* etr = Waiterhead;

	while (etr)
	{
		etr->waiter->printWaiter();
		etr = etr->next;
	}
	cout << "--------------------------------------" << endl;
}

void Restaurant::addTable(int chairs)
{
	Table* aux = new Table(chairs);
	waiterNode* ptr = Waiterhead;
	if (numberOfWaiters == 1)
	{
		Waiterhead->waiter->assignTable(aux);
	}
	else if (numberOfWaiters == 2)
	{
		if (ptr->waiter->getAssigned() <= ptr->next->waiter->getAssigned())
		{
			ptr->waiter->assignTable(aux);
		}
		else
		{
			ptr->next->waiter->assignTable(aux);
		}
		numberOfTables++;
	}
	else
	{
		if (ptr->waiter->getAssigned() < ptr->next->waiter->getAssigned() || ptr->waiter->getAssigned() == ptr->next->waiter->getAssigned())
		{
			ptr->waiter->assignTable(aux);
		}
		else
		{
			while (ptr->next)
			{
				if (ptr->waiter->getAssigned() > ptr->next->waiter->getAssigned())
				{
					ptr = ptr->next;
				}
				else
				{
					break;
				}
			}
			ptr->waiter->assignTable(aux);
		}
		numberOfTables++;
	}
}
/*
void Restaurant::serveCustomers()
{
	waiterNode* etr = Waiterhead;
	while(etr)
	{
		serveCustomers(etr->waiter->getName());
		etr = etr->next;
	}
}*/

void Restaurant::serveCustomers(const char* nam)
{
	cout << nam << endl;
	waiterNode* etr = Waiterhead;
	while (etr)
	{
		if (!strcmp(etr->waiter->getName(), nam))
		{
			break;
		}
		etr = etr->next;
	}
	moneyMade = moneyMade + etr->waiter->serveClients(Menuhead, numberOfDishes);
}

void Restaurant::fireWaiter(const char* nam)
{
	waiterNode* etr = Waiterhead;
	waiterNode* temp = new waiterNode;
	waiterNode* curr = new waiterNode;
	waiterNode* prev = new waiterNode;
	curr = Waiterhead;
	if (etr->waiter->getName() == nam)
	{
		temp = Waiterhead;
		Waiterhead = Waiterhead->next;
		//temp->waiter->removeAllTables();
		numberOfTables = numberOfTables - temp->waiter->getAssigned();
		delete temp;
		numberOfWaiters--;
		return;
	}
	while (etr->waiter->getName() != nam)
	{
		etr = etr->next;
		//etr->waiter->removeAllTables();
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
	numberOfTables = numberOfTables - etr->waiter->getAssigned();
	numberOfWaiters--;
}

void Restaurant::hireWaiter(const char* nam)
{
	Waiter* aux = new Waiter(nam);
	waiterNode* etr = new waiterNode;
	etr->waiter = aux;
	etr->next = Waiterhead;
	Waiterhead = etr;
	numberOfWaiters++;
}

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************
void Restaurant::managerIntervention()
{
	waiterNode* etr = Waiterhead;
	waiterNode* ptr = Waiterhead;
	Table* aux = new Table();

	//this would be long if the max number of waiters wasn't just 8

//while(isAssignedEqually() == false)
	{
		while (etr)
		{
			while (ptr)
			{
				if ((etr->waiter->getAssigned() - ptr->waiter->getAssigned()) > 1 || (ptr->waiter->getAssigned() - etr->waiter->getAssigned()) > 1)
				{
					if ((etr->waiter->getAssigned() > ptr->waiter->getAssigned()))
					{
						aux = etr->waiter->findFree();
						if (aux->getisFree() == true)
						{
							etr->waiter->removeAssignedTable();
							ptr->waiter->assignTable(aux);

							etr->waiter->changePriority();
							ptr->waiter->changePriority();
						}
						else if (aux->getisFree() == false)
						{
							etr->waiter->removeLast();
							ptr->waiter->assignTable(aux);

							etr->waiter->changePriority();
							ptr->waiter->changePriority();
						}
					}
					else if ((ptr->waiter->getAssigned() > etr->waiter->getAssigned()))
					{
						aux = ptr->waiter->findFree();
						if (aux->getisFree() == true)
						{
							ptr->waiter->removeAssignedTable();
							etr->waiter->assignTable(aux);

							ptr->waiter->changePriority();
							etr->waiter->changePriority();
						}
						else if (aux->getisFree() == false)
						{
							ptr->waiter->removeLast();
							etr->waiter->assignTable(aux);

							ptr->waiter->changePriority();
							etr->waiter->changePriority();
						}
					}
				}
				ptr = ptr->next;
			}
			ptr = Waiterhead;
			etr = etr->next;
		}
	}
}

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

void Restaurant::managerFireWaiter(const char* nam)
{
	waiterNode* ptr = Waiterhead;
	if (numberOfWaiters == 1)
	{
		cout << "Can't fire last waiter, restaurant won't operate" << endl;
		return;
	}

	if (numberOfWaiters <= 2)
	{
		cout << "WARNING: Restaurant will be left with only one waiter" << endl;

	}

	while (ptr)
	{
		if (!strcmp(ptr->waiter->getName(), nam))
		{
			break;
		}
		ptr = ptr->next;
	}

	if (!ptr)
	{
		cout << "Waiter not found" << endl;
		return;
	}
	tableNode* aux = new tableNode;
	aux = ptr->waiter->getHead();
	fireWaiter(ptr->waiter->getName());
	while (aux)
	{
		addTable(aux->table->getSeats());
		aux = aux->next;
	}
	delete aux;
}

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

void Restaurant::managerHireWaiter(const char* nam)
{
	hireWaiter(nam);
	waiterNode* ptr = Waiterhead;
	waiterNode* etr = Waiterhead->next;
	while (ptr->waiter->getName() != nam)
	{
		ptr = ptr->next;
	}
	int tables_to_assign = numberOfTables / numberOfWaiters;
	for (int i = 0; i < tables_to_assign; i++)
	{
		Table* aux = new Table;
		aux = etr->waiter->getLast();
		ptr->waiter->assignTable(aux);
		etr->waiter->removeLast();
		etr = etr->next;
		if (!etr)
		{
			etr = Waiterhead->next;
		}
	}
	ptr->waiter->changePriority();
}

int Restaurant::removeTable()
{
	waiterNode* etr = Waiterhead;
	Table* aux = new Table;
	while (etr)
	{
		aux = etr->waiter->findFree();
		if (aux->getisFree() == true)
		{
			etr->waiter->removeAssignedTable();
			numberOfTables--;
			return aux->getSeats();
		}
		else if (aux->getisFree() == false)
		{
			etr->waiter->removeLast();
			numberOfTables--;
			return aux->getSeats();
		}
		etr = etr->next;
	}
	numberOfTables--;
	return -1;
}

void Restaurant::NewDish(const char* ty, float pri, const char* nam)//creates new dish with given parameters
{
	if (numberOfDishes <= 48)
	{
		Dish* aux = new Dish(ty, pri, nam);
		addNewDish(aux);
	}
	else
	{
		cout << "There is enough dishes in the menu (48)" << endl;
	}
}

void Restaurant::addNewDish(Dish* mea)
{
	menuNode* etr = new menuNode;
	etr->meal = mea;
	etr->next = Menuhead;
	Menuhead = etr;
	numberOfDishes++;
}

void Restaurant::removeDish(const char* nam)//removes dish of given name
{
	menuNode* etr = Menuhead;
	menuNode* temp = new menuNode;
	menuNode* curr = new menuNode;
	menuNode* prev = new menuNode;
	curr = Menuhead;
	if (etr->meal->getName() == nam)
	{
		temp = Menuhead;
		Menuhead = Menuhead->next;
		delete temp;
	}
	while (etr->meal->getName() != nam)
	{
		etr = etr->next;
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
}

void Restaurant::printMenu()
{
	menuNode* etr = Menuhead;
	while (etr)
	{
		etr->meal->printDish();
		etr = etr->next;
	}
}

bool Restaurant::isAssignedEqually()
{
	waiterNode* etr = Waiterhead;
	waiterNode* ptr = Waiterhead;
	int counter = 0;
	if (numberOfWaiters < 4)
	{
		cout << "less than 4" << endl;
		while (etr)
		{
			while (ptr)
			{
				if ((etr->waiter->getAssigned() - ptr->waiter->getAssigned()) > 1 || (ptr->waiter->getAssigned() - etr->waiter->getAssigned()) > 1)
				{
					return false;
				}
				ptr = ptr->next;
			}
			ptr = Waiterhead;
			etr = etr->next;
		}
	}
	else if (numberOfWaiters == 4)
	{
		cout << "just 4" << endl;
		while (etr)
		{
			if (etr->waiter->getAssigned() > 6 || etr->waiter->getAssigned() < 5)
			{
				return false;
			}

			etr = etr->next;
		}
	}
	else if (numberOfWaiters > 4)
	{
		cout << "more than 4" << endl;
		while (etr)
		{
			if (etr->waiter->getAssigned() >= 6)
			{
				counter++;
				if (counter > 4)
				{
					return false;
				}
			}
			etr = etr->next;
		}
	}
	return true;
}

