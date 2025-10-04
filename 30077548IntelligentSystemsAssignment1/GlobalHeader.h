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
#include <algorithm>

enum Decision {
	WAIT,
	LEAVE
};

class Questions {
public:
	std::vector<std::pair<std::string, std::string>> questions = {
		{"customers", "How many customers are in the restaurant?"},
		{"wait time", "How long is the waiting time before being seated in minutes?"},
		{"Hungry","Are you hungry?"},
		{"Alternative restaurant", "Are there alternative restaurants you can go to nearby?"},
		{"Reservation", "Do you have a reservation with the restaurant?"},
		{"Bar", "Does the restaurant have a bar?"},
		{"Raining", "Is it a rainy day?"},
		{"Popular day", "Is it one of the restaurants popular days?"},
	};
	std::vector<std::vector<std::string>> answers = {
		{"A few customers", "Some customers", "Full of customers"},
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