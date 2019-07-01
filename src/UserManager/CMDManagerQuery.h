#pragma once
#include "TableFeild_define.h"
#include "CacheUserAllInfo.h"
#include "utility_fun.h"
#include <iostream>
#include <map>
#include <string>
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"
#include "errCodeDef.h"
#include "AuthrityControl.h"
#include "PrintLogMessage.h"

class CManagerQuery
{
public:
	CManagerQuery(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("")
	{}

	~CManagerQuery()
	{
		Json::FastWriter wts;
		std::string msg = wts.write(m_info);
		int nLogType = 0;
		msg.replace(msg.find("\n"), 1, "");
		if (m_errMsg.empty())
		{
			msg.append("==> Success");
			nLogType = LogType::LOG_INFO;
		}
		else
		{
			msg.append("==> Fail:");
			nLogType = LogType::LOG_ERR;

		}
		msg.append(m_errMsg);
		std::cout << msg << std::endl;
		CPrintLogMessage plm(msg, nLogType, "[CMDManagerQuery]");
	}
	void handle()
	{
		try
		{
			std::string userid = m_info[usrID].asString();
			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userid,m_sessionUserID, m_pUserManagerSPI))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg, m_sessionUserID);
				return;
			}

			//查询管理员
			int nRes = 0;
			UserAndRelationShipMap usrMap;
			CCacheUserAllInfo::instance()->queryAccount(userid, usrMap, UsersType::USER_MANAGER);
			if (usrMap.size() <= 0)
				nRes = -1;
			else
				std::cout << "Institution:" << userid << " have " << usrMap.size() << " manager;"
					<< std::endl;

			//反馈 信息
			m_pUserManagerSPI->OnQryManagerAccount(nRes, usrMap, m_sessionUserID);
		}
		catch (const std::exception&e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}
		
	}


private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};


