#include "TableUserRelationShipFuntion.h"
#include <sstream>
#include <iostream>

bool CTableUserRelationShipFuntion::queryUserRelationShipAll(std::map<std::string, userRelationShipPtr>& usrShip, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		ReadLock locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from user_relation_ship;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		userRelationShipPtr usrPtr(new userRelationShip);
		usrPtr->sUserID = dbRecordSet.GetString(0);
		usrPtr->sInstitutionID = dbRecordSet.GetString(1);
		usrPtr->sMonitorID = dbRecordSet.GetString(2);
		usrPtr->sManagerID = dbRecordSet.GetString(3);
		usrPtr->sMainID = dbRecordSet.GetString(4);
		usrPtr->sMarginModuleID = dbRecordSet.GetString(5);
		usrPtr->sFeemoduleID = dbRecordSet.GetString(6);
		usrPtr->sRiskModuleID = dbRecordSet.GetString(7);
		usrPtr->sAuthrityModuleID = dbRecordSet.GetString(8);
		usrPtr->sRiskModuleAuthrityID = dbRecordSet.GetString(9);

		usrShip[usrPtr->sUserID] = usrPtr;
	}

	return true;
}

bool CTableUserRelationShipFuntion::addUserAndRelationShip(userRelationShip& userShip, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "insert into user_relation_ship"
		<< " (userID,institutionID,monitorID,"
		<< "manangerID,marginModuleID,mainID,"
		<< "feeModuleID,authrityModuleID,riskModuleID,riskModuleAuthrityID)"
		<< "values('"
		<< userShip.sUserID << "', '"
		<< userShip.sInstitutionID << "', '"
		<< userShip.sMonitorID << "', '"
		<< userShip.sManagerID << "', '"
		<< userShip.sMarginModuleID << "','"
		<< userShip.sMainID << "', '"
		<< userShip.sFeemoduleID << "', '"
		<< userShip.sAuthrityModuleID << "', '"
		<< userShip.sRiskModuleID << "', '"
		<< userShip.sRiskModuleAuthrityID << "');";

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

bool CTableUserRelationShipFuntion::updateChildAccount(userRelationShip& userShip, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
	{
		std::cout << "pDBConnect user_relation_ship is null" << std::endl;
		return false;
	}
		

	std::cout << "update user_relation_ship" << std::endl;
	std::stringstream ssSql;
	ssSql << "update user_relation_ship set "
		<< "monitorID='"			<< userShip.sMonitorID
		<< "',manangerID='"			<< userShip.sManagerID
		<< "',marginModuleID='"		<< userShip.sMarginModuleID
		<< "',feeModuleID='"		<< userShip.sFeemoduleID
		<< "',riskModuleID='"		<< userShip.sRiskModuleID
		<< "',riskModuleAuthrityID='" << userShip.sRiskModuleAuthrityID
		<< "',authrityModuleID='"	<< userShip.sAuthrityModuleID
		<< "',mainID='"				<< userShip.sMainID
		<< "',institutionID='"		<< userShip.sInstitutionID
		<< "' where userID='"		<< userShip.sUserID << "';";

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

bool CTableUserRelationShipFuntion::deleteUserRelationShip(std::string userID, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "delete from user_relation_ship where userID='" << userID << "';";

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