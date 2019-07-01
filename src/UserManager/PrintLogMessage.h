#pragma once
#include <string>

enum LogType
{
	LOG_ERR = 1,
	LOG_INFO,
	LOG_FATAL,
	LOG_DEBUG,
	LOG_WARN,
	LOG_TRACE
};

class CPrintLogMessage
{
public:
	CPrintLogMessage(std::string sMsg,int nLogType,std::string sMsgSource);
};
