#include "UserAccountDeal.h"
#include "CacheUserAllInfo.h"
#include <iostream>
#include "NetCommandCode.h"
#include "TableFeild_define.h"
#include "utility_fun.h"
#include "DBOperator.h"
#include "CMDRealNameCertifitionVerificate.h"
#include "CMDChildAccountAdd.h"
#include "CMDQryChildAccount.h"
#include "CMDChildAccountUpdate.h"
#include "CMDChildAccountDelete.h"
#include "CMDBankCardBind.h"
#include "CMDRealNameCertification.h"
#include "CMDMainAccountAdd.h"
#include "CMDMainAccountQry.h"
#include "CMDMainAccountDelete.h"
#include "CMDMainAccountUpdate.h"
#include "CMDManagerAdd.h"
#include "CMDManagerQuery.h"
#include "CMDManagerUpdate.h"
#include "CMDManagerDelete.h"
#include "CMDAgentAdd.h"
#include "CMDAgentQuery.h"
#include "CMDAgentUpdate.h"
#include "CMDAgentDelete.h"
#include "CMDQryAllChildAgentInRoot.h"
#include "CMDQryAllChildAccountInAgent.h"
#include "CMDQryAllMainAccountInAgent.h"
#include "CMDQryAllManagerInAgent.h"
#include "CMDQryAllNextChildAgentInAgent.h"
//#include "TaskManager.h"



void CCommandParseAndDeal::CommandParse(Json::Value& root, std::string sessionUserID)
{
	std::cout << "enter CommandParse" << endl;
	//����
	int nCmd = root[CMD].asInt();

	switch (nCmd)
	{
	case CHILD_ACCOUNT_ADD_REQ:					//���˻��������
	{
		m_cmdsPool.AddTask([=] {
			CChildAccountAdd cldacc(root, sessionUserID, m_pUserManagerSPI);
			cldacc.handle();
		});
		
		break;
	}
		
	case CHILD_ACCOUNT_DELETE_REQ:				// ���˻�ɾ������ 
	{
		m_cmdsPool.AddTask([=] {
			CChildAccountDelete childDel(root, sessionUserID,m_pUserManagerSPI);
			childDel.handle();
		});
		break;
	}
	case CHILD_ACCOUNT_UPDATE_REQ :				// ���˻���������
	{
		m_cmdsPool.AddTask([=] {
			CChildAccountUpdate childUp(root, sessionUserID,m_pUserManagerSPI);
			childUp.handle();
		});	
		break;
	}
		
	case CHILD_ACCOUNT_QUERY_REQ:				// ���˻���ѯ���� 
	{
		m_cmdsPool.AddTask([=] {
			CQryChildAccount qryChild(root, sessionUserID, m_pUserManagerSPI);
			qryChild.handle();
		});
		
		break;
	}

	case MAIN_ACCOUNT_QUERY_REQ:				// ���˻���ѯ���� 
	{
		m_cmdsPool.AddTask([=] {
			CMainAccountQry mainAccQry(root, sessionUserID,m_pUserManagerSPI);
			mainAccQry.handle();
		});	
		break;
	}

	case MAIN_ACCOUNT_ADD_REQ :					// ���˻��������� 
	{
		m_cmdsPool.AddTask([=] {
			CMainAccountAdd mainAccAdd(root, sessionUserID, m_pUserManagerSPI);
			mainAccAdd.handle();
		});
		
		break;
	}

	case MAIN_ACCOUNT_UPDATE_REQ :					// ���˻��������� 
	{
		std::cout << " 102 " << std::endl;
		m_cmdsPool.AddTask([=] {
			CMainAccountUpdate mainAccUps(root, sessionUserID, m_pUserManagerSPI);
			mainAccUps.handle();
		});
		
		break;
	}
	case MAIN_ACCOUNT_DELETE_REQ :					// ���˻�ɾ������ 
	{
		m_cmdsPool.AddTask([=] {
			CMainAccountDelete mainAccDel(root, sessionUserID, m_pUserManagerSPI);
			mainAccDel.handle();
		});
		break;
	}
	case MANAGER_QUERY_REQ :					    // ����Ա��ѯ���� 
	{
		m_cmdsPool.AddTask([=] {
			CManagerQuery managerQry(root, sessionUserID, m_pUserManagerSPI);
			managerQry.handle();
		});	
		break;
	}
	case MANAGER_ADD_REQ :						    // ����Ա�������� 
	{
		m_cmdsPool.AddTask([=] {
			CManagerAdd managerAdd(root, sessionUserID, m_pUserManagerSPI);
			managerAdd.handle();
		});
		break;
	}
	case MANAGER_UPDATE_REQ :					    // ����Ա�������� 
	{
		m_cmdsPool.AddTask([=] {
			CManagerUpdate managerUpdate(root, sessionUserID, m_pUserManagerSPI);
			managerUpdate.handle();
		});	
		break;
	}
	case MANAGER_DELETE_REQ :                      // ����Աɾ������ 
	{
		m_cmdsPool.AddTask([=] {
			CManagerDelete managerDel(root, sessionUserID, m_pUserManagerSPI);
			managerDel.handle();
		});	
		break;
	}
		
	case LOWER_AGENT_QUERY_REQ:						// �����̲�ѯ���� 
	{
		m_cmdsPool.AddTask([=] {
			CAgentQuery agentQry(root, sessionUserID,m_pUserManagerSPI);
			agentQry.handle();
		});	
		break;
	}
	case LOWER_AGENT_ADD_REQ :						// �������������� 
	{
		m_cmdsPool.AddTask([=] {
			CAgentAdd agentAdd(root, sessionUserID, m_pUserManagerSPI);
			agentAdd.handle();
		});	
		break;
	}
	case LOWER_AGENT_UPDATE_REQ :					// �����̸������� 
	{
		m_cmdsPool.AddTask([=] {
			CAgentUpdate agentUpdate(root, sessionUserID, m_pUserManagerSPI);
			agentUpdate.handle();
		});
		
		break;
	}
	case LOWER_AGENT_DELETE_REQ :					// ������ɾ������
	{
		m_cmdsPool.AddTask([=] {
			CAgentDelete agentDel(root, sessionUserID, m_pUserManagerSPI);
			agentDel.handle();
		});	
		break;
	}
	// ����(�ܺ�̨)�Ĵ����̲�ѯ���� 
	case ALLAGENTBYINSTID_QUERY_REQ:
	{
		m_cmdsPool.AddTask([=] {
			CQryAllChildAgent qryAllChildAgent(root, sessionUserID, m_pUserManagerSPI);
			qryAllChildAgent.handle();
		});
		
		break;
	}

	// ���������������˻���ѯ���� 
	case ALLCHILDBYAGTID_QUERY_REQ:
	{
		m_cmdsPool.AddTask([=] {
			CQryAllChildAccountInAgent qryChildacc(root, sessionUserID, m_pUserManagerSPI);
			qryChildacc.handle();
		});
		break;
	}
	// �������������˻���ѯ���� 
	case ALLMAINACTBYAGTID_QUERY_REQ:
	{
		m_cmdsPool.AddTask([=] {
			CQryAllMainAccountInAgent qryMainacc(root, sessionUserID, m_pUserManagerSPI);
			qryMainacc.handle();
		});
		break;
	}

	// ���������й���Ա��ѯ���� 
	case ALLMANAGERACTBYAGTID_QUERY_REQ:
	{
		m_cmdsPool.AddTask([=] {
			CQryAllManagerAccountInAgent qryManageracc(root, sessionUserID, m_pUserManagerSPI);
			qryManageracc.handle();
		});

		break;
	}
	// ���������з��Ա��ѯ����
	case ALLRISKACTBYAGTID_QUERY_REQ:
	{
		break;
	}
	// ��ѯ�����������¼�����������
	case ALLAGENTBYAGTID_QUERY_REQ:
	{
		m_cmdsPool.AddTask([=] {
			CQryAllNextChildAgentInAgent qryChildAgentInAgent(root, sessionUserID, m_pUserManagerSPI);
			qryChildAgentInAgent.handle();
		});
		break;
	}
	case BANK_CARD_BIND_REQ:                  //���п�������
	{
		m_cmdsPool.AddTask([=] {
			CBankCardBind bankcard(root, sessionUserID, m_pUserManagerSPI);
			bankcard.handle();
		});
		break;
	}
		
	case REAL_NAME_IDENTIFY_REQ:				//ʵ����֤����
	{
		m_cmdsPool.AddTask([=] {
			CRealNameCertifition realname(root, sessionUserID, m_pUserManagerSPI);
			realname.handle();
		});
		
		break;
	}
		
	case CERTIFICATION_APPROVAL_HANDLE_REQ:  //ʵ����֤�������
	{
		m_cmdsPool.AddTask([=] {
			CRealNameCertifitionVerificate realNameCer(root, sessionUserID, m_pUserManagerSPI);
			realNameCer.handle();
		});	
		break;
	}

	case CERTIFICATION_APPROVAL_QRY_REQ:    //ʵ����֤��ѯ����

		break;
	default:
		break;
	}

}


bool CCommandParseAndDeal::init(int nThreadNum)
{
	//m_cmdsPool = std::make_shared<ThreadPool>();
	if (0 == nThreadNum)
		m_cmdsPool.Start();
	else if (0 < nThreadNum)
		m_cmdsPool.Start(nThreadNum);
	else
		return false;

	m_pUserManagerSPI = std::make_shared<CUserManagerSPI>();
	return true;
}

//nflag  1 == ���п���   2==ʵ����֤ 
void CCommandParseAndDeal::addUserIdentifyTranslate(std::map<string, string>& root, userIdentify& usrIdentify,int nflag)
{
	usrIdentify.m_sUserID = root[usrID];	
	if (1 == nflag)
	{
		usrIdentify.m_sBankName = root[BankName];
		usrIdentify.m_sBranchBank = root[BranchBank];
		usrIdentify.m_sBankCardNo = root[BankCardNo];	
		usrIdentify.m_nIsDentify = 0/*std::stoi(root[IsIdentify])*/;
	}

	if (2 == nflag)
	{
		usrIdentify.m_sIDCard = root[IDCard];
		usrIdentify.m_sSurName = root[SurName];
		//usrIdentify.m_nIsDentify = 0;
	}
	
}

void CCommandParseAndDeal::CertifitionRegRecTranslate(std::map<string, string>& root, certificationRegisterRecordInfo& cer)
{
	try
	{
		cer.m_sUserId = root[usrID];
		cer.m_sLoginName = root[loginName];
		cer.m_sAccountName = root[accountName];
		cer.m_sIDCard = root[IDCard];
		cer.m_sSurName = root[SurName];
		cer.m_sPostTime = UtilityFun::getDateTimeString();
		cer.m_sApprovalTime = root[ApprovalTime].empty()? "0000-00-00 00:00:00": root[ApprovalTime];
		//cer.m_sApprovalID = root[ApprovalID];
		//cer.m_nIsApproval = std::stoi(root[IsApproval]);
		//cer.m_sApprovalReason = root[ApprovalReason];
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	
}


void CCommandParseAndDeal::addUserIdentifyAuthenticate(std::string sessionUserID, std::map<string, string>& root)
{
	certificationRegisterRecordInfo cerRegRec;
	CertifitionRegRecTranslate(root, cerRegRec);

	//1. ��ӻ���
	if (!CCacheUserAllInfo::instance()->addCertifitionRegRecordTableCache(cerRegRec))
		return;
	userIdentify usrIdentify;
	usrIdentify.m_sUserID = cerRegRec.m_sUserId;
	usrIdentify.m_sIDCard = cerRegRec.m_sIDCard;
	usrIdentify.m_sSurName = cerRegRec.m_sSurName;
	if (!CCacheUserAllInfo::instance()->addUserIdentifyAuthenticateCache(usrIdentify))
	{
		std::cout << "add cache UserIdentifyAuthenticate fail,the user is Authenticated or Authenticating!" << endl;
		return;
	}

	//2.������ݿ�
	if (!CDBOpeartor::instance()->addUserIdentifyAuthenticate(cerRegRec))
	{
		std::cout << "add DB UserIdentifyAuthenticate fail!" << endl;
		return;
	}
}