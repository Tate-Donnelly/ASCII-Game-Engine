#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <string>
#include <SFML/Audio.hpp>
namespace df {
	class Music
	{
	private:
		Music(Music const&);          // SFML doesn't allow music copy.
		void operator=(Music const&); // SFML doesn't allow music assignment.
		sf::Music m_music;	        // The SFML music.
		std::string m_label;	        // Text label to identify music.

	public:
		Music();

		// Associate music buffer with file.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename);

		// Set label associated with music.
		void setLabel(std::string new_label);

		// Get label associated with music.
		std::string getLabel() const;

		// Play music.
		// If loop is true, repeat play when done.
		void play(bool loop = true);

		// Stop music.
		void stop();

		// Pause music.
		void pause();

		// Return pointer to SFML music.
		sf::Music* getMusic();
	};
}
#endif

