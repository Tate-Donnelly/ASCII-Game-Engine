#ifndef __DF_VECTOR_H
#define __DF_VECTOR_H

namespace df {
	//2D Vector class
	class Vector {
	private:
		float m_x; //Horizontal
		float m_y; //Vertical

	public:
		//Create Vector with (x,y)
		Vector(float init_x, float init_y);

		// Default (0,0)
		Vector();

		//Copy constructor
		Vector(const Vector& v);

		//Assignment
		Vector& operator=(const Vector& v);

		//Get/Set horizontal
		void setX(float new_x);
		float getX() const;

		//Get/Set vertical
		void setY(float new_y);
		float getY() const;

		//Set horizontal and vertical components.
		void setXY(float new_x, float new_y);

		//Return magnitude of vector.
		float getMagnitude() const;

		//Normalize vector, return self as lval;
		Vector& normalize();

		//Scale vector, return self as lval;
		Vector& scale(float s);

		//Multiply vector with scalar, return new Vector
		Vector operator*(float s) const;

		//Add two Vectors, return new Vector.
		Vector operator+(const Vector& other) const;

		//Subtract two Vectors, return new Vector.
		Vector operator-(const Vector& other) const;

		//Syntactic sugar for scale
		Vector& operator*=(float s);

		//Add to current vector
		Vector& operator+=(const Vector& other);

		//Subtract vector from current vector
		Vector& operator-=(const Vector& other);

		//Compare to vectors for equality
		bool operator==(const Vector& other);

		//Compare to vectors for inequality2
		bool operator!=(const Vector& other);
	};
}

#endif /*DF_VECTOR_H*/