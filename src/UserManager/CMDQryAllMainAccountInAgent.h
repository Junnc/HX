#pragma once
#pragma once
#include <map>
#include <vector>
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

class CQryAllMainAccountInAgent
{
public:
	CQryAllMainAccountInAgent(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::string userID = m_info[usrID].asString();

			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userID,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			int nRes = 0;
			userInfos usr;
			userRelationShip ship;
			UserAndRelationShipMap mainUserMap;
			if(!CCacheUserAllInfo::instance()->selectUsersOne(userID, usr) ||
				!CCacheUserAllInfo::instance()->selectUsersOne(userID, ship))
				nRes = ERR_USER_NOEXIST;
			else
			{
				if (usr.m_nLevel == 1 && usr.m_nUserType == UsersType::USER_INSTITUTION)
				{
					if (!CCacheUserAllInfo::instance()->queryAccount(userID, mainUserMap, UsersType::USER_MONEYACC))
						nRes = -1;
				}
				else
				{
					std::vector<InstitutionMainidMap> mainidVec;
					CCacheUserAllInfo::instance()->selestAssignMainAccount(userID, mainidVec);
					for(auto it = mainidVec.begin();it != mainidVec.end();it++)
					{
						userInfos usrInfo;
						userRelationShip shipInfo;
						UserAndRelationShipMap mainUserMap;
						if (CCacheUserAllInfo::instance()->selectUsersOne(it->m_mainID, usrInfo) &&
							CCacheUserAllInfo::instance()->selectUsersOne(it->m_mainID, shipInfo))
						{
							userInfosPtr usrPtr = std::make_shared<userInfos>(usrInfo);
							userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(shipInfo);
							mainUserMap[usrPtr] = shipPtr;
						}		
					}
				}			
			}


			m_pUserManagerSPI->OnQryAllMainAccount(nRes, mainUserMap, m_sessionUserID);
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


