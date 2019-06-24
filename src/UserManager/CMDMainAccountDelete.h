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
			//d��ɾ�������˺�Uid
			std::string sUsrID = m_info[usrID].asString();
			std::string institution = m_info[InstitutionID].asString();

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

			int nRes = 0;
			userInfos usrInfo;
			CCacheUserAllInfo::instance()->queryAccount(institution, usrInfo);
			bool iRes = false;
			std::cout << "level=" << usrInfo.m_nLevel << ",type=" << usrInfo.m_nUserType
				<< ",institution=" << institution << endl;
			if (usrInfo.m_nLevel == 1 && usrInfo.m_nUserType == UsersType::USER_INSTITUTION ||
				usrInfo.m_nUserType == UsersType::USER_MANAGER)
			{
				//�Ƿ���ڰ����˻�
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(sUsrID, usrMap))
				{
					//�а󶨵����˺� �޷�ɾ�� ����
					std::cout << "�����˺Ŵ��ڰ󶨵����˺�" << endl;
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "���˻����ڰ󶨵����˻�", sUsrID, "", m_sessionUserID);

				}

				//���˻��Ƿ���ڰ󶨵Ŀ���ģ��
				if (0/*����ģ���ж�*/)
				{
					//���ڿ���ģ��  �޷�ɾ��  ����
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "���˻��Ѱ󶨴�����ģ�壬�޷�ɾ��", institution, sUsrID, m_sessionUserID);
				}

				//���˻�ɾ����־��¼�����ݿ�  ��ʵ��
				GlobalParamsLogRecord::instance()->AccountManagerLogRecord("���˻�ɾ��", 
					GlobalParamsLogRecord::instance()->GetLogInfo(m_pUserManagerSPI, m_sessionUserID, OperatorObjType::OOT_MAIN_ACC), nullptr, nullptr, UsersType::USER_MONEYACC, sUsrID);

				//ɾ�����˻�
				if (!CDBOpeartor::instance()->deleteMainAccountOrManager(sUsrID) ||
					!CCacheUserAllInfo::instance()->deleteMainAccAllinfoOrManager(sUsrID))
				{
					//ɾ�����ݿ�ʧ�� ����
					std::cout << "ɾ�����ݿ����˻�ʧ��" << endl;
					nRes = -1;
				}
			}
			else
			{
				UserAndRelationShipMap usrMap;
				if (CCacheUserAllInfo::instance()->selectMainBindChildAccount(institution, sUsrID, usrMap))
				{
					//�а󶨵����˺� �޷�ɾ�� ����
					std::cout << "�����˺Ŵ��ڰ󶨵����˺�" << endl;
					return m_pUserManagerSPI->OnDelMainAccount(ERR_MAINIDTOCHILDACC_EXIST, "���˻����ڰ󶨵����˻�", sUsrID, "", m_sessionUserID);
				}

				if (!CDBOpeartor::instance()->delAssignMainAccount(sUsrID, institution) ||
					!CCacheUserAllInfo::instance()->deleteInstitutionMainidMap(sUsrID, institution))
				{
					nRes = -1;
				}
			}

			if (0 != iRes)
				return m_pUserManagerSPI->OnDelMainAccount(ERR_DB_OPERATOR, "�������ݿ�ʧ��", sUsrID, "", m_sessionUserID);

			m_pUserManagerSPI->OnDelMainAccount(iRes, "��ȷ", sUsrID, institution, m_sessionUserID);
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