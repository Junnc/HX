#include "WSServer.h"
#include "../common/log4cxx/hx_log4cxx.h"

NG_LOGGER(logger, "CWSServer");

CWSServerDaemon::CWSServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){
	m_engine = std::make_shared<CWSServerEngine>(HTTP_NAME);
	m_server = std::make_shared<CHttpServerPtr>(m_engine.get());
};

bool CWSServerDaemon::Init(){
	// init http server engine
	m_engine->Init();
	return true;
}

bool CWSServerDaemon::Start(){
	// start http server daemon
	std::ostringstream s;
	Init();
	SetHandleFactory();
	if(!(*m_server)->Start(m_ip, m_port)) {
		// log launch error
		s << "websocket server start error: " << (*m_server)->GetLastErrorDesc();
		LOG4CXX_FATAL(logger, s.str());
		return false;
	}

	s << "websocket server start on " << m_ip << ":" << m_port;
	LOG4CXX_INFO(logger, s.str());

	//std::cout << s.str() << std::endl;
	return true;
}

bool CWSServerDaemon::Stop(){
	// stop http server daemon
	(*m_server)->Stop();
	std::ostringstream s;
	s << "websocket server " << m_ip << ":" << m_port << " stopped";
	LOG4CXX_INFO(logger, s.str());

	return true;
}

bool CWSServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	CWSHandler::SetHttpHandle();
	return true;
}
