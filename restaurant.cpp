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
	this->getWaiterHead()->waiter->assignTable(aux);
	numberOfTables++;
	this->managerIntervention();
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
		delete temp;
	}
	while (etr->waiter->getName() != nam)
	{
		etr = etr->next;
		//etr->waiter->removeAllTables();
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
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
	if (numberOfWaiters <= 2)
	{
		cout << "Restaurant can't operate" << endl;
		Waiterhead->next->waiter->removeAllTables();
		this->fireWaiter(Waiterhead->next->waiter->getName());
		Waiterhead->waiter->removeAllTables();
		this->fireWaiter(Waiterhead->waiter->getName());
	}
	else
	{
		while (ptr)
		{
			if (!strcmp(ptr->waiter->getName(), nam))
			{
				break;
			}
			ptr = ptr->next;
		}
		waiterNode* etr = Waiterhead;
		Table* aux = new Table();
		int counter = ptr->waiter->getAssigned();
		while (counter)
		{
			//cout << "start of loop: "<<counter <<endl;
			if (etr->waiter == ptr->waiter)
			{
				//cout << "check"<<endl;
				if (etr->next == NULL)
				{
					etr = Waiterhead;
				}
				etr = etr->next;
				//etr->waiter->printWaiter();
			}
			aux = ptr->waiter->findFree();

			if (aux->getisFree() == true)
			{
				//cout << "free"<<endl;
				ptr->waiter->removeAssignedTable();
				etr->waiter->assignTable(aux);
				etr->waiter->changePriority();
				counter--;
			}
			else if (aux->getisFree() == false)
			{
				//cout << "occupied"<<endl;
				ptr->waiter->removeLast();
				etr->waiter->assignTable(aux);
				etr->waiter->changePriority();
				counter--;
			}
			//cout << "end of loop: "<<counter <<endl;
			//etr->waiter->printWaiter();
			if (etr->next == NULL)
			{
				//cout << "NULL"<<endl;
				etr = Waiterhead;
			}
			else
			{
				//cout << "FULL"<<endl;
				etr = etr->next;
				//cout << "kek"<<endl;
			}

			//etr->waiter->printWaiter();
			//cout << "problem?" <<endl;
		}
		this->fireWaiter(ptr->waiter->getName());
	}
}

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

void Restaurant::managerHireWaiter(const char* nam)
{
	this->hireWaiter(nam);
	waiterNode* ptr = Waiterhead;
	while (ptr->waiter->getName() != nam)
	{
		ptr = ptr->next;
	}
	waiterNode* etr = Waiterhead->next;
	Table* aux = new Table();
	while (etr)
	{
		aux = etr->waiter->findFree();
		if (aux->getisFree() == true)
		{
			etr->waiter->removeAssignedTable();
		}
		else if (aux->getisFree() == false)
		{
			etr->waiter->removeLast();
		}
		ptr->waiter->assignTable(aux);
		etr = etr->next;
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

