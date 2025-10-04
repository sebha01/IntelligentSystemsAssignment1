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
		void askQuestion(std::string questionName);

		void fireQuestion();
		std::string traceStep();
		
		std::vector<Rule> matchRules();
		bool ruleReadyToFire(Rule& outRule);
		void presentDecision(Rule& r);
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

void InferenceEngine::askQuestion(std::string questionName)
{
	for (int i = 0; i < q.questions.size(); i++)
	{
		if (q.questions[i].first == questionName)
		{
			std::cout << q.questions[i].second << std::endl;

			for (int x = 0; x < q.answers[i].size(); x++)
			{
				std::cout << x + 1 << " ->\t" << q.answers[i][x] << std::endl;
			}

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

	Rule chosenRule = candidateRules[0];

	for (int i = 0; i < chosenRule.conditions.size(); i++)
	{
		if (!wM.isFactInWM(chosenRule.conditions[i].factName))
		{
			return chosenRule.conditions[i].factName;
		}
	}

	return "";
}

std::vector<Rule> InferenceEngine::matchRules()
{
	std::vector<Rule> matchingRules;
	std::vector<Rule>& rules = rB.getRules();

	for (int i = 0; i < rules.size(); i++)
	{
		bool isMatching = true;

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

}

void InferenceEngine::presentDecision(Rule& r)
{

}