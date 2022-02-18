#include "EventView.h"
namespace df {
    // Create view event with tag VIEW_EVENT, value 0 and delta false.
    EventView::EventView(){
        EventView(VIEW_EVENT, 0, false);
    }

    // Create view event with tag, value and delta as indicated.
    EventView::EventView(std::string new_tag, int new_value, bool new_delta){
        setTag(new_tag);
        setValue(new_value);
        setDelta(new_delta);
    }

    // Set tag to new tag.
    void EventView::setTag(std::string new_tag){
        m_tag = new_tag;
    }

    // Get tag.
    std::string EventView::getTag() const{
        return m_tag;
    }

    // Set value to new value.
    void EventView::setValue(int new_value){
        m_value = new_value;
    }

    // Get value.
    int EventView::getValue() const{
        return m_value;
    }

    // Set delta to new delta.
    void EventView::setDelta(bool new_delta){
        m_delta = new_delta;
    }

    // Get delta.
    bool EventView::getDelta() const{
        return m_delta;
    }

}