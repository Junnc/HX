#include "TableLogRecordFunction.h"
#include <iostream>
#include <sstream>


bool CTableLogRecordFunction::queryLogRecordAll(std::map<int, LogRecordsPtr>& logMap, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from log_records;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		LogRecordsPtr logPtr(new LogRecords);
		logPtr->m_logID = dbRecordSet.GetInt(0);
		logPtr->m_userName = dbRecordSet.GetString(1);
		logPtr->m_userID = dbRecordSet.GetString(2);
		logPtr->m_type = dbRecordSet.GetInt(3);
		logPtr->m_operatorID = dbRecordSet.GetString(4);
		logPtr->m_operatorName = dbRecordSet.GetString(5);
		logPtr->m_createDate = dbRecordSet.GetInt(6);
		logPtr->m_createTime = dbRecordSet.GetInt(7);
		logPtr->m_newContent = dbRecordSet.GetString(8);
		logPtr->m_oldContent = dbRecordSet.GetString(9);
		logPtr->m_sysModule = dbRecordSet.GetInt(10);
		logPtr->m_sysModuleName = dbRecordSet.GetString(11);
		logPtr->m_mac = dbRecordSet.GetString(12);
		logPtr->m_ip = dbRecordSet.GetString(13);


		logMap[logPtr->m_logID] = logPtr;
	}

	return true;

}

bool CTableLogRecordFunction::addLogRecord(LogRecords& logRec, DB::ConnectInfo& dbconInfo)
{

	if (nullptr == dbconInfo.pDBConnect)
		return false;
	std::stringstream ssSql;
	ssSql << "insert into log_records(userName,userID,operatorName,operatorID,"
		<< "createDate,createTime,describeText,content,"
		<< "sysModule,sysModuleName,mac,ip,type)"
		<< "values('"
		<< logRec.m_userName << "', '"
		<< logRec.m_userID << "', '"
		<< logRec.m_operatorName << "', '"
		<< logRec.m_operatorID << "', "
		<< logRec.m_createDate << ", "
		<< logRec.m_createTime << ", '"
		<< logRec.m_newContent << "', '"
		<< logRec.m_oldContent << "', "
		<< logRec.m_sysModule << ", '"
		<< logRec.m_sysModuleName << "', '"
		<< logRec.m_mac << "', '"
		<< logRec.m_ip << "', "
		<< logRec.m_type << ");";
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (nRes < 0)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}

		DB::CDBRecordSet dbRecordSet;
		nRes = dbconInfo.pDBConnect->Select("SELECT LAST_INSERT_ID();", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
		while (dbRecordSet.GetNextRow())
		{
			logRec.m_logID = dbRecordSet.GetInt(0);
		}
	}
	return true;
}