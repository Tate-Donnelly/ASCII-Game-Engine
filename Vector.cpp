#include "Vector.h"
#include <cmath>

namespace df {
	//Creates a vector with (x,y)
	Vector::Vector(float init_x, float init_y) {
		m_x = init_x;
		m_y = init_y;
	}

	//Default 2d (x,y) is (0,0)
	Vector::Vector() {
		m_x = 0;
		m_y = 0;
	}

	//Get/set x
	void Vector::setX(float new_x) {
		m_x = new_x;
	}
	float Vector::getX() const {
		return m_x;
	}

	//Get/set y
	void Vector::setY(float new_y) {
		m_y = new_y;
	}
	float Vector::getY() const {
		return m_y;
	}

	//Sets x and y
	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	//return the vector's magnitude
	float Vector::getMagnitude() const {
		float magnitude = sqrt(m_x * m_x + m_y * m_y);
		return magnitude;
	}

	//Normalize the vector
	void Vector::normalize() {
		float len = getMagnitude();
		if (len > 0) {
			m_x = m_x / len;
			m_y = m_y / len;
		}
	}

	//Scale the vector
	void Vector::scale(float s) {
		m_x = m_x * s;
		m_y = m_y * s;
	}

	//Add two vectors and return their result
	Vector Vector::operator+(const Vector& other) const {
		Vector v;
		v.m_x=m_x+other.m_x;
		v.m_y = m_y + other.m_y;
		return v;
	}

}