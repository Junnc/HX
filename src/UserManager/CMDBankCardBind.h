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

class CBankCardBind
{
public:
	CBankCardBind(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userIdentify usrIdentify;
			usrIdentify.m_sUserID		= m_info[usrID].asString();
			usrIdentify.m_sBankName		= m_info[BankName].asString();
			usrIdentify.m_sBranchBank	= m_info[BranchBank].asString();
			usrIdentify.m_sBankCardNo	= m_info[BankCardNo].asString();

			userIdentifyPtr ideptr = std::make_shared<userIdentify>(usrIdentify);
			if (!CDBOpeartor::instance()->addUserIdentify(usrIdentify) ||
				!CCacheUserAllInfo::instance()->addUserIdentifyCache(usrIdentify))
			{
				std::cout << "add DB UserIdentify fail!" << endl;
				//反馈数据  绑定银行卡失败
				return m_pUserManagerSPI->OnBankCardBind(-1, "数据库操作失败", ideptr, m_sessionUserID);
			}

			//反馈数据 绑定银行卡成功
			m_pUserManagerSPI->OnBankCardBind(0, "正确", ideptr, m_sessionUserID);
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