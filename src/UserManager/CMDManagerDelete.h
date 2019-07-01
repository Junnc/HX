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
#include "GlobalParamLogRecord.h"
#include "errCodeDef.h"
#include "AuthrityControl.h"
#include "PrintLogMessage.h"

class CManagerDelete
{
public:
	CManagerDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CManagerDelete()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDManagerDelete]");
	}
	void handle()
	{
		try
		{
			std::string sUsrID	= m_info[usrID].asString();
			int recourse		= m_info[RESOURCE].asInt();

			//判断是否在线
			if (m_pUserManagerSPI->IsUserOnline(sUsrID))
			{
				Json::Value contentValue;
				contentValue[usrID] = sUsrID;

				Json::Value rootValue;
				rootValue[CMD] = MANAGER_DELETE_RSP;
				rootValue[ERRCODE] = ERR_ACC_ONLINE;
				rootValue[ERRMSG] = "账户在线";
				rootValue[CONTENT] = contentValue;

				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg, m_sessionUserID);
				return;

			}
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

			deleteManager(sUsrID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}	
	}

private:
	void deleteManager(std::string sUsrID)
	{
		userRelationShip usrShip;

		if (!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrShip))
		{
			m_errMsg = "账户已被删除";
			return m_pUserManagerSPI->OnDelManagerAccount(ERR_USER_NOEXIST, "账户已被删除", sUsrID, usrShip.sInstitutionID, m_sessionUserID);
		}

		//记录数据库日志  删除信息
		GlobalParamsLogRecord::instance()->AccountManagerLogRecord("管理员删除", 
			GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MANAGER_ACC), nullptr, nullptr, UsersType::USER_MANAGER, sUsrID);
		
		//删除数据库
		int nRes = 0;
		if (!CDBOpeartor::instance()->deleteMainAccountOrManager(sUsrID) ||
			!CCacheUserAllInfo::instance()->deleteMainAccAllinfoOrManager(sUsrID))
		{
			m_errMsg = "删除数管理员失败";
			nRes = -1;
		}

		//反馈操作成功  待实现
		m_pUserManagerSPI->OnDelManagerAccount(nRes, "正确", sUsrID, usrShip.sInstitutionID, m_sessionUserID);
	}
private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};
