#pragma once
//#include "instance.h"
#include "instance_shared_from_this.h"
#include "UserManagerSPI.h"
#include <map>


class CAuthrityControl : public CommonTools::instance_shared_from_this<CAuthrityControl>
{
public:
	int Init();

	////////////////////// �˻���Ӧ�����Ƿ�Ϸ�//////////////////////
	// �˻�����Ƿ������ӱ���
	bool IsUserIDConnectNormal(const std::string& userID, const std::string& sessionID);
	// �˻������Ƿ������ӱ���
	bool IsLoginNameConnectNormal(const std::string& loginNames, const std::string& sessionID);
	// �����˻��Ƿ���������������
	bool IsAgentIDConnectNormal(const std::string& institutionID, const std::string& sessionID, PUserManagerSPI pSPI);
	// �����˻��Ƿ���������������
	bool IsAgentNameConnectNormal(const std::string& loginNames, const std::string& sessionID);
	// �Ǵ����˻��Ƿ���������������
	bool IsChildAccIDConnectNormal(const std::string& childAccID, const std::string& sessionID, PUserManagerSPI pSPI);
	// ����������ģ��������������
	bool IsAgentFeeIDConnectNormal(const std::string& feeMudoleID, const std::string& sessionID);
	// Ȩ��ģ��������������
	bool IsAuthrityRoleIDConnectNormal(const std::string& rolesID, const std::string& sessionID);
	// Ӷ�������������
	bool IsCommissionApprovalConnectNormal(int serialNumber, const std::string& sessionID);
	// �Ƿ�Ϊ������������
	bool IsSuperConnect(const std::string& sessionID);
	// ��ѡ��Լ��������
	bool IsOptionContractConnectNormal(const std::string& serialNumber, const std::string& sessionID);
	// �Ƿ�Ϊ�����Լ��¼������ķ��Ա�������˻�
	bool IsRiskConnectNormal(const std::string& userID, const std::string& sessionID);

	// �˻�Ȩ���Ƿ����
	bool IsAuthrityExist(const std::string& userID, int cmdCode);

	/*bool IsUserOnline(std::string& userId);*/

private:
	std::map<int, int> m_cmdCodeTofunIDMap;

};
