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

std::vector<std::string> questionsToAsk = 
{
	"How many customers are in the restaurant?\n1| A few\n2| Some\n3| Full of customers\n",
	"How long is the waiting time before being seated?\n1| More than 60 minutes\n2| Between 31 and 60 minutes\n3| Between 10 and 30 minutes?\n4| Less than 10 minutes\n",
	"Are you hungry?\n1| Yes\n2| No\n",
	"Are there alternative restaurants you can go to nearby?\n1| Yes\n2| No\n",
	"Do you have a reservation with the restaurant?\n1| Yes\n2| No\n",
	"Does the restaurant have a bar?\n1| Yes\n2| No\n",
	"Is it a rainy day?\n1| Yes\n2| No\n",
	"Is it one of the restaurants popular days?\n1| Yes\n2| No\n"
};