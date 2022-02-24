#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventView.h"
#include "utillity.h"
#include <iostream>
namespace df {
    // Construct ViewObject. 
// Object settings: SPECTRAL, max altitude.
// ViewObject defaults: border, top_center, default color, draw_value.
    ViewObject::ViewObject() {

        // Initialize Object attributes.
        setSolidness(SPECTRAL);
        setAltitude(MAX_ALTITUDE - 1);
        setType("ViewObject");

        // Initialize ViewObject attributes.
        setValue(0);
        setDrawValue();
        setBorder(true);
        setLocation(TOP_CENTER);
        setColor(COLOR_DEFAULT);
    }

    // Draw view string and value.
    int ViewObject::draw() {
        utillity u;
        // Display view_string + value.
        std::string temp_str = "";
        if (m_draw_value) {
            if (m_border) {
                temp_str = " " + getViewString() + " " + u.toString(getValue()) + " ";
            }
            else {
                temp_str = getViewString() + " " + u.toString(getValue());

            }
        }
        else {
            if (m_border) {
                temp_str = " " + getViewString() + " ";
            }
            else {
                temp_str = getViewString() + " " + u.toString(m_value);

            }
        }
        //std::cout << "\n" << temp_str << "\n";

        // Draw centered at position.
        Vector pos = u.viewToWorld(getPosition());
        DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());
        LM.writeLog(0, "Position (%f,%f)", pos.getX(), pos.getY());
        if (m_border) {
            Box b(Vector(pos.getX() - temp_str.size() * 0.5f, pos.getY() - 0), (float)temp_str.size(), 1);
            b.draw(sf::Color::Yellow, true);
        }
        return 0;
    }

    // Handle `view' event if tag matches view_string (others ignored).
    // Return 0 if ignored, else 1 if handled.
    int ViewObject::eventHandler(const Event* p_e) {
        // See if this is `view' event.
        if (p_e->getType() == VIEW_EVENT) {

            const EventView* p_ve = static_cast<const EventView*> (p_e);

            // See if this event is meant for this object.
            if (p_ve->getTag() == getViewString()) {
                if (p_ve->getDelta()) {
                    LM.writeLog("Set to %d", getValue() + p_ve->getValue());
                    setValue(getValue() + p_ve->getValue());  // Change in value.
                }
                else {
                    setValue(p_ve->getValue());               // New value.
                }
                return 1;
            }
        }
        return 0;
    }

    // General location of ViewObject on screen.
    void ViewObject::setLocation(ViewObjectLocation new_location) {
        Vector p;
        float y_delta = 0;

        LM.writeLog(0, "Get horizontal: %f", WM.getView().getHorizontal());
        // Set new position based on location.
        switch (new_location) {
        case TOP_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case TOP_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case TOP_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case CENTER_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() * 1 / 2);
            y_delta = 0;
            break;
        case CENTER_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() * 1 / 2);
            y_delta = 0;
            break;
        case CENTER_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() * 1 / 2);
            y_delta = 0;
            break;
        case BOTTOM_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
            if (!getBorder()) {
                y_delta = 1;
            }
            break;
        case BOTTOM_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
            if (!getBorder()) {
                y_delta = 1;
            }
            break;
        case BOTTOM_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
            if (!getBorder()) {
                y_delta = 1;
            }
            break;
        }

        // Shift, as needed, based on border.
        p.setY(p.getY() + y_delta);

        // Set position of object to new position.
        setPosition(p);
        LM.writeLog(0, "New location (%f,%f)", p.getX(), p.getY());
        // Set new location.
        m_location = new_location;
    }

    // Get general location of ViewObject on screen.
    ViewObjectLocation ViewObject::getLocation() const {
        return m_location;
    }

    // Set view value.
    void ViewObject::setValue(int new_value) {
        m_value = new_value;
    }

    // Get view value.
    int ViewObject::getValue() const {
        return m_value;
    }

    // Set view border (true = display border).
    void ViewObject::setBorder(bool new_border) {
        if (m_border != new_border) {
            m_border = new_border;
            //Reset location to account for boarder setting
            setLocation(getLocation());
        }
    }

    // Get view border (true = display border).
    bool ViewObject::getBorder() const {
        return m_border;
    }

    // Set view color.
    void ViewObject::setColor(Color new_color) {
        m_color = new_color;
    }

    // Get view color.
    Color ViewObject::getColor() const {
        return m_color;
    }

    // Set view display string.
    void ViewObject::setViewString(std::string new_view_string) {
        view_string = new_view_string;
    }

    // Get view display string.
    std::string ViewObject::getViewString() const {
        return view_string;
    }

    // Set true to draw value with display string.
    void ViewObject::setDrawValue(bool new_draw_value) {
        m_draw_value = new_draw_value;
    }

    // Get draw value (true if draw value with display string).
    bool ViewObject::getDrawValue() const {
        return m_draw_value;
    }
}