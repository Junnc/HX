﻿#pragma once
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
#include "GlobalParamLogRecord.h"
#include "AuthrityControl.h"
#include "PrintLogMessage.h"

class CManagerAdd
{
public:
	CManagerAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}
	~CManagerAdd()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDManagerAdd]");
	}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			addChildAccTranslate(tmp, userShip);

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID,m_sessionUserID, m_pUserManagerSPI))
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

			tmp.m_sUserID = UUID::getUUid();
			userShip.sUserID = tmp.m_sUserID;
			addManager(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
			m_errMsg = e.what();
		}
		
	}

private:

	void addChildAccTranslate(userInfos& tmp, userRelationShip& userShip)
	{

		tmp.m_sUserID		= m_info[usrID].asString();
		tmp.m_nUserType		= UsersType::USER_MANAGER;
		tmp.m_nLevel		= m_info[levels].asInt();
		tmp.m_sLoginName	= m_info[loginName].asString();
		tmp.m_sAccountName	= m_info[accountName].asString();
		tmp.m_sPassword		= m_info[passwords].asString();
		tmp.m_nRegisterDate = UtilityFun::getLocalDateInt();
		tmp.m_nRegisterTime = UtilityFun::getLocalTimeInt();
		tmp.m_nFinanceType  = m_info[financeType].asInt();

		userShip.sInstitutionID		= m_info[InstitutionID].asString();
		userShip.sAuthrityModuleID  = m_info[AuthrityModuleID].asString();
		userShip.sFeemoduleID		= m_info[FeeModuleID].isNull() ? m_info[FeeModuleID].asString() : "";

	}

	void addManager(userInfos& tmp, userRelationShip& userShip)
	{
		//检测账户名不能有中文
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			m_errMsg = "账户名不能包含中文";
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_ACCOUNT_CHINESE, "账户名不能包含中文", tmp, userShip, m_sessionUserID);
		}
		//账户是否已存在
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			m_errMsg = "账户名已存在";
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_ACCOUNT_ALREADY_EXIST, "账户名已存在", tmp, userShip, m_sessionUserID);
		}

		//添加数据库
		if (!CDBOpeartor::instance()->addManager(tmp, userShip))
		{
			m_errMsg = "操作数据库失败";
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_DB_OPERATOR, "操作数据库失败", tmp, userShip, m_sessionUserID);
		}
		//添加缓存
		CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip);

		//反馈 操作成功
		m_pUserManagerSPI->OnAddManagerAccount(0, "正确", tmp, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};

