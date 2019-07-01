#include "NewFuture/NewFutureEngine.h"
#include "log4cxx/hx_log4cxx.h"

bool init() {
	// TODO
	// get config info
	// init db
	// init manager cernter
	// register yun center
	// start api server
	// settle handle

	return true;
}

int main() {
	NG_LOGGER_INIT(logger, "hx", "../conf/ng_log_configuration.xml");

	init();

	LOG4CXX_INFO(logger, "newFuture start");
	CNewFutureEngine::instance()->Run();
	system("pause");

	return 0;
}
