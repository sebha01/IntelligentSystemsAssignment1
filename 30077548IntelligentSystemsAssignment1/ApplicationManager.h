#pragma once

#include "GlobalHeader.h"
#include "InferenceEngine.h"

class ApplicationManager
{
private:
	InferenceEngine iE;

public:
	void init();
	void showTitle();
	void update();
	int resetChoice();
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
	while (iE.getCanExit() == false && iE.getPlayAgain() == true)
	{
		iE.fireQuestion();
	}

	//Exit now that everything needed has been completed
	exit(0);
}