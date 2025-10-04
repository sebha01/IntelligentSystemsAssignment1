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
		{"waitTime", "How long is the waiting time before being seated in minutes?"},
		{"hungry","Are you hungry?"},
		{"alternativeRestaurant", "Are there alternative restaurants you can go to nearby?"},
		{"reservation", "Do you have a reservation with the restaurant?"},
		{"bar", "Does the restaurant have a bar?"},
		{"raining", "Is it a rainy day?"},
		{"popularDay", "Is it one of the restaurants popular days?"},
	};
	std::vector<std::vector<std::string>> answers = {
		{"A few", "Some", "Full of customers"},
		{">60", "31-60", "10-30", "<10"},
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