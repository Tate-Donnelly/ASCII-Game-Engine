#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "ViewObject.h"
#include "Saucer.h"

#include "EventCollision.h"
#include "EventOut.h"
#include "utillity.h"

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
namespace df {
    WorldManager:: WorldManager() {
        setType("WorldManager");
        boundary.setHorizontal(0);
        boundary.setVertical(0);
        view.setHorizontal(0);
        view.setVertical(0);
    }

    WorldManager::WorldManager(WorldManager const&) {
        setType("WorldManager");
    }

    void WorldManager::operator=(WorldManager const&) {}

    //Get the one and only instance of the WorldManager
    WorldManager& WorldManager:: getInstance() {
        static WorldManager worldManager;
        return worldManager;
    }

    //Starts the game world and initializes everything to empty
    int WorldManager::startUp() {
        LM.writeLog(3, "WorldManager startUp()");
        DM.startUp();
        RM.startUp();
        Manager::startUp();
        return 0;
    }

    //Shuts down the game world and deletes all world Objects
    void WorldManager::shutDown() {
        LM.writeLog(3, "WorldManager shutDown()");
        if (m_updates.getCount() > 0) {
            //ObjectList temp = m_updates;
            ObjectListIterator li(new ObjectList(m_updates));
            for (li.first(); !li.isDone(); li.next()) {
                //std::cout<<li.currentObject()->getType();
                delete li.currentObject();
            }
        }
        RM.shutDown();
        DM.shutDown();
        Manager::shutDown();
    }

    //Insert Object into the world
    //Return 0 if ok, otherwise -1
    int WorldManager::insertObject(Object* p_o) {
        LM.writeLog(0, "Object %d inserted by WorldManager", p_o->getId());
        return m_updates.insert(p_o);
    }

    //Remove Objects from the world
    //Return 0 if ok, otherwise -1
    int WorldManager::removeObject(Object* p_o) {
        return m_updates.remove(p_o);
    }

    //Return list of all Objects in the world
    ObjectList WorldManager::getAllObjects() const {
        return m_updates;
    }

    //Return list of all Objects in world matching type
    ObjectList WorldManager::objectsOfType(std::string type) const {
        ObjectListIterator li(&m_updates);
        ObjectList* list=new ObjectList;
        for (li.first(); !li.isDone(); li.next()) {
            if (li.currentObject()->getType() == type) {
                list->insert(li.currentObject());
            }
        }
        return *list;
    }

    //Update world
    //Delete Objects marked for deletion
    void WorldManager::update() {
        ObjectListIterator li(&m_updates);
        for (li.first(); !li.isDone(); li.next()) {
            Object* object = li.currentObject();
            Vector new_pos = object->predictPosition();
            utillity u;
            if (u.positionsIntersect(object->getPosition(),new_pos)) {
                //move object
                moveObject(object, new_pos);
            }
        }
        ObjectListIterator dli(&m_deletions);
        for(dli.first();!dli.isDone(); dli.next()){
            Object* object = dli.currentObject();
            int id = object->getId();
            if (m_updates.contains(object)) {
                LM.writeLog(0, "Object %d is in m_updates", id);
            }
            delete(dli.currentObject());
            if (!m_updates.contains(dli.currentObject())) {
                LM.writeLog(0, "Object %d has been deleted and removed from m_updates", id);
            }
        }
        m_deletions.clear();
        LM.writeLog(0, "Update Complete");
    }

    //Indicate Object is to be deleted at end of current game loop
    //Return 0 if ok, else -1
    int WorldManager::markForDelete(Object* p_o) {
        LM.writeLog(3, "Object %d marked for deletion!", p_o->getId());
        ObjectListIterator li(&m_deletions);
        while (!li.isDone()) {
            if (li.currentObject() == p_o) {
                return 0;
            }
            li.next();
        }
        return m_deletions.insert(p_o);
    }

    void WorldManager::draw() {
        for (int alt = 0; alt < MAX_ALTITUDE; alt++) {
            ObjectListIterator li(&m_updates);
            while (!li.isDone()) {
                if (li.currentObject()->getAltitude()==alt) {
                    utillity u;
                    Object* p_temp_o = li.currentObject();
                    //Convert bounding box coordinates to world coordinates
                    Box temp_box = u.getWorldBox(p_temp_o);
                    LM.writeLog(0, "(%f,%f)", p_temp_o->getBox().getCorner().getX(),p_temp_o->getBox().getCorner().getY());
                    //Only draw if object would be visible on window
                    if (u.boxIntersectsBox(temp_box, view) || dynamic_cast <ViewObject*> (p_temp_o)) {
                        p_temp_o->draw();
                    }
                }
                li.next();
            }
        }
    }

    //Returns list of Object collided with at position where
    //Collisions are only with solid Objects
    //Does not consider if p_o is solid or not
    ObjectList WorldManager::getCollisions(Object* p_o, Vector where) const {
        ObjectListIterator* li = new ObjectListIterator(&m_updates);
        ObjectList* collisions = new ObjectList();
        utillity* u = new utillity;
        // World position bounding box for object at where
        Box box = u->getWorldBox(p_o, where);
        while (!li->isDone()) {
            Object* temp = li->currentObject();
            // World position bounding box for other object
            Box tempBox = u->getWorldBox(temp);
            LM.writeLog(0,"Box Corner (%f, %f) Width %f Height %f", box.getCorner().getX(), box.getCorner().getY(), box.getHorizontal(), box.getVertical());
            LM.writeLog(0,"TempBox Corner (%f, %f) Width %f Height %f", tempBox.getCorner().getX(), tempBox.getCorner().getY(), tempBox.getHorizontal(), tempBox.getVertical());
            if (temp != p_o) {
                if (u->boxIntersectsBox(box, tempBox)  && temp->isSolid()) {
                    LM.writeLog(0, "Collision Found");
                    collisions->insert(temp);
                }
            }
            li->next();
        }
        return *collisions;
    }

    //Move Object
    //If collision with solid, send collision events
    //If no collision with solid, move ok else don't move Object
    //If object is spectral, move ok
    //Return 0 if move ok, else -1 if collision with solid
    int WorldManager::moveObject(Object* p_o, Vector where) {
        Vector og_pos = p_o->getPosition();
        if (p_o->isSolid()) {

            //Get Collisions
            ObjectList* collisions = new ObjectList(getCollisions(p_o, where));

            if (!collisions->isEmpty()) {

                bool do_move = true;

                //Iterate over collisions list
                ObjectListIterator* li = new ObjectListIterator(collisions);
                for (li->first(); !li->isDone(); li->next()) {
                    Object* p_temp = li->currentObject();

                    LM.writeLog(0, "Object 1: %d Object 2: %d", p_o->getSolidness(), p_temp->getSolidness());
                    if (p_temp->isSolid()) {
                        //Create a collision event
                        EventCollision c(p_o, p_temp, where);
                        //Send to both objects
                        p_o->eventHandler(&c);
                        p_temp->eventHandler(&c);

                        //If both HARD, then cannot move
                        if ((p_o->getSolidness() == df::HARD) && (p_temp->getSolidness() == df::HARD)) {
                            do_move = false;//Can't move
                            LM.writeLog(0, "Collision! Object can't move!");
                        }
                    }
                }
                if (!do_move) {
                    return -1;
                }
            }
        }
       
        
        utillity u;
        // Do move.
        Box orig_box = u.getWorldBox(p_o);  // original bounding box
        p_o->setPosition(where);        // move object
        Box new_box = u.getWorldBox(p_o);   // new bounding box

        // If object moved from inside to outside world, generate
         // "out of bounds" event.
        if (u.boxIntersectsBox(orig_box, getBoundary()) && // Was in bounds?
            !(u.boxIntersectsBox(new_box, getBoundary()))) {  // Now out of bounds?
                EventOut ov;                              // Create "out" event
                p_o->eventHandler(&ov);  
                //
                LM.writeLog("Orig_box %f %f", orig_box.getCorner().getX(), orig_box.getCorner().getY());
                LM.writeLog("New_box %f %f", new_box.getCorner().getX(), new_box.getCorner().getY());
                LM.writeLog("Getboundary %f %f Width %f Height %f", getBoundary().getCorner().getX(), getBoundary().getCorner().getY(), getBoundary().getHorizontal(), getBoundary().getVertical());                // Send to Object
        }
        
        //If view is following this object, adjust view
        if (p_view_following == p_o) {
            setViewPosition(p_o->getPosition());
        }
        //If here, there hasn't been a collision between 2 HARD objects so allow move
        p_o->setPosition(where);
        LM.writeLog(0, "Object moved from (%f, %f) to (%f, %f)", p_o->getPosition().getX(), p_o->getPosition().getY(), p_o->predictPosition().getX(), p_o->predictPosition().getY());
        
        
        return 0;
    }

    // Set game world boundary.
    void WorldManager::setBoundary(Box new_boundary) {
        boundary = new_boundary;
    }

    // Get game world boundary.
    Box WorldManager::getBoundary() const{
        return boundary;
    }
    // Set player view of game world.
    void WorldManager::setView(Box new_view){
        view = new_view;
    }

    // Get player view of game world.
    Box WorldManager::getView() const{
        return view;
    }

    // Set view to center window on position view_pos.
    // View edge will not go beyond world boundary.
    void WorldManager::setViewPosition(Vector view_pos) {
        LM.writeLog(0, "Boundary H: %f V: %f", boundary.getHorizontal(), boundary.getVertical());
        LM.writeLog(0, "Hori %f Vert %f", view.getHorizontal()/2, view.getVertical()/2);
        // Make sure horizontal not out of world boundary.
        float x = view_pos.getX() - view.getHorizontal() / 2; //0
        LM.writeLog(0, "view_pos.getX() - view.getHorizontal() / 2 = %f", x);
        LM.writeLog(0, "x + view.getHorizontal() = %f", x + view.getHorizontal());
        if (x + view.getHorizontal() > boundary.getHorizontal()) {//20>100
            x = boundary.getHorizontal() - view.getHorizontal();//100-20=80
        }
        if (x < 0) {
            x = 0;
        }
        LM.writeLog(0, "boundary.getHorizontal() - view.getHorizontal() = %f", x);

        // Make sure vertical not out of world boundary.
        float y = view_pos.getY() - view.getVertical() / 2;//10
        LM.writeLog(0,"view_pos.getY() - view.getVertical() / 2 = %f", y);
        LM.writeLog(0, "y + view.getVertical() = %f", y + view.getVertical());
        if (y + view.getVertical() > boundary.getVertical()) {
            y = boundary.getVertical() - view.getVertical();
        }
        if (y < 0) {
            y = 0;
        }
        LM.writeLog(0, "boundary.getVertical() - view.getVertical() = %f", y);

        // Set view.
        Vector new_corner(x, y);
        view.setCorner(new_corner);
    }
    // Set view to center window on Object.
    // Set to NULL to stop following.
    // If p_new_view_following not legit, return -1 else return 0.
    int WorldManager::setViewFollowing(Object* p_new_view_following) {
        // Set to NULL to turn `off' following.
        if (p_new_view_following == NULL) {
            p_view_following = NULL;
            return 0;
        }

        ObjectListIterator* li=new ObjectListIterator(&m_updates);
        while (!li->isDone()) {
            // If found, adjust attribute accordingly and set view position.
            if (li->currentObject()==p_new_view_following) {
                p_view_following = p_new_view_following;
                setViewPosition(p_view_following->getPosition());
                return 0;
            }
        }

        // If we get here, was not legit.  Don't change current view.
        return -1;
    }
}