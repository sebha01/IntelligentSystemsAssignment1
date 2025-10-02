#pragma once
#include "WorkingMemory.h"
#include "RuleBase.h"

class InferenceEngine {
	private:
		WorkingMemory wM;
		RuleBase rB;
	public:
		void fireQuestion();
		void traceStep();
		void conflictRes();
};