#include "DBOperator.h"
#include <iostream>
//#include "DBConnect.h"


std::shared_ptr<DB::CDBConnPool> CDBOpeartor::getDBPool()
{
	return m_dbconnPoolPtr;
}

bool CDBOpeartor::addUser(const userInfos& user)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	
	return m_tableUserFunc.addUserTableFunction(user, dbconInfo);
}

bool CDBOpeartor::init(DB::DBInfo dbinfo, int nMax, int nMin)
{
	m_dbconnPoolPtr = std::make_shared<DB::CDBConnPool>(dbinfo);
	size_t res = m_dbconnPoolPtr->InitConnection(nMin, nMax);
	if (res <= 0)
		return false;

	std::cout << "success free connNum:" << m_dbconnPoolPtr->GetFreeNum() << endl;

	return true;
}

bool CDBOpeartor::queryAllUser(std::map<std::string, userInfosPtr>& userInfoMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableUserFunc.queryAllUserTableFunction(userInfoMap, dbconInfo);
}

//nflag  1=���п�����Ϣ���   2 = ���û����
bool CDBOpeartor::addUserIdentify(userIdentify& usrIdentify,int nflag)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	if (nflag == 0)
		return m_tableUserIdentifyFunc.addBankToUserIdentifyTableFunction(usrIdentify, dbconInfo);
	else if (nflag == 1)
		return m_tableUserIdentifyFunc.addIdentifyInfo(usrIdentify, dbconInfo);
}

bool CDBOpeartor::queryUserIdentifyAll(std::map<std::string, userIdentifyPtr>& userIdentifyMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableUserIdentifyFunc.queryAllUserIdentifyTableFunction(userIdentifyMap, dbconInfo);
}

bool CDBOpeartor::updateIndentifyState(std::string userID, int state)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableUserIdentifyFunc.updateIndentifyState(userID, state, dbconInfo);
}

bool CDBOpeartor::queryCertifitionRegRecordAll(std::map<int, certificationRegRecordInfoPtr>& cerMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableCerRegRecordFunc.queryCertificationRegRecordAll(cerMap, dbconInfo);
}

bool CDBOpeartor::updateCertifitionRegState(int id, int state, std::string apprReson, std::string apprID)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);	
	return m_tableCerRegRecordFunc.updateCertifitionRegState(id, state, apprReson, apprID, dbconInfo);
}

bool CDBOpeartor::addUserIdentifyAuthenticate(/*userIdentify& usrIdentify*/certificationRegisterRecordInfo &cerRegRec)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//�����֤��¼certification_register_record
	if (!m_tableCerRegRecordFunc.addCertificationRegRecord(cerRegRec, dbconInfo))
	{
		std::cout << "���ʵ����֤���ݿ��¼ʧ��" << endl;
		//m_dbconnPoolPtr->ReleaseConnection(dbconInfo.pDBConnect->getConnectID());
		return false;
	}

	//�޸���֤���Ϊ����֤
	userIdentify usrIdentify;
	usrIdentify.m_sUserID = cerRegRec.m_sUserId;
	usrIdentify.m_sIDCard = cerRegRec.m_sIDCard;
	usrIdentify.m_sSurName = cerRegRec.m_sSurName;
	usrIdentify.m_nIsDentify = 2;
	if (!m_tableUserIdentifyFunc.updateSurNameInfo(usrIdentify, dbconInfo))
	{
		std::cout << "�޸����ݿ���֤���Ϊ����֤ʧ��" << endl;
		//m_dbconnPoolPtr->ReleaseConnection(dbconInfo.pDBConnect->getConnectID());
		return false;
	}
		
	atomTransaction.SetCommit();
	return true;
}


bool CDBOpeartor::queryUserRelationShipAll(std::map<std::string, userRelationShipPtr>& usrShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableUserRelationShipFunc.queryUserRelationShipAll(usrShip, dbconInfo);
}

bool CDBOpeartor::queryUserMoneyInfoAll(std::map<std::string, userMoneyInfoPtr>& usrMoneyCache)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableUserMoneyInfoFunc.queryUserRelationShipAll(usrMoneyCache, dbconInfo);
}

bool CDBOpeartor::addChildAccount(userInfos& tmp, userRelationShip& userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//���users��
	if (!m_tableUserFunc.addUserTableFunction(tmp, dbconInfo))
		return false;

	//���user_relation_ship
	if (!m_tableUserRelationShipFunc.addUserAndRelationShip(userShip, dbconInfo))
		return false;

	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::addUserMoneyInfo(userMoneyInfo& usrMoney)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	return m_tableUserMoneyInfoFunc.addUserMoneyInfo(usrMoney, dbconInfo);
}

bool CDBOpeartor::updateChildAccount(userInfos tmp, userRelationShip userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);
	//����users  ����user_relation_ship
	if (!m_tableUserFunc.updateChildUserInfo(tmp, dbconInfo) || 
		!m_tableUserRelationShipFunc.updateChildAccount(userShip, dbconInfo))
	{
		std::cout << "update DB fail" << endl;
		return false;
	}
	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::deleteChildAccount(const std::string userID)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//ɾ��user table
	if (!m_tableUserFunc.deleteAccount(userID, dbconInfo))
		return false;

	//ɾ��user_relation_ship 
	if (!m_tableUserRelationShipFunc.deleteUserRelationShip(userID, dbconInfo))
		return false;

	//ɾ��user_money_info
	if (!m_tableUserMoneyInfoFunc.deleteUserMoneyInfo(userID, dbconInfo))
		return false;

	atomTransaction.SetCommit();
	return true;
}

bool CDBOpeartor::deleteMainAccountOrManager(const std::string userID)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//ɾ��user table
	if (!m_tableUserFunc.deleteAccount(userID, dbconInfo))
		return false;

	//ɾ��user_relation_ship 
	if (!m_tableUserRelationShipFunc.deleteUserRelationShip(userID, dbconInfo))
		return false;

	atomTransaction.SetCommit();
	return true;
}

//ɾ��ָ�����˻�  institution_mainid_map
bool CDBOpeartor::delAssignMainAccount(const std::string userID, const std::string institution)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	//ɾ��institution_mainid_map table
	if (!m_tableInstitutionMainid.deleteAccount(institution, userID, dbconInfo))
	{
		//ɾ�����ݿ�ʧ��
		return false;
	}

	return true;
}

bool CDBOpeartor::queryInstitutionMainMapAll(std::map <std::string, InstitutionMainidMapPtr>& insMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	//institution_mainid_map table
	if (!m_tableInstitutionMainid.queryInstitutionMainidMapAll(insMap, dbconInfo))
		return false;

	return true;
}


bool CDBOpeartor::updateMainAccount(userInfos tmp, userRelationShip userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	//����users 
	return m_tableUserFunc.updateMainAccount(tmp, dbconInfo);
}


bool CDBOpeartor::addManager(userInfos& tmp, userRelationShip& userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//���users��
	if (!m_tableUserFunc.addUserTableFunction(tmp, dbconInfo))
		return false;

	//���user_relation_ship
	if (!m_tableUserRelationShipFunc.addUserAndRelationShip(userShip, dbconInfo))
		return false;

	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::updateManagerAccount(userInfos tmp, userRelationShip userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);
	//����users  ����user_relation_ship
	if (!m_tableUserFunc.updateManagerUserInfo(tmp, dbconInfo) ||
		!m_tableUserRelationShipFunc.updateChildAccount(userShip, dbconInfo))
	{
		std::cout << "update manager DB fail" << endl;
		return false;
	}
	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::addAgent(userInfos& tmp, userRelationShip& userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//���users��
	if (!m_tableUserFunc.addUserTableFunction(tmp, dbconInfo))
		return false;

	//���user_relation_ship
	if (!m_tableUserRelationShipFunc.addUserAndRelationShip(userShip, dbconInfo))
		return false;

	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::querySystemSetAll(std::map<std::string, SystemSetPtr>& setInfo)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableSystemSet.querySystemSetAll(setInfo, dbconInfo);
}


bool CDBOpeartor::updateChildAgent(userInfos tmp, userRelationShip userShip)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);
	//����users  ����user_relation_ship
	if (!m_tableUserFunc.updateChildAgent(tmp, dbconInfo) ||
		!m_tableUserRelationShipFunc.updateChildAccount(userShip, dbconInfo))
	{
		std::cout << "update child agent DB fail" << endl;
		return false;
	}
	atomTransaction.SetCommit();

	return true;
}

bool CDBOpeartor::deleteChildAgent(const std::string userID)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	DB::CAtomTransaction atomTransaction(dbconInfo.pDBConnect);

	//ɾ��user table
	if (!m_tableUserFunc.deleteAccount(userID, dbconInfo))
		return false;

	//ɾ��user_relation_ship 
	if (!m_tableUserRelationShipFunc.deleteUserRelationShip(userID, dbconInfo))
		return false;

	// ɾ��Ӷ����Ϣ��
	// ������

	atomTransaction.SetCommit();
	return true;
}

bool CDBOpeartor::queryLogRecordAll(std::map<int, LogRecordsPtr>& logMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	return m_tableLogRecord.queryLogRecordAll(logMap, dbconInfo);
}

bool CDBOpeartor::addLogRecord(LogRecords& logMap)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	return m_tableLogRecord.addLogRecord(logMap, dbconInfo);
}

bool CDBOpeartor::SelectDB(int id, certificationRegRecordInfoPtr& cerPtr)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);
	return m_tableCerRegRecordFunc.selectDB(id, cerPtr, dbconInfo);
}

// ��ѯ�����¼�����(����)���������¼�...����(����)
bool CDBOpeartor::SelectAllChildAgentFromDB(const std::string& institutionID, UserAndRelationShipMap& tableInfos)
{
	DB::ConnectInfo dbconInfo;
	CAtomGetConnnect atomConn(dbconInfo);

	// ��ѯ���ȼ�
	SystemSet sysInfo;
	int maxLevel = 0;
	if (!m_tableSystemSet.SelectSystemSet("STITUTION_LEVEL", sysInfo, dbconInfo))
		maxLevel = 3;
	else
		maxLevel = std::stoi(sysInfo.m_sValue);

	return m_tableUserFunc.SelectAllChildAgent(maxLevel, institutionID, tableInfos, dbconInfo);
}