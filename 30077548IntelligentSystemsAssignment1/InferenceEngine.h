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
		bool resetScreen = false;
	public:
		//getters and setters for main loop
		bool getCanExit();
		void setCanExit(bool var);
		bool getResetScreen();
		void setResetScreen(bool var);
		//Input validation function and reset choice
		int validateInput(int minChoice, int maxChoice);
		void resetChoice();
		//Functions for main logic of inference engine
		void askQuestion(std::string questionName);
		void fireQuestion();
		std::string traceStep();
		std::vector<Rule> matchRules();
		bool ruleReadyToFire(Rule& r);
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

bool InferenceEngine::getResetScreen()
{
	return resetScreen;
}

void InferenceEngine::setResetScreen(bool var)
{
	this->resetScreen = var;
}

int InferenceEngine::validateInput(int minChoice, int maxChoice)
{
	//got this validation from my pokemon game year 1 and 2 assignments, if you need me to show you ask me
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
	//Simple but easier to type out a function for finding bugs later than just a line
	//Had it happen in a past assignment and it was just easier to control from one area than multiple
	choice = 0;
}

void InferenceEngine::askQuestion(std::string questionName)
{
	//Loop through the vector or string pairs to match the questionName passed in as a parameter
	//To the question name within the vector of questions
	for (int i = 0; i < q.questions.size(); i++)
	{
		//If questionName matches with the name in the vector then display the question to screen
		if (q.questions[i].first == questionName)
		{
			std::cout << std::endl << q.questions[i].second << std::endl;

			//Display the answers appropriately using the answers variable, as we have the index it is easy to get 
			for (int x = 0; x < q.answers[i].size(); x++)
			{
				std::cout << x + 1 << " ->\t" << q.answers[i][x] << std::endl;
			}

			//Ask for the user choice
			std::cout << std::endl << "Your choice -> ";
			//Validate input from user
			choice = validateInput(q.choiceNumbers[i].first, q.choiceNumbers[i].second);
			//Use fact constructor with the information obtained
			Fact f(q.questions[i].first, q.answers[i][choice - 1]);
			//Add that fact to working memory
			wM.addFact(f);
			//Reset the choice so that it doesn't cause issues on the next question asked
			resetChoice();
			//Return if the question has been found and asked so it doesn't continue looping unecessarily
			return;
		}
	}
}

void InferenceEngine::fireQuestion()
{
	//If the workingMemory has no facts ask the first question, no need to trace the step yet
	if (wM.getFactData().empty())
	{
		askQuestion("customers");
		return;
	}
	//Create rule object to store the rule that has been satisfied if one is found
	Rule satisfiedRule;
	//Check if a rule has been satisfied
	if (ruleReadyToFire(satisfiedRule))
	{
		//If so then present the decision to the user, then ask if the user wants to play again
		//We want to make sure the loop definitely terminates even though setCanExit is called within presentDecision
		presentDecision(satisfiedRule);
		return;
	}

	//If no rule is satisfied or isn't the first question then trace the next question to ask the user
	std::string nextQuestionName = traceStep();

	//As long as the questionName doesn't return empty then we can ask the next question
	//If somehow it does then something went wrong
	if (!nextQuestionName.empty())
	{
		askQuestion(nextQuestionName);
	}
	else
	{
		//If all else fails somehow we need to just abort so nothing crashes
		std::cout << std::endl << "Couldn't make a decision based on the answers you have provided. Exiting program shortly..." << std::endl;
		setCanExit(true);
	}
}

std::string InferenceEngine::traceStep()
{
	//Get a list of rules that could possibly be satisfied by the data currently in the working memory
	std::vector<Rule> candidateRules = matchRules();

	//Make sure the program doesn't crash by returning an empty string if somehow the candidateRules are empty
	if (candidateRules.empty())
	{
		return "";
	}
	else
	{
		//Apply conflict resolution by specificity, select the rule with the largest number of conditions
		Rule chosenRule = conflictResolution(candidateRules);

		//Loop through the chosenRule until it finds a fact that is not in the workingMemory
		for (int i = 0; i < chosenRule.conditions.size(); i++)
		{
			if (!wM.isFactInWM(chosenRule.conditions[i].factName))
			{
				//Return the question name so the next question can be asked
				return chosenRule.conditions[i].factName;
			}
		}

	}

	//If something goes wrong just return an empty string
	return "";
}

std::vector<Rule> InferenceEngine::matchRules()
{
	//Create vector of rules to store the matching rules inside
	std::vector<Rule> matchingRules;
	//Cuts down the length of variables and also only gets a refer
	std::vector<Rule>& rules = rB.getRules();
	//Initialise variable here and control value within loop
	bool isMatching = true;

	//Loop through the list of rules
	for (int i = 0; i < rules.size(); i++)
	{
		isMatching = true;

		//For each rule within the list of rules, check the conditions to make sure that the facts in the
		//working memory match up with the facts within those rules
		for (int j = 0; j < rules[i].conditions.size(); j++)
		{
			//Easier for looking through the code and seeing what is going on than repeatedly long names
			//Passing in by reference so it doesn't make a copy everytime
			Fact& currentCondition = rules[i].conditions[j];

			//If the fact from the working memory does not match with one of the facts within the rule
			//Then it is disregarded and moves onto the next iteration
			if (wM.isFactInWM(currentCondition.factName) 
				&& wM.getFactValue(currentCondition.factName) != currentCondition.factValue)
			{
				//No need to continue looking through this rule if it does not match, move onto the next one
				isMatching = false;
				break;
			}
		}

		//If isMatching is still true meaning that the rule meets the criteria  then
		// it gets pushed back into the matchingRules vector
		if (isMatching)
		{
			matchingRules.push_back(rules[i]);
		}
	}

	return matchingRules;
}

bool InferenceEngine::ruleReadyToFire(Rule& r)
{
	//Call a reference to the rules within rulebase, 
	//saves having to repeatedly call it and the length of variable names
	std::vector<Rule>& rules = rB.getRules();
	//boolean to control whether a rule has been satisfied
	bool ruleIsSatisfied = true;

	//Loop through vector of rules
	for (int i = 0; i < rules.size(); i++)
	{
		//reset boolean value on every iteration of loop
		ruleIsSatisfied = true;

		//Loop through condition within the rule, check for if rule does not match and change boolean to false
		//That way an unsatisfied rule does not get fired
		for (int j = 0; j < rules[i].conditions.size(); j++)
		{
			//Easier for looking through the code and seeing what is going on than repeatedly long names
			//Don't want to make a copy every time we call this so using a reference
			Fact& currentCondition = rules[i].conditions[j];

			if (!wM.isFactInWM(currentCondition.factName) 
				|| wM.getFactValue(currentCondition.factName) != currentCondition.factValue)
			{
				//No need to continue looking through this rule if it does not match, move onto the next one
				ruleIsSatisfied = false;
				break;
			}
		}


		//if boolean still true then return as true and set the Rule object passed in as a parameter 
		// as the current index of the loop
		if (ruleIsSatisfied)
		{
			r = rules[i];
			return true;
		}
	}

	return false;
}

void InferenceEngine::presentDecision(Rule& r)
{
	//First couple sentences for what is the end area
	std::cout << std::endl << "A decision has been reached from the facts you have given." << std::endl;
	std::cout << "The decision is that you should " << (r.decision == WAIT ? "wait for a seat" : "leave the restaurant") << std::endl << std::endl;
	std::cout << "The reasoning for this is because of these facts you gave me:" << std::endl;

	//Loop through the conditions of the satisfied rule to print out the #
	// reasoning for why the expert system came to that conclusion
	for (int i = 0; i < r.conditions.size(); i++)
	{
		switch (i)
		{
			case 0:
				//Make a sentance of the number of customers within the restaurant
				std::cout << "-> " << r.conditions[i].factValue << " in the restaurant." << std::endl;
				break;
			case 1:
				//Switched up the wording so it will make more sense when displaying the wait time
				std::cout << "-> " << r.conditions[i].factValue << " was the " << r.conditions[i].factName << " to be seated." << std::endl;
				break;
			default:
				//Rest of results will just display as the title and whether it was yes or no
				std::cout << "-> " << r.conditions[i].factName << "?  -> " << r.conditions[i].factValue << std::endl;
				break;
		}
	}

	askToPlayAgain();
}

Rule InferenceEngine::conflictResolution(std::vector<Rule>& candidates)
{
	//Conflict resolution by specificity, by choosing this the system will tend to ask more
	//Informative questions reducing unecessary dialogue by being able to cut down the amount of questions quickly
	
	//Set the largest index as the first index
	int largestIndex = 0;

	//Loop through vector of candidate rules to find which rule has the largest amount of conditions
	for (int i = 0; i < candidates.size(); i++)
	{
		//set the next largest index if value at current index of the loop is larger
		if (candidates[i].conditions.size() > candidates[largestIndex].conditions.size())
		{
			largestIndex = i;
		}
	}

	//return the rule with the biggest amount of conditions
	return candidates[largestIndex];
}

void InferenceEngine::askToPlayAgain()
{
	//Asks the player if they would like to replay
	std::cout << std::endl << "Would you like to play again?" << std::endl;
	std::cout << "1| Yes" << std::endl << "2| No" << std::endl << std::endl << "Your choice -> ";

	//Get user input
	choice = validateInput(1, 2);

	switch (choice)
	{
		case 1:
			//clears the facts within working memory so that system can start from scratch
			std::cout << std::endl << "Great let's play again!" << std::endl;
			wM.clearFacts();
			setResetScreen(true);
			setCanExit(false);
			break;
		case 2:
			//exits the program after letting the user know 
			std::cout << std::endl << "No problem, exiting program now..." << std::endl;
			std::cout << std::endl << "Thank you for enquiring the wait for table expert system today, goodbye!" << std::endl << std::endl;
			setCanExit(true);
			break;
		default:
			//If an error were to ever happen then it would just exit the program
			std::cout << "Something went wrong here, exiting program..." << std::endl;
			setCanExit(true);
			break;
	}
}