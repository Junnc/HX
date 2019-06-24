#pragma once
#include <string>
#include <map>
#include "jsoncpp/json/json.h"
#include <memory>
#include "UserTableMsgStruct.h"


class CUserManagerSPI
{
public:
	// ����sessionID�ҵ�userID
	virtual std::string OnGetUseIDBySessionID(const std::string& sessionID) { return ""; }
	// ����sessionID�ҵ�ip
	virtual std::string OnGetIpBySessionID(const std::string& sessionID) { return ""; }
	// ����sessionID�ҵ�mac
	virtual std::string OnGetMacBySessionID(const std::string& sessionID) { return ""; }

	// �������˻� 
	virtual void OnAddChildAccount(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ���˻�����
	virtual void OnAddChildAccPush(int errorCode, const std::string& errmsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ��ѯ���˻�
	virtual void OnQryChildAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// ɾ�����˻�
	virtual void OnDelChildAccount(int errorCode, const std::string& errmsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// �޸����˻� 
	virtual void OnUpdateChildAccount(int errorCode, const std::string& errmsg, const std::string& oldRiskModuleID, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ��ѯ���˻�
	virtual void OnQryMainAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// �������˻�
	virtual void OnAddMainAccount(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ���˻�����
	virtual void OnAddMainAccPush(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// �޸����˻� 
	virtual void OnUpdateMainAccount(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ɾ�����˻� 
	virtual void OnDelMainAccount(int errorCode, const std::string& errMsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// ��ѯ����Ա
	virtual void OnQryManagerAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// ���ӹ���Ա
	virtual void OnAddManagerAccount(int errorCode, const std::string& errmsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// �޸Ĺ���Ա
	virtual void OnUpdateManagerAccount(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ɾ������Ա
	virtual void OnDelManagerAccount(int errorCode, const std::string& errmsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// ��ѯ�¼�����
	virtual void OnQryChildAgent(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// �����¼�����
	virtual void OnAddChildAgent(int errorCode, const std::string& userID, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// �޸��¼�����
	virtual void OnUpdateChildAgent(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// ɾ���¼�����
	virtual void OnDelChildAgent(int errorCode, const std::string& errMsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// �����п�
	virtual void OnBankCardBind(int errorCode, const std::string& errMsg, userIdentifyPtr& userIdentifyInfo, const std::string& sessionID) {}

	// ʵ����֤��Ӧ
	virtual void OnRealNameCertification(int errorCode, const std::string& errMsg, certificationRegRecordInfoPtr tableInfo, int isIdentify, const std::string& sessionID) {}

	// ʵ����֤���ͨ��������Ϣ
	virtual void OnRealNameCertificationSent(int errorCode, const std::string& errMsg, certificationRegRecordInfoPtr& tableInfo, const std::string& sessionID) {}

	// ʵ����ִ֤��
	virtual void OnRealNameCertificationExe(int errorCode, const std::string& errMsg, int id, int state, const std::string& apprReson, const std::string& apprName, const std::string& sessionID) {}

	// ��ѯ���д���
	virtual void OnQryAllChildAgent(int errorCode, const std::string& errMsg, UserAndRelationShipMap& institutionID, const std::string& sessionID) {}

	// ��ѯ���������˻�
	virtual void OnQryAllChildAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// ��ѯ���������˻�
	virtual void OnQryAllMainAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// ��ѯ�����̹���Ա
	virtual void OnQryAllManagerAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// ��ѯ�¼�����
	virtual void OnQryNextAllChildAgent(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	//�����û�Ȩ��
	virtual void OnConnectAhturityLegitimacyInfo(std::string& content, std::string& sessionUserID) { std::cout << content.c_str() << std::endl; }

private:

};

typedef std::shared_ptr<CUserManagerSPI> PUserManagerSPI;
