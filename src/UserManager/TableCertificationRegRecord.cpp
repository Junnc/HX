#include "TableCertificationRegRecord.h"
#include <iostream>
#include <sstream>

bool CTableCertificationRegRecord::addCertificationRegRecord(const certificationRegisterRecordInfo& cerRegRecInfo, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;
	
	std::stringstream ssSql;
	ssSql << "insert into certification_register_record"
		<< "(userID,loginName,accountName,"
		<< "surname,IDCard,PostTime,ApprovalTime,ApprovalID,IsApproval,ApprovalReason)"
		<< "values('" << cerRegRecInfo.m_sUserId << "', '" << cerRegRecInfo.m_sLoginName << "', '" << cerRegRecInfo.m_sAccountName
		<< "', '" << cerRegRecInfo.m_sSurName << "', '" << cerRegRecInfo.m_sIDCard << "', '" << cerRegRecInfo.m_sPostTime << "','"
		<< cerRegRecInfo.m_sApprovalTime << "', '" << cerRegRecInfo.m_sApprovalID << "'," << cerRegRecInfo.m_nIsApproval << ",'" << cerRegRecInfo.m_sApprovalReason << "');";
	
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

bool CTableCertificationRegRecord::queryCertificationRegRecordAll(std::map<int, certificationRegRecordInfoPtr>& cerMap, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	DB::CDBRecordSet dbRecordSet;
	{
		std::unique_lock<std::mutex> locker(mutex);
		int nRes = dbconInfo.pDBConnect->Select("select * from certification_register_record;", dbRecordSet);
		if (0 != nRes)
		{
			DB::DBErrorInfo err = dbconInfo.pDBConnect->GetLastError();
			std::cout << "SQL errorMsg:" << err.errorInfo.c_str() << ",errorCode:" << err.type << endl;
			return false;
		}
	}

	while (dbRecordSet.GetNextRow())
	{
		certificationRegRecordInfoPtr ucerPtr(new certificationRegisterRecordInfo);
		ucerPtr->m_id = dbRecordSet.GetInt(0);
		ucerPtr->m_sUserId = dbRecordSet.GetString(1);
		ucerPtr->m_sLoginName = dbRecordSet.GetString(2);
		ucerPtr->m_sAccountName = dbRecordSet.GetString(3);
		ucerPtr->m_sSurName = dbRecordSet.GetString(4);
		ucerPtr->m_sIDCard = dbRecordSet.GetString(5);
		ucerPtr->m_sPostTime = dbRecordSet.GetString(6);
		ucerPtr->m_sApprovalTime = dbRecordSet.GetInt(7);
		ucerPtr->m_sApprovalID = dbRecordSet.GetString(8);
		ucerPtr->m_nIsApproval = dbRecordSet.GetInt(9);
		ucerPtr->m_sApprovalReason = dbRecordSet.GetString(10);

		cerMap[ucerPtr->m_id] = ucerPtr;
	}

	return true;
}

bool CTableCertificationRegRecord::updateCertifitionRegState(int id,int state,std::string apprReson, std::string apprID, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "update certification_register_record set "
		<< " IsApproval=" << state
		<< ",ApprovalReason='" << apprReson
		<< "',ApprovalID='" << apprID
		<< "',ApprovalTime=NOW()"
		<< " where id =" << id;

	{
		std::unique_lock<std::mutex> locker(mutex);
		int iRes = dbconInfo.pDBConnect->Execute(ssSql.str());
		if (0 != iRes)
			return false;
	}
	return true;
}
bool CTableCertificationRegRecord::selectDB(int id, certificationRegRecordInfoPtr& cerPtr, DB::ConnectInfo& dbconInfo)
{
	if (nullptr == dbconInfo.pDBConnect)
		return false;

	std::stringstream ssSql;
	ssSql << "select id,userID,loginName,accountName,surname,IDCard,PostTime, \
             ApprovalTime,ApprovalID,IsApproval,ApprovalReason "
		<< " from certification_register_record "
		<< " where  id =" << id;

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
		cerPtr->m_id			= dbRecordSet.GetInt(0);
		cerPtr->m_sUserId		= dbRecordSet.GetString(1);
		cerPtr->m_sLoginName	= dbRecordSet.GetString(2);
		cerPtr->m_sAccountName	= dbRecordSet.GetString(3);
		cerPtr->m_sSurName		= dbRecordSet.GetString(4);
		cerPtr->m_sIDCard		= dbRecordSet.GetString(5);
		cerPtr->m_sPostTime		= dbRecordSet.GetString(6);
		cerPtr->m_sApprovalTime = dbRecordSet.GetString(7);
		cerPtr->m_sApprovalID	= dbRecordSet.GetString(8);
		cerPtr->m_nIsApproval	= dbRecordSet.GetInt(9);
		cerPtr->m_sApprovalReason = dbRecordSet.GetString(10);
	}

	return true;
}

