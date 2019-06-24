#include <unistd.h>
#include "WSServer.h"
#include "../common/log4cxx/hx_log4cxx.h"

int main(){
	NG_LOGGER_INIT(logger, "ws_server", "../common/log4cxx/ng_log_configuration.xml");
	auto http_DPtr = new CWSServerDaemon("0.0.0.0", 5555);
	http_DPtr->Start();
	//system("read");
	pause();
}
