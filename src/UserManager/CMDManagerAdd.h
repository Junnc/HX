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

class CManagerAdd
{
public:
	CManagerAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			userInfos tmp;
			userRelationShip userShip;
			addChildAccTranslate(tmp, userShip);

			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID,m_sessionUserID))
			{

				Json::Value rootValue;
				rootValue[ERRCODE] = -1;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			tmp.m_sUserID = UUID::getUUid();
			userShip.sUserID = tmp.m_sUserID;
			addManager(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
		
	}

private:

	void addChildAccTranslate(userInfos& tmp, userRelationShip& userShip)
	{

		tmp.m_sUserID		= m_info[usrID].asString();
		tmp.m_nUserType		= UsersType::USER_MANAGER;
		tmp.m_nLevel		= m_info[level].asInt();
		tmp.m_sLoginName	= m_info[loginName].asString();
		tmp.m_sAccountName	= m_info[accountName].asString();
		tmp.m_sPassword		= m_info[passwords].asString();
		tmp.m_nRegisterDate = UtilityFun::getLocalDateInt();
		tmp.m_nRegisterTime = UtilityFun::getLocalTimeInt();
		tmp.m_nFinanceType  = m_info[financeType].asInt();

		userShip.sInstitutionID		= m_info[InstitutionID].asString();
		userShip.sAuthrityModuleID  = m_info[AuthrityModuleID].asString();
		userShip.sFeemoduleID		= m_info[FeeModuleID].isNull() ? m_info[FeeModuleID].asString() : "";

	}

	void addManager(userInfos& tmp, userRelationShip& userShip)
	{
		//����˻�������������
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			//�����û�����  ������
			std::cout << "�û���������" << endl;
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_ACCOUNT_CHINESE, "�˻������ܰ�������", tmp, userShip, m_sessionUserID);
		}
		//�˻��Ƿ��Ѵ���
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			//�����û�����  �˻����Ѵ���
			std::cout << "�û����Ѵ���" << endl;
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_ACCOUNT_ALREADY_EXIST, "�˻����Ѵ���", tmp, userShip, m_sessionUserID);
		}

		//������ݿ�
		if (!CDBOpeartor::instance()->addManager(tmp, userShip))
		{
			//������ݿ�ʧ�ܣ������ͻ���
			std::cout << "��ӹ���Ա���ݿ�ʧ��" << endl;
			return m_pUserManagerSPI->OnAddManagerAccount(ERR_DB_OPERATOR, "�������ݿ�ʧ��", tmp, userShip, m_sessionUserID);
		}
		//��ӻ���
		CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip);

		//���� �����ɹ�
		std::cout << "��ӹ���Ա�ɹ�" << endl;
		m_pUserManagerSPI->OnAddManagerAccount(0, "��ȷ", tmp, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};

