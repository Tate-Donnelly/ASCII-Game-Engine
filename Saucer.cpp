#include "Saucer.h"
#include "Event.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventView.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include <iostream>

namespace df {
	//Constructor
	Saucer::Saucer() {
		setType("Saucer");
		setSprite("saucer");

		setAltitude(3);

		setColor(df::RED);

		setPosition(Vector(25 + rand() % 50, 3 + rand() % 10));
		setSolidness(HARD);

		LM.writeLog(3, "Saucer created! ID %d", getId());
	}



	//Destructor
	Saucer::~Saucer() {
		LM.writeLog(3, "Saucer deleted! ID %d", getId());
	}
	//Handles events
		//Returns 0 when ignored
	int Saucer::eventHandler(const Event* p_e) {
		if (p_e->getType() == df::KEYBOARD_EVENT) {//testObject moves to the cursor when clicked
			EventKeyboard* m = (EventKeyboard*)p_e;
			LM.writeLog(0, "Key %d", m->getKey());
			if (m->getKey() == Keyboard::Key::Q && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				GM.setGameOver(true);

			}
			return 1;
		}
		if (p_e->getType() == df::STEP_EVENT) {
			if (((EventStep*)p_e)->getStepCount() % 30 == 0) {
				EventView ev("Steps", 1, true);
				GM.onEvent(&ev);
			}
			return 1;
		}
		if (p_e->getType() == OUT_EVENT) {
			LM.writeLog(3, "EventOut ID: %d ", getId());
			LM.writeLog("X: %f %f", getPosition().getX(), getPosition().getX()+getBox().getHorizontal());
			LM.writeLog("Y: %f %f", getPosition().getY(), getPosition().getY()+getBox().getVertical());
			return 1;
		}
		if (p_e->getType() == df::UNDEFINED_EVENT) {
			LM.writeLog(0, "Undefined Event!");
			return 1;
		}
		return 0;
	}

	void Saucer::setColor(int new_color) {
		m_color = new_color;
	}

	int Saucer::getColor() {
		return m_color;
	}
}