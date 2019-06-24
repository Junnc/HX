#pragma once
#include <map>
#include <string>

#include "Session.h"
#include "../common/mutex/rwmutex.h"
#include "../common/instance_shared_from_this.h"

typedef struct SessionInfo_
{
	// 账户编号
	std::string userID;

	// pc端登录点个数
	int pcNum;

	// app端登录点个数
	int appNum;

	// iOS端登录点个数
	int iosNum;

	SessionInfo_()
		: pcNum(0)
		, appNum(0)
		, iosNum(0)
	{}

}SessionInfo,*PSessionInfo;

typedef std::shared_ptr<SessionInfo> SessionInfoPtr;
// 主键为usrID
typedef std::map<std::string, SessionInfoPtr> SessionInfoPtrMap;

typedef struct OnlineUserInfo_
{
	// 子账号
	std::string m_userID;

	// 账户名
	std::string m_accountName;

	// 登录名
	std::string m_loginName;

	// 注册时间
	std::string m_registerTime;

	// 登录时间
	int m_loginTime;

	// 登录日期
	int m_loginDate;

	// 登录ip
	std::string m_ip;

	// 登录mac
	std::string m_mac;

	OnlineUserInfo_()
		: m_loginTime(0)
		, m_loginDate(0)
	{}

}OnlineUserInfo, *POnlineUserInfo;

typedef std::shared_ptr<OnlineUserInfo> OnlineUserInfoPtr;
// 主键为usrID
typedef std::vector<OnlineUserInfoPtr> OnlineUserInfoPtrVec;

class CSessionManager : public CommonTools::instance_shared_from_this<CSessionManager>
{
public:
	CSessionManager()=default;
	~CSessionManager()=default;

public:
	// 添加
	void AddSession(SessionPtr pSession);

	void AddInsAndMCSession(SessionPtr pSession);

	void DelInsAndMCSession(const std::string& sessionID);

	void AddPCSession(SessionPtr pSession);

	void DelPCSession(const std::string& sessionID);

	void AddRiskSession(SessionPtr pSession);

	void DelRiskSession(const std::string& sessionID);

	void AddAppSession(SessionPtr pSession);

	void DelAppSession(const std::string& sessionID);

	// 删除
	void DelSession(const std::string& sessionID);

	// 清空
	void Clear();

public:
	// 修改用户是否在线
	void SetIsOnline(const std::string& sessionID,bool isOnline);

	// 用户是否在线
	bool IsOnline(const std::string& sessionID);

	// 用户是否在线
	bool IsUserOnline(const std::string& userID,int userType);

	// 用户是否存在
	bool IsUserExist(const std::string& sessionID);

	// 查询连接会话
	SessionPtr GetSession(const std::string& sessionID);

	// 查询登录会话
	SessionPtr GetLoginSession(const std::string& sessionID);

	std::vector<std::string> GetAllOnlineSession();

	// 获取所有在线子账户
	OnlineUserInfoPtrVec GetAllOnlineChildAccSession();

	// 获取所有在线用户
	OnlineUserInfoPtrVec GetAllOnlineSessionInfo();

	// 根据userID找到sessionID
	std::vector<std::string> GetSessionID(const std::string& userID);

	// 根据sessionID找到userID
	std::string GetUseIDBySessionID(const std::string& sessionID);
	// 根据sessionID找到ip
	std::string GetIpIDBySessionID(const std::string& sessionID);
	// 根据sessionID找到mac
	std::string GetMacIDBySessionID(const std::string& sessionID);
	
public:
	//////////////////////发送给所有在线用户///////////////////////
	// 发送给所有在线用户
	int SendToAllOnline(const std::string& content);

	// 发送给所有登录用户
	int SendToAllLogin(const std::string& content);

	//////////////////////发送给同一账户的多点登录节点///////////////////////
	// 发送给同一账户的多点登录节点
	int SendByUserID(const std::string& userID, const std::string& content);

	// 发送给所有在线监控员
	int SendToAllMonitor(const std::string& content);

	// 发送给所有在线子账户
	int SendToAllOnlineChildAcc(const std::string& marginModuleID,const std::string& content);

	//////////////////////发送给所有相关监控员///////////////////////
	// 发送给所有相关监控员
	int SendToAllRelatedMonitorByIns(const std::string& userID,const std::string& content);

	// 发送给所有相关监控员
	int SendToAllRelatedMonitorByAcc(const std::string& userID, const std::string& content);

	// 发送给所有的监控员
	int SendToAllMonitorByAcc(const std::string& userID, const std::string& content);

	//////////////////////发送给所有管理员和机构///////////////////////
	// 发送给所有在线管理员和机构
	int SendToAllManagerAndIns(const std::string& content);

	//////////////////////发送给所有本级以及上级管理员和机构///////////////////////
	// 根据机构id，发送给所有相关在线管理员和机构
	int SendToAllRelatedManagerAndInsByIns(const std::string& userID, const std::string& content);

	// 根据管理员id，发送给所有相关在线管理员和机构
	int SendToAllRelatedManagerAndInsByManager(const std::string& userID, const std::string& content);

	// 自判断userID发送给所有相关在线管理员和机构
	int SendToAllRelatedManagerAndIns(const std::string& userID, const std::string& content);

	// 自判断sessionID发送给所有相关在线管理员和机构
	int SendToAllRelatedManagerAndInsBySession(const std::string& sessionID, const std::string& content);

	//////////////////////发送给本级管理员和机构///////////////////////
	// 根据机构id，发送给同级的管理员和机构
	int SendToSameLevelManagerAndIns(const std::string& userID, const std::string& content);

	// 根据机构id，发送给同级的管理员和机构
	int SendToSameLevelManagerAndInsBySession(const std::string& sessionID, const std::string& content);

	//////////////////////发送给super及其管理员///////////////////////
	int SendToSuperManagerAndIns(const std::string& content);

private:
	// session容器,主键为sessionID
	// 所有会话
	std::map<std::string, SessionPtr> m_allSessions;
	// 机构或者管理员会话容器
	std::map<std::string, SessionPtr> m_insSessions;
	// 交易端pc会话容器
	std::map<std::string, SessionPtr> m_tradePcSessions;
	// 交易端app会话容器
	std::map<std::string, SessionPtr> m_tradeAppSessions;
	// 风控员会话容器
	std::map<std::string, SessionPtr> m_riskSessions;

	// session相关信息
	SessionInfoPtrMap m_SessionInfo;

	// 互斥量
	rwMutex m_mutex;

};

typedef std::shared_ptr<CSessionManager> CSessionManagerPtr;
