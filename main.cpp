//
// EPITECH PROJECT, 2017
// Plazza project
// File description:
// main.cpp
//

#include <iostream>
#include "Manager.h"
#include "Order.h"
#include "WindowFront.h"
#include <ncurses.h>
#include <menu.h>
#include <cstring>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream>

void launchOrder (Manager *manager, Order &anOrder, int cookersNb, PizzaFactory *factory){
	manager->convertInputIntoOrder(anOrder);
	manager->manageKitchens(static_cast<unsigned int>(cookersNb), factory);
	manager->nextOrderID();
}

int main(int argc, char *argv[]) {
	std::ofstream ofs;
	ofs.open("Txt/PizzaCooked/Pizzas.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	int baseTime;
	int cookersNb;
	if (argc < 3) {
		baseTime = 2000;
		cookersNb = 5;
	} else {
		baseTime = static_cast<int>(strtol(argv[1], nullptr, 10));
		cookersNb = static_cast<int>(strtol(argv[2], nullptr, 10));
	}
	Manager manager;
	std::list<Order> orders;

	int isNewOrder = 0;
	do {
		WindowFront *windowFront = new WindowFront();
		PizzaFactory factory;

		orders = windowFront->getOrders();
		manager.setTime(baseTime);

		for (auto &order : orders) {
			launchOrder(&manager, order, cookersNb, &factory);
		}
		isNewOrder = windowFront->getOrderFlag();
		delete windowFront;
	} while (isNewOrder);
	return (EXIT_SUCCESS);
}