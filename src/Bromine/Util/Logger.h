#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstdio>
#include <cstdarg>
#include <string>
#include <Config/LogConfig.h>

namespace BromineEngine {

class Logger {
private:
	Logger();

	FILE* _logFile;
	
public:
	enum Priority {
		VERBOSE,
		DEBUG,
		INFO,
		WARNING,
		ERROR
	} minPriority;

	static Logger& instance() {
		static Logger instance;
		return instance;
	}

	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

	~Logger();

	void log(Priority priority, const char* fmt...) __attribute__ (( format(printf, 3, 4) ));
	void vlog(Priority priority, const char* fmt, va_list args);

	void setMinimumPriority(Priority priority);
	void logFile(const char* logFileName);
};

}; // namespace

#endif // _LOGGER_H_