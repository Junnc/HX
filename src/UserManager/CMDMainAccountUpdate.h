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
#include "PrintLogMessage.h"

class CMainAccountUpdate
{
public:
	CMainAccountUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CMainAccountUpdate()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDMainAccountUpdate]");
	}
	void handle()
	{
		try
		{
			userInfos uInfo;
			userRelationShip usrShip;
			TranslateToStruct(uInfo, usrShip);

			int nRes = 0;
			if (!CDBOpeartor::instance()->updateMainAccount(uInfo, usrShip) ||
				!CCacheUserAllInfo::instance()->updateMainAccount(uInfo))
			{
				m_errMsg = "数据库操作失败";
				nRes = -1;
			}
			
			//更新数据库保存 日志记录   log_record
			userInfosPtr usrPtr = std::make_shared<userInfos>(uInfo);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(usrShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("主账户修改", GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MAIN_ACC), usrPtr, shipPtr, UsersType::USER_MONEYACC);
			//反馈数据库操作结果 及 更新数据
			m_pUserManagerSPI->OnUpdateMainAccount(nRes, uInfo, usrShip,m_sessionUserID);
			return;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}
		
	}

private:
	void TranslateToStruct(userInfos& uInfo, userRelationShip& usrShip)
	{
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
	std::string m_errMsg;
};
