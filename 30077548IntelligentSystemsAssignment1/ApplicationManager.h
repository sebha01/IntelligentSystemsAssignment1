#pragma once

#include "GlobalHeader.h"
#include "InferenceEngine.h"

//THIS CLASS WAS TAKEN FROM MY DATA STRUCTURES AND ALGORITHMS SECOND ASSIGNMENT, ADJUSTMENTS MADE SO IT WORKS
//FOR THIS BUT IF YOU NEED PROOF I GOT IT FROM THERE ASK ME

class ApplicationManager
{
private:
	InferenceEngine iE;

public:
	void init();
	void showTitle();
	void update();
	int resetChoice();
	void startDelay(double secondsToDelay, std::string messageToDisplay);
	void clearScreen();
};

void ApplicationManager::init()
{
	//Initialise colour and title of project  
	system("color 1F");
	showTitle();

	//welcome message
	std::cout << "Welcome to the Wait for table Expert System" << std::endl;
}

void ApplicationManager::showTitle()
{
	//set the width for the title
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(70) << "-- -- Wait for Table Expert System -- --" << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void ApplicationManager::update()
{
	//continue to loop until the user decides to exit
	while (iE.getCanExit() == false)
	{
		iE.fireQuestion();

		if (iE.getResetScreen())
		{
			startDelay(2.0, "Loading");
			clearScreen();
			iE.setResetScreen(false);
		}
	}

	//Exit now that everything needed has been completed
	exit(0);
}

void ApplicationManager::startDelay(double secondsToDelay, std::string messageToDisplay)
{
	//Timer splits into 3 and adds a . to the screen then waits a quarter of the time passed in before moving on
	double third = secondsToDelay / 3;
	double quarter = secondsToDelay / 4;

	//display loading message or whatever is passed in
	std::cout << messageToDisplay;

	for (int i = 0; i < 3; i++)
	{
		//idea of the timer obtained from https://www.geeksforgeeks.org/how-to-add-timed-delay-in-cpp/ , then implemented it for microseconds so i could use a double value
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(third * 1000)));
		std::cout << ".";
	}

	//last touch so user can see it has finished loading
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(quarter * 1000)));
	std::cout << std::endl;
}

void ApplicationManager::clearScreen()
{
	//Clear the screen and show the title at the top before next set of outputs are displayed
	system("cls");
	showTitle();
}