#include "LogManager.h"
#include "ObjectList.h"

namespace df {
	ObjectListIterator::ObjectListIterator() {
		ObjectListIterator li(m_p_list);
	}
	//Create iterator over indicated list
	ObjectListIterator::ObjectListIterator(const ObjectList* p_l) {
		m_p_list = p_l;
		first();
	}

	//Set iterator to first item in the list
	void ObjectListIterator::first() {
		m_index = 0;
	}

	//Set iterator to next item in the list
	void ObjectListIterator::next() {
		if (m_index <= 5000 || m_index >= 0) {
			if (m_index < m_p_list->m_counter -1) {
				m_index++;
				//LM.writeLog(5, "Index %d", m_index);
			}
			else {
				m_index++;
			}
		}
	}

	//Return true if at the end of the list
	bool ObjectListIterator::isDone() const {
		return (m_index == m_p_list->m_counter);
	}

	//Return pointer to current Object, NULL if done/empty
	Object* ObjectListIterator::currentObject() const {
		if (!isDone()) {
			return m_p_list->p_list[m_index];
		}
		return NULL;
	}

}