#include "SessionManager.h"
#include "common/utils/utility_fun.h"
#include "common/CommonEnum.h"
//#include "DBBussUser.h"
//#include "DBBussSystemSet.h"

void CSessionManager::AddSession(SessionPtr pSession)
{
	writeLock lock(m_mutex);
	m_allSessions[pSession->SessionID()] = pSession;
}

void CSessionManager::AddInsAndMCSession(SessionPtr pSession)
{
	writeLock lock(m_mutex);
	m_insSessions[pSession->SessionID()] = pSession;
}

void CSessionManager::DelInsAndMCSession(const std::string& sessionID)
{
	writeLock lock(m_mutex);
	m_insSessions.erase(sessionID);
}

void CSessionManager::AddPCSession(SessionPtr pSession)
{
	writeLock lock(m_mutex);
	m_tradePcSessions[pSession->SessionID()] = pSession;
}

void CSessionManager::DelPCSession(const std::string& sessionID)
{
	writeLock lock(m_mutex);
	m_tradePcSessions.erase(sessionID);
}

void CSessionManager::AddRiskSession(SessionPtr pSession)
{
	writeLock lock(m_mutex);
	m_riskSessions[pSession->SessionID()] = pSession;
}

void CSessionManager::DelRiskSession(const std::string& sessionID)
{
	writeLock lock(m_mutex);
	m_riskSessions.erase(sessionID);
}

void CSessionManager::AddAppSession(SessionPtr pSession)
{
	writeLock lock(m_mutex);
	m_tradeAppSessions[pSession->SessionID()] = pSession;
}

void CSessionManager::DelAppSession(const std::string& sessionID)
{
	writeLock lock(m_mutex);
	m_tradeAppSessions.erase(sessionID);
}

void CSessionManager::SetIsOnline(const std::string& sessionID, bool isOnline)
{
	m_insSessions[sessionID]->SetIsOnline(isOnline);
}

SessionPtr CSessionManager::GetSession(const std::string& sessionID)
{
	readLock lock(m_mutex);
	auto iter = m_allSessions.find(sessionID);
	if (iter == m_allSessions.end())
		return nullptr;
	return m_allSessions[sessionID];
}

SessionPtr CSessionManager::GetLoginSession(const std::string& sessionID)
{
	readLock lock(m_mutex);
	for (auto iter : m_insSessions)
	{
		if (iter.first == sessionID)
			return iter.second;
	}
	for (auto iter : m_tradeAppSessions)
	{
		if (iter.first == sessionID)
			return iter.second;
	}
	for (auto iter : m_tradePcSessions)
	{
		if (iter.first == sessionID)
			return iter.second;
	}
	for (auto iter : m_riskSessions)
	{
		if (iter.first == sessionID)
			return iter.second;
	}
	return 0;
}

void CSessionManager::DelSession(const std::string& sessionID)
{
	writeLock lock(m_mutex);
	m_allSessions[sessionID] = NULL;
	m_allSessions.erase(sessionID);
}

void CSessionManager::Clear()
{
	writeLock lock(m_mutex);
	m_allSessions.clear();
	m_insSessions.clear();
	m_riskSessions.clear();
	m_tradeAppSessions.clear();
	m_tradePcSessions.clear();
}

std::vector<std::string> CSessionManager::GetSessionID(const std::string& userID)
{
	readLock lock(m_mutex);
	std::vector<std::string> sessions;
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second && userID == iter.second->GetUserID())
		{
			sessions.emplace_back(iter.second->SessionID());
		}
	}
	return sessions;
}

std::string CSessionManager::GetUseIDBySessionID(const std::string& sessionID)
{
	readLock lock(m_mutex);
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second &&iter.second->SessionID() == sessionID)
			return iter.second->GetUserID();
	}
	return "";
}



std::string CSessionManager::GetIpIDBySessionID(const std::string& sessionID)
{
	readLock lock(m_mutex);
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second &&iter.second->SessionID() == sessionID)
			return iter.second->GetIp();
	}
	return "";
}

std::string CSessionManager::GetMacIDBySessionID(const std::string& sessionID)
{
	readLock lock(m_mutex);
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second &&iter.second->SessionID() == sessionID)
			return iter.second->GetMac();
	}
	return "";
}

std::vector<std::string> CSessionManager::GetAllOnlineSession()
{
	readLock lock(m_mutex);
	std::vector<std::string> sessions;
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;
		sessions.emplace_back(iter.second->SessionID());
	}
	return sessions;
}

OnlineUserInfoPtrVec CSessionManager::GetAllOnlineSessionInfo()
{
	readLock lock(m_mutex);
	OnlineUserInfoPtrVec tableInfos;
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		OnlineUserInfoPtr tableInfo = std::make_shared<OnlineUserInfo>();
		tableInfo->m_userID = iter.second->GetUserID();
		tableInfo->m_accountName = iter.second->GetUserName();
		tableInfo->m_ip = iter.second->GetIp();
		tableInfo->m_loginName = iter.second->GetLoginName();
		UtilityFun::GetDateAndTimeInt(iter.second->GetLoginTime(), tableInfo->m_loginDate, tableInfo->m_loginTime);
		tableInfo->m_registerTime = iter.second->GetRegisterTime();
		tableInfos.emplace_back(tableInfo);
	}
	return tableInfos;
}

int CSessionManager::SendByUserID(const std::string& userID, const std::string& content)
{
	readLock lock(m_mutex);
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (userID == iter.second->GetUserID())
		{
			iter.second->Write(content);
		}
	}
	return 0;
}

int CSessionManager::SendToAllOnline(const std::string& content)
{
	readLock lock(m_mutex);
	for (auto iter : m_allSessions)
	{
		if (iter.second)
			iter.second->Write(content);
	}
	return 0;
}

int CSessionManager::SendToAllLogin(const std::string& content)
{
	readLock lock(m_mutex);
	for (auto iter : m_tradeAppSessions)
	{
		if (iter.second)
			iter.second->Write(content);
	}
	for (auto iter : m_tradePcSessions)
	{
		if (iter.second)
			iter.second->Write(content);
	}
	for (auto iter : m_insSessions)
	{
		if (iter.second)
			iter.second->Write(content);
	}
	for (auto iter : m_riskSessions)
	{
		if (iter.second)
			iter.second->Write(content);
	}
	return 0;
}

OnlineUserInfoPtrVec CSessionManager::GetAllOnlineChildAccSession()
{
	readLock lock(m_mutex);
	OnlineUserInfoPtrVec tableInfos;
	for (auto iter : m_allSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (EAP_Trader == iter.second->GetUserType())
		{
			OnlineUserInfoPtr tableInfo = std::make_shared<OnlineUserInfo>();
			tableInfo->m_userID = iter.second->GetUserID();
			tableInfo->m_accountName = iter.second->GetUserName();
			tableInfo->m_ip = iter.second->GetIp();
			tableInfo->m_loginName = iter.second->GetLoginName();
			UtilityFun::GetDateAndTimeInt(iter.second->GetLoginTime(), tableInfo->m_loginDate, tableInfo->m_loginTime);
			tableInfo->m_registerTime = iter.second->GetRegisterTime();
			tableInfos.emplace_back(tableInfo);
		}
	}
	return tableInfos;
}


int CSessionManager::SendToAllMonitor(const std::string& content)
{
	readLock lock(m_mutex);
	for (auto iter : m_insSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second && EAP_Risker == iter.second->GetUserType())
			iter.second->Write(content);
	}
	return 0;
}

int CSessionManager::SendToAllManagerAndIns(const std::string& content)
{
	readLock lock(m_mutex);
	for (auto iter : m_insSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second && (EAP_Manager == iter.second->GetUserType() || EAP_Agency == iter.second->GetUserType()))
			iter.second->Write(content);
	}
	return 0;
}

/*
 *int CSessionManager::SendToAllRelatedMonitorByIns(const std::string& userID, const std::string& content)
 *{
 *        readLock lock(m_mutex);
 *        std::string parentID = userID;
 *        std::string currnetID = userID;
 *        TableSystemSetPtr sysTemInfo;
 *        int maxLevel = 0;
 *        CDBBussSystemSet::instance()->SelectSystemSet("STITUTION_LEVEL", sysTemInfo);
 *        if (nullptr == sysTemInfo)
 *        {
 *                maxLevel = 3;
 *        }
 *        else
 *        {
 *                maxLevel = atoi(sysTemInfo->m_value.c_str());
 *        }
 *        for (int i = 0; i < maxLevel; ++i)
 *        {
 *                // 通知父节点下的风控员
 *                for (auto iter : m_riskSessions)
 *                {
 *                        if (nullptr == iter.second.get())
 *                                continue;
 *
 *                        if (iter.second->GetParentID() == parentID)
 *                        {
 *                                if (iter.second)
 *                                        iter.second->Write(content);
 *                        }
 *                }
 *
 *                // 是总后台，直接退出
 *                if ("1" == parentID)
 *                        return 0;
 *
 *                TableUsersAndRelationShipPtr userInfo;
 *                CDBBussUser::instance()->SelectUsersAndRelationShip(currnetID, userInfo);
 *                if (nullptr == userInfo)
 *                        continue;
 *                parentID = userInfo->m_institutionID;
 *                currnetID = parentID;
 *        }
 *
 *        return 0;
 *}
 */

/*
 *int CSessionManager::SendToAllRelatedManagerAndInsByIns(const std::string& userID, const std::string& content)
 *{
 *        readLock lock(m_mutex);
 *
 *        std::string parentID = userID;
 *        std::string currnetID = userID;
 *        TableSystemSetPtr sysTemInfo;
 *        int maxLevel = 0;
 *        CDBBussSystemSet::instance()->SelectSystemSet("STITUTION_LEVEL", sysTemInfo);
 *        if (nullptr == sysTemInfo)
 *        {
 *                maxLevel = 3;
 *        }
 *        else
 *        {
 *                maxLevel = atoi(sysTemInfo->m_value.c_str());
 *        }
 *        for (int i = 0; i < maxLevel; ++i)
 *        {
 *                // 通知下属管理员或者父节点机构本身
 *                for (auto iter : m_insSessions)
 *                {
 *                        if (nullptr == iter.second.get())
 *                                continue;
 *
 *                        if ((iter.second->GetParentID() == parentID && iter.second->GetUserType() == EAP_Manager)
 *                                || iter.second->GetUserID() == currnetID)
 *                        {
 *                                if (iter.second)
 *                                        iter.second->Write(content);
 *                        }
 *                }
 *
 *                // 是总后台，直接退出
 *                if ("1" == parentID)
 *                        return 0;
 *
 *                // 获取父节点
 *                TableUsersAndRelationShipPtr userInfo;
 *                CDBBussUser::instance()->SelectUsersAndRelationShip(currnetID, userInfo);
 *                if (nullptr == userInfo)
 *                        continue;
 *                parentID = userInfo->m_institutionID;
 *                currnetID = parentID;
 *        }
 *
 *        return 0;
 *}
 */

/*
 *int CSessionManager::SendToAllRelatedManagerAndInsByManager(const std::string& userID, const std::string& content)
 *{
 *        readLock lock(m_mutex);
 *        std::string parentID;
 *        std::string currnetID = userID;
 *        TableSystemSetPtr sysTemInfo;
 *        int maxLevel = 0;
 *        CDBBussSystemSet::instance()->SelectSystemSet("STITUTION_LEVEL", sysTemInfo);
 *        if (nullptr == sysTemInfo)
 *        {
 *                maxLevel = 3;
 *        }
 *        else
 *        {
 *                maxLevel = atoi(sysTemInfo->m_value.c_str());
 *        }
 *        for (int i = 0; i < maxLevel; ++i)
 *        {
 *                // 获取父节点
 *                TableUsersAndRelationShipPtr userInfo;
 *                CDBBussUser::instance()->SelectUsersAndRelationShip(currnetID, userInfo);
 *                if (nullptr == userInfo)
 *                        continue;
 *                parentID = userInfo->m_institutionID;
 *                currnetID = parentID;
 *
 *                // 通知下属管理员或者父节点机构本身
 *                for (auto iter : m_insSessions)
 *                {
 *                        if (nullptr == iter.second.get())
 *                                continue;
 *
 *                        if ((iter.second->GetParentID() == parentID && iter.second->GetUserType() == EAP_Manager)
 *                                || iter.second->GetUserID() == currnetID)
 *                        {
 *                                if (iter.second)
 *                                        iter.second->Write(content);
 *                        }
 *                }
 *
 *                // 是总后台，直接退出
 *                if ("1" == parentID)
 *                        return 0;
 *        }
 *
 *        return 0;
 *}
 */
/*
 *
 *int CSessionManager::SendToAllRelatedManagerAndInsBySession(const std::string& sessionID, const std::string& content)
 *{
 *        SessionPtr sessionPtr = GetLoginSession(sessionID);
 *        if (nullptr == sessionPtr.get())
 *                return -1;
 *
 *        SendToAllRelatedManagerAndIns(sessionPtr->GetUserID(), content);
 *        return 0;
 *}
 */

/*
 *int CSessionManager::SendToAllRelatedManagerAndIns(const std::string& userID, const std::string& content)
 *{
 *        TableUsersAndRelationShipPtr userInfo;
 *        CDBBussUser::instance()->SelectUsersAndRelationShip(userID, userInfo);
 *        if (nullptr == userInfo)
 *                return -1;
 *
 *        if (EAP_Manager == userInfo->m_userType)
 *                SendToAllRelatedManagerAndInsByManager(userID, content);
 *        if (EAP_Agency == userInfo->m_userType)
 *                SendToAllRelatedManagerAndInsByIns(userID, content);
 *
 *        return 0;
 *}
 */

/*
 *int CSessionManager::SendToAllRelatedMonitorByAcc(const std::string& userID, const std::string& content)
 *{
 *        readLock lock(m_mutex);
 *        std::string parentID;
 *        std::string currnetID = userID;
 *        TableSystemSetPtr sysTemInfo;
 *        int maxLevel = 0;
 *        CDBBussSystemSet::instance()->SelectSystemSet("STITUTION_LEVEL", sysTemInfo);
 *        if (nullptr == sysTemInfo)
 *        {
 *                maxLevel = 3;
 *        }
 *        else
 *        {
 *                maxLevel = atoi(sysTemInfo->m_value.c_str());
 *        }
 *        for (int i = 0; i < maxLevel; ++i)
 *        {
 *                // 查找父节点
 *                TableUsersAndRelationShipPtr userInfo;
 *                CDBBussUser::instance()->SelectUsersAndRelationShip(currnetID, userInfo);
 *                if (nullptr == userInfo)
 *                        continue;
 *                parentID = userInfo->m_institutionID;
 *                currnetID = parentID;
 *
 *                // 通知父节点下的风控员
 *                for (auto iter : m_riskSessions)
 *                {
 *                        if (nullptr == iter.second.get())
 *                                continue;
 *
 *                        if (iter.second->GetParentID() == parentID)
 *                        {
 *                                if (iter.second)
 *                                        iter.second->Write(content);
 *                        }
 *                }
 *
 *                // 是总后台，直接退出
 *                if ("1" == parentID)
 *                        return 0;
 *        }
 *
 *        return 0;
 *}
 */

int CSessionManager::SendToAllMonitorByAcc(const std::string & userID, const std::string & content)
{
	readLock lock(m_mutex);

	// 通知父节点下的风控员
	for (auto iter : m_riskSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second)
			iter.second->Write(content);
	}

	return 0;
}

bool CSessionManager::IsOnline(const std::string& sessionID)
{
	return m_insSessions[sessionID]->IsOnline();
}

bool CSessionManager::IsUserOnline(const std::string& userID, int userType)
{
	switch (userType)
	{
	case EAP_Trader:
	case EAP_Funder:
	{
		for (auto iter : m_tradePcSessions)
		{
			if (nullptr == iter.second.get())
				continue;
			if (iter.second->GetUserID() == userID)
				return true;
		}

		for (auto iter : m_tradeAppSessions)
		{
			if (nullptr == iter.second.get())
				continue;
			if (iter.second->GetUserID() == userID)
				return true;
		}
		break;
	}
	case EAP_Manager:
	case EAP_Agency:
	{
		for (auto iter : m_insSessions)
		{
			if (nullptr == iter.second.get())
				continue;
			if (iter.second->GetUserID() == userID)
				return true;
		}
		break;
	}
	case EAP_Risker:
	{
		for (auto iter : m_riskSessions)
		{
			if (nullptr == iter.second.get())
				continue;
			if (iter.second->GetUserID() == userID)
				return true;
		}
		break;
	}
	default:
		break;
	}

	return false;
}

/*
 *int CSessionManager::SendToAllOnlineChildAcc(const std::string& marginModuleID, const std::string& content)
 *{
 *        TableUsersAndRelationShipPtrVec userInfos;
 *        CDBBussUser::instance()->SelectMarginModuleSubAcc(marginModuleID, userInfos);
 *        for (auto iterUser : userInfos)
 *        {
 *                if (nullptr == iterUser.get())
 *                        continue;
 *
 *                for (auto iterSession : m_tradePcSessions)
 *                {
 *                        if (nullptr == iterSession.second.get())
 *                                continue;
 *
 *                        if (iterUser->m_userID == iterSession.second->GetUserID())
 *                                iterSession.second->Write(content);
 *                }
 *        }
 *
 *        return 0;
 *}
 *
 *int CSessionManager::SendToSameLevelManagerAndIns(const std::string& userID, const std::string& content)
 *{
 *        TableUsersAndRelationShipPtr userInfo;
 *        CDBBussUser::instance()->SelectUsersAndRelationShip(userID, userInfo);
 *        if (nullptr == userInfo)
 *                return -1;
 *
 *        std::string parentID;
 *        if (EAP_Manager == userInfo->m_userType)
 *                parentID = userInfo->m_institutionID;
 *        else if (EAP_Agency == userInfo->m_userType)
 *                parentID = userID;
 *
 *        if (parentID.empty())
 *                return -1;
 *
 *        // 通知父节点下的管理员
 *        for (auto iter : m_insSessions)
 *        {
 *                if (nullptr == iter.second.get())
 *                        continue;
 *
 *                if (iter.second->GetParentID() == parentID || iter.second->GetUserID() == parentID)
 *                {
 *                        if (iter.second)
 *                                iter.second->Write(content);
 *                }
 *        }
 *
 *        return 0;
 *}
 */
/*
 *
 *int CSessionManager::SendToSameLevelManagerAndInsBySession(const std::string& sessionID, const std::string& content)
 *{
 *        SessionPtr sessionPtr = GetLoginSession(sessionID);
 *        if (nullptr == sessionPtr.get())
 *                return -1;
 *
 *        return SendToSameLevelManagerAndIns(sessionPtr->GetUserID(), content);
 *}
 *
 */
int CSessionManager::SendToSuperManagerAndIns(const std::string& content)
{
	for (auto iter : m_insSessions)
	{
		if (nullptr == iter.second.get())
			continue;

		if (iter.second->GetUserLevel() == 1 && (iter.second->GetUserType() == EAP_Manager|| iter.second->GetUserType() == EAP_Agency))
		{
			if (iter.second)
				iter.second->Write(content);
		}
	}

	return 0;
}

bool CSessionManager::IsUserExist(const std::string& sessionID)
{
	readLock lock(m_mutex);
	auto iter = m_allSessions.find(sessionID);
	if (iter != m_allSessions.end())
		return true;
	return false;
}
