#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"
#include "PrintLogMessage.h"

class CRealNameCertifitionVerificate
{
public:

	CRealNameCertifitionVerificate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI):
		m_info(root),m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI),m_errMsg("") {}

	~CRealNameCertifitionVerificate()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDRealNameCertificationVerificate]");
	}
	void handle()
	{
		try
		{
			int id					= m_info[ID].asInt();
			int state				= m_info[IsApproval].asInt();
			std::string userID		= m_info[InstitutionID].asString();
			std::string apprReson	= m_info[ApprovalReason].asString();
			std::string apprID		= m_info[ApprovalID].asString();

			//修改审核状态 数据库和缓存
			if (!CDBOpeartor::instance()->updateCertifitionRegState(id, state, apprReson, apprID) || 
				!CCacheUserAllInfo::instance()->updateCertifitionRegState(id, state, apprReson, apprID))
			{
				m_errMsg = "数据库操作失败";
			}

			//修改用户表验证状态
			if (1 == state)
			{
				//审核通过，改为已认证
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, state) ||
					!CCacheUserAllInfo::instance()->updateIndentifyState(userID, state))
				{
					m_errMsg = "数据库操作失败";
				}
				//更新缓存
				

				//通知首页更新实名认证信息
				certificationRegRecordInfoPtr tableInfo = std::make_shared<certificationRegisterRecordInfo>();
				CDBOpeartor::instance()->SelectDB(id, tableInfo);
				m_pUserManagerSPI->OnRealNameCertificationSent(0, "正确", tableInfo, m_sessionUserID);

			}
			if (2 == state)
			{
				//审核未通过，改为未认证
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, 0) ||
					!CCacheUserAllInfo::instance()->updateIndentifyState(userID, 0))
				{
					m_errMsg = "数据库操作失败";
				}
				
			}

			//正确完成，响应操作事件
			m_pUserManagerSPI->OnRealNameCertificationExe(0, "正确", id, state, apprReson, apprID, m_sessionUserID);
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
