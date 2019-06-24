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

class CMainAccountDelete
{
public:
	CMainAccountDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			//d待删除的主账号Uid
			std::string sUsrID = m_info[usrID].asString();
			std::string institution = m_info[InstitutionID].asString();

			//检测通信是否合法
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(sUsrID,m_sessionUserID))
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

			int nRes = 0;
			userInfos usrInfo;
			CCacheUserAllInfo::instance()->queryAccount(institution, usrInfo);
			bool iRes = false;
			std::cout << "level=" << usrInfo.m_nLevel << ",type=" << usrInfo.m_nUserType
				<< ",institution=" << institution << endl;
			if (usrInfo.m_nLevel == 1 && usrInfo.m_nUserType == UsersType::USER_INSTITUTION ||
				usrInfo.m_nUserType == UsersType::USER_MANAGER)
			{
				//是否存在绑定子账户
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(sUsrID, usrMap))
				{
					//有绑定的子账号 无法删除 反馈
					std::cout << "该主账号存在绑定的子账号" << endl;
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户存在绑定的子账户", sUsrID, "", m_sessionUserID);

				}

				//主账户是否存在绑定的开户模板
				if (0/*开户模板判断*/)
				{
					//存在开户模板  无法删除  反馈
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户已绑定代理开户模板，无法删除", institution, sUsrID, m_sessionUserID);
				}

				//主账户删除日志记录到数据库  待实现
				GlobalParamsLogRecord::instance()->AccountManagerLogRecord("主账户删除", 
					GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MAIN_ACC), nullptr, nullptr, UsersType::USER_MONEYACC, sUsrID);

				//删除主账户
				if (!CDBOpeartor::instance()->deleteMainAccountOrManager(sUsrID) ||
					!CCacheUserAllInfo::instance()->deleteMainAccAllinfoOrManager(sUsrID))
				{
					//删除数据库失败 反馈
					std::cout << "删除数据库主账户失败" << endl;
					nRes = -1;
				}
			}
			else
			{
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(institution, sUsrID, usrMap))
				{
					//有绑定的子账号 无法删除 反馈
					std::cout << "该主账号存在绑定的子账号" << endl;
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "主账户存在绑定的子账户", sUsrID, "", m_sessionUserID);
				}

				if (!CDBOpeartor::instance()->delAssignMainAccount(sUsrID, institution) ||
					!CCacheUserAllInfo::instance()->deleteInstitutionMainidMap(sUsrID, institution))
				{
					nRes = -1;
				}
			}

			if (0 != iRes)
				return m_pUserManagerSPI->OnDelMainAccount(ERR_DB_OPERATOR, "操作数据库失败", sUsrID, "", m_sessionUserID);

			m_pUserManagerSPI->OnDelMainAccount(iRes, "正确", sUsrID, institution, m_sessionUserID);
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