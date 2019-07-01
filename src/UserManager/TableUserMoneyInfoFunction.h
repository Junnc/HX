#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableUserMoneyInfoFuntion
{
public:
	bool queryUserRelationShipAll(std::map<std::string, userMoneyInfoPtr>& usrMoneyCache, DB::ConnectInfo& dbconInfo);

	bool addUserMoneyInfo(userMoneyInfo& usrMoneyInfo, DB::ConnectInfo& dbconInfo);

	bool deleteUserMoneyInfo(std::string userID, DB::ConnectInfo& dbconInfo);
private:
	std::mutex mutex;
};
