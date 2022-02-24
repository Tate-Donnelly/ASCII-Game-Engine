#include "Event.h"
#include "LogManager.h"
namespace df {
	//Creates a base event
	Event::Event() {
		setType(UNDEFINED_EVENT);
		LM.writeLog(0,"Event created");
	}

	//Destructor
	Event:: ~Event() {}

	//Set event type
	void Event::setType(std::string new_type) {
		m_event_type = new_type;
	}

	//Get Event Type
	std::string Event::getType() const {
		return m_event_type;
	}
}