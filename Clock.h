#include < Windows.h >

namespace df {
	class Clock
	{
	private:
		long int m_previous_time;
		int m_sleep_time;
	public:
		Clock();
		
		//Computes elapsed time in microseconds and sets m_previous_time to the current time
		long int delta();

		//Computes elapsed time in microseconds
		long int split();
		
		//Returns the m_previous_time variable
		long int getPreviousTime();
		
		//Computes current time in microseconds
		long int getCurrentTime();
	};

}