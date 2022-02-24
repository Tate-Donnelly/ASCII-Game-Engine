//
// SpriteResourceManager - Sprite management for the resource manager.
//
// Copyright 2017, 2019 by Mark Claypool and WPI
// All Rights Reserved
//

#ifndef __SPRITE_RESOURCE_MANAGER_H__
#define __SPRITE_RESOURCE_MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "LogManager.h"
#include "Sprite.h"

namespace df {

// Delimiters used to parse Sprite files -
// the SpriteResourceManager "knows" file format.
#define HEADER_TOKEN "HEADER"
#define BODY_TOKEN "BODY"
#define FOOTER_TOKEN "FOOTER"
#define FRAMES_TOKEN "frames"
#define HEIGHT_TOKEN "height"
#define WIDTH_TOKEN "width"
#define COLOR_TOKEN "color"
#define SLOWDOWN_TOKEN "slowdown"
#define END_FRAME_TOKEN "end"
#define VERSION_TOKEN "version"

// Maximum number of unique assets in game.
const int MAX_SPRITES = 1000;

class SpriteResourceManager : public Manager {

 private:
  Sprite *p_sprite[MAX_SPRITES]; // Array of (pointers to) Sprites.
  int m_sprite_count;	         // Count of number of loaded sprites.

 public:

  // Get SpriteResourceManager ready to manage resources.
  virtual int startUp();

  // Shut down manager, freeing up any allocated Sprites.
  virtual void shutDown();

  // Load Sprite from file.
  // Assign indicated label to Sprite.
  // Return 0 if ok, else -1.
  int loadSprite(std::string filename, std::string label);

  // Unload Sprite with indicated label.
  // Return 0 if ok, else -1.
  int unloadSprite(std::string label);

  // Find Sprite with indicated label.
  // Return pointer to it if found, else NULL.
  Sprite *getSprite(std::string label) const;
};

} // end of namespace df

#endif //__SPRITE_RESOURCE_MANAGER_H__
