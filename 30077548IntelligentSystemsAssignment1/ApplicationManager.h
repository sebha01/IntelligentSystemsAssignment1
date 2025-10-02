#pragma once

#include "GlobalHeader.h"
#include "InferenceEngine.h"

class ApplicationManager
{
private:
	//game loop variables
	bool canExit = false;
	InferenceEngine iE;

public:
	void init();
	void showTitle();
	void update();
	int validateInput(int minChoice, int maxChoice);
	int resetChoice();
	void startDelay(double secondsToDelay, std::string messageToDisplay);
	void clearScreen();
	void endScreen();
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
	//set the width for the default console window size, hopefully noone maximises the screen
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(70) << "-- -- Wait for Table Expert System -- --" << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void ApplicationManager::update()
{
	//continue to loop until the user decides to exit
	while (!canExit)
	{
		iE.fireQuestion();
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

void ApplicationManager::endScreen()
{
	//Show the end screen after order tracking complete before moving back to the main menu
	std::cout << std::endl << "Enjoy your order, have a lovely day and thank you for using Hot Eats today :)" << std::endl;
	std::cout << "Goodbye!" << std::endl;

	startDelay(8.0, "Returning to main menu");
	clearScreen();
}