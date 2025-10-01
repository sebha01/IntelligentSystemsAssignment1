#pragma once
#include "GlobalHeader.h"
#include "Fact.h"

class Rule {
	public:
		std::vector<Fact> conditions = {};
		Fact conclusion;
};