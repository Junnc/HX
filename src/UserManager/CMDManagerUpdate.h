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

class CManagerUpdate
{
public:
	CManagerUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			TranslateStruct(tmp, userShip);
			//检测连接是否合法 
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(userShip.sInstitutionID,m_sessionUserID))
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


			//更新数据库 和缓存
			int nRes = 0;
			if (!CDBOpeartor::instance()->updateChildAccount(tmp, userShip) ||
				!CCacheUserAllInfo::instance()->updateManagerInfo(tmp, userShip))
			{
				std::cout << "更新管理员数据库失败" << endl;
				nRes = -1;
			}

			userInfosPtr usrPtr = std::make_shared<userInfos>(tmp);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(userShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("管理员更新", 
				GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MANAGER_ACC), usrPtr, shipPtr, UsersType::USER_MANAGER);
			
			std::cout << "更新管理员成功" << endl;
			m_pUserManagerSPI->OnUpdateManagerAccount(nRes, tmp, userShip, m_sessionUserID);
		}
		catch (const std::exception&e)
		{
			std::cout << e.what() << std::endl;
		}
		
	}

private:
	void TranslateStruct(userInfos& tmp, userRelationShip& userShip)
	{
		tmp.m_sUserID = m_info[usrID].asString();
		tmp.m_sLoginName = m_info[loginName].asString();
		tmp.m_sPassword = m_info[passwords].asString();
		tmp.m_sAccountName = m_info[accountName].asString();
		tmp.m_nUserType = UsersType::USER_TRADER;

		userShip.sUserID = m_info[usrID].asString();
		userShip.sInstitutionID = m_info[InstitutionID].asString();
		userShip.sAuthrityModuleID = m_info[AuthrityModuleID].asString();

	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
