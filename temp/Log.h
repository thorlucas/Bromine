#ifndef _LOG_H_
#define _LOG_H_

#include <cstdio>
#include <cstdarg>

namespace BromineEngine {

class LogManager {
public:
	LogManager();
	~LogManager();
	
	void log(const char* format, ...);
	void error(const char* format, ...);
};

} // namespace BromineEngine

#endif // _LOG_H_