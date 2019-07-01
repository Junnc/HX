#include <unistd.h>

#include "NewFuture/NewFutureEngine.h"
#include "log4cxx/hx_log4cxx.h"
#include "config/Config.h"

bool init() {
	// TODO
	// get config info
	NG_LOGGER(logger, "hx_init");
	std::string path = "conf/newFuture.ini";
	if (!CConfig::instance()->IsFileExist(path.c_str()))
	{
		std::ostringstream s;
		s << "load iniFile error:" << path.c_str() << " is not exist，please check filepath...\n";
		LOG4CXX_INFO(logger, s.str());
		return -1;
	}	
	CConfig::instance()->Read(path.c_str());
	// init db
	// init manager cernter
	// register yun center
	// start api server
	// settle handle
	
	return true;
}

int main() {
	NG_LOGGER_INIT(logger, "hx", "conf/ng_log_configuration.xml");

	init();

	LOG4CXX_INFO(logger, "newFuture start");
	CNewFutureEngine::instance()->Run();
	pause();

	return 0;
}
