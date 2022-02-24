#include "Event.h"
#include "Object.h"

#ifndef __EVENT_COLLISION_H__
#define __EVENT_COLLISION_H__

namespace df {
    const std::string COLLISION_EVENT = "df::collision_event";
    class EventCollision :
        public Event
    {
    private:
        Object* p_object1;
        Object* p_object2;
        Vector m_position;
    public:
        EventCollision();
        EventCollision(Object* p_o1, Object* p_o2, Vector p);

        //Getters and setters for objects in collision
        void setObject1(Object* o);
        void setObject2(Object* o);
        Object* getObject1() const;
        Object* getObject2() const;

        //Getter and setter for the collision's position
        void setPosition(Vector v);
        Vector getPosition();
    };
}
#endif
