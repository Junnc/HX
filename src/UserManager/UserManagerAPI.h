#pragma once
#include <string>
#include "UserAccountDeal.h"
#include <map>
#include "jsoncpp/json/json.h"
#include <memory>

using namespace std;

class CUserManageAPI
{
public:
	void CommandOperator(Json::Value& root,std::string& sessionUserID);

private:

};

