#include "PrintLogMessage.h"
#include "log4cxx/hx_log4cxx.h"

NG_LOGGER(logger, "PrintLogMessage");

CPrintLogMessage::CPrintLogMessage(std::string sMsg, int nLogType, std::string sMsgSource)
{
	sMsgSource += " " + sMsg;
	switch (nLogType)
	{

	case LogType::LOG_DEBUG :
		NG_LOG4CXX_DEBUG(logger,sMsgSource);
		break;
	case LogType::LOG_ERR:
		NG_LOG4CXX_ERROR(logger, sMsgSource);
		break;
	case LogType::LOG_FATAL:
		NG_LOG4CXX_FATAL(logger, sMsgSource);
		break;
	case LogType::LOG_INFO:
		NG_LOG4CXX_INFO(logger, sMsgSource);
		break;
	case LogType::LOG_TRACE:
		NG_LOG4CXX_TRACE(logger, sMsgSource);
		break;
	case LogType::LOG_WARN:
		NG_LOG4CXX_WARN(logger, sMsgSource);
		break;

	default:
		break;
	}
}