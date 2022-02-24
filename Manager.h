#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "Event.h"
#include <stdlib.h>
#include <string>

namespace df {
	class Manager
	{
		private:
			std::string m_type;
			bool m_is_started;

		protected:
			//Sets type to the name Manager
			void setType(std::string type);

		public:
			Manager();
			~Manager();

			//Sets the m_is_started variable to true
			virtual int startUp();

			//Sets the m_is_started variable to false. Returns negative if error
			virtual void shutDown();
			
			//Checks if manager has been successfully started
			bool isStarted() const;

			//Return's the Manager's type
			std::string getType() const;

			//Adds support for sending events
			int onEvent(const Event* p_event) const;
	};
}
#endif
