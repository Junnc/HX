#include "TableUserIdentifyFunction.h"
#include <iostream>
#include <sstream>

bool CTableUserIdentifyFunction::addBankToUserIdentifyTableFunction(const userIdentify& user, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "update user_identify_info set "
		<< "bankName='" << user.m_sBankName << "',"
		<< "bankCardNo='" << user.m_sBankCardNo << "',"
		<< "branchBank='" << user.m_sBranchBank << "'"
		<< " where userID='" << user.m_sUserID << "';";

	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (nRes < 0)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	return true;
}

bool CTableUserIdentifyFunction::queryAllUserIdentifyTableFunction(std::map<std::string, userIdentifyPtr>& userIdenfyMap, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from user_identify_info;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		userIdentifyPtr usrPtr(new userIdentify);
		usrPtr->m_sUserID = dbRecordSet.GetString(0);
		usrPtr->m_sIDCard = dbRecordSet.GetString(1);
		usrPtr->m_sBankName = dbRecordSet.GetString(2);
		usrPtr->m_sBranchBank = dbRecordSet.GetString(3);
		usrPtr->m_sBankCardNo = dbRecordSet.GetString(4);
		usrPtr->m_sSurName = dbRecordSet.GetString(5);
		usrPtr->m_nIsDentify = dbRecordSet.GetInt(6);
			
		userIdenfyMap[usrPtr->m_sUserID] = usrPtr;
	}

	return true;
}

bool CTableUserIdentifyFunction::addAuthenticateToUserIdentifyTableFunction(const userIdentify& user, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "insert into user_identify_info"
		<< "(userID,IDCard,bankName,branchBank,bankCardNo,surname,isIdentify)"
		<< "value('"
		<< user.m_sUserID << "','"
		<< user.m_sIDCard << "','','','','"
		<< user.m_sSurName << "','"
		<< user.m_nIsDentify << "')"
		<< "on duplicate key update IDCard='" << user.m_sIDCard << "',"
		<< "surname='" << user.m_sSurName << "',"
		<< "isIdentify='" << user.m_nIsDentify << "';";

	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (nRes < 0)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	return true;
}

bool CTableUserIdentifyFunction::updateIndentifyState(std::string userID,int state, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "update user_identify_info set "
		<< "isIdentify=" << state
		<< " where userID='" << userID << "'";

	{
		std::unique_lock<std::mutex> locker(mutex);
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

bool CTableUserIdentifyFunction::updateSurNameInfo(const userIdentify& user, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "update user_identify_info set "
		<< "isIdentify=" << user.m_nIsDentify << ","
		<< "IDCard='" << user.m_sIDCard << "',"
		<< "surname='" << user.m_sSurName << "'"
		<< " where userID='" << user.m_sUserID << "'";

	{
		std::unique_lock<std::mutex> locker(mutex);
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

bool CTableUserIdentifyFunction::addIdentifyInfo(const userIdentify& user, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "insert into user_identify_info"
		<< "(userID,IDCard,bankName,branchBank,"
		<< "bankCardNo,surname,isIdentify)"
		<< "values('"
		<< user.m_sUserID << "', '"
		<< user.m_sIDCard << "', '"
		<< user.m_sBankName << "', '"
		<< user.m_sBranchBank << "', '"
		<< user.m_sBankCardNo << "', '"
		<< user.m_sSurName << "', '"
		<< user.m_nIsDentify << "'); ";

	{
		std::unique_lock<std::mutex> locker(mutex);
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
