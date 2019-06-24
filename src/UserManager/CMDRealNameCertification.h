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

class CRealNameCertifition
{
public:
	CRealNameCertifition(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI) :
		m_info(root), m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			certificationRegisterRecordInfo cer;
			cer.m_sUserId = m_info[usrID].asString();
			cer.m_sLoginName = m_info[loginName].asString();
			cer.m_sAccountName = m_info[accountName].asString();
			cer.m_sIDCard = m_info[IDCard].asString();
			cer.m_sSurName = m_info[SurName].asString();
			cer.m_sPostTime = UtilityFun::getDateTimeString();
			cer.m_sApprovalTime = m_info[ApprovalTime].empty() ? "0000-00-00 00:00:00" : m_info[ApprovalTime].asString();

			userIdentify usrIdentify;
			usrIdentify.m_sUserID = cer.m_sUserId;
			usrIdentify.m_sIDCard = cer.m_sIDCard;
			usrIdentify.m_sSurName = cer.m_sSurName;

			certificationRegRecordInfoPtr cerPtr = std::make_shared<certificationRegisterRecordInfo>(cer);
			//�ж��Ƿ�����֤
			userIdentify usInfo;
			if (!CCacheUserAllInfo::instance()->selectIdentifyInfo(cer.m_sUserId, usInfo))
			{
				return m_pUserManagerSPI->OnRealNameCertification(-1, "û����֤��Ϣ", cerPtr, 0, m_sessionUserID);
			}

			if (0 != usInfo.m_nIsDentify)
			{
				return m_pUserManagerSPI->OnRealNameCertification(-1, "����֤��������֤", cerPtr, 0, m_sessionUserID);
			}

			//�����֤��¼
			if (!CDBOpeartor::instance()->addUserIdentifyAuthenticate(cer) ||
				!CCacheUserAllInfo::instance()->updateIdentifySurName(usrIdentify) ||
				!CCacheUserAllInfo::instance()->addCertifitionRegRecordTableCache(cer))
			{
				//�����֤��¼ʧ��  ����
				return m_pUserManagerSPI->OnRealNameCertification(-1, "�޸���֤���Ϊ����֤ʧ��", cerPtr, 0, m_sessionUserID);
			}

			//�����޸ĳɹ�  ��ʵ��
			m_pUserManagerSPI->OnRealNameCertification(0, "��ȷ", cerPtr, 2, m_sessionUserID);
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