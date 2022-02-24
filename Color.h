#ifndef __COLOR_H__
#define __COLOR_H__
#include <SFML/Graphics.hpp>
namespace df {
	// Colors Dragonfly recognizes.
	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED=1,
		GREEN=2,
		YELLOW=3,
		BLUE=4,
		MAGENTA=5,
		CYAN=6,
		WHITE=7,
	};

	// If color not specified, will use this.
	const Color COLOR_DEFAULT = WHITE;

}
#endif
