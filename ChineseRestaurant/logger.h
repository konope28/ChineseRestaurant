#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_
#include <string>
#include <cstdio>

class Logger 
{
public:
	enum LogType { LOG_ERROR, LOG_NEW_EVENT, LOG_INFO };
	enum LogVerbosity { L1 = 1, L2, L3, L4 };

	void Print(const std::string text, LogVerbosity logVerb = L1, LogType logType = LOG_INFO);
	void SetLogVerbosity(LogVerbosity lv);

	LogVerbosity GetLogVerbosity();
	static Logger* GetInstance();

protected:
	Logger();
	virtual ~Logger();
	static Logger* instance_;
	LogVerbosity log_verbosity_;
};


#endif /* LOGGER_LOGGER_H_ */