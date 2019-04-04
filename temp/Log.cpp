#include <Log.h>

namespace BromineEngine {

LogManager::LogManager() {}
LogManager::~LogManager() {}

void LogManager::log(const char* format, ...) {
	#ifdef _DEBUG
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	#endif
}

void LogManager::error(const char* format, ...) {
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

} // namespace BromineEngine