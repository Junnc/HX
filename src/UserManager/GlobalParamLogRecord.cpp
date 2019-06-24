#include "GlobalParamLogRecord.h"
#include "utility_fun.h"
#include "DBOperator.h"
#include "CacheUserAllInfo.h"
#include <iostream>
#include <string>


void GlobalParamsLogRecord::AccountManagerLogRecord(const std::string operatorType, LogInfoPtr logInfo, userInfosPtr accountInfo,userRelationShipPtr relationShip, int type, const std::string  userID)
{
	LogRecords logMsg;
	
	logMsg.m_sysModule = SysMoudle::Sys_ManagerCenter;
	logMsg.m_type = logInfo->m_type;
	logMsg.m_sysModuleName = "管理模块";
	logMsg.m_createDate = UtilityFun::getLocalDateInt();
	logMsg.m_createTime = UtilityFun::getLocalTimeInt();
	logMsg.m_newContent = operatorType;
	logMsg.m_userID = logInfo->m_userID;
	logMsg.m_userName = GetUserNameByUserID(logInfo->m_userID);
	logMsg.m_ip = logInfo->m_ip;
	logMsg.m_mac = logInfo->m_mac;

	if (nullptr == accountInfo|| nullptr == relationShip)
	{
		logMsg.m_operatorID = userID;
		logMsg.m_operatorName = GetOperatorName(OperatorObjType::OOT_ACCOUNT, userID);
		//HandLogRecord::Instance()->AddUserRecord(logMsgPtr);
		if (!CDBOpeartor::instance()->addLogRecord(logMsg) ||
			!CCacheUserAllInfo::instance()->addLogRecordCache(logMsg))
		{
			std::cout << "添加日志数据库失败" << std::endl;
		}
		return;
	}
	else
	{
		logMsg.m_operatorID = accountInfo->m_sUserID;
		logMsg.m_operatorName = GetOperatorName(OperatorObjType::OOT_ACCOUNT, accountInfo->m_sUserID);
	}
	switch (type)
	{
	case UsersType::USER_TRADER  :
	{
		logMsg.m_oldContent = "账户名:" + accountInfo->m_sAccountName + " 主:" + relationShip->sMainID + " 所属代理:" + relationShip->sInstitutionID
			+ " 保证金模板ID:" + relationShip->sMarginModuleID + " 手续费模板ID:" + relationShip->sFeemoduleID + " 风控模板ID:" + relationShip->sRiskModuleID;
		break;
	}
	case  UsersType::USER_RISK :
	case  UsersType::USER_MANAGER :
	{
		logMsg.m_oldContent = "账户名:" + accountInfo->m_sAccountName + " 权限模板ID:" + relationShip->sAuthrityModuleID;
		break;
	}
	case  UsersType::USER_INSTITUTION :
	{
		logMsg.m_oldContent = "账户名:" + accountInfo->m_sAccountName + " 主:" +std::to_string(accountInfo->m_nMainIDNum) + "个"
			+ " 子:" + std::to_string(accountInfo->m_nSumIDNum) + "个" + " 手续费模板ID:" + relationShip->sFeemoduleID + " 权限模板ID:" + relationShip->sAuthrityModuleID;
		break;
	}
	case  UsersType::USER_MONEYACC :
	{
		logMsg.m_oldContent = "账户名:" + accountInfo->m_sAccountName + " 柜台类型:" + std::to_string(accountInfo->m_nCounterType);
		break;
	}
	default:
		break;
	}

	if (!CDBOpeartor::instance()->addLogRecord(logMsg) ||
		!CCacheUserAllInfo::instance()->addLogRecordCache(logMsg))
	{
		std::cout << "添加日志数据库失败" << std::endl;
	}
}

void GlobalParamsLogRecord::MoudleNameLogRecord(const std::string operatorTypeconst, LogInfoPtr logInfo, const std::string  moudleID, const std::string  moudleName)
{
	LogRecords logMsg;

	logMsg.m_sysModule = SysMoudle::Sys_ManagerCenter;
	logMsg.m_sysModuleName = "管理模块";
	logMsg.m_createDate = UtilityFun::getLocalDateInt();
	logMsg.m_createTime = UtilityFun::getLocalTimeInt();
	logMsg.m_userID = logInfo->m_userID;
	logMsg.m_userName = GetUserNameByUserID(logInfo->m_userID);
	logMsg.m_ip = logInfo->m_ip;
	logMsg.m_mac = logInfo->m_mac;
	logMsg.m_type = logInfo->m_type;
	logMsg.m_operatorID = moudleID;
	logMsg.m_operatorName = GetOperatorName((OperatorObjType)logMsg.m_type, moudleID);
	logMsg.m_newContent = operatorTypeconst;
	logMsg.m_oldContent = "模板名称：" + moudleName;

	if (!CDBOpeartor::instance()->addLogRecord(logMsg) ||
		!CCacheUserAllInfo::instance()->addLogRecordCache(logMsg))
	{
		std::cout << "添加日志数据库失败" << std::endl;
	}
}

LogInfoPtr GlobalParamsLogRecord::GetLogInfo(PUserManagerSPI pUserManagerSPI, const std::string& sessionID, int type)
{
	LogInfoPtr logInfo = std::make_shared<LogInfo>();
	logInfo->m_userID	= pUserManagerSPI->OnGetUseIDBySessionID(sessionID);
	logInfo->m_ip		= pUserManagerSPI->OnGetIpBySessionID(sessionID);
	logInfo->m_mac		= pUserManagerSPI->OnGetMacBySessionID(sessionID);
	logInfo->m_type = type;
	return logInfo;
}

std::string GlobalParamsLogRecord::GetUserNameByUserID(const std::string userID)
{
	userInfos userInfo;
	if(CCacheUserAllInfo::instance()->selectUsersOne(userID, userInfo))
		return userInfo.m_sLoginName;

	return "";
}

std::string GlobalParamsLogRecord::GetOperatorName(OperatorObjType type, const std::string operatorID)
{
	switch (type)
	{
	case OOT_ACCOUNT:
	{
		userInfos operatorInfo;
		if (CCacheUserAllInfo::instance()->selectUsersOne(operatorID, operatorInfo))
		{
			return operatorInfo.m_sLoginName;
		}
		return "";
	
	}

	case OOT_AGENT_FEEMODULE:
	{
		///根据用户查询代理手续费模板
		/*TableInstitutionModuleInfoPtr moduleInfo;
		CDBBussInstitutionFee::instance()->SelectFeeModuleInfo(operatorID, moduleInfo);

		if (nullptr != moduleInfo)
		{
			return moduleInfo->m_feeModuleName;
		}*/

		return "";
	}

	case OOT_CHILD_FEEMODULE:
	{
		///根据用户查询代理手续费模板
		/*TableFeeModuleInfoPtr moduleInfo;
		CDBBussFee::instance()->SelectFeeModuleInfoByFeeModuleID(operatorID, moduleInfo);

		if (nullptr != moduleInfo)
		{
			return moduleInfo->m_feeModuleName;
		}
		*/

		return "";
	}

	case OOT_MARGINMODULE:
	{

		/*TableMarginModuleInfoPtr moduleInfo;
		CDBBussMargin::instance()->QryMarginModuleByMarginID(operatorID, moduleInfo);

		if (nullptr != moduleInfo)
		{
			return moduleInfo->m_marginModuleName;
		}

		*/
		return "";
	}
	case OOT_RISKMOUDLE:
	{
		/*TableRiskModuleInfoPtr operatorInfo;
		CDBBussRiskInfo::instance()->SelectRiskModuleInfo(operatorID, operatorInfo);
		if (nullptr != operatorInfo)
		{
			return operatorInfo->m_riskModuleName;
		}

		*/
		return "";
	}

	case OOT_AUTHRITYMODULE:
	{
		/*TableAuthorityRolesPtr operatorInfo;
		CDBBussAuthority::instance()->SelectAuthorityRolesByRolesID(operatorID, operatorInfo);

		if (nullptr != operatorInfo)
		{
			return operatorInfo->m_rolesName;
		}
		*/
		return "";
	}

	default:
		break;
	}
	return "";
}

