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
#include "PrintLogMessage.h"


class CChildAccountAdd
{
public:
	CChildAccountAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI), m_errMsg(""){}
	~CChildAccountAdd()
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
		CPrintLogMessage plm(msg, nLogType, "[CMDChildAccountAdd]");
	}
	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			addChildAccTranslate(tmp, userShip);
			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID,m_sessionUserID,m_pUserManagerSPI))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_ADD_RSP;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				m_errMsg = writer.write(rootValue);
				return m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(m_errMsg, m_sessionUserID);
			}

			//添加子账户
			std::string uuid = UUID::getUUid();
			tmp.m_sUserID = uuid;  //获取uuid
			userShip.sUserID = uuid;//同上一个uuid

			addChildaccount(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			m_errMsg = e.what();
		}
	}

private:

	void addChildAccTranslate(userInfos& tmp,userRelationShip& userShip)
	{	
		tmp.m_nUserType = m_info[usrType].asInt();
		tmp.m_nLevel = m_info[levels].asInt();
		tmp.m_sLoginName = m_info[loginName].asString();
		tmp.m_sAccountName = m_info[accountName].asString();
		tmp.m_sPassword = m_info[passwords].asString();
		tmp.m_sPhone = m_info[phone].asString();
		tmp.m_nRegisterDate = UtilityFun::getLocalDateInt();
		tmp.m_nRegisterTime = UtilityFun::getLocalTimeInt();
		tmp.m_nFinanceType = m_info[financeType].asInt();

		userShip.sInstitutionID = m_info[InstitutionID].asString();
		userShip.sMainID = m_info[MainID].asString();
		userShip.sFeemoduleID = m_info[FeeModuleID].asString();
		userShip.sRiskModuleID = m_info[RiskModuleID].asString();
		userShip.sMarginModuleID = m_info[MarginModuleID].asString();

	}

	void addChildaccount(userInfos& tmp, userRelationShip& userShip)
	{
		//检测账户名不能有中文
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			//反馈用户错误  有中文
			m_errMsg = "账户名不能含有中文";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ACCOUNT_CHINESE, "账户名不能含有中文", tmp, userShip, m_sessionUserID);
		}

		//账户是否已存在
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			//反馈用户错误  账户名已存在
			m_errMsg = "账户名已存在";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ACCOUNT_ALREADY_EXIST, "账户名已存在", tmp, userShip, m_sessionUserID);
		}
		

		//是否达到最大个数
		int curNum = 0;
		int rlt = CCacheUserAllInfo::instance()->getMaxChildNumber(userShip.sInstitutionID, curNum);
		if (-1 == rlt)
		{
			//不存在此机构
			m_errMsg = "数据库操作失败，不存在的机构";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "数据库操作失败，不存在的机构", tmp, userShip, m_sessionUserID);
		}
		else if(-2 == rlt)
		{
			//添加子账户已满
			m_errMsg = "添加子账户已达最大值";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ADDCHILDACC_MAX, "添加子账户已达最大值", tmp, userShip, m_sessionUserID);
		}

		//添加数据库
		if (!CDBOpeartor::instance()->addChildAccount(tmp, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip))
		{
			//添加数据库失败，反馈客户端
			m_errMsg = "操作数据库user失败";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "操作数据库失败", tmp, userShip, m_sessionUserID);
		}


		//添加user_money_info
		userMoneyInfo usrMoney;
		usrMoney.m_sUserID = tmp.m_sUserID;
		if (!CDBOpeartor::instance()->addUserMoneyInfo(usrMoney))
		{
			//添加数据库user_money_info失败，反馈客户端
			m_errMsg = "操作数据库money失败";
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "操作数据库失败", tmp, userShip, m_sessionUserID);
		}
		CCacheUserAllInfo::instance()->addUserMoneyinfoCache(usrMoney);

		m_pUserManagerSPI->OnAddChildAccount(0, "正确", tmp, userShip, m_sessionUserID);
		
		m_pUserManagerSPI->OnAddChildAccPush(0, "正确", tmp, userShip, m_sessionUserID);
	}

private:
	/*std::map<std::string, std::string>*/
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
	std::string m_errMsg;
};