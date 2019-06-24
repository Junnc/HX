#include "WSClientEngine.h"

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CWSClientEngine::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteHost(szAddress, iAddressLen, usPort);
	std::cout<< "connect" << std::endl;
	return HR_OK;
}

EnHandleResult CWSClientEngine::OnHandShake(ITcpClient* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CWSClientEngine::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CWSClientEngine::OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CWSClientEngine::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CWSClientEngine::OnMessageBegin(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "message begin" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::cout<< "http body: " << pData << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnChunkComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "message complete" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
	return HPR_OK;
}

EnHttpParseResult CWSClientEngine::OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)
{
	std::cout<< "parse error" << std::endl;
	return HPR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CWSClientEngine::OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{
	return HR_OK;
}

EnHandleResult CWSClientEngine::OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::string body(pData, pData + iLength);
	m_bodyData += body;
	//std::cout << "ws message body: " << m_bodyData << std::endl;
	//std::cout << "ws message body: " << body << std::endl;

	return HR_OK;
}

EnHandleResult CWSClientEngine::OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "on message complete : " << dwConnID << std::endl;

	BYTE iOperationCode;
	pSender->GetWSMessageState(nullptr, nullptr, &iOperationCode, nullptr, nullptr, nullptr);

	if(iOperationCode == 0x8)
		return HR_ERROR;

	std::string content = std::move(m_bodyData);
	handle(content);
	m_bodyData = "";

	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

void CWSClientEngine::handle(const std::string& content){
	// handle ws server pong
	if (content == "pong") {
		m_heartBeatFiled = 0;
		std::cout << "pong" << std::endl;
		return;
	}

	Json::Reader reader;
	Json::Value rootValue;
	if (!reader.parse(content, rootValue)) {
		return;
	}
	std::cout<< content << std::endl;
	// TODO
	// handle quotation
}

bool CWSClientEngine::PongWatcher(){
	// watch ws server pong
	if (m_heartBeatFiled >= 5) {
		return false;
	}

	m_heartBeatFiled++;
	return true;
}
