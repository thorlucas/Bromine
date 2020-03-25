#pragma once

#include <Bromine/Service/Service.h>
#include <spdlog/spdlog.h>
#include "LoggerObjects.h"

namespace BromineEngine {

namespace LogLevel = spdlog::level;

class LoggerService : public Service, private spdlog::logger {
public:
	LoggerService();

	using spdlog::logger::log;
	using spdlog::logger::debug;
	using spdlog::logger::info;
	using spdlog::logger::warn;
	using spdlog::logger::error;
	using spdlog::logger::critical;
	using spdlog::logger::trace;
};

}