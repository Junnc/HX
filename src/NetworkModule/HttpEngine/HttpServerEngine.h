#pragma once

#include <string>
#include <thread>
#include <map>

#include <hpsocket/HPSocket.h> 
#include <hpsocket/common/GlobalDef.h> 

#include "../HttpHandle/HttpHandle.h"
#include "../common/queue/ThreadPool.hpp"

class CHttpServerEngine: public CHttpServerListener {
private:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient);
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);

	virtual EnHttpParseResult OnMessageBegin(IHttpServer* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl);
	virtual EnHttpParseResult OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue);
	virtual EnHttpParseResult OnHeadersComplete(IHttpServer* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHttpParseResult OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHttpParseResult OnChunkComplete(IHttpServer* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnMessageComplete(IHttpServer* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType);
	virtual EnHttpParseResult OnParseError(IHttpServer* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc);

	virtual EnHandleResult OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, 
			BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen);
	virtual EnHandleResult OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID);

private:
	// http request handle
	EnHttpParseResult HttpHandle (IHttpServer* pSender, CONNID dwConnID, std::string& content);
	bool HttpHandleProcess (const std::string& sBody, std::string& sResponse);

public:
	CHttpServerEngine(LPCTSTR lpszName): m_strName(lpszName){}
	~CHttpServerEngine()=default;

	// http server engine init
	void Init();

public:
	// http server type http||https
	std::string m_strName;

	// http handle thread pool
	ThreadPool m_handleTHPool;

	// http body memory pool, default capacity 4096
	//MemoryPool<char> m_bodyMEMPool;

	// http body data
	std::map<CONNID, std::string> m_bodyData; 
};
