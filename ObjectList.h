#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__
#include "Object.h"
#include "ObjectListIterator.h"
namespace df {
	const int MAX = 5000;
	const int MAX_COUNT_INIT = 1;
	class ObjectListIterator;
	class ObjectList
	{
	private:
		Object* p_list[MAX];
		int m_counter;
	public:
		friend class ObjectListIterator;

		//Creates list
		ObjectList();
		//Clears list
		void clear();

		//Returns true if it inserts an object in the list, false if there's no room
		bool insert(Object* p_object);

		//Returns true if object is in the list and false if it isn't
		bool contains(Object* p_object);

		//Returns true if object is in the list and removes object from list, returns false if not in the list
		bool remove(Object* p_object);

		//Return count of objects in list
		int getCount() const;

		//Returns true if the list is empty, false if it isn't
		bool isEmpty() const;

		//Returns true if the list is full, false if it isn't
		bool isFull() const;

		//Combines object lists
		ObjectList operator+(ObjectList list);

	};
}
#endif