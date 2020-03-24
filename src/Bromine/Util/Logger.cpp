#include "Logger.h"

namespace BromineEngine {

Logger::Logger() : minPriority(Logger::DEBUG), _logFile(nullptr) {}

Logger::~Logger() {
	if (_logFile != nullptr) fclose(_logFile);
}

void Logger::log(Priority priority, const char* fmt...) {
	va_list args;
	va_start(args, fmt);
	vlog(priority, fmt, args);
	va_end(args);
}

void Logger::vlog(Priority priority, const char* fmt, va_list args) {
	if (priority >= minPriority) {
		char buffer[256];
		snprintf(buffer, 256, logFormats[priority], fmt);

		if (_logFile != nullptr) {
			vfprintf(_logFile, buffer, args);
		} else {
			vprintf(buffer, args);
		}
	}
}

void Logger::setMinimumPriority(Priority priority) {
	minPriority = priority;
}

void Logger::logFile(const char* logFileName) {
	if (strcmp(logFileName, "") == 0) return;

	if (_logFile != nullptr) {
		fclose(_logFile);
	}

	_logFile = fopen(logFileName, "w");
}

}