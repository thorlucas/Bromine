#pragma once

#include <Bromine/Bromine.h>
#include <Bromine/Service/LoggerService.h>

namespace BromineEngine {
namespace Logger {

#define LOG_FACADE(level)														\
template <typename... Args>														\
inline void level(spdlog::string_view_t fmt, const Args &... args) {			\
	Bromine::instance().getService<LoggerService>().level(fmt, args...);		\
}																				\

LOG_FACADE(critical)
LOG_FACADE(error)
LOG_FACADE(warn)
LOG_FACADE(info)
LOG_FACADE(debug)
LOG_FACADE(trace)

}
}