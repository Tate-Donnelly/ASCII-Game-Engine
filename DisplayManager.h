#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H_
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Manager.h"
#include "Vector.h"
#include "Color.h"

# define DM df :: DisplayManager :: getInstance ()
namespace df {
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";


enum Justification {
        LEFT_JUSTIFIED,
        CENTER_JUSTIFIED,
        RIGHT_JUSTIFIED,
};


//Compute char height based on window size and font
float charHeight(void);

//Compute char width based on window size and font
float charWidth(void);

//Convert ASCII spaces (x,y) to window pixels (x,y)
Vector spacesToPixels(Vector spaces);

//Convert window pixels (x,y) to ASCII spaces (x,y)
Vector pixelsToSpaces(Vector pixels);

class DisplayManager :
        public Manager
    {
    private:
        DisplayManager();
        DisplayManager(DisplayManager const&);
        void operator=(DisplayManager const&);
        sf::Font m_font;
        sf::RenderWindow* m_p_window;
        int m_window_horizontal_pixels;
        int m_window_vertical_pixels;
        int m_window_horizontal_chars;
        int m_window_vertical_chars;
        sf::Color m_window_background_color;
    public:
        //Get the instance of the DisplayManager
        static DisplayManager& getInstance();

        //Open the graphics window
        //Return 0 if ok, -1 otherwise
        int startUp();

        //Close graphics window
        void shutDown();

        //Draw character at the window position with the given color
        //Return 0 if ok, -1 otherwise
        int drawCh(Vector world_pos, char ch, Color color) const;

        //Return window's horizontal maximum (in characters)
        int getHorizontal() const;

        //Return window's vertical maximum  (in characters)
        int getVertical() const;

        //Return window's horizontal maximum  (in pixels)
        int getHorizontalPixels() const;

        //Return window's vertical maximum (in pixels)
        int getVerticalPixels() const;

        //Render current window buffer
        //Return 0 if ok, -1 otherwise
        int swapBuffers();

        //Return pointer to SFML graphics window
        sf::RenderWindow* getWindow() const;

        //Draw a string at the window's location with the default color
        //Justified left, center, or right
        //Return 0 if ok, else -1
        int drawString(Vector pos, std::string str, Justification just, Color color) const;

        bool setBackgroundColor ( int new_color );

    };
}
#endif

