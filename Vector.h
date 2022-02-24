#pragma once
namespace df {
	class Vector
	{
	private:
		float m_x; //Horizontal component
		float m_y; //Vertical component
	public:
		//Creates a vector with (x,y)
		Vector(float init_x, float init_y);

		//Default 2d (x,y) is (0,0)
		Vector();

		//Get/set x
		void setX(float new_x);
		float getX() const;

		//Get/set y
		void setY(float new_y);
		float getY() const;

		//Sets x and y
		void setXY(float new_x, float new_y);

		//return the vector's magnitude
		float getMagnitude() const;

		//Normalize the vector
		void normalize();

		//Scale the vector
		void scale(float s);

		//Add two vectors and return their result
		Vector operator+(const Vector& other) const;
	};
}
