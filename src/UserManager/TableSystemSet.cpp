#include "TableSystemSet.h"
#include <iostream>


bool CTableSystemSet::querySystemSetAll(std::map<std::string , SystemSetPtr>& cerMap, DB::ConnectInfo& dbconInfo)
{

	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from system_set;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		SystemSetPtr setPtr(new SystemSet);
		setPtr->m_sKey = dbRecordSet.GetString(0);
		setPtr->m_sValue = dbRecordSet.GetString(1);
		setPtr->m_sNote = dbRecordSet.GetString(2);
		

		cerMap[setPtr->m_sKey] = setPtr;
	}

	return true;

}

bool CTableSystemSet::SelectSystemSet(std::string sKey, SystemSet& sysSet, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select `key`,`value`,note from system_set where `key`='" + sKey + "';", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		sysSet.m_sKey	= dbRecordSet.GetString(0);
		sysSet.m_sValue = dbRecordSet.GetString(1);
		sysSet.m_sNote	= dbRecordSet.GetString(2);
	}

	return true;
}