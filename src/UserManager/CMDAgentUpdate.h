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

class CAgentUpdate
{
public:
	CAgentUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CAgentUpdate()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDAgentUpdate]");
	}

	void handle()
	{
		try
		{
			userInfos userTmp;
			userRelationShip userShip;
			TranslateStruct(userTmp, userShip);
			//检测连接是否合法 
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(userTmp.m_sUserID,m_sessionUserID,m_pUserManagerSPI))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);	
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg,m_sessionUserID);
				return;
			}


			//更新数据库 和缓存
			int nRes = 0;
			if (!CDBOpeartor::instance()->updateChildAccount(userTmp, userShip) ||
				!CCacheUserAllInfo::instance()->updateChildAgent(userTmp, userShip))
			{
				m_errMsg = "更新代理商数据库失败";
				nRes = -1;
			}
			CCacheUserAllInfo::instance()->selectAccLevel(userTmp.m_sUserID, userTmp.m_nLevel);
			
			//存更新记录到 log_record 表  待完成
			userInfosPtr usrPtr = std::make_shared<userInfos>(userTmp);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(userShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("下级代理更新",
				GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_AGENT), usrPtr, shipPtr, UsersType::USER_INSTITUTION);
			//反馈信息  待完成 成功与否
			m_pUserManagerSPI->OnUpdateChildAgent(nRes, userTmp, userShip, m_sessionUserID);
		}
		catch (const std::exception&e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}

	}

private:
	void TranslateStruct(userInfos& tmp, userRelationShip& userShip)
	{
		tmp.m_sUserID			= m_info[usrID].asString();
		tmp.m_sLoginName		= m_info[loginName].asString();
		tmp.m_sPassword			= m_info[passwords].asString();
		tmp.m_sAccountName		= m_info[accountName].asString();
		tmp.m_sPhone			= m_info[phone].asString();
		tmp.m_nUserType			= UsersType::USER_TRADER;
		tmp.m_nMainIDNum		= m_info[mainIDNum].asInt();
		tmp.m_nSumIDNum			= m_info[subIDNum].asInt();
		tmp.m_sPoularizeLink	= m_info[popularizeLink].asString();

		userShip.sUserID		= m_info[usrID].asString();
		userShip.sFeemoduleID	= m_info[FeeModuleID].asString();
		userShip.sInstitutionID = m_info[InstitutionID].asString();
		userShip.sMainID		= m_info[MainID].asString();
		userShip.sAuthrityModuleID		= m_info[AuthrityModuleID].asString();
		userShip.sRiskModuleAuthrityID  = m_info[RiskModuleAuthrityID].asString();
		


	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};
