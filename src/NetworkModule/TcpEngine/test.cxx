#include <unistd.h>
#include "TcpServer.h"
#include "../common/log4cxx/hx_log4cxx.h"

int main(){
	NG_LOGGER_INIT(logger, "tcp_server", "../common/log4cxx/ng_log_configuration.xml");
	auto tcpDPtr = new CTcpServerDaemon("0.0.0.0", 5555);
	tcpDPtr->Start();
	pause();
}
