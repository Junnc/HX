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
#include "PrintLogMessage.h"

class CRealNameCertifitionQuery
{
public:
	CRealNameCertifitionQuery(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI):
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CRealNameCertifitionQuery()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDRealNameCertificationQuery]");
	}
	void handle()
	{
		//std::string institutionID = m_info[InstitutionID];
		//std::string userID = m_info[usrID];
		//std::string startDate = m_info[PostTime];
		//std::string endDate = m_info[ApprovalTime];
		//int state = std::stoi(m_info[IsApproval]);

	}
private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};