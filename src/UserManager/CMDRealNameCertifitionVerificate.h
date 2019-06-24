#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"

class CRealNameCertifitionVerificate
{
public:

	CRealNameCertifitionVerificate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI):
		m_info(root),m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

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
			if (!CDBOpeartor::instance()->updateCertifitionRegState(id, state, apprReson, apprID))
			{
				//插入数据库 错误处理
			}
			CCacheUserAllInfo::instance()->updateCertifitionRegState(id, state, apprReson, apprID);

			//修改用户表验证状态
			if (1 == state)
			{
				//审核通过，改为已认证
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, state))
				{
					//错误处理
				}
				//更新缓存
				CCacheUserAllInfo::instance()->updateIndentifyState(userID, state);

				//通知首页更新实名认证信息
				certificationRegRecordInfoPtr tableInfo = std::make_shared<certificationRegisterRecordInfo>();
				CDBOpeartor::instance()->SelectDB(id, tableInfo);
				m_pUserManagerSPI->OnRealNameCertificationSent(0, "正确", tableInfo, m_sessionUserID);

			}
			if (2 == state)
			{
				//审核未通过，改为未认证
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, 0))
				{
					//错误处理
				}
				CCacheUserAllInfo::instance()->updateIndentifyState(userID, 0);

			}

			//正确完成，响应操作事件
			m_pUserManagerSPI->OnRealNameCertificationExe(0, "正确", id, state, apprReson, apprID, m_sessionUserID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
