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
#include "AuthrityControl.h"

class CMainAccountAdd
{
public:
	CMainAccountAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			addChildAccTranslate(tmp, userShip);

			//检测通信是否合法  待实现
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "不合法的指令";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//添加主账户
			std::string uuid = UUID::getUUid();
			tmp.m_sUserID = uuid;  //获取uuid
			userShip.sUserID = uuid;//同上一个uuid

			//检测通信是否合法
			if (0/*检测通信*/)
			{

			}

			addChildaccount(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
	}

private:

	void addChildAccTranslate(userInfos& tmp, userRelationShip& userShip)
	{
		std::cout << "enter CCommandParseAndDeal::addUserInfoTranslate" << std::endl;

		tmp.m_nUserType = m_info[usrType].asInt();
		tmp.m_nLevel = m_info[level].asInt();
		tmp.m_sLoginName = m_info[loginName].asString();
		tmp.m_sAccountName = m_info[accountName].asString();
		tmp.m_sPassword = m_info[passwords].asString();
		//tmp.m_sPhone = m_info[phone];
		tmp.m_nRegisterDate = UtilityFun::getLocalDateInt();
		tmp.m_nRegisterTime = UtilityFun::getLocalTimeInt();
		tmp.m_nCounterType = m_info[counterType].asInt();
		tmp.m_nFinanceType = m_info[financeType].asInt();

		userShip.sInstitutionID = m_info[InstitutionID].asString();

	}

	void addChildaccount(userInfos& tmp, userRelationShip& userShip)
	{
		//检测账户名不能有中文
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			//反馈用户错误  有中文
			std::cout << "用户名有中文" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ACCOUNT_CHINESE, "账户名不能包含中文", tmp, userShip,m_sessionUserID);
		}

		//账户是否已存在
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			//反馈用户错误  账户名已存在
			std::cout << "用户名已存在" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ACCOUNT_ALREADY_EXIST, "账户名已存在", tmp, userShip, m_sessionUserID);
		}


		//是否达到最大个数
		int curNum = 0;
		int rlt = CCacheUserAllInfo::instance()->getMaxChildNumber(userShip.sInstitutionID, curNum);
		if (-1 == rlt)
		{
			//不存在此机构
			std::cout << "此机构不存在" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_DB_OPERATOR, "数据库操作失败，不存在的机构", tmp, userShip, m_sessionUserID);
		}
		else if (-2 == rlt)
		{
			//添加子账户已满
			std::cout << "子账号添加已满" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ADDCHILDACC_MAX, "添加主账户已达最大值", tmp, userShip, m_sessionUserID);
		}

		//添加数据库
		if (!CDBOpeartor::instance()->addChildAccount(tmp, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip))
		{
			//添加数据库失败，反馈客户端
			std::cout << "添加子账户数据库失败" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_DB_OPERATOR, "数据库操作失败", tmp, userShip, m_sessionUserID);
		}
		m_pUserManagerSPI->OnAddMainAccount(0, "正确", tmp, userShip, m_sessionUserID);

		//通知登录端添加成功 待实现
		std::cout << "添加主账号成功" << endl;
		m_pUserManagerSPI->OnAddMainAccPush(0, "正确", tmp, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
