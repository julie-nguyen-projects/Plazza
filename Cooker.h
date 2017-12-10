//
// EPITECH PROJECT, 2017
// Plazza project
// File description:
// Cooker.h
//

#ifndef COOKER_H__
#define COOKER_H__

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Pizza/APizza.h"

class Cooker {
private:
	std::mutex cookerMtx;
	int kitchen;
	int id;
	APizza *pizza; // pointeur ?
	bool busy;
public:
	Cooker();
	~Cooker();

	Cooker(const Cooker &);
	Cooker &operator=(Cooker const &);
	int getId() const;
	int getKitchen() const;
	const APizza &getPizza() const;
	void cookPizza(std::string, std::string, int);
	void runThread(const std::string &, const std::string &, int);
	void reset(); // reinit the cooker
	bool isBusy();
};


#endif //COOKER_H
