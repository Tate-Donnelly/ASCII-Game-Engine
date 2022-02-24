
#ifndef __LOG_MANAGER_H__
# define __LOG_MANAGER_H__
#include < stdio.h >
#include "Manager.h"



# define LM df :: LogManager :: getInstance ()
namespace df {
	
	class LogManager : public Manager
	{
	private:
		const char* LOGFILE_NAME = "dragonfly.log";
		bool m_didflush;
		bool log_time_string;
		bool log_step_count;
		FILE* p_logFile;
		int log_level;
	public:
		LogManager();
		~LogManager();
		static LogManager& getInstance();
		//Opens the logfile
		virtual int startUp();
		//Closes the logfile
		virtual void shutDown();
		//Sets the flush of the log file after each write
		void setFlush(bool didFlush = true);
		//Writes to the log file and returns the number of bytes written or -1 if error
		int writeLog(int level, const char* fmt, ...);
		int writeLog(const char* fmt, ...) const;
		//Gets log level
		int getLogLevel();
	};

}
#endif