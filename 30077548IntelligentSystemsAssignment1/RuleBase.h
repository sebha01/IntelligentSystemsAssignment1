#pragma once
#include "GlobalHeader.h"
#include "Fact.h"

class RuleBase {
public:
	std::vector<Fact> rules = 
	{
		{}
	};

	//Member functions
	Decision returnDecision(std::vector<Fact> f);
};


Decision RuleBase::returnDecision(std::vector<Fact> f)
{


	return Decision::WAIT;
}