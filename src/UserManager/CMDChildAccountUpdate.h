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

class CChildAccountUpdate
{
public:
	CChildAccountUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			TranslateStruct(tmp, userShip);
			//检测连接是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_QUERY_RSP;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//参数验证
			userRelationShip old_usership;
			if (!CCacheUserAllInfo::instance()->selectUsersOne(tmp.m_sUserID, old_usership))
			{
				//该子账户不存在  反馈消息给登录端
				return m_pUserManagerSPI->OnUpdateChildAccount(ERR_USER_NOEXIST, "账户不存在", old_usership.sRiskModuleID, tmp, old_usership, m_sessionUserID);
			}

			//修改子账户的主账户时判断是否有持仓
			if (old_usership.sMainID != userShip.sMainID)
			{
				//待处理 有无持仓
				//return;
			}

			
			//更新数据库 和缓存
			if (!CDBOpeartor::instance()->updateChildAccount(tmp, userShip) ||
				!CCacheUserAllInfo::instance()->updateUsersAndRelationShip(tmp, userShip))
			{
				return;
			}
			m_pUserManagerSPI->OnUpdateChildAccount(0, "正确", old_usership.sRiskModuleID, tmp, userShip, m_sessionUserID);

			//存更新记录到 log_record 表  待完成
			userInfosPtr usrPtr = std::make_shared<userInfos>(tmp);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(userShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("子账户更新",
				GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_ACC), usrPtr, shipPtr, UsersType::USER_TRADER);
			
			
			//反馈信息  待完成
			m_pUserManagerSPI->OnAddChildAccPush(0, "正确", tmp, userShip, m_sessionUserID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
	}

private:
	void TranslateStruct(userInfos& tmp, userRelationShip& userShip)
	{
		tmp.m_sUserID = m_info[usrID].asString();
		tmp.m_sLoginName = m_info[loginName].asString();
		tmp.m_sPassword = m_info[passwords].asString();
		tmp.m_sAccountName = m_info[accountName].asString();
		tmp.m_nUserType = m_info[usrType].asInt();
		tmp.m_sPhone = m_info[phone].asString();
		tmp.m_nUserType = UsersType::USER_TRADER;

		userShip.sUserID = m_info[usrID].asString();
		userShip.sInstitutionID = m_info[InstitutionID].asString();
		userShip.sMainID = m_info[MainID].asString();
		userShip.sFeemoduleID = m_info[FeeModuleID].asString();
		userShip.sRiskModuleID = m_info[RiskModuleID].asString();
		userShip.sMarginModuleID = m_info[MarginModuleID].asString();
		
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};