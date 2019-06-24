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

class CAgentUpdate
{
public:
	CAgentUpdate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos userTmp;
			userRelationShip userShip;
			TranslateStruct(userTmp, userShip);
			//��������Ƿ�Ϸ� 
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(userTmp.m_sUserID,m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content,m_sessionUserID);
				return;
			}


			//�������ݿ� �ͻ���
			int nRes = 0;
			if (!CDBOpeartor::instance()->updateChildAccount(userTmp, userShip) ||
				!CCacheUserAllInfo::instance()->updateChildAgent(userTmp, userShip))
			{
				//�������ݿ�ʧ��
				std::cout << "���´��������ݿ�ʧ��" << endl;
				nRes = -1;
			}
			CCacheUserAllInfo::instance()->selectAccLevel(userTmp.m_sUserID, userTmp.m_nLevel);
			
			//����¼�¼�� log_record ��  �����
			userInfosPtr usrPtr = std::make_shared<userInfos>(userTmp);
			userRelationShipPtr shipPtr = std::make_shared<userRelationShip>(userShip);
			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("�¼��������",
				GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_AGENT), usrPtr, shipPtr, UsersType::USER_INSTITUTION);
			//������Ϣ  ����� �ɹ����
			std::cout << "���´����̳ɹ�" << endl;
			m_pUserManagerSPI->OnUpdateChildAgent(nRes, userTmp, userShip, m_sessionUserID);
		}
		catch (const std::exception&e)
		{
			std::cout << e.what() << std::endl;
		}

	}

private:
	void TranslateStruct(userInfos& tmp, userRelationShip& userShip)
	{
		tmp.m_sUserID			= m_info[usrID].asString();
		tmp.m_sLoginName		= m_info[loginName].asString();
		tmp.m_sPassword			= m_info[passwords].asString();
		tmp.m_sAccountName		= m_info[accountName].asString();
		tmp.m_sPhone			= m_info[phone].asString();
		tmp.m_nUserType			= UsersType::USER_TRADER;
		tmp.m_nMainIDNum		= m_info[mainIDNum].asInt();
		tmp.m_nSumIDNum			= m_info[subIDNum].asInt();
		tmp.m_sPoularizeLink	= m_info[popularizeLink].asString();

		userShip.sUserID		= m_info[usrID].asString();
		userShip.sFeemoduleID	= m_info[FeeModuleID].asString();
		userShip.sInstitutionID = m_info[InstitutionID].asString();
		userShip.sMainID		= m_info[MainID].asString();
		userShip.sAuthrityModuleID		= m_info[AuthrityModuleID].asString();
		userShip.sRiskModuleAuthrityID  = m_info[RiskModuleAuthrityID].asString();
		


	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
