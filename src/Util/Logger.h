#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstdio>
#include <cstdarg>
#include "../Config/LogConfig.h"

namespace BromineEngine {

class Logger {
public:
	enum Priority {
		VERBOSE,
		DEBUG,
		INFO,
		WARNING,
		ERROR
	} minPriority;

	Logger(Priority priority);

	void log(Priority priority, const char* fmt...) __attribute__ (( format(printf, 3, 4) ));
	void vlog(Priority priority, const char* fmt, va_list args);
};

}; // namespace

#endif // _LOGGER_H_