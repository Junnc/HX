#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableSystemSet
{
public:
	
	bool querySystemSetAll(std::map<std::string, SystemSetPtr>& cerMap, DB::ConnectInfo& dbconInfo);

	bool SelectSystemSet(std::string sKey ,SystemSet& sysSet, DB::ConnectInfo& dbconInfo);

private:
	std::mutex mutex;
};

