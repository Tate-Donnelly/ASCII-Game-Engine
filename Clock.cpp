#include "Clock.h"
#include "utillity.h"

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <cstring>

namespace df {
	Clock::Clock() {
		m_previous_time = getCurrentTime();
	}

	//Computes elapsed time in microseconds and sets m_previous_time to the current time
	long int Clock::delta() {
		long int elapsedTime= getCurrentTime() - m_previous_time;
		m_previous_time = getCurrentTime();
		return elapsedTime;
	}

	//Computes elapsed time in microseconds
	long int Clock::split(){
		return getCurrentTime() - m_previous_time;
	}

	//Returns the m_previous_time variable
	long int Clock::getPreviousTime() {
		return m_previous_time;
	}

	//Computes current time in microseconds
	long int Clock::getCurrentTime() {
		SYSTEMTIME currentTime;
		GetSystemTime(&currentTime);
		return (currentTime.wDay * 24 * 60 * 60 * 1000000)
			+ (currentTime.wHour * 60 * 60 * 1000000)
			+ (currentTime.wMinute * 60 * 1000000)
			+ (currentTime.wSecond * 1000000)
			+ (currentTime.wMilliseconds * 1000);
	}
}
