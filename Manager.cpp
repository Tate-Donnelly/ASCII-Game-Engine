#include "Manager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"

namespace df {
	Manager::Manager() {
		setType("Manager");
		m_is_started = false;
	}

	Manager::~Manager() {

	}
	//Sets the m_is_started variable to true
	int Manager::startUp() {
		//LM.writeLog(3, "Manager startUp()");
		m_is_started = true;
		return 0;
	}

	//Sets the m_is_started variable to false
	void Manager::shutDown() {
		//LM.writeLog(3, "Manager shutDown()");
		m_is_started = false;
	}

	//Checks if manager has been successfully started
	bool Manager::isStarted() const {
		return m_is_started;
	}

	//Sets type to the name Manager
	void Manager::setType(std::string type) {
		m_type = type;
	}

	//Return's the Manager's type
	std::string Manager::getType() const {
		return m_type;
	}
	int Manager::onEvent(const Event* p_event) const {
		int count = 0;
		//ObjectList all_objects = WM.getAllObjects();
		ObjectListIterator* li = new ObjectListIterator(new ObjectList(WM.getAllObjects()));
		while (!li->isDone()) {
			li->currentObject()->eventHandler(p_event);
			li->next();
			count++;
		}
		return count;
	}
}