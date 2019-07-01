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
#include "GlobalParamLogRecord.h"
#include "PrintLogMessage.h"


class CChildAccountDelete
{
public:
	CChildAccountDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CChildAccountDelete()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDChildAccountDelete]");
	}

	void handle()
	{
		try
		{
			std::string sUsrID = m_info[usrID].asString();
			int resource = m_info[RESOURCE].asInt();
			//判断待删除子账户是否在线
			if (m_pUserManagerSPI->IsUserOnline(sUsrID))
			{
				Json::Value contentValue;
				contentValue[usrID] = sUsrID;

				Json::Value rootValue;
				rootValue[CMD] = CHILD_ACCOUNT_DELETE_RSP;
				rootValue[ERRCODE] = ERR_ACC_ONLINE;
				rootValue[ERRMSG] = "账户在线";
				rootValue[CONTENT] = contentValue;
				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg, m_sessionUserID);
				return;
			}

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(sUsrID, m_sessionUserID, m_pUserManagerSPI))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_QUERY_RSP;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg, m_sessionUserID);
				return;
			}

			//判断子账户是否持仓或者未生效订单，  无法删除
			if (m_pUserManagerSPI->IsHoldPosition(sUsrID))
			{
				m_errMsg = "子账户存在持仓";
				return m_pUserManagerSPI->OnDelChildAccount(ERR_CHILDPOSITION_EXIST, "子账户存在持仓",sUsrID,"",m_sessionUserID);		
			}

			if (m_pUserManagerSPI->IsTodayNoEffectiveOrder(sUsrID))
			{
				m_errMsg = "子账户存在未生效的委托";
				return m_pUserManagerSPI->OnDelChildAccount(ERR_CHILDORDER_EXIST, "子账户存在未生效的委托", sUsrID, "", m_sessionUserID);
			}

			userInfos usrInfo;
			userRelationShip usrShip;
			if (!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrInfo) ||
				!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrShip))
			{
				m_errMsg = "账户已被删除";
				return m_pUserManagerSPI->OnDelChildAccount(ERR_USER_NOEXIST, "账户已被删除", sUsrID, "", m_sessionUserID);
			}
				
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("子账户删除", 
				GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_ACC),
				nullptr, nullptr,UsersType::USER_TRADER, sUsrID);

			//开始删除DB
			if (!CDBOpeartor::instance()->deleteChildAccount(sUsrID))
				return m_pUserManagerSPI->OnDelChildAccount(ERR_DB_OPERATOR, "账户已被删除", sUsrID, "", m_sessionUserID);
			
			CCacheUserAllInfo::instance()->deleteUserAllinfo(sUsrID);
			m_pUserManagerSPI->OnDelChildAccount(0, "正确", sUsrID, usrShip.sInstitutionID, m_sessionUserID);

			usrInfo.m_nIsLogicDel = 1;
			m_pUserManagerSPI->OnAddChildAccPush(0, "正确", usrInfo, usrShip, m_sessionUserID);

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