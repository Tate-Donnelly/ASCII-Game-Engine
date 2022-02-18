#include "InputManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include <iostream>

namespace df {
    InputManager::InputManager() {}
    InputManager::InputManager(InputManager const&) {}
    void InputManager::operator=(InputManager const&) {}
    //Get the instance of the InputManager
    InputManager& InputManager::getInstance() {
        static InputManager inputManager;
        return inputManager;
    }

    //Get window ready to capture input
    //Return 0 if ok, else -1
    int InputManager::startUp() {
        if (!DM.isStarted()) {
            LM.writeLog("DM not started");
            return -1;
        }
        LM.writeLog("InputManager starting up");
        
        sf::RenderWindow* window = DM.getWindow();

        window->setKeyRepeatEnabled(false);
        
        Manager::startUp();
        return 0;
    }

    //Revert back to normal window mode
    void InputManager::shutDown() {
        if (DM.isStarted()) {
            sf::RenderWindow* window = DM.getWindow();
            window->setKeyRepeatEnabled(true);
        }
        LM.writeLog("InputManager shutting down");
        Manager::shutDown();
    }

    //SFML to Key
    static Keyboard::Key keyConverter(sf::Keyboard::Key sfmlkey) {
        switch (sfmlkey) {
        case sf::Keyboard::BackSpace:
            return Keyboard::Key::BACKSPACE;
        case sf::Keyboard::Space:
            return Keyboard::Key::SPACE;
        case sf::Keyboard::Return:
            return Keyboard::Key::RETURN;
        case sf::Keyboard::Escape:
            return Keyboard::Key::ESCAPE;
        case sf::Keyboard::Tab:
            return Keyboard::Key::TAB;
        case sf::Keyboard::Left:
            return Keyboard::LEFTARROW;
        case sf::Keyboard::Right:
            return Keyboard::RIGHTARROW;
        case sf::Keyboard::Up:
            return Keyboard::UPARROW;
        case sf::Keyboard::Down:
            return Keyboard::DOWNARROW;
        case sf::Keyboard::Pause:
            return Keyboard::PAUSE;
        case sf::Keyboard::Subtract:
            return Keyboard::MINUS;
        case sf::Keyboard::Add:
            return Keyboard::PLUS;
        case sf::Keyboard::Tilde:
            return Keyboard::TILDE;
        case sf::Keyboard::Period:
            return Keyboard::PERIOD;
        case sf::Keyboard::Comma:
            return Keyboard::COMMA;
        case sf::Keyboard::Slash:
            return Keyboard::SLASH;
        case sf::Keyboard::Equal:
            return Keyboard::EQUAL;
        case sf::Keyboard::BackSlash:
            return Keyboard::BACKSLASH;
        case sf::Keyboard::Multiply:
            return Keyboard::MULTIPLY;
        case sf::Keyboard::Quote:
            return Keyboard::QUOTE;
        case sf::Keyboard::SemiColon:
            return Keyboard::SEMICOLON;
        case sf::Keyboard::LControl:
            return Keyboard::LEFTCONTROL;
        case sf::Keyboard::RControl:
            return Keyboard::RIGHTCONTROL;
        case sf::Keyboard::LShift:
            return Keyboard::LEFTSHIFT;
        case sf::Keyboard::RShift:
            return Keyboard::RIGHTSHIFT;
        case sf::Keyboard::A: 
            return Keyboard::A;
        case sf::Keyboard::B: 
            return Keyboard::B;
        case sf::Keyboard::C: 
            return Keyboard::C;
        case sf::Keyboard::D: 
            return Keyboard::D;
        case sf::Keyboard::E: 
            return Keyboard::E;
        case sf::Keyboard::F: 
            return Keyboard::F;
        case sf::Keyboard::G: 
            return Keyboard::G;
        case sf::Keyboard::H: 
            return Keyboard::H;
        case sf::Keyboard::I: 
            return Keyboard::I;
        case sf::Keyboard::J: 
            return Keyboard::J;
        case sf::Keyboard::K: 
            return Keyboard::K;
        case sf::Keyboard::L: 
            return Keyboard::L;
        case sf::Keyboard::M: 
            return Keyboard::M;
        case sf::Keyboard::N: 
            return Keyboard::N;
        case sf::Keyboard::O: 
            return Keyboard::O;
        case sf::Keyboard::P: 
            return Keyboard::P;
        case sf::Keyboard::Q: 
            return Keyboard::Q;
        case sf::Keyboard::R: 
            return Keyboard::R;
        case sf::Keyboard::S: 
            return Keyboard::S;
        case sf::Keyboard::T: 
            return Keyboard::T;
        case sf::Keyboard::U: 
            return Keyboard::U;
        case sf::Keyboard::V: 
            return Keyboard::V;
        case sf::Keyboard::W: 
            return Keyboard::W;
        case sf::Keyboard::X: 
            return Keyboard::X;
        case sf::Keyboard::Y: 
            return Keyboard::Y;
        case sf::Keyboard::Z: 
            return Keyboard::Z;
        case sf::Keyboard::Num0: 
            return Keyboard::NUM0;
        case sf::Keyboard::Num1: 
            return Keyboard::NUM1;
        case sf::Keyboard::Num2: 
            return Keyboard::NUM2;
        case sf::Keyboard::Num3: 
            return Keyboard::NUM3;
        case sf::Keyboard::Num4: 
            return Keyboard::NUM4;
        case sf::Keyboard::Num5: 
            return Keyboard::NUM5;
        case sf::Keyboard::Num6: 
            return Keyboard::NUM6;
        case sf::Keyboard::Num7: 
            return Keyboard::NUM7;
        case sf::Keyboard::Num8: 
            return Keyboard::NUM8;
        case sf::Keyboard::Num9: 
            return Keyboard::NUM9;
        case sf::Keyboard::F1: 
            return Keyboard::F1;
        case sf::Keyboard::F2: 
            return Keyboard::F2;
        case sf::Keyboard::F3: 
            return Keyboard::F3;
        case sf::Keyboard::F4: 
            return Keyboard::F4;
        case sf::Keyboard::F5: 
            return Keyboard::F5;
        case sf::Keyboard::F6: 
            return Keyboard::F6;
        case sf::Keyboard::F7: 
            return Keyboard::F7;
        case sf::Keyboard::F8: 
            return Keyboard::F8;
        case sf::Keyboard::F9: 
            return Keyboard::F9;
        case sf::Keyboard::F10: 
            return Keyboard::F10;
        case sf::Keyboard::F11: 
            return Keyboard::F11;
        case sf::Keyboard::F12: 
            return Keyboard::F12; 
        default:
            return Keyboard::Key::UNDEFINED_KEY;
        }
    }

    //SFML to mouse button
    static Mouse::Button mouseConverter(sf::Mouse::Button sfmlbutton) {
        switch (sfmlbutton)
        {
        case sf::Mouse::Left:
            return Mouse::Button::LEFT;
        case sf::Mouse::Right:
            return Mouse::Button::RIGHT;
        case sf::Mouse::Middle:
            return Mouse::Button::MIDDLE;
        default:
            return Mouse::Button::UNDEFINED_MOUSE_BUTTON;
        }
    }

    //Get input from the keyboard and mouse
    //Pass event along to all Objects
    void InputManager::getInput() {
        sf::Event event;
        while (DM.getWindow()->pollEvent(event) /*event*/) {
            if (event.type == sf::Event::KeyPressed /*Key pressed*/) {
                //Create EventKeyboard (key and action)
                EventKeyboard key;
                std::cout << keyConverter(event.key.code);
                key.setKey(keyConverter(event.key.code));
                key.setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
                //send EventKeyboard to all Objects
                WM.onEvent(&key);
            }
            if (event.type == sf::Event::KeyReleased /*Key released*/) {
                //Create EventKeyboard (key and action)
                EventKeyboard key;
                key.setKey(Keyboard::Key(keyConverter(event.key.code)));
                key.setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
                //send EventKeyboard to all Objects
                WM.onEvent(&key);
            }
            if (event.type==sf::Event::MouseMoved /*Mouse moved*/) {
                //Create EventMouse (x,y, and action)
                EventMouse mouse;
                mouse.setMouseAction(EventMouseAction::MOVED);
                mouse.setMousePosition(df::pixelsToSpaces(Vector(event.mouseMove.x, event.mouseMove.y)));
                //send EventMouse to all Objects
                WM.onEvent(&mouse);
            }
            if (event.type == sf::Event::MouseButtonPressed /*Mouse clicked*/) {
                //Create EventMouse (x,y, and action)
                EventMouse mouse;
                mouse.setMouseAction(EventMouseAction::PRESSED);
                mouse.setMouseButton(mouseConverter(event.mouseButton.button));
                mouse.setMousePosition(df::pixelsToSpaces(Vector(event.mouseButton.x, event.mouseButton.y)));
                //send EventMouse to all Objects
                WM.onEvent(&mouse);
            }
        }
        //Check current key press events for each key
        for (int key = 0; key < sf::Keyboard::KeyCount;key++) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key))) {
                //Create EventKeyboard (key and action)
                EventKeyboard keyboard;
                keyboard.setKeyboardAction(EventKeyboardAction::KEY_DOWN);
                Keyboard::Key code = keyConverter(sf::Keyboard::Key(key));
                keyboard.setKey(code);
                //send EventKeyboard to all Objects
                WM.onEvent(&keyboard);
            }
        }
        //Check current mouse press events for each button
        for (int mouse = -1; mouse < 2; mouse++) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button(mouse))) {
                //Create EventMouse (x,y, and action)
                EventMouse eventMouse;
                eventMouse.setMouseAction(EventMouseAction::CLICKED);
                eventMouse.setMouseButton(mouseConverter(sf::Mouse::Button(mouse)));
                eventMouse.setMousePosition(df::pixelsToSpaces(Vector(event.mouseButton.x, event.mouseButton.y)));
                //send EventMouse to all Objects
                WM.onEvent(&eventMouse);
            }
        }
    }
    
}