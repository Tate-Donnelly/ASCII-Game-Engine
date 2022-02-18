#include "testObject.h"
#include <stdlib.h>
#include "DisplayManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "EventKeyboard.h"

namespace df {
	testObject::testObject(){
		setType("testObject");
		setSprite("ship");
		setAltitude(0);	//Puts stars in the background 
		setPosition(df::Vector(50, 5));
		color = df::RED;
		setSolidness(SOFT);
	}

	//Handles events
	//Returns 0 when ignored
	int testObject::eventHandler(const Event* p_e) {
		//For checkpoint 5 test 1 (testGMRun())
		if (p_e->getType() == df::STEP_EVENT) {
			if (((EventStep*)p_e)->getStepCount() % 150 == 0) {
				setAltitude(1);
			}
			if (((EventStep*)p_e)->getStepCount() % 300 == 0) {
				setPosition(Vector(25, 5));
			}
			if (((EventStep*)p_e)->getStepCount() % 600 == 0) {
				setAltitude(5);
				setPosition(Vector(35, 8));
			}
			return 1;
		}
		if (p_e->getType() == df::MSE_EVENT) {//testObject moves to the cursor when clicked
			EventMouse* m = (EventMouse*)p_e;
			LM.writeLog(0,"Key %d", m->getMouseButton());
			if (m->getMouseAction() == EventMouseAction::PRESSED) {
				setPosition(Vector(m->getMousePosition().getX(), m->getMousePosition().getY()));
				int x = getPosition().getX();
				int y = getPosition().getY();
				LM.writeLog(0, "ID: %d Position:(%d, %d)", getId(), x, y);
			}
			return 1;
		}
		if (p_e->getType() == df::KEYBOARD_EVENT) {//testObject moves to the cursor when clicked
			EventKeyboard* m = (EventKeyboard*)p_e;
			LM.writeLog(0,"Key %d", m->getKey());
			if (m->getKey() == Keyboard::Key::NUM1 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::RED;
			}
			if (m->getKey() == Keyboard::Key::NUM2 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::GREEN;
			}
			if (m->getKey() == Keyboard::Key::NUM3 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::YELLOW;
			}
			if (m->getKey() == Keyboard::Key::NUM4 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::BLUE;
			}
			if (m->getKey() == Keyboard::Key::NUM5 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::MAGENTA;
			}
			if (m->getKey() == Keyboard::Key::NUM6 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::CYAN;
			}
			if (m->getKey() == Keyboard::Key::NUM7 && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				color = df::WHITE;
			}
			if (m->getKey() == Keyboard::Key::W && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				setPosition(Vector(getPosition().getX(), getPosition().getY() - .5));
			}
			if (m->getKey() == Keyboard::Key::S && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				setPosition(Vector(getPosition().getX(), getPosition().getY() + .5));
			}
			if (m->getKey() == Keyboard::Key::A && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				setPosition(Vector(getPosition().getX() - .5, getPosition().getY()));
			}
			if (m->getKey() == Keyboard::Key::D && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				setPosition(Vector(getPosition().getX() + .5, getPosition().getY()));
			}
			return 1;
		}
		if (p_e->getType() == df::OUT_EVENT) {
			LM.writeLog(3, "EventOut");
			return 1;
		}
		return 0;
	}

	void testObject::setColor(int c) {
		//color = c;
	}

	/*//Draws testObject
	int testObject::draw() {
		return DM.drawCh(getPosition(), testObject_CHAR, color);
	}*/

}