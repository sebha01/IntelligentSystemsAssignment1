#pragma once
#include "GlobalHeader.h"

class Fact {
public:
	//member variables
	std::string factName = "";
	std::string factValue = "";

	//Constructor
	Fact(std::string name, std::string value)
	{
		this->factName = name;
		this->factValue = value;
	}
};


/*

customers {FEW,SOME,FULL},
waiting-time {<10,10-30,31-60,>60}, 
hungry {YES,NO}, 
alternative {YES,NO}, 
reservation {YES,NO}, 
bar {YES,NO}, 
popular-day {YES,NO}, 
raining {YES,NO}, 
decision {WAIT,LEAVE}

*/