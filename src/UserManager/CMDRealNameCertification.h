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

class CRealNameCertifition
{
public:
	CRealNameCertifition(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CRealNameCertifition()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDRealNameCertification]");
	}

	void handle()
	{
		try
		{
			certificationRegisterRecordInfo cer;
			cer.m_sUserId = m_info[usrID].asString();
			cer.m_sLoginName = m_info[loginName].asString();
			cer.m_sAccountName = m_info[accountName].asString();
			cer.m_sIDCard = m_info[IDCard].asString();
			cer.m_sSurName = m_info[SurName].asString();
			cer.m_sPostTime = UtilityFun::getDateTimeString();
			cer.m_sApprovalTime = m_info[ApprovalTime].empty() ? "0000-00-00 00:00:00" : m_info[ApprovalTime].asString();

			userIdentify usrIdentify;
			usrIdentify.m_sUserID = cer.m_sUserId;
			usrIdentify.m_sIDCard = cer.m_sIDCard;
			usrIdentify.m_sSurName = cer.m_sSurName;

			certificationRegRecordInfoPtr cerPtr = std::make_shared<certificationRegisterRecordInfo>(cer);
			//判断是否已验证
			userIdentify usInfo;
			if (!CCacheUserAllInfo::instance()->selectIdentifyInfo(cer.m_sUserId, usInfo))
			{
				m_errMsg = "没有认证信息";
				return m_pUserManagerSPI->OnRealNameCertification(-1, "没有认证信息", cerPtr, 0, m_sessionUserID);
			}

			if (0 != usInfo.m_nIsDentify)
			{
				m_errMsg = "待认证或者已认证";
				return m_pUserManagerSPI->OnRealNameCertification(-1, "待认证或者已认证", cerPtr, 0, m_sessionUserID);
			}

			//添加认证记录
			if (!CDBOpeartor::instance()->addUserIdentifyAuthenticate(cer) ||
				!CCacheUserAllInfo::instance()->updateIdentifySurName(usrIdentify) ||
				!CCacheUserAllInfo::instance()->addCertifitionRegRecordTableCache(cer))
			{
				//添加认证记录失败  反馈
				m_errMsg = "修改认证标记为待认证失败";
				return m_pUserManagerSPI->OnRealNameCertification(-1, "修改认证标记为待认证失败", cerPtr, 0, m_sessionUserID);
			}

			//反馈修改成功  待实现
			m_pUserManagerSPI->OnRealNameCertification(0, "正确", cerPtr, 2, m_sessionUserID);
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