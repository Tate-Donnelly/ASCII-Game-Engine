#include "Animation.h"
#include "LogManager.h"
namespace df {
	Animation::Animation() {
	}

	//Sets the sprite
	void Animation::setSprite(Sprite* p_new_sprite) {
		m_p_sprite = p_new_sprite;
		// Create Box around centered Sprite.
		Vector corner(-1 * (m_p_sprite->getWidth() / 2.0), -1 * (m_p_sprite->getHeight() / 2.0));
		Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());
		m_box = box;
	}
	//Gets the sprite
	Sprite* Animation::getSprite() const {
		return m_p_sprite;
	}
	//Sets the name
	void Animation::setName(std::string new_name) {
		m_name = new_name;
	}
	//Gets the name
	std::string Animation::getName() const {
		return m_name;
	}

	//Sets the index
	void Animation::setIndex(int new_index) {
		m_index = new_index;
	}
	//Gets the index
	int Animation::getIndex() const {
		return m_index;
	}

	//Sets the slowdown count
	void Animation::setSlowdownCount(int new_slowdown_count) {
		m_slowdown_count = new_slowdown_count;
	}
	//Gets the slowdown count
	int Animation::getSlowdownCount() const {
		return m_slowdown_count;
	}

	//Draw a single frame centered at position (x,y)
	//Drawing accounts for slowdown and advance Sprite frame
	//Return 0 if ok, else -1
	int Animation::draw(Vector position) {
		if (m_p_sprite == NULL) {
			return -1;
		}
	
		int index = getIndex();//Current frame

		//Ask Sprite to draw current frame
		if (-1 == m_p_sprite->draw(getIndex(), position)) {
			LM.writeLog("Could not draw sprite's frame");
			return -1;
		}

		//If slowdown count is -1, then the animation is frozen
		if (getSlowdownCount() == -1) {
			return 0;
		}
			

		//Increment count
		int count = getSlowdownCount() + 1;

		LM.writeLog(0, "Slowdown: %d Count: %d", m_p_sprite->getSlowdown(), count);
		//Advance sprite index, if appropriate
		if (count >= m_p_sprite->getSlowdown()) {  
			count = 0;
			index++;

			if (index >= m_p_sprite->getFrameCount()) {
				index = 0;
			}
			setIndex(index);
		}
		
		setSlowdownCount(count);
		return 0;
	}

	// Set Object's bounding box.
	void Animation::setBox(Box new_box) {
		m_box = new_box;
		
	}

	// Get Object's bounding box.
	Box Animation::getBox() const {
		// If no Sprite, return unit Box centered at (0,0).
		if (!m_p_sprite) {
			Box box(Vector(-0.5, -0.5), 0.99, 0.99);
			return box;
		}
		// Create Box around centered Sprite.
		Vector corner(-1 * (m_p_sprite->getWidth() / 2.0), 
					  -1 * (m_p_sprite->getHeight() / 2.0));
		Box box(corner, m_p_sprite->getWidth(), 
						m_p_sprite->getHeight());
		LM.writeLog(0,"Box width %f height %f", m_box.getHorizontal(), m_box.getVertical());
		LM.writeLog(0,"Animation::getBox() %f %f", box.getCorner().getX(), box.getCorner().getY());
		// Return box.
		return box;
	}
}
