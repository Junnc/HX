#include "CacheUserAllInfo.h"
#include <iostream>
#include "DBOperator.h"
#include <stdlib.h>

bool CCacheUserAllInfo::init()
{
	//1.从用户users_copy表查询用户信息 缓存
	if (!initUserTableCache())
		return false;

	//2.初始化user_identify_info_copy 缓存
	if (!initUserIdentifyTableCache())
		return false;

	//3.初始化certifition_register_record 缓存
	if (!initCertifitionRegRecordTableCache())
		return false;

	//4.初始化user_relation_ship
	if(!initUserRelationShipCache())
		return false;

	//5.初始化user_money_info
	if(!initUserMoneyInfoCache())
		return false;

	//6.初始化institution_mainid_map
	if (!initInstitutionMainidMapCache())
		return false;

	//7.初始化system_set
	if (!initSystemSetCache())
		return false;

	//8.初始化log_record
	if (!initLogRecordCache())
		return false;

	return true;
}

bool CCacheUserAllInfo::initCertifitionRegRecordTableCache()
{
	if (!CDBOpeartor::instance()->queryCertifitionRegRecordAll(m_certifitionCache))
		return false;

	std::cout << "init certifition_register_record table cache success,size:" << m_certifitionCache.size() << endl;
	return true;
}

bool CCacheUserAllInfo::initSystemSetCache()
{
	if (!CDBOpeartor::instance()->querySystemSetAll(m_SysSetCache))
		return false;

	std::cout << "init system_set table cache success,size:" << m_SysSetCache.size() << endl;
	return true;
}
bool CCacheUserAllInfo::initUserTableCache()
{
	//缓存user_copy table
	std::map<std::string, userInfosPtr> userInfoMap;
	if (!CDBOpeartor::instance()->queryAllUser(userInfoMap))
		return false;
	m_userInfoCache = std::forward<std::map<std::string, userInfosPtr>>(userInfoMap);
	std::cout << "init users table cache success,size:" << m_userInfoCache.size() << endl;

	return true;
}

bool CCacheUserAllInfo::initUserIdentifyTableCache()
{
	//缓存 user_identify_info_copy
	std::map<std::string, userIdentifyPtr> userIdentifys;
	if (!CDBOpeartor::instance()->queryUserIdentifyAll(userIdentifys))
		return false;
	m_userIdentifyCache = std::forward<std::map<std::string, userIdentifyPtr>>(userIdentifys);
	std::cout << "init users_identify_info table cache success,size:" << m_userIdentifyCache.size() << endl;

	return true;
}

bool CCacheUserAllInfo::initUserRelationShipCache()
{
	if (!CDBOpeartor::instance()->queryUserRelationShipAll(m_userRelationShipCache))
		return false;

	std::cout << "init user_relation_ship table cache success,size:" << m_userRelationShipCache.size() << endl;
	return true;
}

bool CCacheUserAllInfo::initUserMoneyInfoCache()
{
	if (!CDBOpeartor::instance()->queryUserMoneyInfoAll(m_userMoneyCache))
		return false;

	std::cout << "init user_money_info table cache success,size:" << m_userMoneyCache.size() << endl;
	return true;
}

bool CCacheUserAllInfo::initInstitutionMainidMapCache()
{
	if (!CDBOpeartor::instance()->queryInstitutionMainMapAll(m_institutionMainidMapCache))
		return false;

	std::cout << "init institution_mainid_map table cache success,size:" << m_institutionMainidMapCache.size() << endl;
	return true;
}

bool CCacheUserAllInfo::initLogRecordCache()
{
	if (!CDBOpeartor::instance()->queryLogRecordAll(m_logRecordCache))
		return false;

	std::cout << "init log_records table cache success,size:" << m_logRecordCache.size() << endl;
	return true;
}

bool CCacheUserAllInfo::addUserRelationShipCache(userRelationShip& userShip)
{
	{
		WriteLock locker(m_mtx_users_relationShip);
		m_userRelationShipCache[userShip.sUserID] = std::make_shared<userRelationShip>(userShip);
	}
	return true;
}

bool CCacheUserAllInfo::addUserInfoCache(userInfos& uInfo)
{
	bool bflag = true;

	{
		WriteLock locker(m_mtx_userstable);
		if (m_userInfoCache.find(uInfo.m_sUserID) != m_userInfoCache.end())
			bflag= false;
		else
			m_userInfoCache[uInfo.m_sUserID] = std::make_shared<userInfos>(uInfo);
	}

	return bflag;
}

//查询所有用户   type：1=子账户 2=风控员 3=管理员 4=机构 5=主账户
bool CCacheUserAllInfo::queryAccount(const std::string& institution,UserAndRelationShipMap& usrMap,int type)
{
	bool bRes = false;
	{
		ReadLock locker(m_mtx_users_relationShip);
		auto it = m_userRelationShipCache.begin();
		while (it != m_userRelationShipCache.end())
		{
			if (it->second->sInstitutionID == institution)
			{
				ReadLock lck(m_mtx_userstable);
				auto ite = m_userInfoCache.find(it->first);
				if (ite != m_userInfoCache.end())
				{
					if (ite->second->m_nUserType == type)
					{
						usrMap[ite->second] = it->second;
						bRes = true;
					}
				}
			}
			it++;
		}
	}

	return bRes;
}

bool CCacheUserAllInfo::queryAccount(const std::string& userID, userInfos& usrMap)
{	
	{
		ReadLock locker(m_mtx_userstable);
		auto iter = m_userInfoCache.find(userID);
		if (iter != m_userInfoCache.end())
			usrMap = *iter->second;	
	}
	return false;
}

//nflag  0 = 添加银行卡绑定信息  2 = 添加新用户信息
bool CCacheUserAllInfo::addUserIdentifyCache(userIdentify& uInfo,int nflag)
{
	if (1 == nflag)
	{
		m_userIdentifyCache[uInfo.m_sUserID] = std::make_shared<userIdentify>(uInfo);
	}
	else if (0 == nflag)
	{
		auto iter = m_userIdentifyCache.find(uInfo.m_sUserID);
		if (iter != m_userIdentifyCache.end())
		{
			m_userIdentifyCache[uInfo.m_sUserID]->m_sBankName = uInfo.m_sBankName;
			m_userIdentifyCache[uInfo.m_sUserID]->m_sBankCardNo = uInfo.m_sBankCardNo;
			m_userIdentifyCache[uInfo.m_sUserID]->m_sBranchBank = uInfo.m_sBranchBank;
		}
	}
	
	return true;
}

bool CCacheUserAllInfo::updateIdentifySurName(userIdentify& uInfo)
{
	auto iter = m_userIdentifyCache.find(uInfo.m_sUserID);
	if (iter != m_userIdentifyCache.end())
	{
		iter->second->m_sIDCard = uInfo.m_sIDCard;
		iter->second->m_sSurName = uInfo.m_sSurName;
		iter->second->m_nIsDentify = uInfo.m_nIsDentify;
	}
	return 0;
}
bool CCacheUserAllInfo::addUserIdentifyAuthenticateCache(userIdentify& uInfo)
{
	//实名认证  缓存
	{
		WriteLock locker(m_mtx_users_identify);
		//有该账号记录
		if (m_userIdentifyCache.find(uInfo.m_sUserID) != m_userIdentifyCache.end())
		{
			//记录存在且已认证或待认证
			if (0 != m_userIdentifyCache[uInfo.m_sUserID]->m_nIsDentify)
				return false;
			else
			{
				//记录存在，但未认证，改认证状态为待认证
				m_userIdentifyCache[uInfo.m_sUserID]->m_sIDCard = uInfo.m_sIDCard;
				m_userIdentifyCache[uInfo.m_sUserID]->m_sSurName = uInfo.m_sSurName;
				m_userIdentifyCache[uInfo.m_sUserID]->m_nIsDentify = 2;
				return true;
			}
		}

		//没有该账号信息
		m_userIdentifyCache[uInfo.m_sUserID] = std::make_shared<userIdentify>(uInfo);
	}

	return true;
}

bool CCacheUserAllInfo::addCertifitionRegRecordTableCache(certificationRegisterRecordInfo& cer)
{
	 WriteLock locker(m_mtx_users_certifition);
	cer.m_id = m_certifitionCache.end()->first + 1;
	m_certifitionCache[cer.m_id] = std::make_shared<certificationRegisterRecordInfo>(cer);

	return true;
}

bool CCacheUserAllInfo::updateCertifitionRegState(int id, int state, std::string apprReson, std::string apprID)
{
	WriteLock locker(m_mtx_users_certifition);
	if (m_certifitionCache.find(id) == m_certifitionCache.end())
		return false;
	m_certifitionCache[id]->m_nIsApproval = state;
	m_certifitionCache[id]->m_sApprovalID = apprID;
	m_certifitionCache[id]->m_sApprovalReason = apprReson;

	return true;
}

bool CCacheUserAllInfo::updateIndentifyState(std::string userID, int state)
{
	WriteLock locker(m_mtx_users_identify);
	m_userIdentifyCache[userID]->m_nIsDentify = state;
	return true;
}

bool CCacheUserAllInfo::selectIdentifyInfo(std::string userID, userIdentify& uInfo)
{
	ReadLock lck(m_mtx_users_identify);
	auto iter = m_userIdentifyCache.find(userID);
	if (iter != m_userIdentifyCache.end())
	{
		uInfo = *iter->second;
		return true;
	}
	return false;
}

bool CCacheUserAllInfo::IsUserExist(std::string sloginName)
{
	ReadLock locker(m_mtx_userstable);
	auto iter = m_userInfoCache.begin();
	while (iter != m_userInfoCache.end())
	{
		if (iter->second->m_sLoginName == sloginName)
			return true;
		iter++;
	}

	return false;
}

int CCacheUserAllInfo::getMaxChildNumber(std::string& sInstitution,int& nCurNum )
{
	int subNum = 0;
	nCurNum = 0;
	{
		ReadLock locker(m_mtx_userstable);
		auto iter = m_userInfoCache.find(sInstitution);
		if (iter == m_userInfoCache.end())
			return -1;   //机构不存在
		subNum = iter->second->m_nSumIDNum;
	}
	
	{
		ReadLock locker(m_mtx_users_relationShip);
		auto it = m_userRelationShipCache.begin();
		while (it != m_userRelationShipCache.end())
		{
			if (it->second->sInstitutionID == sInstitution)
			{
				ReadLock lck(m_mtx_userstable);
				auto ite = m_userInfoCache.find(it->first);
				if (ite != m_userInfoCache.end())
				{
					if (ite->second->m_nUserType == UsersType::USER_TRADER)
						nCurNum++;
				}
			}
			it++;
		}
	}
	

	if (nCurNum >= subNum)
		return -2;  //达到最大个数

	return 0;
}

bool CCacheUserAllInfo::addUserAndRelationShipCache(userInfos& tmp, userRelationShip& userShip)
{
	bool rlt = true;
	if (!addUserInfoCache(tmp))
		rlt = false;

	std::string accName = m_userInfoCache[userShip.sInstitutionID]->m_sAccountName;
	userShip.sInstitutionName = accName;

	if (!addUserRelationShipCache(userShip))
		rlt = false;

	return rlt;
	
}

bool CCacheUserAllInfo::addUserMoneyinfoCache(userMoneyInfo& usrMoney)
{
	if (!usrMoney.m_sUserID.empty())
	{
		WriteLock locker(m_mtx_users_money);
		m_userMoneyCache[usrMoney.m_sUserID] = std::make_shared<userMoneyInfo>(usrMoney);
		//重新计算动态权益等相关资金  待实现

		return true;
	}
	return false;
}

bool CCacheUserAllInfo::selectUsersOne(std::string sUserid, userInfos& usr)
{
	if (sUserid.empty())
		return false;
	ReadLock locker(m_mtx_userstable);
	if (m_userInfoCache.find(sUserid) == m_userInfoCache.end())
		return false;
	usr = *m_userInfoCache[sUserid];
	return !usr.m_sUserID.empty();
}


bool CCacheUserAllInfo::selectUsersOne(std::string sUserid, userRelationShip& usrShip)
{
	ReadLock locker(m_mtx_users_relationShip);
	if (m_userRelationShipCache.find(sUserid) == m_userRelationShipCache.end())
		return false;
	usrShip = *m_userRelationShipCache[sUserid];

	return !usrShip.sUserID.empty();
}

bool CCacheUserAllInfo::updateUsersAndRelationShip(userInfos& usr, userRelationShip& usrShip)
{
	std::string accName;
	{
		WriteLock locker(m_mtx_userstable);
		if (m_userInfoCache.find(usr.m_sUserID) == m_userInfoCache.end())
			return false;
		m_userInfoCache[usr.m_sUserID]->m_sPassword = usr.m_sPassword;
		m_userInfoCache[usr.m_sUserID]->m_sAccountName = usr.m_sAccountName;
		m_userInfoCache[usr.m_sUserID]->m_sPhone = usr.m_sPhone;

		accName = m_userInfoCache[usrShip.sInstitutionID]->m_sAccountName;
	}
		
	{
		WriteLock lck(m_mtx_users_relationShip);
		if (m_userRelationShipCache.find(usrShip.sUserID) == m_userRelationShipCache.end())
			return false;
		m_userRelationShipCache[usrShip.sUserID]->sMainID = usrShip.sMainID;
		m_userRelationShipCache[usrShip.sUserID]->sFeemoduleID = usrShip.sFeemoduleID;
		m_userRelationShipCache[usrShip.sUserID]->sRiskModuleID = usrShip.sRiskModuleID;
		m_userRelationShipCache[usrShip.sUserID]->sMarginModuleID = usrShip.sMarginModuleID;
		m_userRelationShipCache[usrShip.sUserID]->sInstitutionID = usrShip.sInstitutionID;

		m_userRelationShipCache[usrShip.sUserID]->sInstitutionName = accName;
	}

	return true;
}

bool CCacheUserAllInfo::deleteUserAllinfo(std::string userId)
{
	{
		WriteLock lck(m_mtx_userstable);
		m_userInfoCache.erase(userId);
	}
	{
		WriteLock lck(m_mtx_users_relationShip);
		m_userRelationShipCache.erase(userId);
	}
	{
		WriteLock lck(m_mtx_users_money);
		m_userMoneyCache.erase(userId);
	}

	return true;
}

bool CCacheUserAllInfo::selectMainBindChildAccount(const std::string& mainId, UserAndRelationShipMap& usrMap)
{
	{
		ReadLock locker(m_mtx_users_relationShip);
		auto it = m_userRelationShipCache.begin();
		while (it != m_userRelationShipCache.end())
		{
			if (it->second->sMainID == mainId)
			{
				ReadLock lck(m_mtx_userstable);
				auto ite = m_userInfoCache.find(it->first);
				if (ite != m_userInfoCache.end() && ite->second->m_nUserType == UsersType::USER_TRADER)
				{
					usrMap[ite->second] = it->second;
				}
			}
			it++;
		}
	}
	return usrMap.empty()? false:true;
}

bool CCacheUserAllInfo::selectMainBindChildAccount(const std::string& institutionID, const std::string& mainId, UserAndRelationShipMap& usrMap)
{
	{
		ReadLock locker(m_mtx_users_relationShip);
		auto it = m_userRelationShipCache.begin();
		while (it != m_userRelationShipCache.end())
		{
			if (it->second->sMainID == mainId && it->second->sInstitutionID == institutionID)
			{
				ReadLock lck(m_mtx_userstable);
				auto ite = m_userInfoCache.find(it->first);
				if (ite != m_userInfoCache.end() && ite->second->m_nUserType == UsersType::USER_TRADER)
				{
					usrMap[ite->second] = it->second;
				}
			}
			it++;
		}
	}
	return usrMap.empty() ? false : true;
}

bool CCacheUserAllInfo::deleteMainAccAllinfoOrManager(std::string userId)
{
	{
		WriteLock lck(m_mtx_userstable);
		m_userInfoCache.erase(userId);
	}
	{
		WriteLock lck(m_mtx_users_relationShip);
		m_userRelationShipCache.erase(userId);
	}
	
	return true;
}

bool CCacheUserAllInfo::deleteInstitutionMainidMap(const std::string& mainId, const std::string& institutionID)
{
	{
		WriteLock lck(m_mtx_institution_mainid);
		auto iter = m_institutionMainidMapCache.begin();
		while (iter != m_institutionMainidMapCache.end())
		{
			if (iter->second->m_mainID == mainId && iter->second->m_institutionID == institutionID)
			{
				m_institutionMainidMapCache.erase(iter->first);
				return true;
			}
			iter++;
		}
		
	}

	return false;
}

bool CCacheUserAllInfo::selectSystemSet(const std::string& sKey, SystemSet& setinfo)
{
	{
		ReadLock lck(m_mtx_systemSet);
		auto iter = m_SysSetCache.find(sKey);
		if (iter != m_SysSetCache.end())
			setinfo = *iter->second;
		else
			return false;
	}
	return true;
}

bool CCacheUserAllInfo::updateMainAccount(userInfos& uInfo)
{
	WriteLock lck(m_mtx_userstable);
	if (m_userInfoCache.find(uInfo.m_sUserID) == m_userInfoCache.end())
		return false;
	m_userInfoCache[uInfo.m_sUserID]->m_sLoginName	 = uInfo.m_sLoginName;
	m_userInfoCache[uInfo.m_sUserID]->m_sPassword	 = uInfo.m_sPassword;
	m_userInfoCache[uInfo.m_sUserID]->m_sAccountName = uInfo.m_sAccountName;
	m_userInfoCache[uInfo.m_sUserID]->m_nCounterType = uInfo.m_nCounterType;
	return true;
}

bool CCacheUserAllInfo::updateManagerInfo(userInfos& usr, userRelationShip& usrShip)
{
	std::string accName;
	{
		WriteLock locker(m_mtx_userstable);
		if (m_userInfoCache.find(usr.m_sUserID) == m_userInfoCache.end())
			return false;
		m_userInfoCache[usr.m_sUserID]->m_sPassword = usr.m_sPassword;
		m_userInfoCache[usr.m_sUserID]->m_sAccountName = usr.m_sAccountName;

		accName = m_userInfoCache[usrShip.sInstitutionID]->m_sAccountName;
	}

	{
		WriteLock lck(m_mtx_users_relationShip);
		if (m_userRelationShipCache.find(usrShip.sUserID) == m_userRelationShipCache.end())
			return false;
		m_userRelationShipCache[usrShip.sUserID]->sAuthrityModuleID = usrShip.sAuthrityModuleID;
		m_userRelationShipCache[usrShip.sUserID]->sInstitutionName = accName;
	}

	return true;
}

bool CCacheUserAllInfo::selectAccLevel(const std::string& userid,int& nLevel)
{
	{
		ReadLock lck(m_mtx_userstable);
		auto iter = m_userInfoCache.find(userid);
		if (iter != m_userInfoCache.end())
			nLevel = iter->second->m_nLevel;
		else
			return false;
	}

	return true;
}

bool CCacheUserAllInfo::IsPopuLinkExist(const std::string& linkNo)
{
	if (linkNo.empty())
		return false;
	{
		ReadLock lck(m_mtx_userstable);
		auto iter = m_userInfoCache.begin();
		while (iter != m_userInfoCache.end())
		{
			if (iter->second->m_sPoularizeLink == linkNo)
				return true;
			iter++;
		}

	}
	return false;
}

/*
bool CCacheUserAllInfo::updateManagerInfo(userInfos& usr, userRelationShip& usrShip)
{
	std::string accName;
	{
		WriteLock locker(m_mtx_userstable);
		m_userInfoCache[usr.m_sUserID]->m_sPassword = usr.m_sPassword;
		m_userInfoCache[usr.m_sUserID]->m_sAccountName = usr.m_sAccountName;

		accName = m_userInfoCache[usrShip.sInstitutionID]->m_sAccountName;
	}

	{
		WriteLock lck(m_mtx_users_relationShip);
		m_userRelationShipCache[usrShip.sUserID]->sAuthrityModuleID = usrShip.sAuthrityModuleID;

		m_userRelationShipCache[usrShip.sUserID]->sInstitutionName = accName;
	}

	return true;
}
*/


bool CCacheUserAllInfo::updateChildAgent(userInfos& usr, userRelationShip& usrShip)
{
	{
		WriteLock locker(m_mtx_userstable);
		if (m_userInfoCache.find(usr.m_sUserID) == m_userInfoCache.end())
			return false;
		m_userInfoCache[usr.m_sUserID]->m_sPassword		= usr.m_sPassword;
		m_userInfoCache[usr.m_sUserID]->m_sAccountName  = usr.m_sAccountName;
		m_userInfoCache[usr.m_sUserID]->m_sPhone		= usr.m_sPhone;
		m_userInfoCache[usr.m_sUserID]->m_nMainIDNum	= usr.m_nMainIDNum;
		m_userInfoCache[usr.m_sUserID]->m_nSumIDNum		= usr.m_nSumIDNum;

	}

	{
		WriteLock lck(m_mtx_users_relationShip);
		if (m_userRelationShipCache.find(usrShip.sUserID) == m_userRelationShipCache.end())
			return false;
		m_userRelationShipCache[usrShip.sUserID]->sFeemoduleID			= usrShip.sFeemoduleID;
		m_userRelationShipCache[usrShip.sUserID]->sAuthrityModuleID		= usrShip.sAuthrityModuleID;
		m_userRelationShipCache[usrShip.sUserID]->sRiskModuleAuthrityID = usrShip.sRiskModuleAuthrityID;
	}

	return true;
}

bool CCacheUserAllInfo::deleteChildAgent(const std::string& userId)
{
	{
		//删除user表
		WriteLock lck(m_mtx_userstable);
		if(m_userInfoCache.find(userId) != m_userInfoCache.end())
			m_userInfoCache.erase(userId);
	}
	{
		//删除user_relation_ship表
		WriteLock lck(m_mtx_users_relationShip);
		if (m_userRelationShipCache.find(userId) != m_userRelationShipCache.end())
			m_userRelationShipCache.erase(userId);
	}
	{
		//删除佣金信息表

	}

	return true;
}

bool CCacheUserAllInfo::addLogRecordCache(LogRecords& logInfo)
{
	{
		WriteLock locker(m_mtx_logRecord);
		m_logRecordCache[logInfo.m_logID] = std::make_shared<LogRecords>(logInfo);
		
	}

	return true;
}
bool CCacheUserAllInfo::selestAssignMainAccount(std::string sUsrid ,std::vector<InstitutionMainidMap>& mainidVec)
{
	ReadLock lock(m_mtx_institution_mainid);
	auto iter = m_institutionMainidMapCache.find(sUsrid);
	if (iter != m_institutionMainidMapCache.end())
		mainidVec.push_back(*iter->second);
	else
		return false;
	return true;
}

bool CCacheUserAllInfo::IsBelongAgent(const std::string& institutionID, const std::string& childAgentID)
{
	if (institutionID.empty() || childAgentID.empty())
		return false;

	std::string tmpChildAgentID = childAgentID;

	{
		// 此链接是否为super
		std::unique_lock<std::mutex> lck(m_mtx_userstable);
		auto iterIns = m_userInfoCache.find(institutionID);
		if (iterIns == m_userInfoCache.end())
			return false;
		if (iterIns->second->m_nLevel == LevelType::LType_Institution && iterIns->second->m_nUserType == UsersType::USER_INSTITUTION)
			return true;
	}
	

	for (;;)
	{
		// 此代理或者管理员是否存在
		std::unique_lock<std::mutex> lck(m_mtx_userstable);
		auto iterChild = m_userInfoCache.find(tmpChildAgentID);
		if (iterChild == m_userInfoCache.end())
			return false;
		
		// 次连接是上级代理或者代理本身
		std::unique_lock<std::mutex> lcks(m_mtx_users_relationShip);
		if (m_userRelationShipCache[tmpChildAgentID]->sInstitutionID == institutionID || childAgentID == institutionID)
			return true;

		// 判断是否是super代理
		if (m_userInfoCache[tmpChildAgentID]->m_nLevel == LevelType::LType_Institution
			&& m_userInfoCache[tmpChildAgentID]->m_nUserType == UsersType::USER_INSTITUTION)
			return false;

		// 赋值到上一级代理继续查找
		tmpChildAgentID = m_userRelationShipCache[tmpChildAgentID]->sInstitutionID;
	}

	return true;
}