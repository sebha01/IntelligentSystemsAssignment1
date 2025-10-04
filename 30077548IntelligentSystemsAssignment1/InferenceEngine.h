#pragma once
#include "WorkingMemory.h"
#include "RuleBase.h"
#include "Questions.h"

class InferenceEngine {
	private:
		WorkingMemory wM;
		RuleBase rB;
		Questions q;
		int choice = 0;
		bool canExit = false;
		bool playAgain = true;
	public:
		bool getCanExit();
		void setCanExit(bool var);
		bool getPlayAgain();
		void setPlayAgain(bool var);
		int validateInput(int minChoice, int maxChoice);
		void resetChoice();
		void askQuestion(std::string questionName);
		void fireQuestion();
		std::string traceStep();
		std::vector<Rule> matchRules();
		bool ruleReadyToFire(Rule& outRule);
		void presentDecision(Rule& r);
		Rule conflictResolution(std::vector<Rule>& candidates);
		void askToPlayAgain();
};

bool InferenceEngine::getCanExit()
{
	return canExit;
}

void InferenceEngine::setCanExit(bool var)
{
	this->canExit = var;
}

bool InferenceEngine::getPlayAgain()
{
	return playAgain;
}

void InferenceEngine::setPlayAgain(bool var)
{
	this->playAgain = var;
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

void InferenceEngine::askQuestion(std::string questionName)
{
	for (int i = 0; i < q.questions.size(); i++)
	{
		if (q.questions[i].first == questionName)
		{
			std::cout << std::endl << q.questions[i].second << std::endl;

			for (int x = 0; x < q.answers[i].size(); x++)
			{
				std::cout << x + 1 << " ->\t" << q.answers[i][x] << std::endl;
			}

			std::cout << std::endl << "Your choice -> ";

			choice = validateInput(q.choiceNumbers[i].first, q.choiceNumbers[i].second);

			Fact f(q.questions[i].first, q.answers[i][choice - 1]);

			wM.addFact(f);

			resetChoice();
			return;
		}
	}
}

void InferenceEngine::fireQuestion()
{
	if (wM.getFactData().empty())
	{
		askQuestion("customers");
		return;
	}
	
	Rule satisfiedRule;

	if (ruleReadyToFire(satisfiedRule))
	{
		//We want to make sure the loop definitely terminates even though setCanExit is called within presentDecision
		presentDecision(satisfiedRule);
		return;
	}

	std::string nextQuestionName = traceStep();
	if (!nextQuestionName.empty())
	{
		askQuestion(nextQuestionName);
	}
	else
	{
		//If all else fails somehow need to just abort
		std::cout << std::endl << "Couldn't make a decision based on the answers you have provided. Exiting program shortly..." << std::endl;
		setCanExit(true);
	}
}

std::string InferenceEngine::traceStep()
{
	std::vector<Rule> candidateRules = matchRules();

	if (candidateRules.empty())
	{
		return "";
	}
	else
	{
		Rule chosenRule = conflictResolution(candidateRules);

		for (int i = 0; i < chosenRule.conditions.size(); i++)
		{
			if (!wM.isFactInWM(chosenRule.conditions[i].factName))
			{
				return chosenRule.conditions[i].factName;
			}
		}

	}

	//If candidate rules is not empty but all the conditions have been met within the rules that are present then return to present the decision
	return "";
}

std::vector<Rule> InferenceEngine::matchRules()
{
	std::vector<Rule> matchingRules;
	std::vector<Rule>& rules = rB.getRules();
	bool isMatching = true;

	for (int i = 0; i < rules.size(); i++)
	{
		isMatching = true;

		for (int j = 0; j < rules[i].conditions.size(); j++)
		{
			//Easier for looking through the code and seeing what is going on than repeatedly long names
			Fact& currentCondition = rules[i].conditions[j];

			if (wM.isFactInWM(currentCondition.factName) && wM.getFactValue(currentCondition.factName) != currentCondition.factValue)
			{
				//No need to continue looking through this rule if it does not match, move onto the next one
				isMatching = false;
				break;
			}
		}

		if (isMatching)
		{
			matchingRules.push_back(rules[i]);
		}
		
	}

	return matchingRules;
}

bool InferenceEngine::ruleReadyToFire(Rule& outRule)
{
	std::vector<Rule>& rules = rB.getRules();
	bool ruleIsSatisfied = true;

	for (int i = 0; i < rules.size(); i++)
	{
		ruleIsSatisfied = true;

		for (int j = 0; j < rules[i].conditions.size(); j++)
		{
			//Easier for looking through the code and seeing what is going on than repeatedly long names
			Fact& currentCondition = rules[i].conditions[j];

			if (!wM.isFactInWM(currentCondition.factName) || wM.getFactValue(currentCondition.factName) != currentCondition.factValue)
			{
				//No need to continue looking through this rule if it does not match, move onto the next one
				ruleIsSatisfied = false;
				break;
			}
		}

		if (ruleIsSatisfied)
		{
			outRule = rules[i];
			return true;
		}
	}

	return false;
}

void InferenceEngine::presentDecision(Rule& r)
{
	std::cout << std::endl << "A decision has been reached from the facts you have given." << std::endl;
	std::cout << "The decision is that you should " << (r.decision == WAIT ? "wait for a seat" : "leave the restaurant") << std::endl << std::endl;

	std::cout << "The reasoning for this is because of these facts you gave me:" << std::endl;

	for (int i = 0; i < r.conditions.size(); i++)
	{
		switch (i)
		{
			case 0:
				std::cout << "-> " << r.conditions[i].factValue << " in the restaurant." << std::endl;
				break;
			case 1:
				std::cout << "-> " << r.conditions[i].factValue << " was the " << r.conditions[i].factName << " to be seated." << std::endl;
				break;
			default:
				std::cout << "-> " << r.conditions[i].factName << "?  -> " << r.conditions[i].factValue << std::endl;
				break;
		}
	}

	askToPlayAgain();
}

Rule InferenceEngine::conflictResolution(std::vector<Rule>& candidates)
{
	int largestIndex = 0;

	for (int i = 0; i < candidates.size(); i++)
	{
		if (candidates[i].conditions.size() > candidates[largestIndex].conditions.size())
		{
			largestIndex = i;
		}
	}

	return candidates[largestIndex];
}

void InferenceEngine::askToPlayAgain()
{
	std::cout << std::endl << "Would you like to play again?" << std::endl;
	std::cout << "1| Yes" << std::endl << "2| No" << std::endl << std::endl << "Your choice -> ";

	choice = validateInput(1, 2);

	switch (choice)
	{
	case 1:
		std::cout << std::endl << "Great let's play again, reloading expert system..." << std::endl;
		wM.clearFacts();
		setPlayAgain(true);
		setCanExit(false);
		break;
	case 2:
		std::cout << std::endl << "No problem, exiting program now..." << std::endl;
		std::cout << std::endl << "Thank you for enquiring the wait for table expert system today, goodbye!" << std::endl << std::endl;
		setPlayAgain(false);
		setCanExit(true);
		break;
	default:
		std::cout << "Something went wrong here, exiting program..." << std::endl;
		setPlayAgain(false);
		setCanExit(true);
		break;
	}
}