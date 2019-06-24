#pragma once
#include "UserTableMsgStruct.h"
#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "instance_shared_from_this.h"

class CCacheUserAllInfo:public CommonTools::instance_shared_from_this<CCacheUserAllInfo>
{
public:
	bool init();
	int getMaxChildNumber(std::string& sInstitution, int& nCurNum);

	//添加users  user_relation_ship
	bool addUserAndRelationShipCache(userInfos& tmp, userRelationShip& userShip);
	bool updateUsersAndRelationShip(userInfos& usr, userRelationShip& usrShip);

	//users  user_relation_ship user_money_info
	bool deleteUserAllinfo(std::string userId);

	bool selectMainBindChildAccount(const std::string& mainId, UserAndRelationShipMap& usrMap);
	bool selectMainBindChildAccount(const std::string& institutionID, const std::string& mainId, UserAndRelationShipMap& usrMap);
	bool deleteMainAccAllinfoOrManager(std::string userId);
	
	//user table
	bool initUserTableCache();
	bool addUserInfoCache(/*std::string& userid,*/ userInfos& uInfo);
	//查找机构下的某一身份类型的所有用户
	bool queryAccount(const std::string& institution, UserAndRelationShipMap& usrMap,int type);
	bool queryAccount(const std::string& institution, userInfos& usrMap);
	bool IsUserExist(std::string sloginName);
	bool selectUsersOne(std::string sUserid, userInfos& usr);
	bool updateMainAccount(userInfos& uInfo);
	bool IsPopuLinkExist(const std::string& linkNo);

	//bool queryChildAgent(std::string& userId, std::map<userInfosPtr, userRelationShipPtr>& userMap);
	bool updateManagerInfo(userInfos& usr, userRelationShip& usrShip);
	bool updateChildAgent(userInfos& usr, userRelationShip& usrShip);
	bool deleteChildAgent(const std::string& userId);
	bool selectAccLevel(const std::string& userid, int& nLevel);
	
	//user_identify_info table
	bool initUserIdentifyTableCache();
	bool addUserIdentifyCache(userIdentify& uInfo, int nflag = 0);
	bool updateIdentifySurName(userIdentify& uInfo);
	bool addUserIdentifyAuthenticateCache(userIdentify& uInfo);
	bool updateIndentifyState(std::string userID, int state);
	bool selectIdentifyInfo(std::string userID, userIdentify& uInfo);
	
	
	//certifition_register_record
	bool initCertifitionRegRecordTableCache();
	bool addCertifitionRegRecordTableCache(certificationRegisterRecordInfo& cer);
	bool updateCertifitionRegState(int id, int state, std::string apprReson, std::string apprID);

	//user_relation_ship
	bool initUserRelationShipCache();
	bool addUserRelationShipCache(userRelationShip& userShip);
	bool selectUsersOne(std::string sUserid, userRelationShip& usrShip);

	//user_money_info
	bool initUserMoneyInfoCache();
	bool addUserMoneyinfoCache(userMoneyInfo& usrMoney);

	//institution_mainid_map
	bool initInstitutionMainidMapCache();
	bool deleteInstitutionMainidMap(const std::string& mainId, const std::string& institutionID);
	bool selestAssignMainAccount(std::string sUsrid, std::vector<InstitutionMainidMap>& mainidVec);

	bool IsBelongAgent(const std::string& institutionID, const std::string& childAgentID);
public:
	//system_set
	bool selectSystemSet(const std::string& sKey,SystemSet& setinfo);
	bool initSystemSetCache();

	//log_record
	bool initLogRecordCache();
	bool addLogRecordCache(LogRecords& uInfo);

private:
	//user table
	std::map<std::string, userInfosPtr> m_userInfoCache;
	std::mutex m_mtx_userstable;  //user 表缓存锁
	
	//user_identify_info table
	std::map<std::string, userIdentifyPtr> m_userIdentifyCache;
	std::mutex m_mtx_users_identify;  //user_identify_info 表缓存锁

	//certifition_register_record
	std::map<int, certificationRegRecordInfoPtr> m_certifitionCache;
	std::mutex m_mtx_users_certifition;  //certifition_register_record 表缓存锁

	//user_relation_ship
	std::map<std::string, userRelationShipPtr> m_userRelationShipCache;
	std::mutex m_mtx_users_relationShip;  //user_ralationship_info 表缓存锁

	std::map<std::string, userMoneyInfoPtr> m_userMoneyCache;
	std::mutex m_mtx_users_money;  //user_Money_info 表缓存锁

	std::map<std::string, InstitutionMainidMapPtr> m_institutionMainidMapCache;
	std::mutex m_mtx_institution_mainid;  //institution_mainid_map 表缓存锁

	std::map<std::string, SystemSetPtr> m_SysSetCache;
	std::mutex m_mtx_systemSet;  //system_set 表缓存锁

	std::map<int, LogRecordsPtr> m_logRecordCache;
	std::mutex m_mtx_logRecord;  //log_record 表缓存锁
};


typedef std::unique_lock<std::mutex> ReadLock;
typedef std::unique_lock<std::mutex> WriteLock;