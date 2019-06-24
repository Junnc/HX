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
#include "errCodeDef.h"
#include "AuthrityControl.h"

class CManagerDelete
{
public:
	CManagerDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::string sUsrID	= m_info[usrID].asString();
			int recourse		= m_info[RESOURCE].asInt();

			//�ж��Ƿ�����
			if (CAuthrityControl::instance()->IsUserOnline(sUsrID))
			{
				Json::Value contentValue;
				contentValue[usrID] = sUsrID;

				Json::Value rootValue;
				rootValue[CMD] = MANAGER_DELETE_RSP;
				rootValue[ERRCODE] = ERR_ACC_ONLINE;
				rootValue[ERRMSG] = "�˻�����";
				rootValue[CONTENT] = contentValue;

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);
				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;

			}
			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(sUsrID,m_sessionUserID))
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

			deleteManager(sUsrID);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}	
	}

private:
	void deleteManager(std::string sUsrID)
	{
		userRelationShip usrShip;

		if (!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrShip))
		{
			std::cout << "�˻��ѱ�ɾ��" << endl;
			//�����˻��ѱ�ɾ��
			return m_pUserManagerSPI->OnDelManagerAccount(ERR_USER_NOEXIST, "�˻��ѱ�ɾ��", sUsrID, usrShip.sInstitutionID, m_sessionUserID);
		}

		//��¼���ݿ���־  ɾ����Ϣ
		GlobalParamsLogRecord::instance()->AccountManagerLogRecord("����Աɾ��", 
			GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MANAGER_ACC), nullptr, nullptr, UsersType::USER_MANAGER, sUsrID);
		
		//ɾ�����ݿ�
		int nRes = 0;
		if (!CDBOpeartor::instance()->deleteMainAccountOrManager(sUsrID) ||
			!CCacheUserAllInfo::instance()->deleteMainAccAllinfoOrManager(sUsrID))
		{
			std::cout << "ɾ��������Աʧ��" << endl;
			nRes = -1;
		}

		//���������ɹ�  ��ʵ��
		std::cout << "ɾ������Ա�˺ųɹ�" << endl;
		m_pUserManagerSPI->OnDelManagerAccount(nRes, "��ȷ", sUsrID, usrShip.sInstitutionID, m_sessionUserID);
	}
private:
	Json::Value m_info;
	std::string m_sessionUserID;
	PUserManagerSPI m_pUserManagerSPI;
};
