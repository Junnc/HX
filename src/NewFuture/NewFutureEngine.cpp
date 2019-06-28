#include "NewFutureEngine.h"

#include <thread>
#include <string>

#include "WebSocketEngine/client/WSClient.h"
#include "WebSocketEngine/WSServer.h"
#include "HttpEngine/HttpServer.h"
#include "log4cxx/hx_log4cxx.h"
#include "config/Config.h"

NG_LOGGER(logger, "CNewFutureEngine");

bool CNewFutureEngine::Init() {
	// TODO
	// get config info
	// init db
	// init manager cernter
	
	return true;
}

bool CNewFutureEngine::Run() {
	// init 
	if (!Init()) {
		LOG4CXX_ERROR(logger, "CNewFutureEngine init error");
		return false;
	}

	// register quotation
	std::thread tWScli([]{
		std::string ip = CConfig::instance()->m_quotationServer.ip;
		int port = std::stoi(CConfig::instance()->m_quotationServer.port);

		CWSClient cli(ip.c_str(), port);
		cli.Run();
	});
	tWScli.join();

	// start newFuture http server
	std::thread tHttpcli([]{
		std::string ip = CConfig::instance()->m_httpServer.ip;
		int port = CConfig::instance()->m_httpServer.port;

		CHttpServerDaemon serv(ip.c_str(), port);
		serv.Start();
	});
	tHttpcli.join();

	// start newFuture websocket server
	std::thread tWSserv([]{
		std::string ip = CConfig::instance()->m_WSServerInfo.ip;
		int port = CConfig::instance()->m_WSServerInfo.port;

		CWSServerDaemon serv(ip.c_str(), port);
		serv.Start();
	});
	tWSserv.join();

	return 0;
}
