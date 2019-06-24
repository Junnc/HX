#include "UserManagerAPI.h"
#include "UserManageCenter.h"


void CUserManageAPI::CommandOperator(Json::Value& root,std::string& sessionUserID)
{
	CCommandParseAndDeal::instance()->CommandParse(root, sessionUserID);
}