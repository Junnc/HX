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

class CMainAccountDelete
{
public:
	CMainAccountDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CMainAccountDelete()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDMainAccountDelete]");
	}

	void handle()
	{
		try
		{
			//d待删除的主账号Uid
			std::string sUsrID = m_info[usrID].asString();
			std::string institution = m_info[InstitutionID].asString();

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(sUsrID,m_sessionUserID, m_pUserManagerSPI))
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

			int nRes = 0;
			userInfos usrInfo;
			CCacheUserAllInfo::instance()->queryAccount(institution, usrInfo);
			bool iRes = false;
			if (usrInfo.m_nLevel == 1 && usrInfo.m_nUserType == UsersType::USER_INSTITUTION ||
				usrInfo.m_nUserType == UsersType::USER_MANAGER)
			{
				//是否存在绑定子账户
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(sUsrID, usrMap))
				{
					m_errMsg = "主账户存在绑定的子账户";
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户存在绑定的子账户", sUsrID, "", m_sessionUserID);

				}

				//主账户是否存在绑定的开户模板
				if (0/*开户模板判断*/)
				{
					m_errMsg = "主账户已绑定代理开户模板，无法删除";
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户已绑定代理开户模板，无法删除", institution, sUsrID, m_sessionUserID);
				}

				//主账户删除日志记录到数据库
				GlobalParamsLogRecord::instance()->AccountManagerLogRecord("主账户删除", 
					GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MAIN_ACC), nullptr, nullptr, UsersType::USER_MONEYACC, sUsrID);

				//删除主账户
				if (!CDBOpeartor::instance()->deleteMainAccountOrManager(sUsrID) ||
					!CCacheUserAllInfo::instance()->deleteMainAccAllinfoOrManager(sUsrID))
				{
					m_errMsg = "删除数据库主账户失败";
					nRes = -1;
				}
			}
			else
			{
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(institution, sUsrID, usrMap))
				{
					m_errMsg = "主账户存在绑定的子账户";
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户存在绑定的子账户", sUsrID, "", m_sessionUserID);
				}

				if (!CDBOpeartor::instance()->delAssignMainAccount(sUsrID, institution) ||
					!CCacheUserAllInfo::instance()->deleteInstitutionMainidMap(sUsrID, institution))
				{
					nRes = -1;
				}
			}

			if (0 != iRes)
			{
				m_errMsg = "操作数据库失败";
				return m_pUserManagerSPI->OnDelMainAccount(ERR_DB_OPERATOR, "操作数据库失败", sUsrID, "", m_sessionUserID);
			}
				

			m_pUserManagerSPI->OnDelMainAccount(iRes, "正确", sUsrID, institution, m_sessionUserID);
		}
		catch (const std::exception& e)
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