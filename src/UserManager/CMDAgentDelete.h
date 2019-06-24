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
#include "GlobalParamLogRecord.h"

class CAgentDelete
{
public:
	CAgentDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::string sUsrID  = m_info[usrID].asString();
			int recourse		= m_info[RESOURCE].asInt();

			//�ж��Ƿ�����
			if (CAuthrityControl::instance()->IsUserOnline(sUsrID))
			{
				Json::Value contentValue;
				contentValue[usrID] = sUsrID;

				Json::Value rootValue;
				rootValue[CMD] = LOWER_AGENT_DELETE_RSP;
				rootValue[ERRCODE] = ERR_ACC_ONLINE;
				rootValue[ERRMSG] = "�˻�����";
				rootValue[CONTENT] = contentValue;

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);

				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);

				return;
			}
			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsAgentIDConnectNormal(sUsrID,m_sessionUserID))
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

			deleteAgent(sUsrID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

private:
	void deleteAgent(std::string sUsrID)
	{
		userRelationShip usrShip;

		// �������´������˺ţ��޷�ɾ��
		UserAndRelationShipMap usermap;
		if (CCacheUserAllInfo::instance()->queryAccount(sUsrID, usermap, UsersType::USER_TRADER))
		{
			//���� �����˻�����
			return m_pUserManagerSPI->OnDelChildAgent(ERR_CHILDAACC_EXIST, "�������˻�", sUsrID, "", m_sessionUserID);
		}  

		// �����̴����¼������޷�ɾ��
		if (CCacheUserAllInfo::instance()->queryAccount(sUsrID, usermap, UsersType::USER_INSTITUTION))
		{
			//���� ����һ�������̴���
			return m_pUserManagerSPI->OnDelChildAgent(ERR_CHILDAGENT_EXIST, "�����¼�����", sUsrID, "", m_sessionUserID);
		}

		if (!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrShip))
		{
			std::cout << "�˻��ѱ�ɾ��" << endl;
			//�����˻��ѱ�ɾ��
			return m_pUserManagerSPI->OnDelChildAgent(ERR_USER_NOEXIST, "�˻��ѱ�ɾ��", sUsrID, "", m_sessionUserID);
		}

		//��¼���ݿ���־  ɾ����Ϣ
		GlobalParamsLogRecord::instance()->AccountManagerLogRecord("�¼�����ɾ��", 
			GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_AGENT), nullptr, nullptr, UsersType::USER_INSTITUTION, sUsrID);

		//ɾ�����ݿ�
		int nRes = 0;
		if (!CDBOpeartor::instance()->deleteChildAgent(sUsrID) ||
			!CCacheUserAllInfo::instance()->deleteChildAgent(sUsrID))
		{
			std::cout << "ɾ�����ݿ������ʧ��" << endl;
			nRes = -1;
		}

		//���������ɹ�  ��ʵ��
		std::cout << "ɾ���������˺ųɹ�" << endl;
		m_pUserManagerSPI->OnDelChildAgent(nRes, "��ȷ", sUsrID, usrShip.sInstitutionID, m_sessionUserID);
	}
private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};

