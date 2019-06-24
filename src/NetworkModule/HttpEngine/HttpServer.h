#pragma once

#include "HttpServerEngine.h"

// default serv_ip & serv_port
#define DEFAULT_HTTP_IP "127.0.0.1"
#define DEFAULT_HTTP_PORT 8080

class CHttpServerDaemon{

public:
	CHttpServerDaemon():CHttpServerDaemon(DEFAULT_HTTP_IP, DEFAULT_HTTP_PORT){};
	CHttpServerDaemon(const char* ip, const int port);
	~CHttpServerDaemon()=default;

public:
	// http server daemon init
	bool Init();
	// http server daemon start
	bool Start();
	// http server daemon stop
	bool Stop();
	// http server daemon handle registed
	bool SetHandleFactory();

private:
	const char* m_ip;
	const int m_port;

	// http engine & server ptr;
	std::shared_ptr<CHttpServerEngine> m_engine;
	std::shared_ptr<CHttpServerPtr> m_server;
};

typedef std::shared_ptr<CHttpServerDaemon> CHttpServerDaemonPtr;
