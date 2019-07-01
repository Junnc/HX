#pragma once
#include "UserTableMsgStruct.h"
#include <map>
#include "ThreadPool.hpp"
#include "instance_shared_from_this.h"
#include "jsoncpp/json/json.h"
//#include "UserManagerAPI.h"
#include <memory>
#include "UserManagerSPI.h"


using namespace std;

class CCommandParseAndDeal :public CommonTools::instance_shared_from_this<CCommandParseAndDeal>
{
public:
	CCommandParseAndDeal() {}
	void CommandParse(Json::Value& root, std::string sessionUserID);
	bool init(int nTrreadNum = 0);


private:

	//user_identify_info
	/*void addUserIdentifyBank(std::string sessionUserID, std::map<string, string>& root);
	void addUserIdentifyTranslate(std::map<string, string>& root, userIdentify& usrIdentify,int nflag);
	void CertifitionRegRecTranslate(std::map<string, string>& root, certificationRegisterRecordInfo& cer);
	void addUserIdentifyAuthenticate(std::string sessionUserID, std::map<string, string>& root);*/

private:
	PUserManagerSPI m_pUserManagerSPI;
	ThreadPool m_cmdsPool;
};

