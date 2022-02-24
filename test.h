
namespace df {
	class test
	{
	private:
		int success_level = 10;
		int fail_level = 10;
		bool testing=false;
	public:
		//Checks if all the tests passed
		bool doTests();
		void clear();

		//Check point 1
		//Tests writeLog level
		bool testWriteLogLevelFail();
		//Tests writeLog with a string
		bool testWriteLogStr();
		//Tests writeLog with a int
		bool testWriteLogInt();
		//Tests writeLog with a float
		bool testWriteLogFloat();
		//Tests writeLog with two strings
		bool testWriteLogStr2();
		//Tests writeLog with two ints
		bool testWriteLogInt2();
		//Tests writeLog with two floats
		bool testWriteLogFloat2();
		//Tests writeLog with a string and a int
		bool testWriteLogStrInt();


		//Check point 2
		//Tests the clock's delta function
		bool testDelta();
		//Tests the clock's split function
		bool testSplit();


		//Check point 3
		//Tests object id
		bool testObjectID();
		//Tests object type
		bool testObjectType();
		//Tests object and vector 
		bool testObjectVector();
		//Tests ObjectList's getCount()
		bool testObjectListGetCount();
		//Tests ObjectList's isEmpty()
		bool testObjectListIsEmpty();
		//Tests ObjectList's isFull()
		bool testObjectListIsFull();
		//Tests ObjectList's contains()
		bool testObjectListContains();
		//Tests ObjectList's insert()
		bool testObjectListInsert();
		//Tests ObjectList's remove()
		bool testObjectListRemove();
		//Tests ObjectListIterator's currentObject()
		bool testObjectListIteratorCurrentObject();
		//Tests ObjectListIterator's currentObject()
		bool testObjectListIteratorCurrentObjectEmpty();
		//Tests ObjectListIterator's isDone()
		bool testObjectListIteratorIsDoneFail();

		//Check point 4
		//Tests the set and get functions
		bool testEventType();
		//Tests the getter and setter for EventStep
		bool testEventStep();
		//Tests WorldManager's insertObject, getAllObjects(), objectsOfType(), and removeObject()
		bool testWorldManager();
		
		//Check point 5
		//Tests the GameManager's run for step events
		bool testGMRun();
		//Tests the display Manager's startUp and shutDown and all drawing functions
		bool testDraw();
		//Tests the DisplayManager's getHorizontal() and getVertical() spaces
		bool testGetHorizontalVertical();
		//Tests the DisplayManager's getHorizontal() and getVertical() pixels
		bool testGetHorizontalVerticalPixels();

		//Checkpoint 6
		//Tests the InputManager's startUp and shutDown
		bool testInputManager();
		//Tests EventMouse's and EventKeyboard's getters and setters
		bool testMouseKeyboard();

		//Checkpoint 7
		//Tests position intersection
		bool testPositionIntersection();
		//Tests EventCollision
		bool testEventCollision();
		//Test for solid Object collisions
		bool testSolidObjectCollision();
		//Test for soft Object collisions
		bool testSoftObjectCollision();
		//Test for spectral Object collisions
		bool testSpectralObjectCollision();
		//Tests all object types collision
		bool testObjectCollision();

		//Checkpoint 8
		//Tests Frame getters/setters
		bool testFrame();
		//Test Frame draw
		bool testFrameDraw();
		//Tests Sprite getters/setters
		bool testSprite();
		//Test Sprite addFrame and getFrame
		bool testSpriteFrames();
		//Tests getSprite and unloadSprite
		bool testGetAndUnloadSprite();

		//Checkpoint 9
		//Tests Animation's getters/setters
		bool testAnimation();
		//Tests Animation's draw()
		bool testAnimationDraw();
		//Tests Object's draw()
		bool testObjectDraw();

		//Checkpoint 10
		//Test Box's getters/setters
		bool testBox();
		//Test Object's bounding boxes
		bool testBoundingBoxes();
		//Tests boxIntersectsBox()
		bool testBoxIntersectBox();
		//Tests WorldManager's setBoundary
		bool testWMBoundary();
		//Tests WorldManager's setView
		bool testWMSetView();
		//Tests WorldManager's setViewFollowing
		bool testWMSetViewFollowing();
		//Tests WorldManager's setViewPosition
		bool testWMSetViewPosition();

		//Checkpoint 11
		//Tests Sound's functions
		bool testSound();
		//Tests Music's functions
		bool testMusic();
		//Tests ResourceManager's sound functions
		bool testRMSound();
		//Tests ResourceManager's music functions
		bool testRMMusic();

		//Checkpoint 13
		//Tests utillity's toString()
		bool testToString();
		//Tests ViewObject
		bool testViewObject();
		//Tests EventView and ViewObject
		bool testEventView();

	};

}