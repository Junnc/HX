#include "TableInstitutionMainidMap.h"
#include <iostream>
#include <sstream>

bool CTableInstitutionMainidMap::deleteAccount(std::string institutionID, std::string mainID,DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return -1;

	std::stringstream ssSql;
	ssSql << "delete from institution_mainid_map where institutionID='" << institutionID << "' and mainID='" << mainID << "';";
	
	{
		WriteLock lck(mutex);
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

bool CTableInstitutionMainidMap::queryInstitutionMainidMapAll(std::map <std::string, InstitutionMainidMapPtr>& insMap, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from institution_mainid_map;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		InstitutionMainidMapPtr insPtr(new InstitutionMainidMap);
		insPtr->m_id			 = dbRecordSet.GetString(0);
		insPtr->m_institutionID  = dbRecordSet.GetString(1);
		insPtr->m_mainID		 = dbRecordSet.GetString(2);
		
		insMap[insPtr->m_id] = insPtr;
	}

	return true;
}
