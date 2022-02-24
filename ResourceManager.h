#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "SpriteResourceManager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"

#include <string>
#include <iostream>
#include <fstream>

#define RM df::ResourceManager::getInstance()


namespace df {

	// Maximum number of unique assets in game.
	//const int MAX_SPRITES = 1000;

	// Delimiters used to parse Sprite files -
	// the ResourceManager "knows" file format.
	#define HEADER_TOKEN "HEADER"
	#define BODY_TOKEN "BODY"
	#define FOOTER_TOKEN "FOOTER"
	#define FRAMES_TOKEN "frames"
	#define TRANSPARENCY_TOKEN "transparency"
	#define HEIGHT_TOKEN "height"
	#define WIDTH_TOKEN "width"
	#define COLOR_TOKEN "color"
	#define SLOWDOWN_TOKEN "slowdown"
	#define END_FRAME_TOKEN "end"
	#define VERSION_TOKEN "version"
	const int MAX_SOUNDS = 64;
	const int MAX_MUSICS = 64;
	class ResourceManager : public SpriteResourceManager {

	private:
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&); 
		ResourceManager();	           
		Sprite* m_p_sprite[MAX_SPRITES]; //Array of sprites.
		int m_sprite_count;	           //Count of number of loaded sprites.

		Sound m_sound[MAX_SOUNDS];	// Array of sound buffers.
		int m_sound_count;	        // Count of number of loaded sounds.
		Music m_music[MAX_MUSICS];	// Array of music buffers.
		int m_music_count;	        // Count of number of loaded musics.

	public:
		//Get the one and only instance of the ResourceManager.
		static ResourceManager& getInstance();

		//Get ResourceManager ready to manage resources.
		int startUp() override;

		//Shut down manager, freeing up any allocated Sprites, Music and Sounds.
		void shutDown() override;

		
		//Load Sprite from file.
		//Assign indicated label to Sprite.
		//Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		//Unload Sprite with indicated label.
		//Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		//Find Sprite with indicated label.
		//Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		// Load Sound from file.
		// Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		// Remove Sound with indicated label.
		// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		// Find Sound with indicated label.
		// Return pointer to it if found, else NULL.
		Sound* getSound(std::string label);

		// Associate file with Music.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		// Remove label for Music with indicated label.
		// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		// Find Music with indicated label.
		// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);
	};

}
#endif 