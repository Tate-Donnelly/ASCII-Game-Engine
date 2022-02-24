#ifndef __SAUCER_H__
#define __SAUCER_H__
#include "Object.h"
namespace df {
	class Saucer : public Object
	{
	private:
		int m_color;//Color of sprite added for fun and testing purposes:)
	public:
		//Constructor
		Saucer();
		//Destructor
		~Saucer(); 

		//Handles events
		//Returns 0 when ignored
		int eventHandler(const df::Event* p_e) override;

		//Draw a "saucer"
		//int draw();
		//Get/Set color
		void setColor(int new_color);
		int getColor();
	};
}
#endif
