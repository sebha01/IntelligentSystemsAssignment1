#include <iostream>
#include <vector>

class Fact {
	public:
};

class WorkingMemory {
	public:
		std::vector<Fact> facts;

		void addFact(Fact f);
};

int main()
{
	return 0;
}

void WorkingMemory::addFact(Fact f)
{
	facts.push_back(f);
}