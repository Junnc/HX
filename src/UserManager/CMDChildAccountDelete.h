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


class CChildAccountDelete
{
public:
	CChildAccountDelete(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			std::string sUsrID = m_info[usrID].asString();
			int resource = m_info[RESOURCE].asInt();
			//�жϴ�ɾ�����˻��Ƿ�����
			if (CAuthrityControl::instance()->IsUserOnline(sUsrID))
			{
				Json::Value contentValue;
				contentValue[usrID] = sUsrID;

				Json::Value rootValue;
				rootValue[CMD] = CHILD_ACCOUNT_DELETE_RSP;
				rootValue[ERRCODE] = ERR_ACC_ONLINE;
				rootValue[ERRMSG] = "�˻�����";
				rootValue[CONTENT] = contentValue;
				Json::FastWriter writer;
				std::string content = writer.write(rootValue);

				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//���ͨ���Ƿ�Ϸ�
			if (!CAuthrityControl::instance()->IsChildAccIDConnectNormal(sUsrID, m_sessionUserID))
			{
				Json::Value rootValue;
				rootValue[ERRCODE] = CHILD_ACCOUNT_QUERY_RSP;
				rootValue[ERRMSG] = "���Ϸ���ָ��";
				rootValue[CONTENT] = "";

				Json::FastWriter writer;
				std::string content = writer.write(rootValue);

				m_pUserManagerSPI->OnConnectAhturityLegitimacyInfo(content, m_sessionUserID);
				return;
			}

			//�ж����˻��Ƿ�ֲֻ���δ��Ч������  �޷�ɾ��
			if (0/*�ж϶���*/)
			{
				//����  �������� ����δ��Ч���� ��Ϣ
			}

			userInfos usrInfo;
			userRelationShip usrShip;
			if (!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrInfo) ||
				!CCacheUserAllInfo::instance()->selectUsersOne(sUsrID, usrShip))
				return m_pUserManagerSPI->OnDelChildAccount(ERR_USER_NOEXIST, "�˻��ѱ�ɾ��", sUsrID, "", m_sessionUserID);
		

			GlobalParamsLogRecord::instance()->AccountManagerLogRecord("���˻�ɾ��", GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_CHILD_ACC), nullptr, nullptr,UsersType::USER_TRADER, sUsrID);

			//��ʼɾ��DB
			if (!CDBOpeartor::instance()->deleteChildAccount(sUsrID))
				return m_pUserManagerSPI->OnDelChildAccount(ERR_DB_OPERATOR, "�˻��ѱ�ɾ��", sUsrID, "", m_sessionUserID);
			
			CCacheUserAllInfo::instance()->deleteUserAllinfo(sUsrID);
			m_pUserManagerSPI->OnDelChildAccount(0, "��ȷ", sUsrID, usrShip.sInstitutionID, m_sessionUserID);


			usrInfo.m_nIsLogicDel = 1;
			m_pUserManagerSPI->OnAddChildAccPush(0, "��ȷ", usrInfo, usrShip, m_sessionUserID);

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