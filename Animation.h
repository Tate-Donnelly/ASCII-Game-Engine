#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include "Sprite.h"
#include "Box.h"
namespace df {
	class Animation
	{
	private:
		Sprite* m_p_sprite;
		std::string m_name;
		int m_index;
		int m_slowdown_count;
		Box m_box;  // Box for sprite boundary & collisions.

	public:
		Animation();

		//Getters and Setters
		void setSprite(Sprite* p_new_sprite);
		Sprite* getSprite() const;

		void setName(std::string new_name);
		std::string getName() const;

		void setIndex(int new_index);
		int getIndex() const;

		void setSlowdownCount(int new_slowdown_count);
		int getSlowdownCount() const;

		//Draw a single frame centered at position (x,y)
		//Drawing accounts for slowdown and advance Sprite frame
		//Return 0 if ok, else -1
		int draw(Vector position);

		// Set Object's bounding box.
		void setBox(Box new_box);

		// Get Object's bounding box.
		Box getBox() const;
	};

}
#endif

