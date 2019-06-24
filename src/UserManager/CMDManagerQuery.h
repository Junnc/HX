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

class CManagerQuery
{
public:
	CManagerQuery(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI)
	{}

	void handle()
	{
		try
		{
			std::string userid = m_info[usrID].asString();
			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userid,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
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
		}
		
	}


private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};


