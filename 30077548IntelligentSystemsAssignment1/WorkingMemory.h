#pragma once
#include "GlobalHeader.h"
#include "Fact.h"

class WorkingMemory {
public:
	std::vector<Fact> facts;

	//Member functions
	void addFact(Fact f);
};

void WorkingMemory::addFact(Fact f)
{
	facts.push_back(f);
}