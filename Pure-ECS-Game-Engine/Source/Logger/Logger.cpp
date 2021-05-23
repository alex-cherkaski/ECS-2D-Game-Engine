#include "./Logger.h"
#include "../Constants/Constants.h"
#include <iostream>
#include <sstream>

void Logger::Log(const std::string & message, ERROR_LEVEL level)
{
	std::string dateAndTime = DateAndTimeString();

	switch (level)
	{
		case (ERROR_LEVEL::MESSAGE):
		{
			std::cout << Constants::ConsoleColors::GREEN << "MESSAGE: " << dateAndTime << message << Constants::ConsoleColors::RESET << std::endl;
			break;
		}

		case (ERROR_LEVEL::WARNING):
		{
			std::cout << Constants::ConsoleColors::YELLOW << "WARNING: " << dateAndTime << message << Constants::ConsoleColors::RESET << std::endl;
			break;
		}

		case (ERROR_LEVEL::ERROR):
		{
			std::cout << Constants::ConsoleColors::RED << "ERROR: " << dateAndTime << message << Constants::ConsoleColors::RESET << std::endl;
			break;
		}

		default:
		{
			std::cout << Constants::ConsoleColors::GREEN << "MESSAGE: " << message << Constants::ConsoleColors::RESET << std::endl;
			break;
		}
	}
}

std::string Logger::DateAndTimeString()
{
	struct tm newtime;
	time_t now = time(nullptr);
	localtime_s(&newtime, &now);

	std::stringstream result;
	result << "On ";
	result << std::to_string(newtime.tm_year + 1900) + "-";
	result << std::to_string(newtime.tm_mon + 1) + "-";
	result << std::to_string(newtime.tm_mday) + ", At ";
	result << std::to_string(newtime.tm_hour) + ":";
	result << std::to_string(newtime.tm_min) + ":";
	result << std::to_string(newtime.tm_sec) + ":";
	
	return result.str();
}
