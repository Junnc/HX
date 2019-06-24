#include "TcpServer.h"
#include "../common/log4cxx/hx_log4cxx.h"

NG_LOGGER(logger, "CTcpServer");
	
CTcpServerDaemon::CTcpServerDaemon(const char* ip, const int port): m_ip(ip), m_port(port){ m_engine = std::make_shared<CTcpServerEngine>();
	m_server = std::make_shared<CTcpPullServerPtr>(m_engine.get());
}

// HP-Socket tcp daemon start
bool CTcpServerDaemon::Start(){
	std::ostringstream s;
	SetHandleFactory();
	if(!(*m_server)->Start(m_ip, m_port)) {
		s << "tcp server start error: " << (*m_server)->GetLastErrorDesc();
		LOG4CXX_FATAL(logger, s.str());
		return false;
	}

	s << "tcp server start on " << m_ip << ":" << m_port;
	LOG4CXX_INFO(logger, s.str());
	return true;
}

bool CTcpServerDaemon::SetHandleFactory(){
	// register tcp request handle
	CTcpHandler::SetTcpHandle();
	return true;
}

void CTcpServerDaemon::Stop(){
	(*m_server)->Stop();
	std::ostringstream s;
	s << "tcp server " << m_ip << ":" << m_port << " stopped";
	LOG4CXX_INFO(logger, s.str());
}
