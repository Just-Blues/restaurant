#include <iostream>
#include <string>

#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

using namespace std;

class Dish
{
private:
	const char* type;//main dish, dessert, soup, drink
	const char* name;
	float* price;

public:
	Dish();
	Dish(const char* ty, float pri, const char* nam);
	void printDish();
	const char* getName() { return name; };
	const char* getType() { return type; };
	float* getPrice() { return price; };
};

struct menuNode
{
	Dish* meal;
	menuNode* next;
};

class Table
{
private:
	const char** orders;
	int numberOfSeats;
	int numberOfTakenSeats;
	bool Free;
	bool Paid;

public:
	Table();
	Table(int numberOfChairs);
	void wasPaid(float price);
	void placeOrder(const menuNode* menu, int numberOfDishes);
	void printTable();

	void copyTable(Table &tabl);
	void setTaken(int seats) { numberOfTakenSeats = seats; };
	int getTaken() { return numberOfTakenSeats; };
	bool getisFree() { return Free; };
	bool getwasPaid() { return Paid; };
	int getSeats() { return numberOfSeats; };
	const char** getOrders() { return orders; };
	void changeStatus(bool status) { Free = status; };
	void deleteOrder();
	void changeStatus();
	void changePaymentStatus();
	void printOrder();
};

struct tableNode
{
	Table* table;
	tableNode* next;
};

class Waiter
{
private:
	const char* name;
	tableNode* head;
	int numberOfAssignedTables;
	float bill;

public:
	Waiter();
	Waiter(const char* nam);
	~Waiter();
	void removeAllTables();
	float serveClients(const menuNode* menu, int numberOfDishes);//Kinda problematic
	float prepareMeal(const menuNode* menu, const char** orders);
	void assignTable(Table* tabl);
	void changePriority();
	void removeAssignedTable();
	void removeLast();
	void printWaiter();
	Table* findFree();//or return last possible
	bool isInTheZone(Table* tabl);
	int getAssigned() { return numberOfAssignedTables; };
	tableNode* getHead() { return head; };
	const char* getName() { return name; };
};

struct waiterNode
{
	Waiter* waiter;
	waiterNode* next;
};

class Restaurant
{
private:
	waiterNode* Waiterhead;
	menuNode* Menuhead;
	int numberOfWaiters;
	int numberOfClients;
	int numberOfTables;
	int numberOfDishes;
	float moneyMade;

public:

	Restaurant();
	~Restaurant();
	//void createMenu();
	void NewDish(const char* ty, float pri, const char* nam);
	void addNewDish(Dish* mea);
	void removeDish(const char* nam);
	void printMenu();
	void addTable(int chairs);
	void hireWaiter(const char* nam);
	void fireWaiter(const char* nam);
	void managerIntervention();
	void managerFireWaiter(const char* nam);
	void managerHireWaiter(const char* nam);
	//void serveCustomers();//THIS IS PROBLEMATIC DOESN'T WORK DON'T TOUCH IT
	void serveCustomers(const char* nam);
	int removeTable();
	void printRestaurant();
	bool isAssignedEqually();
	int getNumberOfClients() { return numberOfClients; };
	menuNode* getMenuhead() { return Menuhead; };
	waiterNode* getWaiterHead() { return Waiterhead; };
	int getNumberOfDishes() { return numberOfDishes; };
	void setNumberOfClients(int x) { numberOfClients = numberOfClients + x; };
	int getNumberOfWaiters() { return numberOfWaiters; };
	float getMoneyMade() { return moneyMade; };
};

void clientEnters(int howMany, Restaurant* restaurant);
Restaurant* createRestaurant();
void clientLeaves(Restaurant* restaurant);
void interface();


#endif // DECLARATIONS_H_INCLUDED