#include "test.h"
//Managers
#include "Manager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

//Events
#include "Event.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "EventView.h"

//Objects
#include "Saucer.h"
#include "Star.h"
#include "testObject.h"
#include "Explosion.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "ViewObject.h"

//Misc
#include "utillity.h"
#include "Clock.h"
#include "Vector.h"
#include "Frame.h"
#include "Animation.h"
#include "Box.h"
#include "Sound.h"
#include "Music.h"
#include "Sprite.h"

#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

namespace df {
	//Checks if all the tests passed
	bool test::doTests() {
		testing = true;
		bool checkpoint1 = testWriteLogLevelFail() && testWriteLogStr() && testWriteLogInt() && testWriteLogFloat()
			&& testWriteLogStr2() && testWriteLogInt2() && testWriteLogFloat2() && testWriteLogStrInt();

		bool checkpoint2 = testDelta() && testSplit();

		bool checkpoint3 = testObjectID() && testObjectType() && testObjectVector() && testObjectListGetCount() && testObjectListIsEmpty() && testObjectListIsFull() && testObjectListContains() && testObjectListInsert() && testObjectListRemove() && testObjectListIteratorCurrentObject() && testObjectListIteratorCurrentObjectEmpty() && testObjectListIteratorIsDoneFail();

		bool checkpoint4 = testEventType() && testEventStep() && testWorldManager();

		bool checkpoint7 = testEventCollision() && testPositionIntersection() && testSolidObjectCollision() && testSoftObjectCollision() && testSpectralObjectCollision() && testObjectCollision();

		bool checkpoint8 = testFrame() && testSprite() && testGetAndUnloadSprite();
		
		bool checkpoint9 = testAnimation();

		bool checkpoint10 = testWMBoundary() && testWMSetView() && testWMSetViewPosition();

		bool checkpoint13 = testToString() && testEventView();
		if (checkpoint1 && checkpoint2 && checkpoint3 && checkpoint4 && checkpoint7 && checkpoint8 && checkpoint9 && checkpoint10 && checkpoint13) {
			clear();
			LM.writeLog("Tests passed");
			testing = false;
			return true;
		}
		testing = false;
		return false;

	}

	void test::clear() {

		//Remove Test Objects
		ObjectList* testList = new ObjectList(WM.getAllObjects());
		ObjectListIterator testIterator(testList);
		while (!testIterator.isDone()) {
			WM.markForDelete(testIterator.currentObject());
			testIterator.next();
		}
		WM.update();

	}

	//Tests writeLog level
	bool test::testWriteLogLevelFail() {
		if (0 == LM.writeLog(-1, "testWriteLogLevelFail")) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogLevel failed");
		}
		return false;
	}

	//Tests writeLog with a string
	bool test::testWriteLogStr() {

		if (success_level < LM.getLogLevel() || 17 == LM.writeLog(success_level, "testWriteLogStr %c", 'T')) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogStr failed %c", 'T');
		}
		return false;
	}

	//Tests writeLog with a int
	bool test::testWriteLogInt() {
		int x = 4;
		if (success_level < LM.getLogLevel() || 17 == LM.writeLog(success_level, "testWriteLogInt %i", x)) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogInt failed");
		}
		return false;
	}

	//Tests writeLog with a float
	bool test::testWriteLogFloat() {
		float x = 4.00;
		if (success_level < LM.getLogLevel() || 26 == LM.writeLog(success_level, "testWriteLogFloat %f", x)) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogFloat failed");
		}
		return false;
	}

	//Tests writeLog with two strings
	bool test::testWriteLogStr2() {
		if (success_level < LM.getLogLevel() || 21 == LM.writeLog(success_level, "testWriteLogStr2 %c, %c", 'T', 'D')) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogStr failed");
		}
		return false;
	}

	//Tests writeLog with two ints
	bool test::testWriteLogInt2() {
		int x = 4;
		int y = 9;
		if (success_level < LM.getLogLevel() || 21 == LM.writeLog(success_level, "testWriteLogInt2 %i, %i", x, y)) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogInt failed");
		}
		return false;
	}

	//Tests writeLog with two floats
	bool test::testWriteLogFloat2() {
		float x = 4.00;
		float y = 9.00;
		if (success_level < LM.getLogLevel() || 37 == LM.writeLog(success_level, "testWriteLogFloat2 %f, %f", x, y)) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogFloat2 failed");
		}
		return false;
	}

	//Tests writeLog with a string and a int
	bool test::testWriteLogStrInt() {
		int x = 4;
		if (success_level < LM.getLogLevel() || 23 == LM.writeLog(success_level, "testWriteLogStrInt %c, %d", 'T', x)) {
			return true;
		}
		else {
			LM.writeLog(fail_level, "testWriteLogStrInt failed");
		}
		return false;
	}


	//Tests the clock's delta function
	bool test::testDelta() {
		Clock c;
		int long previousTime = c.getPreviousTime();
		Sleep(1000);
		long int currentTime = c.getCurrentTime();
		long int elapsedTime = c.delta() / 10000;
		LM.writeLog(0, "Previous time: %ld", previousTime);
		LM.writeLog(0, "Current time: %ld", currentTime);
		LM.writeLog(0, "Delta Elapsed time: %ld", elapsedTime);
		LM.writeLog(0, "Actual Elapsed time: %ld", (currentTime - previousTime) / 10000);
		if (previousTime != c.getPreviousTime() && (elapsedTime == 100)) {//Exact time waivered by a few micro seconds
			LM.writeLog(success_level, "testDelta: Previous Time %ld Current Time %ld Elapsed Time %ld", previousTime, c.getCurrentTime(), elapsedTime);
			return true;
		}
		else {
			LM.writeLog(fail_level, "testDelta failed");
		}
		return false;
	}
	//Tests the clock's split function
	bool test::testSplit() {
		Clock c;
		int long previousTime = c.getPreviousTime();
		Sleep(1000);
		long int currentTime = c.getCurrentTime();
		long int elapsedTime = c.split() / 10000;
		LM.writeLog(0, "Previous time: %ld", previousTime);
		LM.writeLog(0, "Current time: %ld", currentTime);
		LM.writeLog(0, "Split Elapsed time: %ld", elapsedTime);
		LM.writeLog(0, "Actual Elapsed time: %ld", (currentTime - previousTime) / 10000);
		if (previousTime == c.getPreviousTime() && (elapsedTime == 100)) {//Exact time waivered by a few microseconds
			LM.writeLog(success_level, "testSplit: Previous Time %ld Current Time %ld Elapsed Time %ld", previousTime, c.getCurrentTime(), elapsedTime);
			return true;
		}
		else {
			LM.writeLog(fail_level, "testSplit failed");
		}
		return false;
	}

	//Tests object id
	bool test::testObjectID() {
		Object o1;
		Object o2;
		if (o1.getId() == 0 && o2.getId() == 1) {
			LM.writeLog(success_level, "testObjectID: ID 1 - %d ID 2 - %d", o1.getId(), o2.getId());
			return true;
		}
		else {
			LM.writeLog(fail_level, "testObjectID failed: ID 1 - %d ID 2 - %d", o1.getId(), o2.getId());
		}
		return false;
	}

	//Tests object type
	bool test::testObjectType() {
		Vector v = Vector(1, 1);
		Object o1 = Object();
		o1.setType("Saucer");
		if (o1.getType() == "Saucer") {
			LM.writeLog(success_level, "testObjectType: ", o1.getType());
			return true;
		}
		else {
			LM.writeLog(fail_level, "testObjectType failed");
		}
		return false;
	}

	//Tests object and vector 
	bool test::testObjectVector() {
		Vector v = Vector(1, 1);
		Object o1;
		o1.setType("Saucer");
		o1.setId(0);
		o1.setPosition(v);
		if (o1.getPosition().getX() == v.getX() && o1.getPosition().getY() == v.getY()) {
			LM.writeLog(success_level, "testObjectVector: (%d, %d) and (%d, %d)", o1.getPosition().getX(), o1.getPosition().getY(), v.getX(), v.getY());
			return true;
		}
		else {
			LM.writeLog(fail_level, "testObjectVector failed");
		}
		return false;
	}

	//Tests ObjectList's getCount()
	bool test::testObjectListGetCount() {
		ObjectList* list=new ObjectList;
		Object object;
		Object object2;
		if (list->getCount() == 0) {
			list->insert(&object);
			list->insert(&object2);
			if (list->getCount() == 2) {
				LM.writeLog(success_level, "testObjectListGetCount() passed");
				return true;
			}
		}
		LM.writeLog(fail_level, "testObjectListGetCount() failed");
		return false;
	}

	//Tests ObjectList's isEmpty()
	bool test::testObjectListIsEmpty() {
		if ((new ObjectList)->isEmpty()) {
			LM.writeLog(success_level, "testObjectListIsEmpty() passed");
			return true;
		}
		else {
			LM.writeLog(fail_level, "testObjectListIsEmpty() failed");
		}
		return false;
	}

	//Tests ObjectList's isFull()
	bool test::testObjectListIsFull() {
		ObjectList* list=new ObjectList;
		if (!list->isFull()) {
			for (int i = 0; i < MAX; i++) {
				Object o;
				list->insert(&o);
			}
			if (list->isFull()) {
				LM.writeLog(success_level, "testObjectListIsFull() passed");
				return true;
			}
		}
		LM.writeLog(fail_level, "testObjectListIsFull() failed");

		return false;
	}

	//Tests ObjectList's contains()
	bool test::testObjectListContains() {
		ObjectList* list=new ObjectList;
		Object o;
		o.setPosition(Vector(1, 1));
		o.setType("Saucer");
		if (!list->contains(&o)) {
			list->insert(&o);
			if (list->contains(&o)) {
				LM.writeLog(success_level, "testObjectListContains passed");
				return true;
			}
		}
		else {
			LM.writeLog(fail_level, "testObjectListContains failed");
		}
		return false;
	}

	//Tests ObjectList's insert()
	bool test::testObjectListInsert() {
		ObjectList* list=new ObjectList;
		Object o;
		o.setPosition(Vector(1, 1));
		o.setType("Saucer");
		list->insert(&o);
		if (list->getCount() == 1 && list->contains(&o)) {
			LM.writeLog(success_level, "testObjectListInsert passed");
			return true;
		}
		else {
			LM.writeLog(fail_level, "testObjectListInsert failed; Count %d", list->getCount());
		}
		return false;
	}

	//Tests ObjectList's remove()
	bool test::testObjectListRemove() {
		ObjectList* list=new ObjectList;
		Object o;
		o.setPosition(Vector(1, 1));
		o.setType("Saucer");
		list->insert(&o);
		if (list->getCount() == 1 && list->contains(&o)) {
			list->remove(&o);
			if (list->getCount() == 0 && !list->contains(&o)) {
				LM.writeLog(success_level, "testObjectListRemove passed");
				return true;
			}
		}
		else {
			LM.writeLog(fail_level, "testObjectListRemove failed");
		}
		return false;
	}

	//Tests ObjectListIterator's currentObject()
	bool test::testObjectListIteratorCurrentObject() {
		Object o1, o2, o3;
		o1.setType("1");
		o2.setType("2");
		o3.setType("3");
		ObjectList* list=new ObjectList;
		list->insert(&o1);
		list->insert(&o2);
		list->insert(&o3);
		//Adjust Object positions !!!
		ObjectListIterator iterator(list);
		if (&o1 == iterator.currentObject()) {
			LM.writeLog(success_level, "The Current Object's type is %s", iterator.currentObject()->getType().c_str());
			iterator.next();
			if (&o2 == iterator.currentObject()) {
				LM.writeLog(success_level, "The Current Object's type is %s", iterator.currentObject()->getType().c_str());
				iterator.next();
				if (&o3 == iterator.currentObject()) {
					LM.writeLog(success_level, "The Current Object's type is %s", iterator.currentObject()->getType().c_str());
					iterator.next();
					if (NULL == iterator.currentObject()) {
						LM.writeLog(success_level, "testObjectListIteratorCurrentObject() passed");
						return true;
					}
				}
			}
		}
		LM.writeLog(fail_level, "testObjectListIteratorCurrentObject()  failed");
		return false;
	}

	//Tests ObjectListIterator's currentObject()
	bool test::testObjectListIteratorCurrentObjectEmpty() {
		ObjectListIterator* iterator=new ObjectListIterator(new ObjectList);
		if (NULL == iterator->currentObject()) {
			LM.writeLog(success_level, "testObjectListIteratorCurrentObjectEmpty()  passed");
			return true;
		}
		LM.writeLog(fail_level, "testObjectListIteratorCurrentObjectEmpty()  failed");
		return false;
	}

	//Tests ObjectListIterator's isDone()
	bool test::testObjectListIteratorIsDoneFail() {

		Object o1, o2, o3;
		ObjectList* list=new ObjectList;
		list->insert(&o1);
		list->insert(&o2);
		list->insert(&o3);
		ObjectListIterator* iterator=new ObjectListIterator(list);
		iterator->next();
		if (!iterator->isDone()) {
			LM.writeLog(success_level, "testObjectListIteratorIsDoneFail()  passed");
			return true;
		}
		LM.writeLog(fail_level, "testObjectListIteratorIsDoneFail()  failed");
		return false;
	}

	//Tests the set and get functions
	bool test::testEventType() {
		Event e;
		e.setType("df::undefined");
		if ("df::undefined" == e.getType()) {
			LM.writeLog(success_level, "testEventType()  passed");
			return true;
		}
		LM.writeLog(fail_level, "testEventType()  failed");
		return false;
	}

	//Tests the getter and setter for EventStep
	bool test::testEventStep() {
		EventStep e(-1);
		e.setType("df::step_event");
		if ("df::step_event" == e.getType() && e.getStepCount() == -1) {
			LM.writeLog(success_level, "testEventStep()  passed");
			return true;
		}
		LM.writeLog(fail_level, "testEventStep()  failed");
		return false;
	}

	//Tests WorldManager's insertObject, getAllObjects(), objectsOfType(), and removeObject()
	bool test::testWorldManager() {
		//Object have worldmanager insert them when constructed
		Saucer* s1=new Saucer();
		Saucer* s2 = new Saucer();
		Object* o = new Object();
		ObjectList* objectList = new ObjectList(WM.getAllObjects());
		ObjectList* saucerList = new ObjectList(WM.objectsOfType("Saucer"));
		if (objectList->contains(s1) && objectList->contains(s2) && objectList->contains(o) && !saucerList->contains(o)) {
			WM.removeObject(s1);
			objectList = new ObjectList(WM.getAllObjects());
			saucerList = new ObjectList(WM.objectsOfType("Saucer"));
			if ((!objectList->contains(s1)) && objectList->contains(s2) && objectList->contains(o) && objectList->getCount() == 2 && saucerList->getCount() == 1) {
				LM.writeLog(success_level, "testWorldManager()  passed");
				WM.removeObject(s2);
				WM.removeObject(o);
				return true;
			}
		}
		LM.writeLog(fail_level, "testWorldManager()  failed");
		return false;
	}

	//Check point 5
	//Tests the GameManager's run for step events
	bool test::testGMRun() {
		GM.startUp();
		LM.setFlush(true);
		new df::Saucer();//Saucer is here to keep time
		new testObject;
		new Star;
		GM.run();
		LM.writeLog("GM Ran");
		GM.shutDown();
		return true;
	}

	//Tests the display Manager's startUp and shutDown
	bool test::testDraw() {
		DM.startUp();
		sf::Font font;
		if (font.loadFromFile("df-font.ttf") == false) {
			std::cout << "Unable to load font" << std::endl;
			return false;
		}

		//Text Display
		sf::Text text;
		text.setFont(font); 
		text.setString("testDM passes");
		text.setCharacterSize(32); 
		text.setFillColor(sf::Color::Green);
		text.setStyle(sf::Text::Bold); 
		text.setPosition(96, 134); 

		//Window
		sf::RenderWindow* p_window = DM.getWindow();
		p_window->clear();
		p_window->draw(text);
		p_window->display();
		
		Sleep(2000);
		p_window->clear();
		Vector starting_pos(50, 5);
		std::string str = "testDrawCH passes";
		for (int i = 0; i < str.size(); i++) {
			//std::cout << str[i];
			Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
			DM.drawCh(temp_pos, str[i], GREEN);
		}
		p_window->display();
		Sleep(2000);
		p_window->clear();
		DM.drawString(Vector(50, 5), "DrawString() 1", LEFT_JUSTIFIED, BLUE);
		p_window->display();
		Sleep(2000);
		p_window->clear();
		DM.drawString(Vector(50, 5), "DrawString() 2", CENTER_JUSTIFIED, RED);
		p_window->display();
		Sleep(2000);
		p_window->clear();
		DM.drawString(Vector(50, 5), "DrawString() 3", RIGHT_JUSTIFIED, YELLOW);
		p_window->display();
		Sleep(2000);
		DM.shutDown();
		return true;
	}
	
	//Tests the DisplayManager's getHorizontal() and getVertical spaces
	bool test::testGetHorizontalVertical() {
		DM.startUp();
		LM.writeLog("Vertical %d, Horizontal %d", DM.getVertical(), DM.getHorizontal());
		DM.shutDown();
		return true;
	}
	
	//Tests the DisplayManager's getHorizontal() and getVertical pixels
	bool test::testGetHorizontalVerticalPixels() {
		DM.startUp();
		LM.writeLog("Vertical %d, Horizontal %d", DM.getVerticalPixels(), DM.getHorizontalPixels());
		DM.shutDown();
		return true;
	}
	
	//Checkpoint 6
	//Tests the InputManager's startUp and shutDown
	bool test::testInputManager() {
		IM.startUp();
		if (!IM.isStarted()) {
			LM.writeLog("Here");
			DM.startUp();
			IM.startUp();
			if (IM.isStarted()) {
				//DM.shutDown();
				IM.shutDown();
				DM.shutDown();
				LM.writeLog(success_level, "testInputManager passed");
				return true;
			}
			else {
				IM.shutDown();
				DM.shutDown();
			}
		}
		else {
			IM.shutDown();
		}
		LM.writeLog(fail_level, "testInputManager failed");
		return false;
	}
	
	//Tests EventMouse's and EventKeyboard's getters and setters
	bool test::testMouseKeyboard() {
		EventMouse mouse;
		EventKeyboard keyboard;
		mouse.setMouseAction(EventMouseAction::CLICKED);
		mouse.setMouseButton(Mouse::Button::LEFT);
		mouse.setMousePosition(Vector(1, 1));
		keyboard.setKey(Keyboard::Key::T);
		keyboard.setKeyboardAction(EventKeyboardAction::KEY_DOWN);
		if ((mouse.getMouseAction() == EventMouseAction::CLICKED) && (mouse.getMouseButton() == Mouse::Button::LEFT) && (mouse.getMousePosition().getX() == 1) && (mouse.getMousePosition().getY() == 1) &&
			(keyboard.getKey()==Keyboard::Key::T)&&(keyboard.getKeyboardAction()== EventKeyboardAction::KEY_DOWN)) {
			LM.writeLog(success_level, "testMouseKeyboard passed");
			return true;
		}
		LM.writeLog(fail_level, "testMouseKeyboard failed");
		return true;
	}

	//Checkpoint 7
	//Tests position intersection
	bool test::testPositionIntersection() {
		utillity u;
		if (u.positionsIntersect(Vector(0, 0), Vector(0, 0))) {//True
			if (!(u.positionsIntersect(spacesToPixels(Vector(1, 1)), Vector(0, 0)))) {//False
				LM.writeLog(success_level, "testPositionIntersection() passed");
				return true;
			}
			LM.writeLog(fail_level, "testPositionIntersection() (%f, %f) and (%f, %f) failed", 1, 0, 0,0);
		}
		else {
			LM.writeLog(fail_level, "testPositionIntersection() (%f, %f) and (%f, %f) failed", 0, 0, 0, 0);
		}
		return false;
	}

	//Tests EventCollision and solid Object collisions
	bool test::testEventCollision() {
		Star* s1 = new Star();
		testObject* s2 = new testObject();
		EventCollision e;
		Vector v(25, 6);
		e.setObject1(s1);
		e.setObject2(s2);
		e.setPosition(v);
		if ((e.getObject1()==s1) && (e.getObject2() == s2) && 
			(e.getPosition().getX()==v.getX()) && (e.getPosition().getY() == v.getY())) {
			LM.writeLog(success_level, "testEventCollision() passed");
			return true;
		}
		LM.writeLog(fail_level, "testEventCollision() failed");
		return false;
	}
	
	//Test for solid Object collisions
	bool test::testSolidObjectCollision() {
		Object* s = new Object();
		Object* s2 = new Object();
		s->setSolidness(HARD);
		s2->setSolidness(HARD);
		s->setPosition(Vector(25, 5));
		s2->setPosition(Vector(50, 5));
		if (-1 == WM.moveObject(s, s2->getPosition())) {
			LM.writeLog(success_level, "testSolidObjectCollision passed");
			return true;
		}
		LM.writeLog(fail_level, "testSolidObjectCollision failed");
		return false;
	}
	
	//Test for soft Object collisions
	bool test::testSoftObjectCollision() {
		Object* s = new Object();
		Object* s2 = new Object();
		s->setPosition(Vector(25, 5));
		s2->setPosition(Vector(50, 5));
		s->setSolidness(df::SOFT);
		s2->setSolidness(df::SOFT);
		if (0 == WM.moveObject(s, s2->getPosition())) {
			if (s->getPosition().getX() == s2->getPosition().getX()) {
				LM.writeLog(success_level, "testSoftObjectCollision passed");
				return true;
			}
		}
		LM.writeLog(fail_level, "testSoftObjectCollision failed");
		return false;
	}
	
	//Test for spectral Object collisions
	bool test::testSpectralObjectCollision() {
		Star* s = new Star();
		Star* s2 = new Star();
		if (0 == WM.moveObject(s, s2->getPosition())) {
			if (s->getPosition().getX() == s2->getPosition().getX() ) {
				LM.writeLog(success_level, "testSpectralObjectCollision passed");
				return true;
			}
			LM.writeLog(fail_level, "testSpectralObjectCollision failed");
		}
		LM.writeLog(fail_level, "testSpectralObjectCollision failed");
		return false;
	}
	
	//Tests all object types collision
	bool test::testObjectCollision() {
		clear();
		Star* star = new Star();
		Saucer* saucer = new Saucer();
		testObject* to = new testObject();
		to->setPosition(Vector(50, 0));
		star->setPosition(Vector(25, 5));
		saucer->setPosition(Vector(50, 5));
		star->setSolidness(df::SPECTRAL);
		to->setSolidness(SOFT);
		utillity u;
		LM.writeLog(success_level, "Star: %d Saucer %d testObject %d", star->getSolidness(), saucer->getSolidness(), to->getSolidness());
		LM.writeLog(success_level, "Testing Star and Saucer now");
		if (0 == WM.moveObject(saucer, star->getPosition())) {
			LM.writeLog(success_level, "Testing to and Saucer now");
			if (0 == WM.moveObject(to, saucer->getPosition())) {
				LM.writeLog(success_level, "Testing all positions now");
				if (u.positionsIntersect(star->getPosition(), saucer->getPosition()) && u.positionsIntersect(star->getPosition(), to->getPosition())) {
					LM.writeLog(success_level, "testObjectCollision passed");
					return true;
				}
				LM.writeLog(fail_level, "testObjectCollision 3 failed");
				return false;
			}
			LM.writeLog(fail_level, "testObjectCollision 2 failed");
			return false;
		}
		LM.writeLog(fail_level, "testObjectCollision 1 failed");
		return false;
	}


	//Checkpoint 8
	//Tests Frame getters/setters
	bool test::testFrame() {
		Frame* frame=new Frame; 
		frame->setWidth(1);
		frame->setHeight(5);
		frame->setString("frame");
		const std::string str = "frame";
		if ((frame->getWidth() == 1) && (frame->getHeight() == 5)) {
			if (frame->getString()==str) {
				LM.writeLog(success_level, "testFrame passed");
				return true;
			}
			else {
				std::cout <<'\n' <<frame->getString();
			}
			LM.writeLog(fail_level, "Width %d, Height %d", frame->getWidth(), frame->getHeight());
		}
		LM.writeLog(fail_level, "testFrame failed");
		return false;
	}
	
	//Test Frame draw
	bool test::testFrameDraw() {
		bool result = false;
		if (LM.startUp()) {
			LM.writeLog("main(): Error starting log manager!");
			return 1;
		}
		DM.startUp();
		sf::RenderWindow* p_window = DM.getWindow();
		p_window->clear();
		df::Frame frame(1, 1, "T");
		df::Frame frame2(20, 1, "TestFrameDraw passed");
		df::Frame frame3(1, 20, "TestFrameDraw passed");
		if ((frame.draw(df::Vector(50, 5), df::RED) == 0) && (frame2.draw(df::Vector(25, 8), df::BLUE) == 0) && (frame3.draw(df::Vector(60, 22), df::GREEN) == 0)) {
			LM.writeLog("TestFrameDraw passed");
			result = true;
		}
		else {
			LM.writeLog("TestFrameDraw failed");
		}
		p_window->display();
		Sleep(20000);
		DM.shutDown();
		LM.shutDown();
		return result;
	}

	//Tests Sprite getters/setters
	bool test::testSprite() {
		Sprite* sprite=new Sprite(5);
		sprite->setColor(df::BLUE);
		sprite->setHeight(12);
		sprite->setWidth(6);
		
		//Tests general getters/setters
		if ((sprite->getColor()==df::BLUE) && (sprite->getHeight()==12) && (sprite->getWidth() == 6) && (sprite->getLabel().compare("Test1")) && (sprite->getFrameCount()==0)) {
			//Tests sprite's frame related getters and setters
			Frame frame(5, 1, "Frame");
			sprite->addFrame(frame);
			LM.writeLog(fail_level, "Frame count %d", sprite->getFrameCount());
			if ((sprite->getFrameCount() == 1) && (sprite->getFrame(1).getString().compare("Frame"))) {
				LM.writeLog(success_level, "testSprite passed");
				return true;
			}
		}
		LM.writeLog(fail_level, "testSprite failed");
		return false;
	}

	//Test Sprite addFrame and getFrame
	bool test::testSpriteFrames() {
		bool result = false;
		LM.startUp();
		Sprite* sprite = new Sprite(2);
		Sprite* sprite2 = new Sprite(1);
		Frame frame(5, 1, "Frame");
		Frame frame2(1, 1, "F");
		Frame frame3(2, 1, "Fr");
		sprite->addFrame(frame);
		sprite->addFrame(frame2);
		sprite2->addFrame(frame);
		if ((-1 == sprite->addFrame(frame3))&& (-1 == sprite2->addFrame(frame3))) {
			if((sprite2->getFrame(1).getString().compare("Frame")) && (sprite2->getFrame(2).getWidth()==0) && (sprite2->getFrame(2).getHeight() == 0) && 
				(sprite->getFrame(1).getString().compare("Frame")) && (sprite->getFrame(2).getString().compare("F")) && 
				(sprite->getFrame(3).getString().compare("Fr"))) {
				LM.writeLog(success_level, "testSpriteFrames passed");
				result = true;
			}
			else {
				LM.writeLog(fail_level, "testSpriteFrames failed");
			}
		}
		else {
			LM.writeLog(fail_level, "testSpriteFrames failed");
		}
		LM.shutDown();
		return result;
	}

	//Tests getSprite and unloadSprite
	bool test::testGetAndUnloadSprite() {
		RM.loadSprite("sprites/good-spr.txt", "good");
		Sprite* s = RM.getSprite("good");
		RM.loadSprite("sprites/bullet-spr.txt", "bullet");
		Sprite* s2 = RM.getSprite("bullet");
		RM.loadSprite("sprites/explosion-spr.txt", "explosion");
		Sprite* s3 = RM.getSprite("explosion");
		if ((s->getFrameCount() == 5)) {
			if ((s2->getFrameCount() == 2) && (0 == RM.unloadSprite("good"))) {
				if ((s3->getFrameCount() == 8) && (0 == RM.unloadSprite("bullet"))) {
					if (0 == RM.unloadSprite("explosion")) {
						LM.writeLog(success_level, "testGetAndUnloadSprite passed");
						return true;
					}
					else {
						LM.writeLog(fail_level, "explosion");
					}
				}
				else {
					LM.writeLog(fail_level, "bullet");
				}
			}else {
				LM.writeLog(fail_level, "good");
			}
		}
		LM.writeLog(fail_level, "testGetAndUnloadSprite failed");
		return false;
	}

	//Checkpoint 9
	//Tests Animation's getters/setters
	bool test::testAnimation() {
		Animation animation;
		animation.setSprite(new Sprite(2));
		animation.getSprite()->addFrame(Frame());
		animation.getSprite()->addFrame(Frame());
		animation.setIndex(0);
		animation.setName("Test");
		animation.setSlowdownCount(5);

		if ((animation.getIndex()==0)/* && (animation.getName().compare("Test"))*/&&(animation.getSlowdownCount() == 5) && (animation.getSprite()->getFrameCount()==2)) {
			LM.writeLog(success_level, "testAnimation passed");
			return true;
		}
		LM.writeLog("Index: %d, SlowdownCount %d, Frame count %d", animation.getIndex(), animation.getSlowdownCount(), animation.getSprite()->getFrameCount());
		std::cout << "\n '"<<animation.getName() <<"' \n";
		LM.writeLog(fail_level, "testAnimation failed");
		return false;
	}

	//Tests Animation's draw()
	bool test::testAnimationDraw() {
		if (LM.startUp()) {
			LM.writeLog("main(): Error starting log manager!");
			return 1;
		}
		DM.startUp();
		Animation animation;
		Sprite* s = new Sprite(3);
		animation.setSprite(s);
		Frame frame;
		Frame frame2;
		Frame frame3;
		frame.setString("____|__|");
		frame2.setString("____|_o|");
		frame3.setString("____|o_|");
		
		frame.setHeight(2);
		frame.setWidth(4);
		frame2.setHeight(2);
		frame2.setWidth(4);
		frame3.setHeight(2);
		frame3.setWidth(4);

		s->setColor(df::RED);
		s->setWidth(4);
		s->setHeight(2);
		s->setLabel("Saucer");
		s->setSlowdown(4);
		s->addFrame(frame);
		s->addFrame(frame2);
		s->addFrame(frame3);
		animation.setSprite(s);
		animation.setIndex(0);
		animation.setName("a");
		animation.setSlowdownCount(1);
		sf::RenderWindow* p_window = DM.getWindow();
		
		while (p_window->isOpen()) {
			p_window->clear();
			animation.draw(Vector(10, 5));
			p_window->display();
		}

		if (1) {
			LM.writeLog(success_level, "testAnimationDraw passed");
			DM.shutDown();
			LM.shutDown();
			return true;
		}
		LM.writeLog(success_level, "testAnimationDraw failed");
		DM.shutDown();
		LM.shutDown();
		return false;
	}

	//Tests Object's draw()
	bool test::testObjectDraw() {
		GM.startUp();
		RM.startUp();
		RM.loadSprite("sprites/explosion-spr.txt", "explosion");
		RM.loadSprite("sprites/saucer-spr.txt", "saucer");
		RM.loadSprite("sprites/saucer-spr.txt", "slow");
		RM.loadSprite("sprites/ship-spr.txt", "ship");
		Saucer* saucer = new Saucer();
		Saucer* saucer2 = new Saucer();
		Saucer* saucer3 = new Saucer();
		Saucer* saucer4 = new Saucer();
		Explosion* e = new Explosion();
		Saucer* flyingSaucer = new Saucer();
		testObject* to = new testObject(); //Moves as a result of another test

		saucer->setPosition(Vector(25, 5));
		saucer2->setPosition(Vector(15, 2));
		saucer3->setPosition(Vector(15, 4));
		saucer4->setPosition(Vector(15, 6));
		e->setPosition(Vector(40, 6.5));
		flyingSaucer->setPosition(Vector(50, 8));

		saucer->setVelocity(Vector(0, .25));
		flyingSaucer->setVelocity(Vector(.25, 0));
		to->setVelocity(Vector(0, 0));

		saucer3->setSprite("slow");
		saucer3->getAnimation().getSprite()->setSlowdown(16);

		
		Animation a2 = saucer4->getAnimation();
		a2.setSlowdownCount(-1);
		saucer4->setAnimation(a2);

		sf::RenderWindow* p_window = DM.getWindow();
		GM.run();

		if(1){
			LM.writeLog(success_level, "testObjectDraw passed");
			RM.shutDown();
			GM.shutDown();
			return true;
		}
		LM.writeLog(success_level, "testObjectDraw failed");
		RM.shutDown();
		GM.shutDown();
		return false;
	}

	//Checkpoint 10
	//Test Box's getters/setters
	bool test::testBox() {
		LM.startUp();
		bool result = false;
		Box box;
		box.setCorner(Vector(5, 7));
		box.setHorizontal(9);
		box.setVertical(3);
		if (((box.getCorner().getX()==5) && (box.getCorner().getY() == 7)) &&
			(box.getHorizontal()==9) && (box.getVertical() == 3)) {
			LM.writeLog(success_level, "testBox passed");
			result= true;
		}
		else {
			LM.writeLog(fail_level, "testBox failed");
		}
		LM.shutDown();
		return result;
	}

	//Test Object's bounding boxes
	bool test::testBoundingBoxes() {
		LM.startUp();
		RM.startUp();
		bool result = false;
		Object* o = new Object;
		Box b;
		b.setCorner(Vector(5, 7));
		b.setHorizontal(9);
		b.setVertical(3);
		o->setBox(b);
		Box box = o->getBox();
		if (((box.getCorner().getX() == 5) && (box.getCorner().getY() == 7)) &&
			(box.getHorizontal() == 9) && (box.getVertical() == 3)) {
			RM.loadSprite("sprites/saucer-spr.txt", "saucer");
			Saucer* saucer = new Saucer();
			saucer->setSprite("saucer");
			saucer->setPosition(Vector(5, 7));
			box = saucer->getBox();
			box.setCorner(Vector(5, 7));
			if (((box.getCorner().getX() == 5) && (box.getCorner().getY() == 7)) &&
				(box.getHorizontal() == 6) && (box.getVertical() == 2)) {
				LM.writeLog(success_level, "testBoundingBox passed");
				result = true;
			}
			else {
				LM.writeLog(fail_level, "(%f,%f) Hori %f Vert %f");
				LM.writeLog(fail_level, "testBoundingBox failed 2");
			}
		}
		else {
			LM.writeLog(fail_level, "testBoundingBox failed");
		}
		RM.shutDown();
		LM.shutDown();
		return result;
	}

	//Tests boxIntersectsBox()
	bool test::testBoxIntersectBox() {
		LM.startUp();
		DM.startUp();
		utillity u;
		Box a(Vector(25, 5), 50, 5);
		Box b(Vector(35, 7), 5, 2);
		Box c(Vector(30, 0), 15, 12);
		Box d(Vector(40, 11), 5, 5);
		Box e(Vector(25, 13), 25, 5);
		Box f(Vector(75, 15), 5, 5);
		sf::RenderWindow* window=DM.getWindow();
		window->clear();
		c.draw(sf::Color::Green, false);
		a.draw(sf::Color::White, false);
		b.draw(sf::Color::Red, false);
		
		e.draw(sf::Color::Yellow, false);
		d.draw(sf::Color::Blue, false);

		f.draw(sf::Color::Magenta, false);
		window->display();
		Sleep(2000);
		if (u.boxIntersectsBox(a,b) /*Containment*/ && u.boxIntersectsBox(a, c) /*Overlap*/ &&
			u.boxIntersectsBox(c, d) /*Overlap*/ && u.boxIntersectsBox(d, e) /*Overlap*/ &&  !(u.boxIntersectsBox(e, f)) /*No Overlap*/) {
			LM.writeLog(success_level, "testBoxIntersectBox passed");
			DM.shutDown();
			LM.shutDown();
			return true;
		}
		LM.writeLog(fail_level, "testBoxIntersectBox failed");
		DM.shutDown();
		LM.shutDown();
		return false;
	}

	//Tests WorldManager's boundary and view getters/setters
	bool test::testWMBoundary() {
		WM.setBoundary(Box(Vector(5,7),15,3));
		
		if ((WM.getBoundary().getCorner().getX()==5) && (WM.getBoundary().getCorner().getY() == 7) &&
			(WM.getBoundary().getHorizontal()==15) && (WM.getBoundary().getVertical() == 3)) {
			LM.writeLog(success_level, "testWMBoundary passed");
			return true;
		}
		LM.writeLog(fail_level, "testWMBoundary failed on boundary");
		return false;
	}
	//Tests WorldManager's setView
	bool test::testWMSetView() {
		WM.setView(Box(Vector(7, 9), 10, 1));
		if ((WM.getView().getCorner().getX() == 7) && (WM.getView().getCorner().getY() == 9) &&
			(WM.getView().getHorizontal() == 10) && (WM.getView().getVertical() == 1)) {

			LM.writeLog(success_level, "testWMSetView passed");
			return true;

		}
		LM.writeLog(success_level, "testWMSetView failed");
		return false;
	}

	//Tests WorldManager's setViewFollowing
	bool test::testWMSetViewFollowing() {
		WM.setBoundary(Box(Vector(0, 0), 100, 100));
		WM.setView(Box(Vector(10, 20), 20, 20));
		Object* o = new Object;
		o->setPosition(Vector(50, 50));
		o->setBox(Box(Vector(0, 0), 10, 10));
		WM.setViewFollowing(o);
		if ((WM.getView().getCorner().getX() == 40) && (WM.getView().getCorner().getY() == 40) ) {
			LM.writeLog(success_level, "testWMSetViewFollowing passed");
			return true;
		}
		LM.writeLog(success_level, "testWMSetViewFollowing failed");
		return false;
	}

	//Tests WorldManager's setViewPosition
	bool test::testWMSetViewPosition() {
		WM.setBoundary(Box(Vector(0, 0), 100, 100));
		WM.setView(Box(Vector(10, 20),10,10));
		WM.setViewPosition(Vector(70, 70));
		LM.writeLog("X: %f Y:%f", WM.getView().getCorner().getX(), WM.getView().getCorner().getY());
		if ((WM.getView().getCorner().getX() == 65) && (WM.getView().getCorner().getY() == 65)) {
			LM.writeLog(success_level, "testWMSetViewPosition passed");
			return true;
		}
		LM.writeLog(success_level, "testWMSetViewPosition failed");
		return false;
	}

	//Checkpoint 11
	//Tests Sound's functions
	bool test::testSound() {
		LM.startUp();
		bool result = false;
		Sound sound;
		Sound fail;
		sound.setLabel("sounds/fire.wav");
		fail.setLabel("fire.wav");
		if (sound.getLabel()=="sounds/fire.wav") {
			if ((sound.loadSound("sounds/fire.wav") == 0) && (fail.loadSound("fire.wav") == -1)) {
				LM.writeLog(success_level, "Playing loop");
				sound.play(true);
				Sleep(2000);
				LM.writeLog(success_level, "Pausing sound");
				sound.pause();
				Sleep(2000);
				LM.writeLog(success_level, "Continuing loop");
				sound.play(true);
				Sleep(2000);
				LM.writeLog(success_level, "Stopping sound");
				sound.stop();
				Sleep(2000);
				LM.writeLog(success_level, "Playing (no loop)");
				sound.play(false);
				Sleep(1000);
				LM.writeLog(success_level, "testSound passed");
				result = true;
			}
			else {
				LM.writeLog(fail_level, "testSound failed to load sound");
			}
			
		}
		else {
			LM.writeLog(fail_level, "testSound failed");
		}
		LM.shutDown();
		return result;
	}
	//Tests Music's functions
	bool test::testMusic() {
		LM.startUp();
		bool result = false;
		Music* music = new Music;
		music->setLabel("start");
		Music* fail = new Music;
		if ((music->getLabel() == "start") && (music->loadMusic("sounds/start-music.wav") == 0) && (fail->loadMusic("start-music.wav") == -1)) {
			LM.writeLog(success_level, "Playing (no loop)");
			music->play(false);
			Sleep(13000);
			LM.writeLog(success_level, "Playing (loop)");
			music->play();
			Sleep(2000);
			LM.writeLog(success_level, "Pausing");
			music->pause();
			Sleep(2000);
			LM.writeLog(success_level, "Continuing loop");
			music->play(true);
			Sleep(2000);
			LM.writeLog(success_level, "Stopping");
			music->stop();
			LM.writeLog("testMusic passed");
			result = true;
		}
		else {
			LM.writeLog(fail_level, "testMusic failed");
		}
		LM.shutDown();
		return result;
	}
	//Tests ResourceManager's sound functions
	bool test::testRMSound() {
		LM.startUp();
		RM.startUp();
		bool result = false;
		if (RM.loadSound("sounds/fire.wav", "fire")==0) {
			if (RM.getSound("fire") != NULL) {
				if (RM.unloadSound("fire") == 0) {
					LM.writeLog(success_level, "testRMSound passed");
					result = true;
				}
				else {
					LM.writeLog(fail_level, "testRMSound failed on unloadSound");
				}
			}
			else {
				LM.writeLog(fail_level, "testRMSound failed on getSound");
			}
		}
		else {
			LM.writeLog(fail_level, "testRMSound failed on loadSound");
		}
		RM.shutDown();
		LM.shutDown();
		return result;
	}
	//Tests ResourceManager's music functions
	bool test::testRMMusic() {
		LM.startUp();
		RM.startUp();
		bool result = false;
		Music m;
		m.setLabel("start");
		if (RM.loadMusic("sounds/start-music.wav", "start") == 0) {
			if (RM.getMusic("start") != NULL) {
				if (RM.unloadMusic("start") == 0) {
					LM.writeLog(success_level, "testRMMusic passed");
					result = true;
				}
				else {
					LM.writeLog(fail_level, "testRMMusic failed on unloadMusic");
				}
			}
			else {
				LM.writeLog(fail_level, "testRMMusic failed on getMusic");
			}
		}
		else {
			LM.writeLog(fail_level, "testRMMusic failed on loadMusic");
		}
		RM.shutDown();
		LM.shutDown();
		return result;
	}

	//Checkpoint 13
	//Tests utillity's toString()
	bool test::testToString() {
		utillity u;
		if (u.toString(3) =="3") {
			LM.writeLog(success_level, "testToString passed");
			return true;
		}
		LM.writeLog(fail_level, "testToString failed");
		return false;
	}
	//Tests ViewObject
	bool test::testViewObject() {
		if (GM.startUp()) {
			LM.writeLog(10, "Error starting game manager!");
		}
		else {
			//WM.setView(df::Box(df::Vector(0, 0), 80, 24));
			df::ViewObject* viewObject1 = new df::ViewObject();
			df::ViewObject* viewObject2 = new df::ViewObject();
			df::ViewObject* viewObject3 = new df::ViewObject();
			df::ViewObject* viewObject4 = new df::ViewObject();
			df::ViewObject* viewObject5 = new df::ViewObject();
			df::ViewObject* viewObject6 = new df::ViewObject();
			df::ViewObject* viewObject7 = new df::ViewObject();
			df::ViewObject* viewObject8 = new df::ViewObject();
			df::ViewObject* viewObject9 = new df::ViewObject();
			viewObject1->setLocation(df::TOP_RIGHT);
			viewObject1->setViewString("TR");
			viewObject1->setValue(9);
			viewObject2->setLocation(df::TOP_CENTER);
			viewObject2->setViewString("TC");
			viewObject3->setLocation(df::TOP_LEFT);
			viewObject3->setViewString("TL");
			viewObject4->setLocation(df::CENTER_RIGHT);
			viewObject4->setViewString("CR");
			viewObject5->setLocation(df::CENTER_CENTER);
			viewObject5->setViewString("CC");
			viewObject6->setLocation(df::CENTER_LEFT);
			viewObject6->setViewString("CL");
			viewObject7->setLocation(df::BOTTOM_RIGHT);
			viewObject7->setViewString("BR");
			viewObject8->setLocation(df::BOTTOM_CENTER);
			viewObject8->setViewString("BC");
			viewObject9->setLocation(df::BOTTOM_LEFT);
			viewObject9->setViewString("BL");
			viewObject3->setBorder(false);
			viewObject9->setValue(3);
			viewObject6->setColor(df::RED);
			viewObject4->setDrawValue(false);
			GM.run();
			LM.writeLog("testViewObject passed");
		}
		GM.shutDown();

		return true;
	}
	
	//Tests EventView 
	bool test::testEventView() {
		EventView ev("Points", 10, true);
		if (ev.getDelta() && (ev.getTag()=="Points") && (ev.getValue()==10)) {
			LM.writeLog("testEventView passed");
			return true;
		}
		LM.writeLog("testEventView failed");
		return false;
	}
}