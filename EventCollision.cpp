#include "EventCollision.h"
#include "LogManager.h"
namespace df {
	EventCollision::EventCollision() {
        EventCollision(p_object1, p_object2, m_position);
	}

    EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) {
        setPosition(p);
        setObject1(p_o1);
        setObject2(p_o2);
        setType(COLLISION_EVENT);
        LM.writeLog(0, "EventCollision created");
    }

    //Getters and setters for objects in collision
    void EventCollision::setObject1(Object* o){
        p_object1 = o;
    }
    void EventCollision::setObject2(Object* o) {
        p_object2 = o;
    }
    Object* EventCollision::getObject1() {
        return p_object1;
    }
    Object* EventCollision::getObject2() {
        return p_object2;
    }

    //Getter and setter for the collision's position
    void EventCollision::setPosition(Vector v) {
        m_position = v;
    }
    Vector EventCollision::getPosition() {
        return m_position;
    }

}