#pragma once

#include <memory>
#include <jsoncpp/json/json.h>

#include "WSClientEngine.h"
#include "../../common/net/NetBaseDef.h"

#define UPGRADE_HEADER                  "Upgrade"
#define WEB_SOCKET_HEADER_VALUE         "WebSocket"

class CWSClient {
public:
	CWSClient(const char* ip, const int port);
	~CWSClient()=default;

public:

	bool Start();

	bool Stop();

	void HeartBeat();

	void Run();

	void ReConnectThread();

	//void HandleQuotation(ShortQuotationInfoPtr quotationInfo);

	void QuotationPushCheckThread();

	bool IsHolidayTime(const int curDate, const int curTime, std::string& holidayName);

	inline void SetDisconnect(bool isConn)
	{
		//writeLock lock(mutex);
		m_isConnected = isConn;
	}

	inline bool GetDisconnect()
	{
		//readLock lock(mutex);
		return m_isConnected;
	}

	bool SendWebSocket(const std::string& content);

private:
	// init
	void init();
	// upgrade http to ws
	bool upgradeProtocal();
	// request quotation
	bool requestQuotation();

private:
	//IWSClientApi* m_pApi;

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//CMsgQueueDispathcherPtr m_pMsgQueueDispathcher;
	bool m_isConnected;
	int m_heartBeatFailNum;
	time_t m_lastPushTime;
	bool m_isQuitConn;
	//CommonTools::event m_evt;
	//rwMutex mutex;
	
	// ws server party ip
	const char* m_serverIp;
	// ws server party port
	const int m_serverPort;

	// ws engine & client ptr;
	std::shared_ptr<CWSClientEngine> m_engine;
	std::shared_ptr<CHttpClientPtr> m_pClient;

};
