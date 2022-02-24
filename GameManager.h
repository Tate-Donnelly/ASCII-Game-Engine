#pragma once
#include "Manager.h"

# define GM df :: GameManager :: getInstance ()
namespace df {
	const int TARGET_TIME = 33;
	class GameManager : public Manager
	{
	private:
		GameManager();
		GameManager(GameManager const&);
		void operator=(GameManager const&);
		int loop_time;
		bool game_over;
		int frame_time;
		
	public:
		//Gets the singleton instance of the GameManager
		static GameManager& getInstance();
		//Starts the game manager
		virtual int startUp();
		//Shuts the game manager down
		virtual void shutDown();

		//Runs the game loop
		void run();

		//Set game over status
		//If true ends the game loop
		void setGameOver(bool new_game_over = true);

		//Gets the game over status
		bool getGameOver() const;

		//Returns the frame time
		int getFrameTime() const;

		
	};
}
