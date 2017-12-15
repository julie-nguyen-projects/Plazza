/*
** EPITECH PROJECT, 2017
** Plazza project
** File description:
** Manager.cpp
*/

#include "Manager.h"
#include <boost/algorithm/string.hpp>

Manager::Manager() : managerTeam(30){
	std::cout << "Manager : I'm the Plazza's manager !" << std::endl;
	orderID = 1;
}

Manager::~Manager() {
        while(!kitchens.empty()){
                delete kitchens.front();
                kitchens.pop_front();
        }
	std::cout << "Manager : Here is the end of the day, see you !" << std::endl;
}

static inline std::string &ltrim(std::string &s) {
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
	return s;
}

template <class Container>
void split5(const std::string& str, Container& cont,
	    const std::string& delims = ";")
{
	boost::split(cont, str, boost::is_any_of(delims));
}

std::queue<std::string> Manager::convertInputIntoOrder(Order order) {
	std::string orderToConvert = order.getCommand();
	std::vector<std::string> result;
	int pizzaCounter;
        int cpt;

	ltrim(orderToConvert);
	std::cout << orderToConvert << std::endl;
	split5(orderToConvert, result);
	std::copy(result.begin(), result.end(),
		  std::ostream_iterator<std::string>(std::cout, "\n"));
	for (auto &entry : result){
                pizzaCounter = 0;
                cpt = 1;
                while (entry.back() > 47 && entry.back() < 58){
                        pizzaCounter = pizzaCounter + ((entry.back() - 48) * cpt);
                        cpt = cpt * 10;
                        entry.pop_back();
                }
		for (int i = 0; i < pizzaCounter; ++i) {
			pizzas.push(entry);
		}
	}

	return pizzas;
}

void Manager::setTime(int timeBase) {
	baseTime = timeBase;
}

int Manager::getTime() {
	return (baseTime);
}

std::queue<std::string> Manager::getPizzas() {
	return pizzas;
}

unsigned int Manager::getOrderID() {
	return orderID;
}

void Manager::nextOrderID() {
	++orderID;
}

void Manager::manageKitchens(unsigned int maxCookers) {
	int nbKitchens = pizzas.size() / maxCookers;

	//security: limit of 10 processes
	if (nbKitchens > 10)
		nbKitchens = 10;
	else if (nbKitchens < 1)
		nbKitchens = 1;
	else if (pizzas.size() % maxCookers != 0)
		nbKitchens++;
	for (int i = 0; i < nbKitchens; ++i){
		std::cout << "COOKING " << std::endl;
                kitchens.push_front(new Kitchen(i, maxCookers));        //new list version
		//Kitchen processK(maxCookers);                         //old version
		if (pizzas.size() < maxCookers){
			maxCookers = pizzas.size();
		}
		for(unsigned int j = 0; j < maxCookers; ++j){
                        kitchens.front()->addOrder(pizzas.front());     //new list version
			//processK.addOrder(pizzas.front());            //old version
			pizzas.pop();
		}

		switch (fork()){
			case -1:
                        std::cerr << "Fatal error: can't create process!" << std::endl;
				exit(1);
			case 0:
			std::cout << " CASE 0 " << std::endl;
                                kitchens.front()->dispatch(managerTeam, baseTime);      //new list version
				//processK.dispatch(managerTeam, baseTime);             //old version
				exit(0);
			default:
				std::cout << std::endl;
		}
	}
}
/*
list<int> Manager::getKitchenStatus() {
	list<Kitchen> kitchens = getKitchen();
	list<int> cookers;

	for (auto &kitchen : kitchens) {
		cookers.add(kitchen.getNbOfBusyCookers());
	}*/
	// (1, 2, 0, 5)
	/*
	 * a.out 2000 5
	 * Kitchen 1 = 1 busy cooker / 5
	 * Kitchen 2 = 2 busy cookers / 5
	 * Kitchen 3 = 0 busy cooker / 5
	 * Kitchen 4 = 5 busy cookers / 5
	 */
/*	return cookers;
}*/