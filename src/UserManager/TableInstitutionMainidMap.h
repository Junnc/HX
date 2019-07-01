#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>
#include <string>

class CTableInstitutionMainidMap
{
public:
	bool deleteAccount(std::string institutionID, std::string mainID, DB::ConnectInfo& dbconInfo);

	bool queryInstitutionMainidMapAll(std::map <std::string , InstitutionMainidMapPtr> & insMap, DB::ConnectInfo& dbconInfo);
	
private:
	std::mutex mutex;
};