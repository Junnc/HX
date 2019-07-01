#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include "utility_fun.h"
#include <iostream>
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"
#include "errCodeDef.h"
#include "AuthrityControl.h"
#include "PrintLogMessage.h"

class CQryAllChildAgent
{
public:
	CQryAllChildAgent(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CQryAllChildAgent()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDQryAllChildAgentInRoot]");
	}
	void handle()
	{
		try
		{
			std::string userID = m_info[usrID].asString();

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userID,m_sessionUserID, m_pUserManagerSPI))
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

			int nRes = 0;
			UserAndRelationShipMap agentUserMap;
			if (!CDBOpeartor::instance()->SelectAllChildAgentFromDB(userID, agentUserMap))
			{
				nRes = -1;
				m_errMsg = "数据库操作失败";
			}
			else
			{
				std::cout << "AllchildAgent is " << agentUserMap.size() << std::endl;
			}
				

			m_pUserManagerSPI->OnQryAllChildAgent(nRes, "正确", agentUserMap, m_sessionUserID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}
	}



private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string  m_errMsg;
};


