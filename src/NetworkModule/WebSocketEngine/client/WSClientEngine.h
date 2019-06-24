#pragma once

#include <iostream>
#include <string>

#include <hpsocket/HPSocket.h> 
#include <hpsocket/HPSocket-SSL.h> 
#include <hpsocket/common/GlobalDef.h> 
#include <jsoncpp/json/json.h>

const BYTE HTTP_WEB_SOCKET_MASK_KEY[]	= {0x1, 0x2, 0x3, 0x4};

class CWSClientEngine : public CHttpClientListener
{
public:
	CWSClientEngine(LPCTSTR lpszName): m_strName(lpszName), m_heartBeatFiled(0){}
	~CWSClientEngine()=default;

private:
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID);

	virtual EnHttpParseResult OnMessageBegin(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc);
	virtual EnHttpParseResult OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue);
	virtual EnHttpParseResult OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHttpParseResult OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength);
	virtual EnHttpParseResult OnChunkComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnMessageComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType);
	virtual EnHttpParseResult OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc);

	virtual EnHandleResult OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen);
	virtual EnHandleResult OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID);

private:
	void handle(const std::string& content);
	
public:
	bool PongWatcher();

public:
	std::string m_strName;

	// ws body buffer
	std::string m_bodyData;

	// heartbeat filed times
	int m_heartBeatFiled;
};
