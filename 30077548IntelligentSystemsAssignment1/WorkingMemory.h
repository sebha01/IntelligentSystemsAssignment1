#pragma once
#include "GlobalHeader.h"
#include "Fact.h"

class WorkingMemory {
	private:
		std::vector<Fact> facts = {};

	public:
		void addFact(Fact f);
		bool isFactInWM(std::string name);
		std::string getFactValue(std::string name);
		bool decisionReached();
};

void WorkingMemory::addFact(Fact f)
{
	//Only add the fact into the working memory as long as there isn't duplicate found
	if (!isFactInWM(f.factName)) 
	{ 
		facts.push_back(f); 
	}
}

bool WorkingMemory::isFactInWM(std::string name)
{
	for (int i = 0; i < facts.size(); i++)
	{
		if (facts[i].factName == name)
		{
			return true;
		}
	}

	return false;
}

std::string WorkingMemory::getFactValue(std::string name)
{
	//We will always know if a fact is known by isKnownFact 
	// function before calling getFactValue so don't need to handle errors

	for (int i = 0; i < facts.size(); i++)
	{
		if (facts[i].factName == name)
		{
			return facts[i].factValue;
		}
	}
}

bool WorkingMemory::decisionReached()
{
	for (int i = 0; i < facts.size(); i++)
	{
		if (facts[i].factName == "decision")
		{
			return true;
		}
	}

	return false;
}