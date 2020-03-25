#pragma once

#include <Bromine/Service/LoggerService.h>

#define DEFAULT_SERVICE_REGISTRATION(instance)	\
instance.registerService<LoggerService>();		\
