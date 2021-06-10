#include "logger.h"


Logger* Logger::instance_ = nullptr;

Logger* Logger::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Logger();
	}
	return instance_;
}
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Print(const std::string text, LogVerbosity logVerb, LogType logType)
{
	if (logVerb > log_verbosity_)
	{
		return;
	}

	switch (logType)
	{
	case LOG_ERROR:
		printf("[ERROR]: ");
		break;
	case LOG_NEW_EVENT:
		printf("[NEW EVENT]: ");
		break;
	default:
		break;
	}
	printf(text.c_str());
	printf("\n");
}
void Logger::SetLogVerbosity(LogVerbosity lv)
{
	this->log_verbosity_ = lv;
}
Logger::LogVerbosity Logger::GetLogVerbosity()	//type LogVerbosity
{
	return this->log_verbosity_;
}