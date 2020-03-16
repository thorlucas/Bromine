#include "Logger.h"

namespace BromineEngine {

Logger::Logger() : minPriority(Logger::DEBUG) {}

void Logger::log(Priority priority, const char* fmt...) {
	if (priority >= minPriority) {
		char buffer[256];
		snprintf(buffer, 256, logFormats[priority], fmt);

		va_list args;
		va_start(args, fmt);
		vprintf(buffer, args);
		va_end(args);
	}
}

void Logger::vlog(Priority priority, const char* fmt, va_list args) {
	if (priority >= minPriority) {
		char buffer[256];
		snprintf(buffer, 256, logFormats[priority], fmt);

		vprintf(buffer, args);
	}
}

void Logger::setMinimumPriority(Priority priority) {
	minPriority = priority;
}

}