#include "Music.h"
namespace df {
	Music::Music() {
		m_label = "";
		m_music.setVolume(100);
	}
	// SFML doesn't allow music copy.
	Music::Music(Music const&) {} 

	// SFML doesn't allow music assignment.
	void Music::operator=(Music const&) {} 

	// Associate music buffer with file.
	// Return 0 if ok, else -1.
	int Music::loadMusic(std::string filename) {
		if (m_music.openFromFile(filename)==false) {
			return -1;
		}
		m_music.play();
		return 0;
	}

	// Set label associated with music.
	void Music::setLabel(std::string new_label) {
		m_label = new_label;
	}

	// Get label associated with music.
	std::string Music::getLabel() const {
		return m_label;
	}

	// Play music.
	// If loop is true, repeat play when done.
	void Music::play(bool loop) {
		m_music.setLoop(loop);
		m_music.play();
	}

	// Stop music.
	void Music::stop() {
		m_music.stop();
	}

	// Pause music.
	void Music::pause() {
		m_music.pause();
	}

	// Return pointer to SFML music.
	sf::Music* Music::getMusic() {
		return (&m_music);
	}
}