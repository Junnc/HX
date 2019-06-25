#include "HttpServer.h"

#include "common/net/NetBaseDef.h"
#include "common/log4cxx/hx_log4cxx.h"

NG_LOGGER(logger, "CHttpServer");

CHttpServerDaemon::CHttpServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){
	m_engine = std::make_shared<CHttpServerEngine>(HTTP_NAME);
	m_server = std::make_shared<CHttpServerPtr>(m_engine.get());
}

bool CHttpServerDaemon::Init(){
	// init http server engine
	m_engine->Init();
	return true;
}

bool CHttpServerDaemon::Start(){
	// start http server daemon
	std::ostringstream s;
	Init();
	SetHandleFactory();
	//if(g_HttpServer->Start(m_ip, m_port)) {
	if(!(*m_server)->Start(m_ip, m_port)) {
		// log launch error
		s << "http server start error: " << (*m_server)->GetLastErrorDesc();
		LOG4CXX_FATAL(logger, s.str());
		return false;
	}

	s << "http server start on " << m_ip << ":" << m_port;
	LOG4CXX_INFO(logger, s.str());
	return true;
}

bool CHttpServerDaemon::Stop(){
	// stop http server daemon
	(*m_server)->Stop();
	std::ostringstream s;
	s << "http server " << m_ip << ":" << m_port << " stopped";
	LOG4CXX_INFO(logger, s.str());

	return true;
}

bool CHttpServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	CHttpHandler::SetHttpHandle();
	return true;
}
