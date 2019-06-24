#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include "utility_fun.h"
#include <iostream>
#include "DigitalVisa.h"
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"
#include "errCodeDef.h"
#include "AuthrityControl.h"
#include "GlobalParamLogRecord.h"
#include "AuthrityControl.h"
#include "NetCommandCode.h"

class CAgentAdd
{
public:
	CAgentAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID),m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			TranslateStruct(tmp, userShip);

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID, m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_ADD_RSP;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//添加代理商
			std::string uuid = UUID::getUUid();
			tmp.m_sUserID = uuid;  
			userShip.sUserID = uuid;

			addAgent(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

private:

	void TranslateStruct(userInfos& tmp, userRelationShip& userShip)
	{
		tmp.m_nUserType			= UsersType::USER_INSTITUTION;
		tmp.m_nLevel			= m_info[level].asInt();
		tmp.m_sLoginName		= m_info[loginName].asString();
		tmp.m_sAccountName		= m_info[accountName].asString();
		tmp.m_sPassword			= m_info[passwords].asString();
		tmp.m_sPhone			= m_info[phone].asString();
		tmp.m_nRegisterDate		= UtilityFun::getLocalDateInt();
		tmp.m_nRegisterTime		= UtilityFun::getLocalTimeInt();
		tmp.m_nMainIDNum		= m_info[mainIDNum].asInt();
		tmp.m_nSumIDNum			= m_info[subIDNum].asInt();
		tmp.m_nFinanceType		= m_info[financeType].asInt();

		userShip.sInstitutionID			= m_info[InstitutionID].asString();
		userShip.sFeemoduleID			= m_info[FeeModuleID].asString();
		userShip.sAuthrityModuleID		= m_info[AuthrityModuleID].asString();
		userShip.sRiskModuleAuthrityID  = m_info[RiskModuleAuthrityID].asString();

	}

	void addAgent(userInfos& users, userRelationShip& userShip)
	{
		//检测账户名不能有中文
		if (UtilityFun::isChineseString(users.m_sLoginName))
		{
			//反馈用户错误  有中文
			std::cout << "登录名有中文" << std::endl;
			return m_pUserManagerSPI->OnAddChildAgent(ERR_ACCOUNT_CHINESE, "账户名不能包含中文", users, userShip, m_sessionUserID);
		}

		//账户是否已存在
		if (CCacheUserAllInfo::instance()->IsUserExist(users.m_sLoginName))
		{
			//反馈用户错误  账户名已存在
			std::cout << "该登录名已存在" << std::endl;
			return m_pUserManagerSPI->OnAddChildAgent(ERR_ACCOUNT_ALREADY_EXIST, "账户名已存在", users, userShip, m_sessionUserID);
		}

		//判断父节点的等级
		int nLevel = 0;
		CCacheUserAllInfo::instance()->selectAccLevel(userShip.sInstitutionID,nLevel);
		SystemSet setinfo;
		int nMaxLevel = 0;
		if (!CCacheUserAllInfo::instance()->selectSystemSet("STITUTION_LEVEL", setinfo))
			nMaxLevel = 3;
		else
			nMaxLevel = std::stoi(setinfo.m_sValue);

		if (nLevel > (nMaxLevel - 1))
		{
			//反馈 代理商增加已达最大等级
			return m_pUserManagerSPI->OnAddChildAgent(ERR_AGENTADD_MAXLEVEL, "代理商增加已达最大等级", users, userShip, m_sessionUserID);
		}
		//获取推广码
		for (;;)
		{
			users.m_sPoularizeLink = CDigitalVisa::CreatPopularizeLink();//写函数生成推广码
			if (users.m_sPoularizeLink.size() < 4)
				continue;
			if(CCacheUserAllInfo::instance()->IsPopuLinkExist(users.m_sPoularizeLink))
				continue;
			break;
		}

		// 父节点等级+1,表示下一级
		users.m_nLevel = nLevel + 1;
		if (!CDBOpeartor::instance()->addAgent(users, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(users, userShip))
		{
			//反馈数据库操作失败
			return m_pUserManagerSPI->OnAddChildAgent(ERR_DB_OPERATOR, "操作数据库失败", users, userShip, m_sessionUserID);
		}

		// 用户信息问题存取
		userIdentify identifyInfo;
		identifyInfo.m_sUserID = users.m_sUserID;
		identifyInfo.m_nIsDentify = 0;
		if (!CDBOpeartor::instance()->addUserIdentify(identifyInfo, 1) ||
			!CCacheUserAllInfo::instance()->addUserIdentifyCache(identifyInfo, 1))
		{
			//反馈数据库操作失败
			return m_pUserManagerSPI->OnAddChildAgent(ERR_DB_OPERATOR, "操作数据库失败", users, userShip, m_sessionUserID);
		}

		// 添加一条机构佣金信息
		// 添加佣金信息数据库和缓存


		//反馈添加代理成功
		std::cout << "添加代理商成功" << endl;
		m_pUserManagerSPI->OnAddChildAgent(0, "正确", users, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};

