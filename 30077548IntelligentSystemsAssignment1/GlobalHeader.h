#pragma once

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

enum Decision {
	WAIT,
	LEAVE
};

class Questions {
public:
	std::vector<std::pair<std::string, std::string>> questions = {
		{"customers", "How many customers are in the restaurant?"},
		{"waitTime", "How long is the waiting time before being seated?"},
		{"hungry","Are you hungry?"},
		{"alternativeRestaurant", "Are there alternative restaurants you can go to nearby?"},
		{"reservation", "Do you have a reservation with the restaurant?"},
		{"bar", "Does the restaurant have a bar?"},
		{"rainy", "Is it a rainy day?"},
		{"popularDay", "Is it one of the restaurants popular days?"},
	};
	std::vector<std::vector<std::string>> answers = {
		{"A few", "Some", "Full of customers"},
		{"More than 60 minutes", "Between 31 and 60 minutes", "Between 10 and 30 minutes", "Less than 10 minutes"},
		{"Yes", "No"},
		{"Yes", "No"},
		{"Yes", "No"},
		{"Yes", "No"},
		{"Yes", "No"},
		{"Yes", "No"}
	};
	std::vector<std::pair<int, int>> choiceNumbers =
	{
		{1, 3},
		{1, 4},
		{1, 2},
		{1, 2},
		{1, 2},
		{1, 2},
		{1, 2},
		{1, 2}
	};
};