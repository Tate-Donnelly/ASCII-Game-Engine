#include "ResourceManager.h"
#include <Windows.h>
namespace df {
	ResourceManager::ResourceManager(ResourceManager const&) {
		setType("ResourceManager");
		//m_p_sprite[MAX_SPRITES] = {};
	}
	void ResourceManager::operator=(ResourceManager const&) {}
	ResourceManager::ResourceManager() {
		setType("ResourceManager");
		//m_p_sprite[MAX_SPRITES] = {};
	}

	//Get the one and only instance of the ResourceManager.
	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager resourceManager;
		return resourceManager;
	}

	//Get ResourceManager ready to manage resources.
	int ResourceManager::startUp(){
		m_sprite_count = 0;
		m_music_count = 0;
		m_sound_count = 0;
		SpriteResourceManager::startUp();
		Manager::startUp();
		return 0;
	}

	//Shut down manager, freeing up any allocated Sprites, Music and Sounds.
	void ResourceManager::shutDown(){
		if (m_p_sprite != NULL) {
			while (m_sprite_count != 0) {
				delete m_p_sprite[m_sprite_count];
				m_sprite_count--;
			}
		}
		SpriteResourceManager::shutDown();
		Manager::shutDown();
	}
	
	//Load Sprite from file.
	//Assign indicated label to Sprite.
	//Return 0 if ok, else -1.
	int ResourceManager::loadSprite(std::string filename, std::string label) {
		return SpriteResourceManager::loadSprite(filename,label);
	}

	//Unload Sprite with indicated label.
	//Return 0 if ok, else -1.
	int ResourceManager::unloadSprite(std::string label) {
		return SpriteResourceManager::unloadSprite(label);
	}

	//Find Sprite with indicated label.
	//Return pointer to it if found, else NULL.
	Sprite* ResourceManager::getSprite(std::string label) const {
		return SpriteResourceManager::getSprite(label);
	}

	// Load Sound from file.
// Return 0 if ok, else -1.
	int ResourceManager::loadSound(std::string filename, std::string label) {

		if (m_sound_count == MAX_SOUNDS) {
			LM.writeLog("Sound array full.");
			return -1;
		}
		Sound s;
		//s.loadSound(filename);
		
		if (m_sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog("Unable to load from file");
			return -1;
		}

		// All is well.
		m_sound[m_sound_count].setLabel(label);
		m_sound_count++;
		return 0;
	}

	// Remove Sound with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadSound(std::string label) {
		for (int i = 0; i < m_sound_count; i++) {
			if (label == m_sound[i].getLabel()) {
				//Scoot over remaining sounds
				for (int j = i; j < m_sound_count - 2; j++) {
					m_sound[j] = m_sound[j + 1];
				}
				m_sound_count--;
				return 0;
			}
		}
		//Sound not found
		return -1;
	}

	// Find Sound with indicated label.
	// Return pointer to it if found, else NULL.
	Sound* ResourceManager::getSound(std::string label) {
		for (int i = 0; i < m_sound_count; i++) {
			if (m_sound[i].getLabel()==label) {
				return &m_sound[i];
			}
		}
		//Pointer not found
		return NULL;
	}

	// Associate file with Music.
	// Return 0 if ok, else -1.
	int ResourceManager::loadMusic(std::string filename, std::string label) {
		if (label == "") {
			LM.writeLog("Music's label is empty");
			return -1;
		}
		if (m_music_count == MAX_MUSICS) {
			LM.writeLog("Max music limit has been reached. Can not add music");
			return -1;
		}
		if (m_music[m_music_count].loadMusic(filename) == -1)
		{
			LM.writeLog("Music was unable to be loaded");
			return -1;
		}
		m_music[m_music_count].setLabel(label);
		m_music_count++;
		return 0;
	}

	// Remove label for Music with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadMusic(std::string label) {
		for (int i = 0; i < m_music_count; i++) {
			if (m_music[i].getLabel()==label) {
				m_music[i].setLabel("");
				return 0;
			}
		}
		//Error
		return -1;
	}

	// Find Music with indicated label.
	// Return pointer to it if found, else NULL.
	Music* ResourceManager::getMusic(std::string label) {
		for (int i = 0; i < m_music_count; i++) {
			if (m_music[i].getLabel()==label) {
				return &m_music[i];
			}
		}
		return NULL;
	}
}