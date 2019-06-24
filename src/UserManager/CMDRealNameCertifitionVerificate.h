#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include "jsoncpp/json/json.h"
#include "UserManagerAPI.h"

class CRealNameCertifitionVerificate
{
public:

	CRealNameCertifitionVerificate(Json::Value root, std::string sessionUserID, PUserManagerSPI pUserManagerSPI):
		m_info(root),m_sessionUserID(sessionUserID), m_pUserManagerSPI(pUserManagerSPI) {}

	void handle()
	{
		try
		{
			int id					= m_info[ID].asInt();
			int state				= m_info[IsApproval].asInt();
			std::string userID		= m_info[InstitutionID].asString();
			std::string apprReson	= m_info[ApprovalReason].asString();
			std::string apprID		= m_info[ApprovalID].asString();

			//�޸����״̬ ���ݿ�ͻ���
			if (!CDBOpeartor::instance()->updateCertifitionRegState(id, state, apprReson, apprID))
			{
				//�������ݿ� ������
			}
			CCacheUserAllInfo::instance()->updateCertifitionRegState(id, state, apprReson, apprID);

			//�޸��û�����֤״̬
			if (1 == state)
			{
				//���ͨ������Ϊ����֤
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, state))
				{
					//������
				}
				//���»���
				CCacheUserAllInfo::instance()->updateIndentifyState(userID, state);

				//֪ͨ��ҳ����ʵ����֤��Ϣ
				certificationRegRecordInfoPtr tableInfo = std::make_shared<certificationRegisterRecordInfo>();
				CDBOpeartor::instance()->SelectDB(id, tableInfo);
				m_pUserManagerSPI->OnRealNameCertificationSent(0, "��ȷ", tableInfo, m_sessionUserID);

			}
			if (2 == state)
			{
				//���δͨ������Ϊδ��֤
				if (!CDBOpeartor::instance()->updateIndentifyState(userID, 0))
				{
					//������
				}
				CCacheUserAllInfo::instance()->updateIndentifyState(userID, 0);

			}

			//��ȷ��ɣ���Ӧ�����¼�
			m_pUserManagerSPI->OnRealNameCertificationExe(0, "��ȷ", id, state, apprReson, apprID, m_sessionUserID);
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
