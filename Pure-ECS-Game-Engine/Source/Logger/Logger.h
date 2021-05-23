#pragma once
#include <string>
#include <ctime>

enum class ERROR_LEVEL
{
	MESSAGE = 0,
	WARNING = 1,
	ERROR = 2
};

class Logger
{
public:
	static void Log(const std::string& message, ERROR_LEVEL level = ERROR_LEVEL::MESSAGE);

private:
	static std::string DateAndTimeString();
};
