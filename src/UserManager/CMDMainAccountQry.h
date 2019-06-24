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

class CMainAccountQry
{
public:
	CMainAccountQry(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI)
	{}

	void handle()
	{
		try
		{

			std::string institution = m_info[usrID].asString();
			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(institution,m_sessionUserID))
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
			//查询主账户
			
			UserAndRelationShipMap usrMap;
			int nRes = -1;
			if (!CCacheUserAllInfo::instance()->queryAccount(institution, usrMap, UsersType::USER_MONEYACC))
				std::cout << "Institution:" << institution << " have 0 main account" << std::endl;
			else
			{
				std::cout << "Institution:" << institution << " have " << usrMap.size() << " main acconut;"
					<< std::endl;
				nRes = 0;
			}

			//反馈 信息
			m_pUserManagerSPI->OnQryMainAccount(nRes, usrMap, m_sessionUserID);
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


