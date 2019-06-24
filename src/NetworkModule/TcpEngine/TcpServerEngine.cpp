#include "TcpServerEngine.h"

#include <thread>

#include "../common/log4cxx/hx_log4cxx.h"

// tcp msg header & end
const char* const G_MSGHEADER = "<HX>";
const char* const G_MSGEND = "<END>";
const char* const G_ZEORMSG = "<HX><END>";
const int G_ZEORMSGLEN = 9;

NG_LOGGER(logger, "CTcpServerEngine");

EnHandleResult CTcpServerEngine::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	std::ostringstream s;
	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	s << "accept one connect: " << szAddress << ":" << usPort;
	LOG4CXX_INFO(logger, s.str());
	//std::cout<< s.str() << std::endl;

	// set $CONNID stream remain buffer 
	m_remain.insert(std::make_pair(dwConnID, ""));

	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnHandShake(ITcpServer* pSender, CONNID dwConnID) 
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength) 
{
	std::vector<BYTE> vec;
	ITcpPullServer* pServer = ITcpPullServer::FromS(pSender);
	// fetch buffer chunk size 16
	int chunkSize = 16;
	int remain = iLength;

	while(remain > 0){
		BYTE buf[chunkSize];
		if (chunkSize > remain) {
			chunkSize = remain;
		}
		EnFetchResult result = pServer->Fetch(dwConnID, buf, chunkSize);
		if(result == FR_OK) {
			vec.insert(vec.end(), buf, buf+chunkSize);
			remain -= chunkSize;
		} else if (result == FR_DATA_NOT_FOUND) {
			return HR_ERROR;
		}
	}
	
	std::string content(vec.begin(), vec.end());
	Handle(pSender, dwConnID, content);

	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	// remove $CONNID stream remain
	m_remain.erase(dwConnID);
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnShutdown(ITcpServer* pSender) 
{
	return HR_OK;
}

std::vector<std::string> CTcpServerEngine::Parser(const CONNID dwConnID, const std::string &content){
	auto allMsgStr = m_remain[dwConnID] + content;
	auto startPos = allMsgStr.find(G_MSGHEADER); 
	auto endPos = allMsgStr.find(G_MSGEND);
	auto headLen = strlen(G_MSGHEADER);
	auto endLen = strlen(G_MSGEND);

	if (startPos == std::string::npos || endPos == std::string::npos)
		m_remain[dwConnID] = allMsgStr;

	std::vector<std::string> res;
	while (startPos != std::string::npos && endPos != std::string::npos){
		auto pkg = allMsgStr.substr(startPos + headLen, endPos - startPos - headLen);
		res.push_back(pkg);

		allMsgStr = allMsgStr.substr(endPos + endLen);
		startPos = allMsgStr.find(G_MSGHEADER); 
		endPos = allMsgStr.find(G_MSGEND);
		m_remain[dwConnID] = allMsgStr;
	}

	return res;
}

void CTcpServerEngine::Handle(ITcpServer* pSender, const CONNID dwConnID, const std::string& content){
	// parse recrived pkg
	auto vec = Parser(dwConnID, content);

	for(auto v : vec) {
		// push response into sys_mq
		//m_handleTHPool.AddTask([=]{
			HandleProcess(pSender, dwConnID, v);
		//});
	}
}

void CTcpServerEngine::HandleProcess(ITcpServer* pSender, const CONNID dwConnID, const std::string& content) {
	std::string response;
	// parse content json body
	try{
		Json::Reader reader;
		Json::Value rootValue;
		if (!reader.parse(content, rootValue)) {
			response = "ERROR_REQUEST_BODY";
			// respose to client
			pSender->Send(dwConnID, (BYTE*)response.data(), response.length());
			return ;
		}

		int cmdCode = 0;
		// handle request action
		cmdCode = rootValue["cmdcode"].asInt();
		//TODO
		// do some secure check, md5, access time, etc..
		if(CTcpHandler::ms_handles.find(cmdCode) != CTcpHandler::ms_handles.end()) {
			auto handler = CTcpHandler::ms_handles[cmdCode];
			handler(content, response);
		} else {
			response = "UNKNOW_CMD";
		}
	} 
	catch(std::exception& e) {
		response = e.what();
	}

	// respose to client
	pSender->Send(dwConnID, (BYTE*)response.data(), response.length());
}

void CTcpServerEngine::Init() {
	// set http handle thread pool
	m_handleTHPool.Start();
}
