#include "LogManager.h"
#include "EventStep.h"

namespace df {
	
	//Default constructor
	EventStep::EventStep() {
		m_step_count = 0;
		EventStep(m_step_count);
	}

	//Constructor with initial step count
	EventStep::EventStep(int init_step_count) {
		setStepCount(init_step_count);
		setType(STEP_EVENT);
		LM.writeLog(0, "EventStep created");
	}

	//Sets the step count
	void EventStep::setStepCount(int new_step_count) {
		m_step_count = new_step_count;
	}

	//Gets the step count
	int EventStep::getStepCount() const {
		return m_step_count;
	}

}

