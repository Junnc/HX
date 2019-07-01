#pragma once
#include "UserTableMsgStruct.h"
#include "instance_shared_from_this.h"
#include "DBConnPool.h"
#include "TableUserFunction.h"
#include "TableUserIdentifyFunction.h"
#include "TableCertificationRegRecord.h"
#include "TableUserRelationShipFuntion.h"
#include "TableUserMoneyInfoFunction.h"
#include "TableInstitutionMainidMap.h"
#include <map>
#include "TableSystemSet.h"
#include "TableLogRecordFunction.h"

class CDBOpeartor:public CommonTools::instance_shared_from_this<CDBOpeartor>
{
public:
	bool init(DB::DBInfo dbinfo,int nMax,int nMin);
	bool updateChildAccount(userInfos tmp, userRelationShip userShip);
	bool deleteChildAccount(const std::string userID);
	bool deleteMainAccountOrManager(const std::string userID);
	bool addManager(userInfos& tmp, userRelationShip& userShip);

	bool updateManagerAccount(userInfos tmp, userRelationShip userShip);
	bool addAgent(userInfos& tmp, userRelationShip& userShip);
	bool updateChildAgent(userInfos tmp, userRelationShip userShip);
	
	bool deleteChildAgent(const std::string userID);
	//user table
	bool addUser(const userInfos& user);
	bool queryAllUser(std::map<std::string, userInfosPtr>& userInfoMap);
	bool updateMainAccount(userInfos tmp, userRelationShip userShip);


	//user_identify_info table
	bool addUserIdentify(userIdentify& usrIdentify, int flag = 0);
	bool queryUserIdentifyAll(std::map<std::string, userIdentifyPtr>& userIdentifyMap);
	bool updateIndentifyState(std::string userID, int state);

	
	//certifition_register_record  +  user_identify_info
	bool addUserIdentifyAuthenticate(certificationRegisterRecordInfo &cerRegRec);

	
	//certifition_register_record
	bool queryCertifitionRegRecordAll(std::map<int, certificationRegRecordInfoPtr>& cerMap);
	bool updateCertifitionRegState(int id, int state, std::string apprReson, std::string apprID);
	bool SelectDB(int id ,certificationRegRecordInfoPtr& cerPtr);

	//user_relation_ship
	bool queryUserRelationShipAll(std::map<std::string, userRelationShipPtr>& usrShip);

	
	bool addChildAccount(userInfos& tmp, userRelationShip& userShip);

	
	//user_money_info
	bool queryUserMoneyInfoAll(std::map<std::string, userMoneyInfoPtr>& usrMoneyCache);
	bool addUserMoneyInfo(userMoneyInfo& usrMoney);

	//institution_mainid_map
	bool queryInstitutionMainMapAll(std::map <std::string, InstitutionMainidMapPtr>& insMap);
	
	//删除指派主账户
	bool delAssignMainAccount(const std::string userID, const std::string institution);

	//system_set
	bool querySystemSetAll(std::map<std::string, SystemSetPtr>& userInfoMap);

	//log_records
	bool queryLogRecordAll(std::map<int, LogRecordsPtr>& logMap);
	bool addLogRecord(LogRecords& logMap);

	// 查询所有下级代理(机构)，包括下下级...代理(机构)
	bool SelectAllChildAgentFromDB(const std::string& institutionID, UserAndRelationShipMap& tableInfos);
	
	std::shared_ptr<DB::CDBConnPool> getDBPool();
private:

	std::shared_ptr<DB::CDBConnPool>	m_dbconnPoolPtr;

	CTableUserFunction					m_tableUserFunc;
	CTableUserIdentifyFunction			m_tableUserIdentifyFunc;
	CTableCertificationRegRecord		m_tableCerRegRecordFunc;

	CTableUserRelationShipFuntion		m_tableUserRelationShipFunc;
	CTableUserMoneyInfoFuntion			m_tableUserMoneyInfoFunc;
	CTableInstitutionMainidMap			m_tableInstitutionMainid;
	CTableSystemSet						m_tableSystemSet;
	CTableLogRecordFunction				m_tableLogRecord;
};

class  CAtomGetConnnect
{
public:
	CAtomGetConnnect(DB::ConnectInfo_& connectInfo)
	{
		CDBOpeartor::instance()->getDBPool()->GetConnection(connectInfo);
		m_connectID = -1;
		if (nullptr == connectInfo.pDBConnect)
			return;
		m_connectID = connectInfo.pDBConnect->getConnectID();
	}

	~CAtomGetConnnect()
	{
		if (-1 == m_connectID)
			return;
		CDBOpeartor::instance()->getDBPool()->ReleaseConnection(m_connectID);
	}

private:
	CAtomGetConnnect();

private:
	size_t m_connectID;
};
