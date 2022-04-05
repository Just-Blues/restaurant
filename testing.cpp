#include "declarations.h"
#include <cstring>
#include <limits>
#include <iostream>

void clientEnters(int howMany, Restaurant* restaurant)
{
	waiterNode* etr = restaurant->getWaiterHead();
	tableNode* ttr;
	int limit = 0;
	while (etr)
	{
		ttr = etr->waiter->getHead();
		while (ttr)
		{
			if (ttr->table->getisFree() == true)
			{
				limit = limit + ttr->table->getSeats();
			}
			ttr = ttr->next;
		}
		etr = etr->next;
	}
	etr = restaurant->getWaiterHead();
	int tracker = howMany;
	int counter = 0;
	int more = 0;
	Table** aux = new Table*;//check it!!
	if (howMany <= limit)
	{
		while (tracker > 0)
		{
			aux[counter] = etr->waiter->findFree();
			if (aux[counter]->getisFree() == true)
			{
				if (!(tracker <= aux[counter]->getSeats()))
				{
					more = aux[counter]->getSeats();
					aux[counter]->changeStatus();
					aux[counter]->changePaymentStatus();
					aux[counter]->setTaken(more);
					counter++;
					tracker = tracker - more;
				}
				else if (tracker <= aux[counter]->getSeats())
				{
					//more = aux[counter]->getSeats();
					aux[counter]->changeStatus();
					aux[counter]->changePaymentStatus();
					aux[counter]->setTaken(tracker);
					counter++;
					tracker = tracker - tracker;
				}
			}
			if (etr->next == NULL)
			{
				etr = restaurant->getWaiterHead();
			}
			else
			{
				etr = etr->next;
			}
		}
		restaurant->setNumberOfClients(howMany);
	}
	else
	{
		cout << "Not enough room for all the clients. Restaurant can hold: " << limit << " more customers" << endl;
	}
}

void clientLeaves(Restaurant* restaurant)
{
	waiterNode* etr = restaurant->getWaiterHead();
	tableNode* ttr;

	while (etr)
	{
		ttr = etr->waiter->getHead();
		while (ttr)
		{
			if (ttr->table->getisFree() == false && ttr->table->getwasPaid() == true)
			{
				restaurant->setNumberOfClients(-ttr->table->getTaken());
				ttr->table->deleteOrder();
				ttr->table->changeStatus();
				ttr->table->setTaken(0);
			}
			ttr = ttr->next;
		}
		etr->waiter->changePriority();
		etr = etr->next;
	}
}

Restaurant* createRestaurant()
{
	Restaurant* rest = new Restaurant;
	rest->NewDish("Main", 38.90f, "Steak");
	rest->NewDish("Soup", 15.34f, "Tomatoe Soup");
	rest->NewDish("Dessert", 24.44f, "Brownie");
	rest->NewDish("Soft", 4.22f, "Orange juice");
	rest->NewDish("Alcohol", 6.51f, "Beer");
	rest->NewDish("Main", 34.44f, "Sushi");
	rest->NewDish("Main", 21.3f, "Spaghetti");
	rest->NewDish("Soup", 11.32f, "Potatoe Soup");
	rest->NewDish("Dessert", 26.34f, "Panna cotta");
	rest->NewDish("Soft", 3.12f, "Apple juice");
	rest->NewDish("Alcohol", 14.36f, "Wine");
	rest->NewDish("Main", 23.32f, "Italian Pasta");

	rest->hireWaiter("John");
	rest->hireWaiter("Bart");
	rest->hireWaiter("Mark");
	rest->hireWaiter("Mary");

	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(3);
	rest->addTable(3);
	rest->addTable(3);
	rest->addTable(3);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(2);
	rest->addTable(2);
	rest->addTable(2);
	rest->addTable(2);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);
	rest->addTable(4);

	return rest;
}
void printCommands()
{
	cout << "terminate - closes program" << endl;
	cout << "help - shows all the available commands" << endl;
	cout << "clear - clears console screen using system(cls)" << endl;
	cout << "create - creates hardcoded restaurant with 4 waiters, 20 tables with different numbers of seats, and 12 dishes" << endl;
	cout << "showmenu - shows current menu" << endl;
	cout << "reststate - shows state of restaurant" << endl;
	cout << "empty - creates empty restaurant (NOT RECOMMENDED)" << endl;
	cout << "table - adds table with entered number of seats" << endl;
	cout << "removetable - removes any free table" << endl;
	cout << "dish - adds new dish to the menu with entered parameters" << endl;
	cout << "removedish - removes dish with given name" << endl;
	cout << "hire - hires (adds) waiter with given name" << endl;
	cout << "fire - fires (deletes) waiter with given name" << endl;
	cout << "simulate - the entered number of clients enter restaurant" << endl;
	cout << "serve - chosen waiter will serve his/her assigned clients" << endl;
	cout << "leave - served clients will leave their tables" << endl;
	cout << "money - shows all earned money" << endl;
}

void interface()
{
	Restaurant* rest = NULL;
	Restaurant emp;
	string dishName, dishType, waiterName;
	int seats, aux;
	float price;
	string command;
	cout << "Welcome user!" << endl;
	cout << "Available commands:" << endl;
	printCommands();
preserve:
	while (strcmp(command.c_str(), "terminate"))
	{
		cout << "Enter command: ";
		cin >> command;
		if (!strcmp(command.c_str(), "help"))
		{
			printCommands();
			goto preserve;//to preserve the loop
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "clear"))
		{
			system("cls");
			goto preserve;//to preserve the loop
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "create"))
		{
			rest = createRestaurant();
			//rest->printRestaurant();
			goto preserve;//to preserve the loop
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "showmenu"))
		{
			if (rest != NULL)
			{
				rest->printMenu();
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "reststate"))
		{
			if (rest != NULL)
			{
				rest->printRestaurant();
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "empty"))
		{
			rest = &emp;
			//rest->printRestaurant();
			goto preserve;//to preserve the loop
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "table"))
		{
			if (rest != NULL)
			{
				if (rest->getNumberOfWaiters() >= 1)
				{
					cout << "Enter the number of seats: ";
					cin >> seats;
					while (cin.fail() || seats < 1 || seats > 6)
					{
						cout << "The number must be integer or is unreasonable (the number must be between 2 and 5)" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin >> seats;
					}
					cout << endl;
					rest->addTable(seats);
					goto preserve;
				}
				else
				{
					cout << "Hire at least one waiter" << endl;
					goto preserve;
				}
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "removetable"))
		{
			if (rest != NULL)
			{
				rest->removeTable();
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		if (!strcmp(command.c_str(), "dish"))
		{
			if (rest != NULL)
			{
				cout << "Enter type of dish: ";
				cin >> dishType;
				char *dishT = new char[dishType.length() + 1];
				strcpy_s(dishT, dishType.length()+1 ,dishType.c_str());
				cin.ignore();
				cin.clear();
				cout << "Enter name of dish: ";
				cin >> dishName;
				char* dishN = new char[dishName.length() + 1];
				strcpy_s(dishN, dishName.length() + 1,dishName.c_str());
				cin.clear();
				cin.ignore();
				cout << "Enter price: ";
				cin >> price;
				while (cin.fail() || price < 0 || price > 100)
				{
					cout << "It must be a number bigger than 0 and lower than 100" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> seats;
				}
				price = price - 0.01f;
				rest->NewDish(dishT, price, dishN);
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}

		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "removedish"))
		{
			if (rest != NULL)
			{
				cout << "Enter name of dish: ";
				cin >> dishName;
				char* dishN = new char[dishName.length() + 1];
				strcpy_s(dishN, dishName.length() + 1, dishName.c_str());
				cin.clear();
				cin.ignore();
				rest->removeDish(dishN);
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "hire"))
		{
			if (rest != NULL)
			{
				cout << "Enter waiter's name: ";
				cin >> waiterName;
				char* waiterN = new char[waiterName.length() + 1];
				strcpy_s(waiterN, waiterName.length() + 1, waiterName.c_str());
				if (rest->getNumberOfWaiters() < 2)
				{
					rest->hireWaiter(waiterN);
					goto preserve;
				}
				else
				{
					rest->managerHireWaiter(waiterN);
					goto preserve;
				}
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "fire"))
		{
			if (rest != NULL)
			{
				if (rest->getNumberOfWaiters() >= 1)
				{
					cout << "Enter waiter's name: ";
					cin >> waiterName;
					char* waiterN = new char[waiterName.length() + 1];
					strcpy_s(waiterN, waiterName.length() + 1, waiterName.c_str());
					rest->managerFireWaiter(waiterN);
					goto preserve;
				}
				else
				{
					cout << "There are no waiters to fire" << endl;
					goto preserve;
				}
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "simulate"))
		{
			if (rest != NULL)
			{
				cout << "Enter number of clients that enter" << endl;
				cin >> aux;
				while (cin.fail())
				{
					cout << "The number must be an integer" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> aux;
				}
				clientEnters(aux, rest);
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "serve"))
		{
			if (rest != NULL)
			{
				cout << "Select waiter by writing his/her name: ";
				cin >> waiterName;
				char* waiterN = new char[waiterName.length() + 1];
				strcpy_s(waiterN, waiterName.length() + 1, waiterName.c_str());
				rest->serveCustomers(waiterN);
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "leave"))
		{
			if (rest != NULL)
			{
				cout << "Satisfied customers left restaurant" << endl;
				clientLeaves(rest);
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		if (!strcmp(command.c_str(), "money"))
		{
			if (rest != NULL)
			{
				cout << "Earned money: " << rest->getMoneyMade() << endl;
				goto preserve;
			}
			else
			{
				cout << "You must create Restaurant first using - create" << endl;
				goto preserve;
			}
		}
		else if (!strcmp(command.c_str(), "terminate"))
		{
			break;
		}
		else
		{
			cout << "Invalid command, Check your spelling or type help to see all available commands" << endl;
			goto preserve;
		}
	}
}

