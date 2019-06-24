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

			//���ͨ���Ƿ�Ϸ�  ��ʵ��
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

			//������˻�
			std::string uuid = UUID::getUUid();
			tmp.m_sUserID = uuid;  //��ȡuuid
			userShip.sUserID = uuid;//ͬ��һ��uuid

			//���ͨ���Ƿ�Ϸ�
			if (0/*���ͨ��*/)
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
		//����˻�������������
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			//�����û�����  ������
			std::cout << "�û���������" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ACCOUNT_CHINESE, "�˻������ܰ�������", tmp, userShip,m_sessionUserID);
		}

		//�˻��Ƿ��Ѵ���
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			//�����û�����  �˻����Ѵ���
			std::cout << "�û����Ѵ���" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ACCOUNT_ALREADY_EXIST, "�˻����Ѵ���", tmp, userShip, m_sessionUserID);
		}


		//�Ƿ�ﵽ������
		int curNum = 0;
		int rlt = CCacheUserAllInfo::instance()->getMaxChildNumber(userShip.sInstitutionID, curNum);
		if (-1 == rlt)
		{
			//�����ڴ˻���
			std::cout << "�˻���������" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_DB_OPERATOR, "���ݿ����ʧ�ܣ������ڵĻ���", tmp, userShip, m_sessionUserID);
		}
		else if (-2 == rlt)
		{
			//������˻�����
			std::cout << "���˺��������" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_ADDCHILDACC_MAX, "������˻��Ѵ����ֵ", tmp, userShip, m_sessionUserID);
		}

		//������ݿ�
		if (!CDBOpeartor::instance()->addChildAccount(tmp, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip))
		{
			//������ݿ�ʧ�ܣ������ͻ���
			std::cout << "������˻����ݿ�ʧ��" << endl;
			return m_pUserManagerSPI->OnAddMainAccount(ERR_DB_OPERATOR, "���ݿ����ʧ��", tmp, userShip, m_sessionUserID);
		}
		m_pUserManagerSPI->OnAddMainAccount(0, "��ȷ", tmp, userShip, m_sessionUserID);

		//֪ͨ��¼����ӳɹ� ��ʵ��
		std::cout << "������˺ųɹ�" << endl;
		m_pUserManagerSPI->OnAddMainAccPush(0, "��ȷ", tmp, userShip, m_sessionUserID);
	}

private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
