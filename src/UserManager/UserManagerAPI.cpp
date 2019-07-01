#include "UserManagerAPI.h"
#include "UserManageCenter.h"
#include "PrintLogMessage.h"


void CUserManageAPI::CommandOperator(Json::Value& root,std::string& sessionUserID)
{
	Json::FastWriter fwt;
	std::string smsg = fwt.write(root);
	smsg.replace(smsg.find("\n"), 1, "");
	CPrintLogMessage plm(smsg,LogType::LOG_INFO,"[CUserManageAPI]");
	CCommandParseAndDeal::instance()->CommandParse(root, sessionUserID);
}