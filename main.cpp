#include "declarations.h"

using namespace std;
int main()
{
	/*
	interface() is a function that is suppose to simulate the program
	basicly it's just an interface with some available commands
	Should it not work, because some commands combinations lead to memory leakage (I couldn't check every combination possible)
	below I'm listing function that can achieve the same, but through main().
	*/
	//interface();


	// TEST FOR OLD VERSION WITH THE ERROR
	//Here is a stress test and a description of functions/methods used to test this program

	Restaurant* rest = new Restaurant;
	rest->hireWaiter("John");
	rest->hireWaiter("Ashley");
	rest->hireWaiter("Bart");
	rest->addTable(2);
	rest->addTable(3);
	//rest->addTable(3);
	//rest->addTable(4);
	//rest->addTable(4);
	rest->printRestaurant();
	//rest->printMenu();//shows current menu

	/*
	rest->printRestaurant();//shows state of Restaurant
	clientEnters(30, rest);//clients enter restaurant, number of clients and restaurant are parameters
	rest->managerHireWaiter("Ashley");//hires waiter, give name as a parameter
	rest->printRestaurant();//shows state of Restaurant
	rest->managerFireWaiter("John");//fires waiter, give name as a parameter (STARTING WAITERS: Mary, Mark, Bart, John)
	rest->serveCustomers("Mary");//waiter serve customers in his/her zone, takes name of waiter as parameter
	rest->printRestaurant();//shows state of Restaurant
	clientLeaves(rest);//customers with generated orders and after paying leave restaurant, take Restaurant as parameter
	clientEnters(20, rest);//clients enter restaurant, number of clients and restaurant are parameters
	rest->serveCustomers("Ashley");//waiter serve customers in his/her zone, takes name of waiter as parameter
	rest->printRestaurant();
	*/
	//And so on



	// TEST THAT SHOW THAT MOST OF THE PROGRAM WORKS
	/*
	Restaurant* test;
	test = createRestaurant();
	test->printRestaurant();
	clientEnters(4,test);
	test->getWaiterHead()->waiter->getHead()->table->placeOrder(test->getMenuhead(),test->getNumberOfDishes());
	test->printRestaurant();
	test->getWaiterHead()->waiter->getHead()->table->changePaymentStatus();
	clientLeaves(test);
	test->printRestaurant();
	test->managerFireWaiter("Mary");
	test->printRestaurant();
	test->managerHireWaiter("Ashley");
	test->addTable(5);
	test->addTable(5);
	test->addTable(5);
	test->addTable(5);
	test->managerHireWaiter("Julia");
	test->printRestaurant();
	test->NewDish("Main",23.45,"Kebab");
	test->printMenu();*/

	getchar();
	return 0;
}

