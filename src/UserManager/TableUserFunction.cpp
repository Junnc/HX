#include "TableUserFunction.h"
#include <iostream>
#include <sstream>
#include <vector>

bool CTableUserFunction::addUserTableFunction(const userInfos& user, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "insert into users"
		<< "(userID,userType,level,loginName,accountName,password,phone,poularizeLink,address,isLogicDel,registerDate,registerTime,mainIDNum,subIDNum,counterType,financeType,totalMoney,futureMoney,stockMoney)"
		<< "values('"
		<< user.m_sUserID << "', '" << user.m_nUserType << "', '" << user.m_nLevel << "', '" << user.m_sLoginName <<"', '" << user.m_sAccountName << "', '" << user.m_sPassword << "', '"
		<< user.m_sPhone << "', '" << user.m_sPoularizeLink << "', '" << user.m_sAddress << "', '" << user.m_nIsLogicDel << "', '" << user.m_nRegisterDate << "', '"
		<< user.m_nRegisterTime << "', '" << user.m_nMainIDNum << "', '" << user.m_nSumIDNum << "', '" << user.m_nCounterType << "', '" << user.m_nFinanceType<<"', '"
		<<user.m_dTotalMoney<<"', '"<<user.m_dFutureMoney<<"', '"<<user.m_dStockMoney
		<< "');";

	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (nRes < 0)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout <<"SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
			
		std::cout <<"Sql=> "<<ssSql.str().c_str()<< ",  execute res:" << nRes << endl;
	}	
	return true;
}

bool CTableUserFunction::queryAllUserTableFunction(std::map<std::string, userInfosPtr>& userInfoMap, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	
	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from users;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
			
	}

	while (dbRecordSet.GetNextRow())
	{
		userInfosPtr usrPtr(new userInfos);
		usrPtr->m_sUserID		= dbRecordSet.GetString(0);
		usrPtr->m_nUserType		= dbRecordSet.GetInt(1);
		usrPtr->m_nLevel		= dbRecordSet.GetInt(2);
		usrPtr->m_sLoginName	= dbRecordSet.GetString(3);
		usrPtr->m_sAccountName	= dbRecordSet.GetString(4);
		usrPtr->m_sPassword		= dbRecordSet.GetString(5);
		usrPtr->m_sPhone		= dbRecordSet.GetString(6);
		usrPtr->m_sPoularizeLink = dbRecordSet.GetString(7);
		usrPtr->m_sAddress		= dbRecordSet.GetString(8);
		usrPtr->m_nIsLogicDel	= dbRecordSet.GetInt(9);
		usrPtr->m_nRegisterDate = dbRecordSet.GetInt(10);
		usrPtr->m_nRegisterTime = dbRecordSet.GetInt(11);
		usrPtr->m_nMainIDNum	= dbRecordSet.GetInt(12);
		usrPtr->m_nSumIDNum		= dbRecordSet.GetInt(13);
		usrPtr->m_nCounterType  = dbRecordSet.GetInt(14);
		usrPtr->m_nFinanceType  = dbRecordSet.GetInt(15);
		usrPtr->m_dTotalMoney   = dbRecordSet.GetDouble(16);
		usrPtr->m_dFutureMoney  = dbRecordSet.GetDouble(17);
		usrPtr->m_dStockMoney	= dbRecordSet.GetDouble(18);

		userInfoMap[usrPtr->m_sUserID] = usrPtr;
	}

	return true;
}

bool CTableUserFunction::updateChildUserInfo(const userInfos& usr, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::cout << "update users" << std::endl;
	std::stringstream ssSql;
	ssSql << "update users set "
		<< "`password`='" << usr.m_sPassword << "',"
		<< "phone = '" << usr.m_sPhone << "',"
		<< "accountName = '" << usr.m_sAccountName
		<< "' where userID = '" << usr.m_sUserID << "'";

	{
		WriteLock locker(mutex);
		int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (0 != iRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}
	
	return true;
}

bool CTableUserFunction::deleteAccount(std::string userID, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "delete from users where users.userID = '" << userID << "';";

	WriteLock lck(mutex);
	int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
	if (0 != iRes)
	{
		DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
		std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
		return false;
	}

	return true;
}

bool CTableUserFunction::updateMainAccount(const userInfos& usr, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "update users set "
		<< "loginName='" << usr.m_sLoginName
		<< "',`password`='" << usr.m_sPassword
		<< "',accountName='" << usr.m_sAccountName
		<< "',counterType=" << usr.m_nCounterType
		<< " where userID = '" << usr.m_sUserID << "';";

	{
		WriteLock locker(mutex);
		int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (0 != iRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}


	return true;
}

bool CTableUserFunction::updateManagerUserInfo(const userInfos& usr, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::cout << "update users" << std::endl;
	std::stringstream ssSql;
	ssSql << "update users set "
		<< "`password`='" << usr.m_sPassword << "',"
		<< "accountName = '" << usr.m_sAccountName
		<< "' where userID = '" << usr.m_sUserID << "'";

	{
		WriteLock locker(mutex);
		int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (0 != iRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	return true;
}

bool CTableUserFunction::updateChildAgent(const userInfos& usr, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "update users set "
		<< "accountName='" << usr.m_sAccountName
		<< "',`password`='" << usr.m_sPassword
		<< "',phone = '" << usr.m_sPhone
		<< "', mainIDNum = " << usr.m_nMainIDNum
		<< ", subIDNum = " << usr.m_nSumIDNum
		<< " where userID = '" << usr.m_sUserID << "';";

	{
		WriteLock locker(mutex);
		int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (0 != iRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	return true;
}

bool CTableUserFunction::SelectAllChildAgent(int maxLevel,const std::string sUserID, UserAndRelationShipMap& tableInfos, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	// 机构容器
	userInfosPtr userInfoRootTmp;
	userRelationShipPtr shipInfoRootTmp;
	SelectUsersAndRelationShip(sUserID, userInfoRootTmp, shipInfoRootTmp, dbconInfo);

	if (nullptr == userInfoRootTmp || nullptr == shipInfoRootTmp)
		return false;
	tableInfos[userInfoRootTmp] = shipInfoRootTmp;

	int level = userInfoRootTmp->m_nLevel;
	std::vector<std::string> institutionsTmp;
	institutionsTmp.emplace_back(sUserID);

	for (int i = 0; i < maxLevel - level; i++)
	{
		std::vector<std::string> institutionsCurr;
		for(auto iterIns=institutionsTmp.begin(); iterIns != institutionsTmp.end(); iterIns++)
		{
			SelectNextInsAcc(*iterIns, institutionsCurr, dbconInfo);
		}

		for(auto iterUser = institutionsCurr.begin(); iterUser != institutionsCurr.end(); iterUser++)
		{
			userInfosPtr userRootTmp;
			userRelationShipPtr shipRootTmp;

			SelectUsersAndRelationShip(*iterUser, userRootTmp, shipRootTmp, dbconInfo);
			if (nullptr == userRootTmp || nullptr == shipRootTmp)
				continue;
			tableInfos[userRootTmp] = shipRootTmp;
		}
		institutionsTmp = institutionsCurr;
	}

	return true;
}

bool CTableUserFunction::SelectUsersAndRelationShip(const std::string sUserID, userInfosPtr& usr, userRelationShipPtr& ship, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	// 查询数据并读取
	std::stringstream ssSql;
	ssSql << "select a.userID,userType,`level`,loginName,accountName,`password`,phone,poularizeLink, \
                                   address,isLogicDel,registerDate,registerTime,institutionID,monitorID,  \
		                           manangerID, mainID, marginModuleID, feeModuleID, riskModuleID,mainIDNum,subIDNum,counterType,authrityModuleID \
                                   from users a, user_relation_ship b where a.userID = b.userID "
		<< " and a.userID='" << sUserID << "'";
	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select(ssSql.str(), dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}

	}
	while (dbRecordSet.GetNextRow())
	{
		usr = std::make_shared<userInfos>();
		ship = std::make_shared<userRelationShip>();

		usr->m_sUserID		= dbRecordSet.GetString(0);
		ship->sUserID		= usr->m_sUserID;
		usr->m_nUserType	= dbRecordSet.GetInt(1);
		usr->m_nLevel		= dbRecordSet.GetInt(2);
		usr->m_sLoginName	= dbRecordSet.GetString(3);
		usr->m_sAccountName = dbRecordSet.GetString(4);
		usr->m_sPassword	= dbRecordSet.GetString(5);
		usr->m_sPhone		= dbRecordSet.GetString(6);
		usr->m_sPoularizeLink = dbRecordSet.GetString(7);
		usr->m_sAddress		= dbRecordSet.GetString(8);
		usr->m_nIsLogicDel	= dbRecordSet.GetInt(9);
		usr->m_nRegisterDate = dbRecordSet.GetInt(10);
		usr->m_nRegisterTime = dbRecordSet.GetInt(11);
		ship->sInstitutionID = dbRecordSet.GetString(12);
		ship->sMonitorID	= dbRecordSet.GetString(13);
		ship->sManagerID	= dbRecordSet.GetString(14);
		ship->sMainID		= dbRecordSet.GetString(15);
		ship->sMarginModuleID= dbRecordSet.GetString(16);
		ship->sFeemoduleID	= dbRecordSet.GetString(17);
		ship->sRiskModuleID = dbRecordSet.GetString(18);
		usr->m_nMainIDNum	= dbRecordSet.GetInt(19);
		usr->m_nSumIDNum	= dbRecordSet.GetInt(20);
		usr->m_nCounterType = dbRecordSet.GetInt(21);
		ship->sAuthrityModuleID = dbRecordSet.GetString(22);

	}

	return true;
}

bool CTableUserFunction::SelectNextInsAcc(const std::string& institutionID, std::vector<std::string>& userIDs, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	// 查询数据并读取
	DB::CDBRecordSet dbRecordSet;
	std::stringstream ssSql;
	ssSql << "select a.userID from users a, user_relation_ship b where a.userID = b.userID and b.institutionID = '" << institutionID << "' and a.userType=" << UsersType::USER_INSTITUTION;
	int iRes = dbconInfo.pDBConnect->Select(ssSql.str(), dbRecordSet);
	if (0 != iRes)
		return false;
	while (dbRecordSet.GetNextRow())
	{
		std::string userID = dbRecordSet.GetString(0);
		userIDs.emplace_back(userID);
	}

	return true;
}
