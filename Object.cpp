#include "Object.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventKeyboard.h"

namespace df {
	//Object constructor
		//add to WorldManager
	Object::Object() {
		static int max_id;
		setId(max_id);
		max_id++;

		m_position = Vector(0, 0);
		setType("Object");
		//Altitude
		setAltitude(MAX_ALTITUDE/2);

		//Kinematics
		m_direction = Vector(0, 0);
		float m_speed=0.25;

		//Box
		m_box = Box(Vector(0,0), 1, 1);


		LM.writeLog(0, "Object created! ID %d", getId());//Turned off for testing
		//Add self to game world (WorldManager)
		WM.insertObject(this);
	}

	//Object destructor
	//Removes object from the game world (WorldManager)
	Object::~Object() {
		LM.writeLog(0, "Object deleted! ID %d", getId());//Turned off for testing
		WM.removeObject(this);
	}

	//Sets the object's ID
	void Object::setId(int new_id) {
		m_id=new_id;
	}

	//Gets the object's ID
	int Object::getId() const {
		return m_id;
	}

	//Sets the object's type
	void Object::setType(std::string new_type) {
		m_type = new_type;
	}

	//Gets the object's type
	std::string Object::getType() const {
		return m_type;
	}

	//Sets the object's position
	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	//Gets the object's position
	Vector Object::getPosition() const {
		return m_position;
	}

	//Handles events
	//Returns 0 when ignored
	int Object::eventHandler(const Event* p_e) {
		if (p_e->getType() == df::KEYBOARD_EVENT) {//testObject moves to the cursor when clicked
			EventKeyboard* m = (EventKeyboard*)p_e;
			LM.writeLog(3, "Key %d", m->getKey());
			if (m->getKey() == Keyboard::Key::Q && m->getKeyboardAction() == EventKeyboardAction::KEY_DOWN) {
				GM.setGameOver(true);
				
			}
			return 1;
		}
		if (p_e->getType() == df::OUT_EVENT) {
			LM.writeLog(3, "EventOut");
			return 1;
		}
		return 0;
	}

	//Set altitude of Object with checks for range [0, MAX_ALTITUDE]
	//Return 0 if ok, else -1
	int Object::setAltitude(int new_altitude) {
		if (new_altitude <= MAX_ALTITUDE && new_altitude >= 0) {
			m_altitude = new_altitude;
			return 0;
		}
		LM.writeLog("Object's altitude is not possible");
		return -1;
	}

	//Return altitude of Object
	int Object::getAltitude() const {
		return m_altitude;
	}

	//Set speed of Object
	void Object::setSpeed(float speed) {
		m_speed = speed;
	}
	//Get speed of Object
	float Object::getSpeed() const {
		return m_speed;
	}
	//Set the direction of Object
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}
	//Get the direction of Object
	Vector Object::getDirection() const {
		return m_direction;
	}
	//Set direction and speed of Object
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude();
		new_velocity.normalize();
		m_direction = new_velocity;
	}
	//Get the velocity of Object based on direction and speed
	Vector Object::getVelocity() const {
		Vector v = m_direction;
		v.scale(m_speed);
		return v;
	}
	//Predict Object position based on speed and direction
	//Return predicted position
	Vector Object::predictPosition() {
		Vector new_pos = m_position + getVelocity();
		return new_pos;
	}

	//True if Hard or Soft, else false
	bool Object::isSolid() const {
		return (getSolidness() == df::HARD)|| (getSolidness() == df::SOFT);
	}
	//Set object solidness, with checks for consistency
	//Return 0 if ok, else -1
	int Object::setSolidness(Solidness new_solid) {
		if ((new_solid == df::HARD) || (new_solid == df::SOFT) || (new_solid == df::SPECTRAL)) {
			m_solidness = new_solid;
			return 0;
		}
		return -1;
	}
	//Return object solidness
	Solidness Object::getSolidness() const {
		return m_solidness;
	}

	//Animation
	//Set sprite for object to animate
	//Return 0 if ok, else -1
	int Object::setSprite(std::string sprite_label) {
		Sprite* p_sprite = RM.getSprite(sprite_label);
		if (p_sprite == NULL) {
			return -1;
		}
		m_animation.setSprite(p_sprite);
		setBox(m_animation.getBox());
		LM.writeLog(0, "Object::setSprite %f %f", m_animation.getBox().getCorner().getX(),m_animation.getBox().getCorner().getY());
		return 0;
	}

	//Set Animation for this Object
	//Set bounding box to size of associated Sprite
	void Object::setAnimation(Animation new_animation) {
		m_animation = new_animation;
	}

	//Get animation
	Animation Object::getAnimation() const {
		return m_animation;
	}

	int Object::draw() {
		Vector pos = getPosition();
		return m_animation.draw(pos);
	}

	// Set Object's bounding box.
	void Object::setBox(Box new_box) {
		m_box = new_box;
	}

	// Get Object's bounding box.
	Box Object::getBox() const {
		return m_box;
	}
}
