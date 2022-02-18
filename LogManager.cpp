#include "LogManager.h"
#include "utillity.h"
#include "Clock.h"

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdarg.h>
#include <iostream>
#include <cstring>

using namespace std;
namespace df {
	df::Manager M;
	LogManager::LogManager() {
		setType("LogManager");
		p_logFile = NULL;
		m_didflush = false;
		log_time_string = false;
		log_step_count = false;
		log_level = 1;
	}

	LogManager::~LogManager() {
		if (p_logFile != NULL) {
			fclose(p_logFile);
		}
	}

	LogManager& LogManager::getInstance() {
		static LogManager logManager;
		return logManager;
	}

	//Opens the logfile
	int LogManager::startUp() {
		
		fopen_s(&p_logFile, LOGFILE_NAME, "w+");
		if (p_logFile == NULL) {
			writeLog(10, "Error with openning file");
			return -1;
		}
		writeLog(3, "LogManager startUp()");
		
		return Manager::startUp();
	}

	//Closes the logfile
	void LogManager::shutDown() {
		writeLog(3, "LogManager shutDown()");
		if (p_logFile != NULL) {
			fclose(p_logFile);
		}
		Manager::shutDown();
	}

	//Sets the flush of the log file after each write
	void LogManager::setFlush(bool flushed) {
		m_didflush = flushed;
	}
	//Writes to the log file and returns the number of bytes written or -1 if error
	int LogManager::writeLog(const char* fmt, ...) const {
		//writeLog(3, fmt, ...);
		int len = 0;
		utillity u;
		fprintf(stderr, "\n %s : ", u.getTimeString());
		fprintf(p_logFile, "\n %s : ", u.getTimeString());
		va_list args;
		va_start(args, fmt);
		vfprintf(p_logFile, fmt, args);
		len = vfprintf(stderr, fmt, args);
		va_end(args);
		return len;
	}
	//Writes to the log file and returns the number of bytes written or -1 if error
	int LogManager::writeLog(int level, const char* fmt, ...) {
		int len = 0;
		if (level >= log_level) {
			utillity u;
			fprintf(stderr, "\n %s : ", u.getTimeString());
			fprintf(p_logFile, "\n %s : ", u.getTimeString());
			va_list args;
			va_start(args, fmt);
			vfprintf(p_logFile, fmt, args);
			len = vfprintf(stderr, fmt, args);
			
			va_end(args);
			//printf("%d\n", len);
			fflush(p_logFile);
		}
		return len;
	}

	//Gets log level
	int LogManager::getLogLevel() {
		return log_level;
	}
}