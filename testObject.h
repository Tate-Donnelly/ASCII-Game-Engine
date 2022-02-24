#ifndef __TEST_OBJECT_H__
#define __TEST_OBJECT_H__
#include "Object.h"
#include "Color.h"
namespace df {
#define testObject_CHAR '/'
	class testObject :
		public Object
	{
	private:
		Color color;
	public:
		testObject();
		//Handles events
		//Returns 0 when ignored
		int eventHandler(const df::Event* p_e) override;
		//Draws the test Object
		//int draw();
		//Changes the object's color
		void setColor(int c);
	};
}
#endif

