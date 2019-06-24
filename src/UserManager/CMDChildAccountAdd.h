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

class CChildAccountAdd
{
public:
	CChildAccountAdd(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
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
				rootValue[ERRCODE] = CHILD_ACCOUNT_ADD_RSP;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				return m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
			}

			//������˻�
			std::string uuid = UUID::getUUid();
			tmp.m_sUserID = uuid;  //��ȡuuid
			userShip.sUserID = uuid;//ͬ��һ��uuid

			addChildaccount(tmp, userShip);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

private:

	void addChildAccTranslate(userInfos& tmp,userRelationShip& userShip)
	{	
		tmp.m_nUserType = m_info[usrType].asInt();
		tmp.m_nLevel = m_info[level].asInt();
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
		//����˻�������������
		if (UtilityFun::isChineseString(tmp.m_sLoginName))
		{
			//�����û�����  ������
			std::cout << "��¼��������" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ACCOUNT_CHINESE, "�˻������ܺ�������", tmp, userShip, m_sessionUserID);
		}

		//�˻��Ƿ��Ѵ���
		if (CCacheUserAllInfo::instance()->IsUserExist(tmp.m_sLoginName))
		{
			//�����û�����  �˻����Ѵ���
			std::cout << "�õ�¼���Ѵ���" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ACCOUNT_ALREADY_EXIST, "�˻����Ѵ���", tmp, userShip, m_sessionUserID);
		}
		

		//�Ƿ�ﵽ������
		int curNum = 0;
		int rlt = CCacheUserAllInfo::instance()->getMaxChildNumber(userShip.sInstitutionID, curNum);
		if (-1 == rlt)
		{
			//�����ڴ˻���
			std::cout << "�˻���������" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "���ݿ����ʧ�ܣ������ڵĻ���", tmp, userShip, m_sessionUserID);
		}
		else if(-2 == rlt)
		{
			//������˻�����
			std::cout << "���˻�������" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_ADDCHILDACC_MAX, "������˻��Ѵ����ֵ", tmp, userShip, m_sessionUserID);
		}

		//������ݿ�
		if (!CDBOpeartor::instance()->addChildAccount(tmp, userShip) ||
			!CCacheUserAllInfo::instance()->addUserAndRelationShipCache(tmp, userShip))
		{
			//������ݿ�ʧ�ܣ������ͻ���
			std::cout << "������ݿ�userʧ��" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "�������ݿ�ʧ��", tmp, userShip, m_sessionUserID);
		}


		//���user_money_info
		userMoneyInfo usrMoney;
		usrMoney.m_sUserID = tmp.m_sUserID;
		if (!CDBOpeartor::instance()->addUserMoneyInfo(usrMoney))
		{
			//������ݿ�user_money_infoʧ�ܣ������ͻ���
			std::cout << "������ݿ�moneyʧ��" << std::endl;
			return m_pUserManagerSPI->OnAddChildAccount(ERR_DB_OPERATOR, "�������ݿ�ʧ��", tmp, userShip, m_sessionUserID);
		}
		CCacheUserAllInfo::instance()->addUserMoneyinfoCache(usrMoney);

		m_pUserManagerSPI->OnAddChildAccount(0, "��ȷ", tmp, userShip, m_sessionUserID);
		
		std::cout << "������˻��ɹ�" << std::endl;
		m_pUserManagerSPI->OnAddChildAccPush(0, "��ȷ", tmp, userShip, m_sessionUserID);
	}

private:
	/*std::map<std::string, std::string>*/
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};