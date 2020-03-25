#pragma once

#include <Bromine/Bromine.h>
#include <Bromine/Service/LoggerService.h>

namespace BromineEngine {
namespace Logger {

template <typename... Args>
inline void error(spdlog::string_view_t fmt, const Args &... args) {
	Bromine::instance().getService<LoggerService>().error(fmt, args...);
}

template <typename... Args>
inline void debug(spdlog::string_view_t fmt, const Args &... args) {
	Bromine::instance().getService<LoggerService>().debug(fmt, args...);
}

template <typename... Args>
inline void warn(spdlog::string_view_t fmt, const Args &... args) {
	Bromine::instance().getService<LoggerService>().warn(fmt, args...);
}

template <typename... Args>
inline void info(spdlog::string_view_t fmt, const Args &... args) {
	Bromine::instance().getService<LoggerService>().info(fmt, args...);
}

template <typename... Args>
inline void trace(spdlog::string_view_t fmt, const Args &... args) {
	Bromine::instance().getService<LoggerService>().trace(fmt, args...);
}

}
}