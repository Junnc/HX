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
	// �˻�������־��¼
	void AccountManagerLogRecord(const std::string  operatorType, LogInfoPtr logInfo, userInfosPtr accountInfo, userRelationShipPtr relationShip, int type, const std::string  userID = "");
	// ģ��������־��¼
	void MoudleNameLogRecord(const std::string  operatorType, LogInfoPtr logInfo, const std::string  moudleID, const std::string  moudleName);
	// ��ȡ��־��Ϣ
	LogInfoPtr GetLogInfo(PUserManagerSPI pUserManagerSPI, const std::string& sessionID, int type = 0);

	//��ȡ�û���
	std::string GetUserNameByUserID(const std::string userID);
	//��ȡ��������
	std::string GetOperatorName(OperatorObjType type, const std::string operatorID);
};




