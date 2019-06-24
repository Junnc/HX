#include "TableUserMoneyInfoFunction.h"
#include <sstream>
#include <iostream>

bool CTableUserMoneyInfoFuntion::queryUserRelationShipAll(std::map<std::string, userMoneyInfoPtr>& usrMoneyCache, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		ReadLock locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from user_money_info;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		userMoneyInfoPtr usrPtr(new userMoneyInfo);
		usrPtr->m_sUserID			= dbRecordSet.GetString(0);
		usrPtr->m_dUserDeposit		= dbRecordSet.GetDouble(1);
		usrPtr->m_dEquipment		= dbRecordSet.GetDouble(2);
		usrPtr->m_dPreBalance		= dbRecordSet.GetDouble(3);
		usrPtr->m_dCurrentTotal		= dbRecordSet.GetDouble(4);
		usrPtr->m_dFrozenOutMoney	= dbRecordSet.GetDouble(5);
		usrPtr->m_dTodayCloseProfit	= dbRecordSet.GetDouble(6);
		usrPtr->m_dTodayFee			= dbRecordSet.GetDouble(7);
		usrPtr->m_dTodayInMoney		= dbRecordSet.GetDouble(8);
		usrPtr->m_dTodayOutMoney	= dbRecordSet.GetDouble(9);
		usrPtr->m_dHistoryProfit	= dbRecordSet.GetDouble(10);
		usrPtr->m_dHistoryFee		= dbRecordSet.GetDouble(11);
		usrPtr->m_dHistoryOutMoney	= dbRecordSet.GetDouble(12);
		usrPtr->m_dHistoryInMoney	= dbRecordSet.GetDouble(13);
	

		usrMoneyCache[usrPtr->m_sUserID] = usrPtr;
	}

	return true;
}

bool CTableUserMoneyInfoFuntion::addUserMoneyInfo(userMoneyInfo& usrMoneyInfo, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "insert into user_money_info"
		<< "(userID,userDeposit,equipment,preBalance,"
		<< "currentTotal,todayCloseProfit,todayFee,"
		<< "todayInMoney,todayOutMoney,historyProfit,"
		<< "historyFee,historyOutMoney,historyInMoney,frozenOutMoney)"
		<< "values('"
		<< usrMoneyInfo.m_sUserID << "', "
		<< usrMoneyInfo.m_dUserDeposit << ", "
		<< usrMoneyInfo.m_dEquipment << ", "
		<< usrMoneyInfo.m_dPreBalance << ", "
		<< usrMoneyInfo.m_dCurrentTotal << ", "
		<< usrMoneyInfo.m_dTodayCloseProfit << ", "
		<< usrMoneyInfo.m_dTodayFee << ", "
		<< usrMoneyInfo.m_dTodayInMoney << ", "
		<< usrMoneyInfo.m_dTodayOutMoney << ", "
		<< usrMoneyInfo.m_dHistoryProfit << ", "
		<< usrMoneyInfo.m_dHistoryFee << ", "
		<< usrMoneyInfo.m_dHistoryOutMoney << ", "
		<< usrMoneyInfo.m_dHistoryInMoney << ", "
		<< usrMoneyInfo.m_dFrozenOutMoney << ");";

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

bool CTableUserMoneyInfoFuntion::deleteUserMoneyInfo(std::string userID, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "delete from user_money_info where userID = '" << userID << "';";

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
