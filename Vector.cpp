#include "Vector.h"
#include <math.h>

namespace df {
	//Create Vector with (x,y)
	Vector::Vector(float init_x, float init_y) : m_x(init_x), m_y(init_y) {
	}

	// Default (0,0)
	Vector::Vector() : m_x(0), m_y(0) {
	}

	//Copy constructor
	Vector::Vector(const Vector& v) : m_x(v.m_x), m_y(v.m_y) {
	}

	//Assignment
	Vector& Vector::operator=(const Vector& v) {
		m_x = v.m_x;
		m_y = v.m_y;

		return *this;
	}

	//Get/Set horizontal
	void Vector::setX(float new_x) {
		m_x = new_x;
	}

	float Vector::getX() const {
		return m_x;
	}

	//Get/Set vertical
	void Vector::setY(float new_y) {
		m_y = new_y;
	}

	float Vector::getY() const {
		return m_y;
	}

	//Set horizontal and vertical components.
	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	//Return magnitude of vector.
	float Vector::getMagnitude() const {
		return (float)sqrt(m_x * m_x + m_y * m_y);
	}

	//Normalize vector.
	Vector& Vector::normalize() {
		float length = getMagnitude();

		if (length > 0) {
			m_x /= length;
			m_y /= length;
		}

		return *this;
	}

	//Scale vector.
	Vector& Vector::scale(float s) {
		m_x *= s;
		m_y *= s;

		return *this;
	}

	//Add two Vectors, return new Vector.
	Vector Vector::operator+(const Vector& other) const {
		Vector v(*this);
		return v += other;
	}

	//Subtract two Vectors, return new Vector.
	Vector Vector::operator-(const Vector& other) const {
		Vector v(*this);
		return v -= other;
	}

	//Add to current vector
	Vector& Vector::operator+=(const Vector& other) {
		m_x += other.m_x;
		m_y += other.m_y;

		return *this;
	}

	//Subtract vector from current vector
	Vector& Vector::operator-=(const Vector& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;

		return *this;
	}

	//Compare to vectors for equality
	bool Vector::operator==(const Vector& other) {
		return (m_x == other.m_x) && (m_y == other.m_y);
	}

	//Compare to vectors for inequality2
	bool Vector::operator!=(const Vector& other) {
		return !(*this == other);
	}

	//Multiply vector with scalar, return new Vector
	Vector Vector::operator*(float s) const {
		Vector v(*this);
		return v.scale(s);
	}

	//Syntactic sugar for scale
	Vector& Vector::operator*=(float s) {
		return scale(s);
	}
}