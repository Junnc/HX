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

class CQryChildAccount
{
public:
	CQryChildAccount(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI):
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("")
	{
	}
	
	~CQryChildAccount()
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
		CPrintLogMessage plm(msg,nLogType,"[CMDQryChildAccount]");
	}
	void handle()
	{
		try
		{
			std::string institution = m_info[usrID].asString();
			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(institution,m_sessionUserID, m_pUserManagerSPI))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_QUERY_RSP;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_errMsg = content;
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//查询子账户
			UserAndRelationShipMap usrMap;
			CCacheUserAllInfo::instance()->queryAccount(institution, usrMap, UsersType::USER_TRADER);
			if (usrMap.size() <= 0)
			{
				std::cout << "Institution:" << institution << " have 0 child account" << std::endl;
			}	
			else
			{
				std::cout << "Institution:" << institution << " have " << usrMap.size() << " child acconut;"
					<< std::endl;
			}
		
			m_pUserManagerSPI->OnQryChildAccount(0, usrMap, m_sessionUserID);
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

