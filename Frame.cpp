#include "Frame.h"
#include "DisplayManager.h"
#include "LogManager.h"

namespace df {
	//Creates an empty frame
	Frame::Frame() {
		m_width = 0;
		m_height = 0;
		m_frame_str = "";
	}

	//Create frame of indicated width and height with string
	Frame::Frame(int new_width, int new_height, std::string frame_str) {
		setWidth(new_width);
		setHeight(new_height);
		setString(frame_str);
	}

	//Set width of frame
	void Frame::setWidth(int new_width) {
		m_width=new_width;
	}

	//Get width of frame
	int Frame::getWidth() const {
		return m_width;
	}

	//Set height of frame
	void Frame::setHeight(int new_height) {
		m_height = new_height;
	}

	//Get height of frame
	int Frame::getHeight() const {
		return m_height;
	}

	//Set frame characters (stored as string)
	void Frame::setString(std::string new_frame_str) {
		m_frame_str = new_frame_str;
	}

	//Get frame characters (stored as string)
	std::string Frame::getString() const {
		return m_frame_str;
	}

	//Draw self, centered at position (x,y) with color
	//Return 0 if ok, else -1
	//Note: top-left coordinate is (0,0)
	int Frame::draw(Vector position, Color color) const {
		if (m_frame_str.empty()) {
			return -1;
		}

		//Determine offset since centered at position
		float x_offset = (float)getWidth()/2;
		float y_offset = (float)getHeight()/2;

		//Draw character by character
		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				Vector temp_pos(position.getX() + x - x_offset,
								position.getY() + y - y_offset);
				DM.drawCh(temp_pos, m_frame_str[(y*m_width) + x], color);
			}
		}
		return 0;
	}
}