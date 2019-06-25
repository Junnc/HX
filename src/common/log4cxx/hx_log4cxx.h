/*
 * version: 1.0.0.2
 * last modified date: 2019/6/17
 * last modified by: Junc
 *
 * 使用步骤：
 * 1. main函数中添加：
 *	NG_LOGGER_INIT(logger,"ng_logger","ng_log_configuration.xml");
 * 2. 在要用到的cpp文件开头加上：
 *	NG_LOGGER(logger,"ng_logger");
 */

#ifndef NG_HEADER_FOR_LOG4CXX_HPP
#define NG_HEADER_FOR_LOG4CXX_HPP

#include <memory>

#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/logmanager.h>

// 用在 cpp 中
#define NG_LOGGER(logger,logger_name) \
  static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(logger_name);

#if defined(_DEBUG)
#define NG_LOG4CXX_TRACE(logger,message)  LOG4CXX_TRACE(logger,message)
#else
#define NG_LOG4CXX_TRACE(logger,message)
#endif

#define NG_LOG4CXX_DEBUG(logger,message) LOG4CXX_DEBUG(logger,message)

#define NG_LOG4CXX_INFO(logger,message) LOG4CXX_INFO(logger,message)

#define NG_LOG4CXX_WARN(logger,message) LOG4CXX_WARN(logger,message)

#define NG_LOG4CXX_ERROR(logger,message) LOG4CXX_ERROR(logger,message)

#define NG_LOG4CXX_FATAL(logger,message) LOG4CXX_FATAL(logger,message)

#define NG_LOGGER_INIT(logger,logger_name,xml_file_name) \
    log4cxx::xml::DOMConfigurator::configureAndWatch(xml_file_name,30);\
    log4cxx::LoggerPtr logger=log4cxx::Logger::getLogger(logger_name);\
    auto log4cxx_remove = [&](int*p){\
      delete p;\
      logger->removeAllAppenders();\
    };\
    std::shared_ptr<int> for_log4cxx_delete (new int,log4cxx_remove);

#define NG_ANOTHER_LOGGER(logger,logger_name) \
    log4cxx::LoggerPtr logger=log4cxx::Logger::getLogger(logger_name);\
    auto log4cxx_remove_##logger = [&](int*p){\
      delete p;\
      logger->removeAllAppenders();\
    };\
    std::shared_ptr<int> for_log4cxx_delete_##logger (new int,log4cxx_remove_##logger);

class NGTrace
{
public:
	NGTrace(log4cxx::LoggerPtr logger, const char *funcName)
	{
		funcName_ = funcName;
		logger_ = logger;
		LOG4CXX_TRACE(logger_, funcName_ << " [ENTER] ");
	}
	~NGTrace()
	{
		LOG4CXX_TRACE(logger_, funcName_ << " [EXIT]  ");
	}

private:
	const char *funcName_;
	log4cxx::LoggerPtr logger_;
};

#endif//NG_HEADER_FOR_LOG4CXX_HPP
