#ifndef _CONFIG_LOG_H_
#define _CONFIG_LOG_H_

namespace BromineEngine {

#define LOGGER_MIN_PRIORITY Logger::DEBUG

static const char* logFormats[] = {
	"[VERBOSE] %s\n",
	"[DEBUG] %s\n",
	"\033[34;1m[INFO] %s\033[0m\n",
	"\033[33;1m[WARNING] %s\033[0m\n",
	"\033[31;43;1m[ERROR] %s\033[0m\n"
};

static const char* logFileName = "TestLogFile.log";

} // namespace

#endif //_CONFIG_LOG_H_