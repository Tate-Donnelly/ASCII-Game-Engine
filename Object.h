#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Vector.h"
#include "Event.h"
#include "Animation.h"
#include "Box.h"
#include <string>

namespace df {
	enum Solidness {
		HARD,//Object causes collisions and impedes
		SOFT,//Object causes collisions, but doesn't impede
		SPECTRAL,//Doesn't cause collisions
	};
	class Object
	{
		
	private:
		//Objects game engine ID
		int m_id;

		//Object's Type
		std::string m_type;

		//Object's position
		Vector m_position;
		
		//Object's altitude
		int m_altitude;

		//Direction vector
		Vector m_direction;

		//Object's speed
		float m_speed;

		//Solidness of object
		Solidness m_solidness;

		Animation m_animation; //Animation associated with Object

		Box m_box;  // Box for sprite boundary & collisions.

	public:
		//Object constructor
		//add to WorldManager
		Object();

		//Object destructor
		//remove from WorldManager
		virtual ~Object();

		//Sets the object's ID
		void setId(int new_id);

		//Gets the object's ID
		int getId() const;

		//Sets the object's type
		void setType(std::string new_type);

		//Gets the object's type
		std::string getType() const;

		//Sets the object's position
		void setPosition(Vector new_pos);

		//Gets the object's position
		Vector getPosition() const;

		//Handles events
		virtual int eventHandler(const Event* p_e);

		//Set altitude of Object with checks for range [0, MAX_ALTITUDE]
		//Return 0 if ok, else -1
		int setAltitude(int new_altitude);

		//Return altitude of Object
		int getAltitude() const;

		//Set speed of Object
		void setSpeed(float speed);
		//Get speed of Object
		float getSpeed() const;
		//Set the direction of Object
		void setDirection(Vector new_direction);
		//Get the direction of Object
		Vector getDirection() const;
		//Set direction and speed of Object
		void setVelocity(Vector new_velocity);
		//Get the velocity of Object based on direction and speed
		Vector getVelocity() const;
		//Predict Object position based on speed and direction
		//Return predicted position
		Vector predictPosition();

		//Collision
		//True if Hard or Soft, else false
		bool isSolid() const; 
		//Set object solidness, with checks for consistency
		//Return 0 if ok, else -1
		int setSolidness(Solidness new_solid);
		//Return object solidness
		Solidness getSolidness() const;
		
		//Animation
		//Set sprite for object to animate
		//Return 0 if ok, else -1
		int setSprite(std::string sprite_label);

		//Set Animation for this Object
		//Set bounding box to size of associated Sprite
		void setAnimation(Animation new_animation);

		//Get animation
		Animation getAnimation() const;

		//Draw object Animation
		virtual int draw();

		// Set Object's bounding box.
		void setBox(Box new_box);

		// Get Object's bounding box.
		Box getBox() const;
	};

}
#endif
