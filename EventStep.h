#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__
#include "Event.h"
namespace df {
	const std::string STEP_EVENT = "df::step_event";
    class EventStep :
        public Event
    {
	private:
		int m_step_count;
	public:
		//Default constructor
		EventStep();

		//Constructor with initial step count
		EventStep(int init_step_count);

		//Sets the step count
		void setStepCount(int new_step_count);

		//Gets the step count
		int getStepCount() const;
    };
}
#endif