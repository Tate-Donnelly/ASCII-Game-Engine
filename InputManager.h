#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H_
#include "Manager.h"
#include <SFML/Graphics.hpp>

# define IM df :: InputManager :: getInstance ()
namespace df {
    class InputManager :
        public Manager
    {
    private:
        InputManager();
        InputManager(InputManager const&);
        void operator=(InputManager const&);
    public:
        //Get the instance of the InputManager
        static InputManager& getInstance();

        //Get window ready to capture input
        //Return 0 if ok, else -1
        int startUp();

        //Revert back to normal window mode
        void shutDown();

        //Get input from the keyboard and mouse
        //Pass event along to all Objects
        void getInput();
    };
}
#endif
