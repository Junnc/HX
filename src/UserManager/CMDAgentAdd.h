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

			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(userShip.sInstitutionID, m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_ADD_RSP;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//��Ӵ�����
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
		//����˻�������������
		if (UtilityFun::isChineseString(users.m_sLoginName))
		{
			//�����û�����  ������
			std::cout << "��¼��������" << std::endl;
			return m_pUserManagerSPI->OnAddChildAgent(ERR_ACCOUNT_CHINESE, "�˻������ܰ�������", users, userShip, m_sessionUserID);
		}

		//�˻��Ƿ��Ѵ���
		if (CCacheUserAllInfo::instance()->IsUserExist(users.m_sLoginName))
		{
			//�����û�����  �˻����Ѵ���
			std::cout << "�õ�¼���Ѵ���" << std::endl;
			return m_pUserManagerSPI->OnAddChildAgent(ERR_ACCOUNT_ALREADY_EXIST, "�˻����Ѵ���", users, userShip, m_sessionUserID);
		}

		//�жϸ��ڵ�ĵȼ�
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
			//���� �����������Ѵ����ȼ�
			return m_pUserManagerSPI->OnAddChildAgent(ERR_AGENTADD_MAXLEVEL, "�����������Ѵ����ȼ�", users, userShip, m_sessionUserID);
		}
		//��ȡ�ƹ���
		for (;;)
		{
			users.m_sPoularizeLink = CDigitalVisa::CreatPopularizeLink();//д���������ƹ���
			if (users.m_sPoularizeLink.size() < 4)
				continue;
			if(CCacheUserAllInfo::instance()->IsPopuLinkExist(users.m_sPoularizeLink))
				continue;
			break;
		}

		// ���ڵ�ȼ�+1,��ʾ��һ��
		users.m_nLevel = nLevel + 1;
		if (!CDBOpeartor::instance()->addAgent(users, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(users, userShip))
		{
			//�������ݿ����ʧ��
			return m_pUserManagerSPI->OnAddChildAgent(ERR_DB_OPERATOR, "�������ݿ�ʧ��", users, userShip, m_sessionUserID);
		}

		// �û���Ϣ�����ȡ
		userIdentify identifyInfo;
		identifyInfo.m_sUserID = users.m_sUserID;
		identifyInfo.m_nIsDentify = 0;
		if (!CDBOpeartor::instance()->addUserIdentify(identifyInfo, 1) ||
			!CCacheUserAllInfo::instance()->addUserIdentifyCache(identifyInfo, 1))
		{
			//�������ݿ����ʧ��
			return m_pUserManagerSPI->OnAddChildAgent(ERR_DB_OPERATOR, "�������ݿ�ʧ��", users, userShip, m_sessionUserID);
		}

		// ���һ������Ӷ����Ϣ
		// ���Ӷ����Ϣ���ݿ�ͻ���


		//������Ӵ���ɹ�
		std::cout << "��Ӵ����̳ɹ�" << endl;
		m_pUserManagerSPI->OnAddChildAgent(0, "��ȷ", users, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};

