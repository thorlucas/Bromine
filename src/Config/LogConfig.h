#pragma once

#define LOG_FILE "TestLogFile.log"
#define STDOUT_LOG_LEVEL LogLevel::info
#define FILE_LOG_LEVEL LogLevel::trace
#define LOG_PATTERN "[%T.%e] %^[%l]%$ %v"