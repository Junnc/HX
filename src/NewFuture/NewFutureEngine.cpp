#include "NewFutureEngine.h"

#include <string>

#include "WebSocketEngine/client/WSClient.h"
#include "WebSocketEngine/WSServer.h"
#include "HttpEngine/HttpServer.h"
#include "log4cxx/hx_log4cxx.h"
#include "config/Config.h"

NG_LOGGER(logger, "CNewFutureEngine");

bool CNewFutureEngine::Init() {

	return true;
}

bool CNewFutureEngine::Run() {
	// init 
	if (!Init()) {
		LOG4CXX_ERROR(logger, "CNewFutureEngine init error");
		return false;
	}

	// register quotation
	std::string ip = CConfig::instance()->m_quotationServer.ip;
	int port = std::stoi(CConfig::instance()->m_quotationServer.port);

	// TODO
	// log start err
	CWSClient cli(ip.c_str(), port);
	cli.Run();

	// start newFuture http server
	ip = CConfig::instance()->m_httpServer.ip;
	port = CConfig::instance()->m_httpServer.port;

	CHttpServerDaemon httpServ(ip.c_str(), port);
	httpServ.Start();

	// start newFuture websocket server
	ip = CConfig::instance()->m_WSServerInfo.ip;
	port = CConfig::instance()->m_WSServerInfo.port;

	CWSServerDaemon wsServ(ip.c_str(), port);
	wsServ.Start();

	return 0;
}
