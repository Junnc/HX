#pragma once
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

class CAgentQuery
{
public:
	CAgentQuery(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::string userID = m_info[usrID].asString();

			//检测通信是否合法 
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userID,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);

				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content,m_sessionUserID);
				return;
			}
 
			//查询代理商
			UserAndRelationShipMap userMap;
			int nRes = 0;
			 if(!CCacheUserAllInfo::instance()->queryAccount(userID, userMap, UsersType::USER_INSTITUTION))
				 nRes = -1;

			//返回查询结果
			std::cout << userID << "有 " << userMap.size() << " 个子代理" << endl;
			m_pUserManagerSPI->OnQryChildAgent(nRes, userMap, m_sessionUserID);


		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};

