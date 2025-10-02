#pragma once
#include "WorkingMemory.h"
#include "RuleBase.h"

class InferenceEngine {
	private:
		WorkingMemory wM;
		RuleBase rB;
		Questions q;
		int choice = 0;
		bool canExit = false;
	public:
		bool getCanExit();
		void setCanExit(bool var);
		int validateInput(int minChoice, int maxChoice);
		void resetChoice();
		void fireQuestion();
		void traceStep();
		void conflictRes();
		void askQuestion(std::string questionName);
};

bool InferenceEngine::getCanExit()
{
	return canExit;
}

void InferenceEngine::setCanExit(bool var)
{
	this->canExit = var;
}

int InferenceEngine::validateInput(int minChoice, int maxChoice)
{
	//got this validation from my pokemon game year 1 assignment, if you need me to show you ask me
	while (!(std::cin >> choice) || (choice < minChoice || choice > maxChoice))
	{
		std::cout << std::endl << "Invalid input, please choose a number between " << minChoice << " and " << maxChoice << " -> ";

		//clear the input and ignore any other characters on that line if user has typed in a sentence
		std::cin.clear();
		std::cin.ignore(500, '\n');
	}

	return choice;
}


void InferenceEngine::resetChoice()
{
	//Simple but easier to type out a fuction for finding bugs later than just a line
	choice = 0;
}

void InferenceEngine::fireQuestion()
{
	if (wM.getFactData().empty())
	{
		askQuestion("customer");
	}

	traceStep();
}

void InferenceEngine::traceStep()
{
	
}

void InferenceEngine::conflictRes()
{

}

void InferenceEngine::askQuestion(std::string questionName)
{
	for (int i = 0; i < q.questions.size(); i++)
	{
		if (q.questions[i].first == questionName)
		{
			std::cout << q.questions[i].second << q.answers[i];
			validateInput(q.choiceNumbers[i].first, q.choiceNumbers[i].second);
		}
	}
}