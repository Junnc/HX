#include "WSClient.h"

#include <thread>

CWSClient::CWSClient(const char* ip, const int port):m_serverIp(ip), m_serverPort(port){
	// init hp-socket http-cli engine
	m_engine = std::make_shared<CWSClientEngine>(HTTP_NAME);
	m_pClient = std::make_shared<CHttpClientPtr>(m_engine.get());
}

bool CWSClient::SendWebSocket(const std::string& content){
	BYTE bCode = 0x1;
	std::string data = content;
	int iLength = data.length();

	std::cout << "send websocket body: " << content << std::endl;
	return (*m_pClient)->SendWSMessage(TRUE, 0, bCode, HTTP_WEB_SOCKET_MASK_KEY, (BYTE*)data.data(), iLength);
}

void CWSClient::init(){
	// disable hp-socket heartbeat
	(*m_pClient)->SetKeepAliveTime(0);
	(*m_pClient)->SetKeepAliveInterval(0);
}

bool CWSClient::upgradeProtocal(){
	THeader header[] = {
		{"Connection", UPGRADE_HEADER},
		{UPGRADE_HEADER, WEB_SOCKET_HEADER_VALUE},
		{"Sec-WebSocket-Version", "13"},
		// TODO
		// sec-key generate by random
		{"Sec-WebSocket-Key", "w4v7O6xFTi36lq3RNcgctw=="},
		{nullptr, nullptr},         
		{nullptr, nullptr}};

	// ws addr, ws://139.224.233.67:5522/childServer/websocketquote
	//if(!g_pClient->SendGet("/childServer/websocketquote", header, 4)) {
	if(!(*m_pClient)->SendGet("/socket/futures", header, 4)) {
		// log error msg
		std::cout<< "UpgradeProtocal error" << std::endl;
		return false;
	}

	return true;
}

bool CWSClient::requestQuotation(){
	// quotation params
	Json::Value content;
	content["type"]	= 7;
	content["data"]	= "*";
	
	Json::FastWriter writer;
	std::string msg = writer.write(content);

	return SendWebSocket(msg);
}

bool CWSClient::Start(){
	// init ws client engine
	init();

	// start ws client
	const char* cliIP = "0.0.0.0";
	if (!(*m_pClient)->Start(m_serverIp, m_serverPort, false, cliIP)) {
		// TODO
		// log error msg
		std::cout<< "ws start error: " << (*m_pClient)->GetLastErrorDesc() << std::endl;
		return false;
	}

	// upgrade ws potocal
	if (!upgradeProtocal()) {
		// log error msg
		std::cout<< "ws upgrade protocal error" << std::endl;
		return false;
	}

	// request quotation 
	/*
	 *if (!requestQuotation()) {
	 *        // log error msg
	 *        std::cout<< "request quotation error" << std::endl;
	 *        return false;
	 *}
	 */

	return true;
}

bool CWSClient::Stop(){
	return (*m_pClient)->Stop();
}

void CWSClient::HeartBeat(){
	while(true) {
		if(!m_engine->PongWatcher()) {
			// restart ws client
			Stop();
			Start();
		}

		// send ping to ws server
		SendWebSocket("ping");
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}

void CWSClient::Run(){
	// start client
	Start();

	// heart beat
	std::thread th([=]{
		HeartBeat();
	});
	th.detach();
}
