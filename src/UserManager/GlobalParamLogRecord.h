#pragma once
#include"instance_shared_from_this.h"
#include"UserTableMsgStruct.h"
#include "UserManagerAPI.h"

typedef struct LogInfo_
{
	std::string		 m_userID;
	std::string		 m_mac;
	std::string		 m_ip;
	int				 m_type;

	LogInfo_(int type = 0)
		:m_type(type)
	{

	}
} LogInfo;

typedef std::shared_ptr<LogInfo>  LogInfoPtr;

class GlobalParamsLogRecord
	:public CommonTools::instance_shared_from_this<GlobalParamsLogRecord>
{
public:
	// 账户管理日志记录
	void AccountManagerLogRecord(const std::string  operatorType, LogInfoPtr logInfo, userInfosPtr accountInfo, userRelationShipPtr relationShip, int type, const std::string  userID = "");
	// 模板名称日志记录
	void MoudleNameLogRecord(const std::string  operatorType, LogInfoPtr logInfo, const std::string  moudleID, const std::string  moudleName);
	// 获取日志信息
	LogInfoPtr GetLogInfo(PUserManagerSPI pUserManagerSPI, const std::string& sessionID, int type = 0);

	//获取用户名
	std::string GetUserNameByUserID(const std::string userID);
	//获取操作对象
	std::string GetOperatorName(OperatorObjType type, const std::string operatorID);
};




