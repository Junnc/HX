#pragma once
#include <map>
#include <string>
#include "TableFeild_define.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"

class CRealNameCertifitionQuery
{
public:
	CRealNameCertifitionQuery(std::map<std::string, std::string>& root, std::string sessionUserID):
		m_info(root), m_sessionUserID(sessionUserID) {}

	void handle()
	{
		//std::string institutionID = m_info[InstitutionID];
		//std::string userID = m_info[usrID];
		//std::string startDate = m_info[PostTime];
		//std::string endDate = m_info[ApprovalTime];
		//int state = std::stoi(m_info[IsApproval]);

	}
private:
	std::map<std::string, std::string>& m_info;
	std::string m_sessionUserID;
};