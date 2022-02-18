#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "EventStep.h"
#include "Clock.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
namespace df {

	GameManager::GameManager() {
		setType("GameManager");
		loop_time = 0;
		frame_time = TARGET_TIME;
		game_over = false;
	}
	
	void GameManager::operator=(GameManager const&) {}

	GameManager& GameManager::getInstance() {
		static GameManager gameManager;
		return gameManager;
	}

	//Starts the game manager
	int GameManager::startUp() {
		LM.startUp();
		LM.writeLog(0, "GameManager startUp()");
		WM.startUp();
		IM.startUp();
		Box windowBox(Vector(0,0), DM.getHorizontal(), DM.getVertical());
		WM.setBoundary(windowBox);
		WM.setView(windowBox);
		LM.writeLog("Box width %f height %f", windowBox.getHorizontal(), windowBox.getVertical());
		Manager::startUp();
		timeBeginPeriod(1);
		return 0;
	}
	//Shuts the game manager down
	void GameManager::shutDown() {
		IM.shutDown();
		WM.shutDown();
		LM.writeLog(3, "GameManager shutDown()");
		LM.shutDown();
		Manager::shutDown();
		timeEndPeriod(1);
	}

	//Runs the game loop
	void GameManager::run() {
		LM.writeLog(3, "GameManager run()");
		Clock clock;
		int game_loop_count = 0;
		while (!getGameOver()) {
			game_loop_count++;
			loop_time = 0;
			clock.delta();

			//Send step event to all objects
			EventStep e(game_loop_count);
			onEvent(new EventStep(game_loop_count));

			//Get input (Key and mouse)
			IM.getInput();
			WM.update();
			WM.draw();
			DM.swapBuffers();
			loop_time = (clock.split() / 1000);//Measures how long the above steps took
			LM.writeLog(0, "Loop time %ld milliseconds", loop_time);
			
			if (TARGET_TIME > loop_time) {
				LM.writeLog(0, "Sleep for %ld milliseconds or %ld seconds", (TARGET_TIME - loop_time), (TARGET_TIME - loop_time) / 1000);
				Sleep(TARGET_TIME - loop_time);
			}
		}
		LM.writeLog(10, "Game loop is done");
	}

	//Set game over status
	//If true ends the game loop
	void GameManager::setGameOver(bool new_game_over) {
		game_over = true;
		LM.writeLog(10, "GameOver set to true");
	}

	//Gets the game over status
	bool GameManager::getGameOver() const {
		return game_over;
	}

	//Returns the frame time
	int GameManager::getFrameTime() const {
		return frame_time;
	}
}