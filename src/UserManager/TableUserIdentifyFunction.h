#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableUserIdentifyFunction
{
public:
	bool addBankToUserIdentifyTableFunction(const userIdentify& user, DB::ConnectInfo& dbconInfo);

	bool queryAllUserIdentifyTableFunction(std::map<std::string, userIdentifyPtr>& userIdenfyMap, DB::ConnectInfo& dbconInfo);
	
	bool addAuthenticateToUserIdentifyTableFunction(const userIdentify& user, DB::ConnectInfo& dbconInfo);

	bool updateIndentifyState(std::string userID, int state, DB::ConnectInfo& dbconInfo);

	bool updateSurNameInfo(const userIdentify& user, DB::ConnectInfo& dbconInfo);

	bool addIdentifyInfo(const userIdentify& user, DB::ConnectInfo& dbconInfo);
private:
	std::mutex mutex;

};