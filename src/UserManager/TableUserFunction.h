#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>
#include <vector>

class CTableUserFunction
{
public:
	bool addUserTableFunction(const userInfos& user, DB::ConnectInfo& dbconInfo);

	bool queryAllUserTableFunction(std::map<std::string, userInfosPtr>& userInfoMap, DB::ConnectInfo& dbconInfo);

	bool updateChildUserInfo(const userInfos& usr, DB::ConnectInfo& dbconInfo);

	bool deleteAccount(std::string userID, DB::ConnectInfo& dbconInfo);

	bool updateMainAccount(const userInfos& usr, DB::ConnectInfo& dbconInfo);

	bool updateManagerUserInfo(const userInfos& usr, DB::ConnectInfo& dbconInfo);

	bool updateChildAgent(const userInfos& usr, DB::ConnectInfo& dbconInfo);

	bool SelectAllChildAgent(int maxLevel, const std::string sUserID, UserAndRelationShipMap& tableInfos, DB::ConnectInfo& dbconInfo);

	bool SelectUsersAndRelationShip(const std::string sUserID, userInfosPtr & usr, userRelationShipPtr & ship, DB::ConnectInfo & dbconInfo);

	bool SelectNextInsAcc(const std::string& institutionID, std::vector<std::string>& userIDs, DB::ConnectInfo& dbconInfo);


private:
	std::mutex mutex;

};