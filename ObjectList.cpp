#include "ObjectList.h"
#include "LogManager.h"

namespace df {
	//Creates list
	ObjectList::ObjectList() {
		m_counter = 0;
		p_list[MAX] = {};
	}

	//Clears list
	void ObjectList::clear() {
		m_counter = 0;
	}

	//Returns true if it inserts an object in the list, false if there's no room
	bool ObjectList::insert(Object *p_object) {
		if (m_counter < MAX) {
			LM.writeLog(0, "Object %d inserted by ObjectList", p_object->getId());
			p_list[m_counter] = p_object;
			m_counter++;
			return true;
		}
		LM.writeLog(10, "Object %d NOT inserted by ObjectList", p_object->getId());
		return false; //No room left
	}

	//Returns true if object is in the list and false if it isn't
	bool ObjectList::contains(Object* p_object) {
		if (!isEmpty()) {
			for (int i = 0; i < m_counter; i++) {
				if (p_list[i] == p_object) {
					LM.writeLog(0, "p_list contains Object %d", p_object->getId());
					return true;
				}
			}
		}
		return false;
	}

	//Returns true if object is in the list and removes object from list, returns false if not in the list
	bool ObjectList::remove(Object *p_object) {
		for (int i = 0; i < m_counter; i++) {
			if (p_list[i] == p_object) {
				p_list[i] = p_list[m_counter - 1];
				m_counter--;
				return true;
			}
		}
		return false;
	}

	//Return count of objects in list
	int ObjectList::getCount() const {
		return m_counter;
	}

	//Returns true if the list is empty, false if it isn't
	bool ObjectList::isEmpty() const {
		if (m_counter == 0) {
			return true;
		}
		return false;
	}

	//Returns true if the list is full, false if it isn't
	bool ObjectList::isFull() const {
		if (m_counter == MAX) {
			return true;
		}
		return false;
	}

	//Combines object lists
	ObjectList ObjectList::operator+(ObjectList list) {
		ObjectList big_list = *this;

		ObjectListIterator li(&list);
		for (li.first(); not li.isDone(); li.next()) {
			Object* p_o = li.currentObject();
			big_list.insert(p_o);
		}
		return big_list;
	}
}