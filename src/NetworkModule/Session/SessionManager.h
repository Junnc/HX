#pragma once
#include <map>
#include <string>

#include "Session.h"
#include "../common/mutex/rwmutex.h"
#include "../common/instance_shared_from_this.h"

typedef struct SessionInfo_
{
	// �˻����
	std::string userID;

	// pc�˵�¼�����
	int pcNum;

	// app�˵�¼�����
	int appNum;

	// iOS�˵�¼�����
	int iosNum;

	SessionInfo_()
		: pcNum(0)
		, appNum(0)
		, iosNum(0)
	{}

}SessionInfo,*PSessionInfo;

typedef std::shared_ptr<SessionInfo> SessionInfoPtr;
// ����ΪusrID
typedef std::map<std::string, SessionInfoPtr> SessionInfoPtrMap;

typedef struct OnlineUserInfo_
{
	// ���˺�
	std::string m_userID;

	// �˻���
	std::string m_accountName;

	// ��¼��
	std::string m_loginName;

	// ע��ʱ��
	std::string m_registerTime;

	// ��¼ʱ��
	int m_loginTime;

	// ��¼����
	int m_loginDate;

	// ��¼ip
	std::string m_ip;

	// ��¼mac
	std::string m_mac;

	OnlineUserInfo_()
		: m_loginTime(0)
		, m_loginDate(0)
	{}

}OnlineUserInfo, *POnlineUserInfo;

typedef std::shared_ptr<OnlineUserInfo> OnlineUserInfoPtr;
// ����ΪusrID
typedef std::vector<OnlineUserInfoPtr> OnlineUserInfoPtrVec;

class CSessionManager : public CommonTools::instance_shared_from_this<CSessionManager>
{
public:
	CSessionManager()=default;
	~CSessionManager()=default;

public:
	// ���
	void AddSession(SessionPtr pSession);

	void AddInsAndMCSession(SessionPtr pSession);

	void DelInsAndMCSession(const std::string& sessionID);

	void AddPCSession(SessionPtr pSession);

	void DelPCSession(const std::string& sessionID);

	void AddRiskSession(SessionPtr pSession);

	void DelRiskSession(const std::string& sessionID);

	void AddAppSession(SessionPtr pSession);

	void DelAppSession(const std::string& sessionID);

	// ɾ��
	void DelSession(const std::string& sessionID);

	// ���
	void Clear();

public:
	// �޸��û��Ƿ�����
	void SetIsOnline(const std::string& sessionID,bool isOnline);

	// �û��Ƿ�����
	bool IsOnline(const std::string& sessionID);

	// �û��Ƿ�����
	bool IsUserOnline(const std::string& userID,int userType);

	// �û��Ƿ����
	bool IsUserExist(const std::string& sessionID);

	// ��ѯ���ӻỰ
	SessionPtr GetSession(const std::string& sessionID);

	// ��ѯ��¼�Ự
	SessionPtr GetLoginSession(const std::string& sessionID);

	std::vector<std::string> GetAllOnlineSession();

	// ��ȡ�����������˻�
	OnlineUserInfoPtrVec GetAllOnlineChildAccSession();

	// ��ȡ���������û�
	OnlineUserInfoPtrVec GetAllOnlineSessionInfo();

	// ����userID�ҵ�sessionID
	std::vector<std::string> GetSessionID(const std::string& userID);

	// ����sessionID�ҵ�userID
	std::string GetUseIDBySessionID(const std::string& sessionID);
	// ����sessionID�ҵ�ip
	std::string GetIpIDBySessionID(const std::string& sessionID);
	// ����sessionID�ҵ�mac
	std::string GetMacIDBySessionID(const std::string& sessionID);
	
public:
	//////////////////////���͸����������û�///////////////////////
	// ���͸����������û�
	int SendToAllOnline(const std::string& content);

	// ���͸����е�¼�û�
	int SendToAllLogin(const std::string& content);

	//////////////////////���͸�ͬһ�˻��Ķ���¼�ڵ�///////////////////////
	// ���͸�ͬһ�˻��Ķ���¼�ڵ�
	int SendByUserID(const std::string& userID, const std::string& content);

	// ���͸��������߼��Ա
	int SendToAllMonitor(const std::string& content);

	// ���͸������������˻�
	int SendToAllOnlineChildAcc(const std::string& marginModuleID,const std::string& content);

	//////////////////////���͸�������ؼ��Ա///////////////////////
	// ���͸�������ؼ��Ա
	int SendToAllRelatedMonitorByIns(const std::string& userID,const std::string& content);

	// ���͸�������ؼ��Ա
	int SendToAllRelatedMonitorByAcc(const std::string& userID, const std::string& content);

	// ���͸����еļ��Ա
	int SendToAllMonitorByAcc(const std::string& userID, const std::string& content);

	//////////////////////���͸����й���Ա�ͻ���///////////////////////
	// ���͸��������߹���Ա�ͻ���
	int SendToAllManagerAndIns(const std::string& content);

	//////////////////////���͸����б����Լ��ϼ�����Ա�ͻ���///////////////////////
	// ���ݻ���id�����͸�����������߹���Ա�ͻ���
	int SendToAllRelatedManagerAndInsByIns(const std::string& userID, const std::string& content);

	// ���ݹ���Աid�����͸�����������߹���Ա�ͻ���
	int SendToAllRelatedManagerAndInsByManager(const std::string& userID, const std::string& content);

	// ���ж�userID���͸�����������߹���Ա�ͻ���
	int SendToAllRelatedManagerAndIns(const std::string& userID, const std::string& content);

	// ���ж�sessionID���͸�����������߹���Ա�ͻ���
	int SendToAllRelatedManagerAndInsBySession(const std::string& sessionID, const std::string& content);

	//////////////////////���͸���������Ա�ͻ���///////////////////////
	// ���ݻ���id�����͸�ͬ���Ĺ���Ա�ͻ���
	int SendToSameLevelManagerAndIns(const std::string& userID, const std::string& content);

	// ���ݻ���id�����͸�ͬ���Ĺ���Ա�ͻ���
	int SendToSameLevelManagerAndInsBySession(const std::string& sessionID, const std::string& content);

	//////////////////////���͸�super�������Ա///////////////////////
	int SendToSuperManagerAndIns(const std::string& content);

private:
	// session����,����ΪsessionID
	// ���лỰ
	std::map<std::string, SessionPtr> m_allSessions;
	// �������߹���Ա�Ự����
	std::map<std::string, SessionPtr> m_insSessions;
	// ���׶�pc�Ự����
	std::map<std::string, SessionPtr> m_tradePcSessions;
	// ���׶�app�Ự����
	std::map<std::string, SessionPtr> m_tradeAppSessions;
	// ���Ա�Ự����
	std::map<std::string, SessionPtr> m_riskSessions;

	// session�����Ϣ
	SessionInfoPtrMap m_SessionInfo;

	// ������
	rwMutex m_mutex;

};

typedef std::shared_ptr<CSessionManager> CSessionManagerPtr;
