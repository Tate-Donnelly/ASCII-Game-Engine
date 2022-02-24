#pragma once
#include <string>
#include "Object.h"
#include "Event.h"	
namespace df {

    // General location of ViewObject on screen.
    enum ViewObjectLocation {
        UNDEFINED = -1,
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER_CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT,
    };

    class ViewObject : public Object {

    private:
        std::string view_string;          // Label for value (e.g., "Points").
        int m_value;                      // Value displayed (e.g., points).
        bool m_draw_value;                // True if should draw value.
        bool m_border;                    // True if border around display.
        Color m_color;                    // Color for text (and border).
        ViewObjectLocation m_location;    // Location of ViewObject.

    public:
        // Construct ViewObject. 
        // Object settings: SPECTRAL, max alt.
        // ViewObject defaults: border, top_center, default color, draw_value.
        ViewObject();

        // Draw view string and value.
        virtual int draw() override;

        // Handle `view' event if tag matches view_string (others ignored).
        // Return 0 if ignored, else 1 if handled.
        virtual int eventHandler(const Event* p_e) override;

        // General location of ViewObject on screen.
        void setLocation(ViewObjectLocation new_location);

        // Get general location of ViewObject on screen.
        ViewObjectLocation getLocation() const;

        // Set view value.
        void setValue(int new_value);

        // Get view value.
        int getValue() const;

        // Set view border (true = display border).
        void setBorder(bool new_border);

        // Get view border (true = display border).
        bool getBorder() const;

        // Set view color.
        void setColor(Color new_color);

        // Get view color.
        Color getColor() const;

        // Set view display string.
        void setViewString(std::string new_view_string);

        // Get view display string.
        std::string getViewString() const;

        // Set true to draw value with display string.
        void setDrawValue(bool new_draw_value = true);

        // Get draw value (true if draw value with display string).
        bool getDrawValue() const;

    };

}
