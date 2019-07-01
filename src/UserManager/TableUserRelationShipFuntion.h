#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableUserRelationShipFuntion
{
public:
	bool queryUserRelationShipAll(std::map<std::string, userRelationShipPtr>& usrShip, DB::ConnectInfo& dbconInfo);

	bool addUserAndRelationShip(userRelationShip& userShip, DB::ConnectInfo& dbconInfo);

	bool updateChildAccount(userRelationShip& userShip, DB::ConnectInfo& dbconInfo);

	bool deleteUserRelationShip(std::string userID, DB::ConnectInfo& dbconInfo);
private:
	std::mutex mutex;
};
