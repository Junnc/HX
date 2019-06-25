#include "HttpServerEngine.h"

#include <sstream>
#include <jsoncpp/json/json.h>

#include "common/log4cxx/hx_log4cxx.h"
#include "common/mempool/MemoryPool.h"
#include "common/mutex/cmutex.h"

NG_LOGGER(logger, "CHttpServerEngine");

EnHandleResult CHttpServerEngine::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	std::ostringstream s;
	s << "accept one connect: " << szAddress << ":" << usPort;
	LOG4CXX_DEBUG(logger, s.str());

	//std::cout<< s.str() << std::endl;
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	 return HR_OK;
}

EnHandleResult CHttpServerEngine::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	std::cout << dwConnID << "on close" << std::endl;
	m_bodyData.erase(dwConnID);
	//m_bodyMEMPool.deallocate(mC_bodyData[dwConnID]);
	//
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnShutdown(ITcpServer* pSender)
{
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CHttpServerEngine::OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)
{
	//mC_bodyData[dwConnID] = m_bodyMEMPool.allocate();
	//
	// set $CONNID body buffer 
	m_bodyData.insert(std::make_pair(dwConnID, ""));
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)
{
	//std::cout<< lpszMethod << ":" << lpszUrl << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	//std::cout<< lpszName << ":" << lpszValue << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnHeadersComplete(IHttpServer* pSender, CONNID dwConnID)
{
	//std::cout<< "on header complete" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	//std::cout<< "on body" << std::endl;
	//pSender->SetConnectionExtra(dwConnID, PVOID(pData));
	//std::string tmp += (char*) pData;
	//memncpy(mC_bodyData[dwConnID], tmp.data(), tmp.length);
	//
	std::string body(pData, pData + iLength);
	m_bodyData[dwConnID] += body;

	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	//std::cout<< "on message complete : " << dwConnID << std::endl;

	// get body content
	std::string content = std::move(m_bodyData[dwConnID]);
	//m_handleTHPool.AddTask([&]{
		HttpHandle(pSender, dwConnID, content);
	//});

	// reset body buffer
	m_bodyData[dwConnID] = "";

	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
	return HPR_OK;
}

EnHttpParseResult CHttpServerEngine::OnParseError(IHttpServer* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)
{
	return HPR_OK;
}

EnHandleResult CHttpServerEngine::OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpServerEngine::OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHttpParseResult CHttpServerEngine::HttpHandle(IHttpServer* pSender, CONNID dwConnID, std::string& content){
	// http extra body;
	/*
	 *LPVOID pExBody = nullptr;
	 *if(!pSender->GetConnectionExtra(dwConnID, (PVOID*)&pExBody)) {
	 *        std::cout << "get connection extra error" << std::endl;
         *	  return HPR_ERROR;
	 *}
	 *if (pExBody == nullptr) {
	 *        // default extra body init
	 *        pExBody = (LPVOID)"HX_DEFAULT";
	 *}
	 */

	try {
		std::string resp;
		auto res = HttpHandleProcess(content, resp);

		// set http response header 
		THeader header[] = {{"Content-type", "text/plain"}};
		int iHeaderCount = sizeof(header) / sizeof(THeader);
		int reCode = HSC_OK;
		std::string reStatus = "OK";
		if (!res) {
			// reCode = HSC_INTERNAL_SERVER_ERROR;
			// reStatus = "ERROR";
		}

		pSender->SendResponse(dwConnID, 
				reCode, reStatus.data(),
				header, iHeaderCount,
				(const BYTE*)resp.data(),
				resp.length()
				);
	} catch (std::exception&){}

        if(!pSender->IsKeepAlive(dwConnID))
		pSender->Release(dwConnID);

	return HPR_OK;
}

bool CHttpServerEngine::HttpHandleProcess(const std::string& sBody, std::string& sResponse) {
	bool res = false;

	// parse content json body
	try{
		Json::Reader reader;
		Json::Value rootValue;

		if (sBody.empty()) {
			sResponse = "EMPTY_HTTP_BODY";
			return false;
		}
		if (!reader.parse(sBody, rootValue)) {
			sResponse = "ERROR_HTTP_BODY";
			return false;
		}
		int cmdCode = 0;

		// handle request action
		cmdCode = rootValue["cmdcode"].asInt();
		//TODO
		// do some secure check, md5, access time, etc..
		if(CHttpHandler::ms_handles.find(cmdCode) != CHttpHandler::ms_handles.end()) {
			auto handler = CHttpHandler::ms_handles[cmdCode];
			handler(sBody, sResponse);
		} else {
			res = false;
			sResponse = "UNKNOW_HTTP_CMD";
		}
		/*
		 *switch (cmdCode) {
		 *case ECHO_TEST: {
		 *        CEchoHttpHandlePtr handle = std::make_shared<CEchoHttpHandle>();
		 *        res = handle->Handle(sResponse);
		 *        break;
		 *}
		 *default: {
		 *        res = false;
		 *        sResponse = "UNKONW_HTTP_CMD";
		 *}
		 *}
		 */
	} 
	catch(std::exception& e) {
		sResponse = e.what();
	}

	return res;
}

void CHttpServerEngine::Init() {
	// set http handle thread pool
	m_handleTHPool.Start();
}
