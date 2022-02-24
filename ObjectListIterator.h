#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__

namespace df {
	class ObjectList;
	class ObjectListIterator
	{
	private:
		ObjectListIterator();
		int m_index;
		const ObjectList *m_p_list;
	public:
		//Create iterator over indicated list
		ObjectListIterator(const ObjectList* p_l);
		//Set iterator to first item in the list
		void first();
		//Set iterator to next item in the list
		void next();
		//Return true if at the end of the list
		bool isDone() const;
		//Return pointer to current Object, NULL if done/empty
		Object* currentObject() const;
		
	};
}
#endif