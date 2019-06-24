#include "Session.h"

void Session::Write(const std::string& content) {
	if(m_sender == nullptr || m_connID == 0) {
		return;
	}

        BOOL bFinal;
        BYTE iReserved, iOperationCode;
	// check current ws state
        if (!m_sender->GetWSMessageState(m_connID, &bFinal, &iReserved, &iOperationCode, nullptr, nullptr, nullptr)) {
		return;
	}
	// 0x8: websocket send DISCONNECT operation
	if(iOperationCode == 0x8) {
		return;
	}	

	// send ws response
	BYTE optCode = 0x1;
	m_sender->SendWSMessage(m_connID, bFinal, iReserved, optCode, nullptr, (BYTE*)content.data(), content.length());
}

int Session::Init(const std::string& ip, unsigned short port) {
	m_ip = ip;
	m_sessionID = ip + "_" + std::to_string(port);
	return 0;
}
