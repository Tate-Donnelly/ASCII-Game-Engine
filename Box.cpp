#include "Box.h"
#include "utillity.h"
#include "LogManager.h"
#include "DisplayManager.h"
namespace df {
	// Create box with (0,0) for the corner, and 0 for horiz and vert.
	Box::Box() {
		setCorner(Vector());
		setHorizontal(0);
		setVertical(0);
	}

	// Create box with an upper-left corner, horiz and vert sizes.
	Box::Box(Vector init_corner, float init_horizontal, float init_vertical) {
		setCorner(init_corner);
		setHorizontal(init_horizontal);
		setVertical(init_vertical);
	}

	// Set upper left corner of box.
	void Box::setCorner(Vector new_corner) {
		m_corner = new_corner;
	}

	// Get upper left corner of box.
	Vector Box::getCorner() const {
		return m_corner;
	}

	// Set horizontal size of box.
	void Box::setHorizontal(float new_horizontal) {
		m_horizontal = new_horizontal;
	}

	// Get horizontal size of box.
	float Box::getHorizontal() const {
		return m_horizontal;
	}

	// Set vertical size of box.
	void Box::setVertical(float new_vertical) {
		m_vertical = new_vertical;
	}

	// Get vertical size of box.
	float Box::getVertical() const{
		return m_vertical;
	}
	
	//Draws a box
	void Box::draw(sf::Color c, bool transparentCenter) {
		utillity u;
		Vector view = u.worldToView(getCorner());
		Vector pixel = spacesToPixels(view);
		static sf::RectangleShape box;
		box.setOutlineColor(c);
		if (transparentCenter) {
			box.setFillColor(sf::Color::Transparent);
		}
		else {
			box.setFillColor(c);
		}
		box.setOutlineThickness(1.5);
		box.setSize(sf::Vector2f(getHorizontal() * charWidth(), getVertical() * charHeight()));
		box.setPosition(sf::Vector2f(pixel.getX(), pixel.getY()));
		DM.getWindow()->draw(box);
	}

}