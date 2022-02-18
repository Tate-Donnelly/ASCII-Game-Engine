#include "DisplayManager.h"
#include "LogManager.h"
#include "Color.h"
#include "Vector.h"
#include <iostream>
#include "utillity.h"

namespace df {
    DisplayManager::DisplayManager() {
        setType("DisplayManager");
        m_p_window=NULL;
        m_window_horizontal_pixels= WINDOW_HORIZONTAL_PIXELS_DEFAULT;
        m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
        m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
        m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
        m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
        if (setBackgroundColor(BLACK)) {
            LM.writeLog("Background color set");
        }
        else {
            LM.writeLog("Background color not set");
        }
    }
    DisplayManager::DisplayManager(DisplayManager const&) {
        setType("DisplayManager");
        m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
        m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
        m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
        m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
        m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
        m_p_window = NULL;

        
    }
    void DisplayManager::operator=(DisplayManager const&) {}

    //Get the instance of the DisplayManager
    DisplayManager& DisplayManager::getInstance() {
        static DisplayManager displayManager;
        return displayManager;
    }

    //Open the graphics window
    //Return 0 if ok, -1 otherwise
    int DisplayManager::startUp() {
        if (m_p_window!=NULL) {
            LM.writeLog("Window is not null");
            return 0;
        }
        
        m_p_window=new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), WINDOW_TITLE_DEFAULT);
        //turn off mouse cursor
        m_p_window->setMouseCursorVisible(false);

        //synchronize refresh rate with monitor
        m_p_window->setVerticalSyncEnabled(true);
        //load font
        if (m_font.loadFromFile(FONT_FILE_DEFAULT) == false) {
            std::cout << "Error";
        }
        else {
            LM.writeLog("Font accepted");

        }
        LM.writeLog("DisplayManager started");
        
        return Manager::startUp();
        return 0;
    }

    //Close graphics window
    void DisplayManager::shutDown() {
        LM.writeLog("DisplayManager shutting down");
        m_p_window->close();
        Manager::shutDown();
    }

    //Compute char height based on window size and font
    float charHeight(){
        return (DM.getVerticalPixels()) / (DM.getVertical());
    }

    //Compute char width based on window size and font
    float charWidth(){
        return (DM.getHorizontalPixels()) / (DM.getHorizontal());
    }

    //Convert ASCII spaces (x,y) to window pixels (x,y)
    Vector spacesToPixels(Vector spaces){
        return Vector((spaces.getX() * charWidth()), (spaces.getY() * charHeight()));
    }

    //Convert window pixels (x,y) to ASCII spaces (x,y)
    Vector pixelsToSpaces(Vector pixels){
        return Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight());
    }

    //Draw character at the window position with the given color
    //Return 0 if ok, -1 otherwise
    int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const{
       if (m_p_window == NULL) {
            return -1;
       }
       utillity u;
       Vector view_pos = u.worldToView(world_pos);

        //Convert spaces to pixels
        Vector pixel_pos = spacesToPixels(view_pos);
        LM.writeLog(0,"Position %f,  %f", pixel_pos.getX(), pixel_pos.getY());

      /*  //background rectangle
        static sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
        rectangle.setFillColor(m_window_background_color);
        rectangle.setPosition(pixel_pos.getX() - charWidth() / 10,
            pixel_pos.getY() + charHeight() / 5);
        m_p_window->draw(rectangle);*/

        sf::Text text("", m_font);
        text.setString(ch);
        text.setStyle(sf::Text::Bold);

        //Scale to the right size
        if (charWidth() < charHeight()) {
            text.setCharacterSize(charWidth() * 2);
        }
        else {
            text.setCharacterSize(charHeight() * 2);
        }
        LM.writeLog(0, "Char width %f, height %f", charWidth(), charHeight() );
        switch (color) {
        case YELLOW:
            text.setFillColor(sf::Color::Yellow);
            break;
        case RED:
            text.setFillColor(sf::Color::Red);
            break;
        case GREEN:
            text.setFillColor(sf::Color::Green);
            break;
        case BLACK:
            text.setFillColor(sf::Color::Black);
            break;
        case BLUE:
            text.setFillColor(sf::Color::Blue);
            break;
        case CYAN:
            text.setFillColor(sf::Color::Cyan);
            break;
        case MAGENTA:
            text.setFillColor(sf::Color::Magenta);
            break;
        default:
            text.setFillColor(sf::Color::White);
            break;
        }
        LM.writeLog(0, "Position %f,  %f", pixel_pos.getX(), pixel_pos.getY());
        text.setPosition(pixel_pos.getX(), pixel_pos.getY());
        m_p_window->draw(text);
        return 0;
    }

    //Return window's horizontal maximum (in characters)
    int DisplayManager::getHorizontal() const {
        return m_window_horizontal_chars;
    }

    //Return window's vertical maximum  (in characters)
    int DisplayManager::getVertical() const {
        return  m_window_vertical_chars;
    }

    //Return window's horizontal maximum  (in pixels)
    int DisplayManager::getHorizontalPixels() const {
        return m_window_horizontal_pixels;
    }

    //Return window's vertical maximum (in pixels)
    int DisplayManager::getVerticalPixels() const {
        return m_window_vertical_pixels;
    }

    //Render current window buffer
    //Return 0 if ok, -1 otherwise
    int DisplayManager::swapBuffers() {
        //Make sure the window is allocated
        if (m_p_window == NULL) {
            return -1;
        }

        //Display the current window
         m_p_window->display();
        //Clear other window to get ready for next draw
         m_p_window->clear();
        //Success
        return 0;
    }


    //Return pointer to SFML graphics window
    sf::RenderWindow* DisplayManager::getWindow() const {
        return m_p_window;
    }

    int DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
        Vector starting_pos = pos;
        switch (just) {
        case CENTER_JUSTIFIED:
            starting_pos.setX(pos.getX() - str.size() / 2);
            break;
        case RIGHT_JUSTIFIED:
            starting_pos.setX(pos.getX() - str.size());
            break;
        case LEFT_JUSTIFIED:
        default:
            break;
        }
        for (int i = 0; i < str.size(); i++) {
            Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
            drawCh(temp_pos, str[i], color);
        }
        return 0;
    }
    
    bool DisplayManager::setBackgroundColor(int new_color) {
        if (Color(new_color)!=NULL) {
            switch (Color(new_color)) {
            case YELLOW:
                m_window_background_color=(sf::Color::Yellow);
                break;
            case RED:
                m_window_background_color = (sf::Color::Red);
                break;
            case GREEN:
                m_window_background_color = (sf::Color::Green);
                break;
            case BLACK:
                m_window_background_color = (sf::Color::Black);
                break;
            case BLUE:
                m_window_background_color = (sf::Color::Blue);
                break;
            case CYAN:
                m_window_background_color = (sf::Color::Cyan);
                break;
            case MAGENTA:
                m_window_background_color = (sf::Color::Magenta);
                break;
            default:
                m_window_background_color = (sf::Color::White);
                break;
            }
            return true;
        }
        m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
        return false;
    }
}