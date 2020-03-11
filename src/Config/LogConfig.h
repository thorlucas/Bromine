#ifndef _CONFIG_LOG_H_
#define _CONFIG_LOG_H_

namespace BromineEngine {

#define LOGGER_MIN_PRIORITY DEBUG

static const char* logFormats[] = {
	"[VERBOSE] %s\n",
	"[DEBUG] %s\n",
	"\033[34;1m[INFO] %s\033[0m\n",
	"\033[33;1m[WARNING] %s\033[0m\n",
	"\033[31;43;1m[ERROR] %s\033[0m\n"
};

} // namespace

#endif //_CONFIG_LOG_H_