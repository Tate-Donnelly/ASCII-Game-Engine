#include "test.h"
#include "Manager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SpriteResourceManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "Saucer.h"
#include "Star.h"
#include "testObject.h"
#include "ViewObject.h"
#include "Vector.h"
#include "utillity.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
//#include "Enemy.h"
df::test T;

#define TEST(test_name) \
  if (test_name) \
    pass++; \
  else \
    fail++;


int main(int argc, char* argv[]) {
    //While many tests are run when run_engine=true, others tests need to be run seperately
    //Only one of the booleans below can be true
    bool run_engine = true; //Runs the engine

    //2b
    bool testInputManager = false; //Tests the InputManager's startUp and shutDown functions
    bool testGetInput = false; //Tests the getInput function
    bool testGMRun = false; //Tests the GameManager's run for step events
    bool testWindowSpaces = false;//Tests the DisplayManager's getHorizontal() and getVertical spaces
    bool testWindowPixels = false;//Tests the DisplayManager's getHorizontal() and getVertical pixels
    bool testDrawingFunctions = false; //Tests draw() and the DisplayManagers's startUp(), shutDown, drawCH(), and drawString()
    bool testVelocityAndCollisions = false; //Tests the velocity and collision functions
    bool testEventMouseAndEventKeyboard = false; //Tests EventMouse's and EventKeyboard's getters and setters
    
    //2c
    bool testGood();
    bool testBad();
    bool testBigBad();
    bool testFrameDraw = false; //Tests Frame's draw function
    bool testSpriteResourceManager = false;//Tests provided with the SpriteResourceManager
    bool testSpriteFrames = false; //Test Sprite addFrame and getFrame
    bool testAnimationDraw = false; //Tests the Animation draw()
    bool testObjectDraw = false; //Tests the Object draw()
    bool testBox = false; //Tests the Box's getters and setters
    bool testBoundingBoxes = false; //Tests the object's bounding box
    bool testBoxIntersectBox = false;//Tests boxIntersectBox
    bool testWMDraw = false;//Tests the world manager's draw function
    bool testBoundaryBoxCollision = false;//Tests collisions for objects with boundary boxes
    bool testWMSetViewFollowing = false; //Tests WorldManager's setViewFollowing()
    bool testAudio = false; //Tests the sound and music class and the ResourceManager's audio functions
    bool testViewObjects = false; //Tests ViewObject with GM's run

    if(run_engine){
        if (GM.startUp()) {
            LM.writeLog(10, "Error starting game manager!");
        }
        else {
            if (T.doTests()) {
                WM.setView(df::Box(df::Vector(0, 0), 80, 24));
                RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
                df::Object* start = new df::Object;
                start->setSprite("gamestart");
                start->setPosition(df::Vector(40, 12));
                LM.writeLog("(%f,%f)", start->getPosition().getX(), start->getPosition().getY());
                GM.run();
            }
            GM.shutDown();
        }
    }
    else if(testInputManager){
        LM.startUp();
        T.testInputManager();
        LM.writeLog("InputManager test passed");
        LM.shutDown();
    }
    //Change color by pressing 1-9, or move with W, A, S, and D
    //Click to have testObject move to your cursor
    else if (testGetInput) {
        LM.startUp();
        DM.startUp();
        IM.startUp();
        int i = 0;
        df::testObject* t = new df::testObject();

        t->setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/ 2));
        while (i < 900) {
            IM.getInput();
            WM.draw();
            DM.swapBuffers();
            i++;
        }
        IM.shutDown();
        DM.shutDown();
        LM.shutDown();
    }
    else if (testGMRun) {
        T.testGMRun();
    }
    else if (testDrawingFunctions) {
        LM.startUp();
        T.testDraw();
        LM.shutDown();
    }
    else if (testWindowSpaces) {
        LM.startUp();
        T.testGetHorizontalVertical();
        LM.shutDown();
    }
    else if (testWindowPixels) {
        LM.startUp();
        T.testGetHorizontalVerticalPixels();
        LM.shutDown();
    }
    else if (testVelocityAndCollisions || testWMDraw) {
        if (GM.startUp()) {
            LM.writeLog(10, "Error starting game manager!");
        }
        else {
            RM.loadSprite("sprites/saucer-spr.txt", "saucer");
            LM.setFlush(true);//Set flush of logfile during development
            df::Saucer* s1 = new df::Saucer();
            LM.writeLog("Box width %f height %f", s1->getBox().getHorizontal(), s1->getBox().getVertical());
            s1->setVelocity(df::Vector(.25, .25));
            s1->setPosition(df::Vector(50, 5));
            df::Saucer* s2 = new df::Saucer();
            s2->setVelocity(df::Vector(-.10, .25));
            s2->setPosition(df::Vector(25, 5));
            df::Saucer* s3 = new df::Saucer();
            s3->setVelocity(df::Vector(.75, -.10));
            df::Saucer* s4 = new df::Saucer();
            s4->setVelocity(df::Vector(0, -.25));
            df::Saucer* s5 = new df::Saucer();
            s5->setVelocity(df::Vector(.25, 0));
            GM.run();
            GM.shutDown();
        }
    }
    else if (testEventMouseAndEventKeyboard) {//Will run for 30 seconds 
        //Click A to change the sprite's colors
        //click on the display to have the testObject move there
        GM.startUp();
        LM.setFlush(true);
        T.testMouseKeyboard();
        new df::testObject;
        new df::Saucer();
        GM.run();
        LM.writeLog("GM Ran");
        GM.shutDown();
    }
    else if (testFrameDraw) {
        T.testFrameDraw();
    }
    else if(testSpriteResourceManager){
        // Start up LogManager.
        if (LM.startUp()) {
            LM.writeLog("main(): Error starting log manager!");
            return 1;
        }
        
        // Start up ResourceManager.
        if (RM.startUp()) {
            LM.writeLog("main(): Error starting resource manager!");
            return 1;
        }

        // Run tests.
        int pass = 0, fail = 0;
        TEST(testGood());
        TEST(testBad());
        TEST(testBigBad());
        LM.writeLog("----------------------");
        LM.writeLog("Summary: %d of %d tests pass.",
            pass, pass + fail);
        if (fail != 0)
            LM.writeLog("FAILURE");
        else
            LM.writeLog("SUCCESS");
        LM.writeLog("----------------------");

        // Shut everything down.
        RM.shutDown();
        LM.shutDown();
    }
    else if (testSpriteFrames) {
    T.testSpriteFrames();
    }
    else if (testAnimationDraw){
    
    T.testAnimationDraw();
    }
    else if (testObjectDraw) {
        T.testObjectDraw();
    }
    else if(testBox){
        T.testBox();
    }
    else if (testBoundingBoxes) {
    T.testBoundingBoxes();
    }
    else if (testBoxIntersectBox) {
    T.testBoxIntersectBox();
    }
    else if (testWMSetViewFollowing) {
    GM.startUp();
    T.testWMSetViewFollowing();
    GM.shutDown();
    }
    else if (testBoundaryBoxCollision) {
    if (GM.startUp()) {
        LM.writeLog(10, "Error starting game manager!");
    }
    else {
        RM.loadSprite("sprites/saucer-spr.txt", "saucer");
        LM.setFlush(true);//Set flush of logfile during development
        df::Saucer* s1 = new df::Saucer();
        s1->setPosition(df::Vector(30, 5));
        s1->setVelocity(df::Vector(0, 0));
        df::Saucer* s2 = new df::Saucer();
        s2->setPosition(df::Vector(55, 5));
        s2->setVelocity(df::Vector(-.25, 0));
        df::Saucer* s3 = new df::Saucer();
        s3->setPosition(df::Vector(30, 13));
        s3->setVelocity(df::Vector(0,-.25));
        df::utillity u;
        if (u.boxIntersectsBox(s1->getBox(), s3->getBox())) {
            LM.writeLog("Intersection");
        }
        else {
            LM.writeLog("Not Box Intersect");
        }
        GM.run();
        GM.shutDown();
    }
    }
    else if (testAudio) {
        T.testSound();
        T.testMusic();
        T.testRMSound();
        T.testRMMusic();
    }
    else if (testViewObjects) {
        T.testViewObject();
    }
    else {
    LM.startUp();
    LM.writeLog("Nothing ran");
    LM.shutDown();
    if (GM.startUp()) {
        LM.writeLog(10, "Error starting game manager!");
    }
    else {
        if (T.doTests()) {
            WM.setView(df::Box(df::Vector(0, 0), 80, 24));
            RM.loadSprite("sprites/saucer-spr.txt", "saucer");
            LM.setFlush(true);//Set flush of logfile during development
            df::Saucer* s1 = new df::Saucer();
            LM.writeLog("Box width %f height %f", s1->getBox().getHorizontal(), s1->getBox().getVertical());
            s1->setVelocity(df::Vector(.25, .25));
            s1->setPosition(df::Vector(50, 5));
            df::Saucer* s2 = new df::Saucer();
            s2->setVelocity(df::Vector(-.10, .25));
            s2->setPosition(df::Vector(25, 5));
            df::Saucer* s3 = new df::Saucer();
            s3->setVelocity(df::Vector(.75, -.10));
            df::Saucer* s4 = new df::Saucer();
            s4->setVelocity(df::Vector(0, -.25));
            df::Saucer* s5 = new df::Saucer();
            s5->setVelocity(df::Vector(.25, 0));

            GM.run();
        }
        GM.shutDown();
    }
    }
    
    return 0;
}

// Load good sprite.
// Return TRUE if test passes, else FALSE.
bool testGood() {
    if (RM.loadSprite("sprites/good-spr.txt", "good") != 0) {
        LM.writeLog("%s: FAIL - Error loading good sprite!", __FUNCTION__);
        return false;
    }

    LM.writeLog("%s: PASS", __FUNCTION__);
    return true;
}

// Load bad sprite.
// Return TRUE if test passes, else FALSE.
bool testBad() {

    if (RM.loadSprite("sprites/bad-spr.txt", "bad") == 0) {
        LM.writeLog("%s: FAIL - Loaded bad sprite, but should not have!",
            __FUNCTION__);
        return false;
    }

    LM.writeLog("%s: PASS", __FUNCTION__);
    return true;
}

// Load large, bad sprite.
// Return TRUE if test passes, else FALSE.
bool testBigBad() {

    if (RM.loadSprite("sprites/map-spr.txt", "map") == 0) {
        LM.writeLog("%s: FAIL - Loaded map sprite, but should not have!",  __FUNCTION__);
        return false;
    }

    LM.writeLog("%s: PASS", __FUNCTION__);
    return true;
}
