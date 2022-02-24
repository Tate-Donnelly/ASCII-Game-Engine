#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__
#include "Manager.h"
#include "ObjectList.h"
# define WM df :: WorldManager :: getInstance ()
const int MAX_ALTITUDE = 4;
namespace df {
    class WorldManager :
        public Manager
    {
    private:
        WorldManager();
        WorldManager(WorldManager const&);
        void operator=(WorldManager const&);

        ObjectList m_updates;
        ObjectList m_deletions;

        ObjectList m_objects_out;

        Box boundary;	 // World boundary.
        Box view;	 // Player view of game world.

        Object* p_view_following;//Object view is following
    public:
        
        //Get the one and only instance of the WorldManager
        static WorldManager& getInstance();

        //Starts the game world and initializes everything to empty
        int startUp();

        //Shuts down the game world and deletes all world Objects
        void shutDown();

        //Insert Object into the world
        //Return 0 if ok, otherwise -1
        int insertObject(Object* p_o);

        //Remove Objects from the world
        //Return 0 if ok, otherwise -1
        int removeObject(Object* p_o);

        //Return list of all Objects in the world
        ObjectList getAllObjects() const;

        //Return list of all Objects in world matching type
        ObjectList objectsOfType(std::string type) const;

        //Update world
        //Delete Objects marked for deletion
        void update();

        //Indicate Object is to be deleted at end of current game loop
        //Return 0 if ok, else -1
        int markForDelete(Object* p_o);
        //Draws all objects in m_updates
        void draw();

        //Returns list of Object collided with at position where
        //Collisions are only with solid Objects
        //Does not consider if p_o is solid or not
        ObjectList getCollisions(Object* p_o, Vector where) const;

        //Move Object
        //If collision with solid, send collision events
        //If no collision with solid, move ok else don't move Object
        //If object is spectral, move ok
        //Return 0 if move ok, else -1 if collision with solid
        int moveObject(Object* p_o, Vector where);

        // Set game world boundary.
        void setBoundary(Box new_boundary);

        // Get game world boundary.
        Box getBoundary() const;

        // Set player view of game world.
        void setView(Box new_view);

        // Get player view of game world.
        Box getView() const;

        // Set view to center window on position view_pos.
        // View edge will not go beyond world boundary.
        void setViewPosition(Vector view_pos);

        // Set view to center window on Object.
        // Set to NULL to stop following.
        // If p_new_view_following not legit, return -1 else return 0.
        int setViewFollowing(Object* p_new_view_following);
    };

}
#endif