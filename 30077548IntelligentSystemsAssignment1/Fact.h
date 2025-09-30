#pragma once
#include "GlobalHeader.h"

class Fact {
public:
	//member variables
	std::string factName;
	std::string factValue;

	//member functions
	void setFactValue(std::string f);
};

void Fact::setFactValue(std::string f) 
{
	this->factValue = f;
}
