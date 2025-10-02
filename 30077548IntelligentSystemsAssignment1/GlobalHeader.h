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
	std::vector<std::string> answers = {
		"\n1 | A few\n2 | Some\n3 | Full of customers\n",
		"\n1 | More than 60 minutes\n2 | Between 31 and 60 minutes\n3 | Between 10 and 30 minutes ? \n4 | Less than 10 minutes\n",
		"\n1| Yes\n2| No\n",
		"\n1| Yes\n2| No\n",
		"\n1| Yes\n2| No\n",
		"\n1| Yes\n2| No\n",
		"\n1| Yes\n2| No\n",
		"\n1| Yes\n2| No\n",
	};
};