#include "LoggerService.h"

#include <Config/LogConfig.h>

#include <vector>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace BromineEngine {

LoggerService::LoggerService() : spdlog::logger("bromine-logger") {
	set_level(FILE_LOG_LEVEL <= STDOUT_LOG_LEVEL ? FILE_LOG_LEVEL : STDOUT_LOG_LEVEL);

	auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	stdoutSink->set_level(STDOUT_LOG_LEVEL);
	sinks().push_back(stdoutSink);

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_st>(LOG_FILE);
	fileSink->set_level(FILE_LOG_LEVEL);
	sinks().push_back(fileSink);

	set_pattern(LOG_PATTERN);

	info("Constructed LoggerService");
}

}