/*
** EPITECH PROJECT, 2017
** Plazza project
** File description:
** Team.cpp
*/

#include "Team.h"

Team::Team(int howMany) {
	for (int i = 0; i < howMany; ++i){
		cookers.push(new Cooker());
	}
}

Team::~Team(){
	for (unsigned int i = 0; i <= cookers.size(); ++i){
		delete cookers.front();
		cookers.pop();
	}
}