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
#include "GlobalParamLogRecord.h"
#include "errCodeDef.h"
#include "AuthrityControl.h"

class CMainAccountUpdate
{
public:
	CMainAccountUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::cout << "  26 " << std::endl;
			userInfos uInfo;
			userRelationShip usrShip;
			TranslateToStruct(uInfo, usrShip);

			std::cout << "  30 " << std::endl;
			int nRes = 0;
			if (!CDBOpeartor::instance()->updateMainAccount(uInfo, usrShip) ||
				!CCacheUserAllInfo::instance()->updateMainAccount(uInfo))
			{
				nRes = -1;
			}
			std::cout << "  37 " << std::endl;
			//更新数据库保存 日志记录   log_record
			userInfosPtr usrPtr = std::make_shared<userInfos>(uInfo);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(usrShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("主账户修改", GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MAIN_ACC), usrPtr, shipPtr, UsersType::USER_MONEYACC);
			//反馈数据库操作结果 及 更新数据
			std::cout << "主账户更新成功" << endl;
			m_pUserManagerSPI->OnUpdateMainAccount(nRes, uInfo, usrShip,m_sessionUserID);
			return;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
	}

private:
	void TranslateToStruct(userInfos& uInfo, userRelationShip& usrShip)
	{
		std::cout << " TranslateToStruct 56 " << std::endl;
		uInfo.m_sUserID			= m_info[usrID].asString();
		uInfo.m_sLoginName		= m_info[loginName].asString();
		uInfo.m_sPassword		= m_info[passwords].asString();
		uInfo.m_sAccountName	= m_info[accountName].asString();
		uInfo.m_nCounterType	= m_info[counterType].asInt();

		usrShip.sUserID			= m_info[usrID].asString();
		usrShip.sInstitutionID	= m_info[InstitutionID].asString();
	}
private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
