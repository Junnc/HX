#include "AuthrityControl.h"
#include "UserTableMsgStruct.h"
#include "CacheUserAllInfo.h"
#include <iostream>



bool CAuthrityControl::IsAgentIDConnectNormal(const std::string& institutionID, const std::string& sessionID)
{
	//通过sessionID得到userID  待实现
	std::string userIDTmp("hengbang1");

	userInfos usrIn;
	userRelationShip ship;
	if (!CCacheUserAllInfo::instance()->selectUsersOne(userIDTmp, usrIn) ||
		!CCacheUserAllInfo::instance()->selectUsersOne(userIDTmp, ship))
		return false;
	
	if (usrIn.m_nUserType == UsersType::USER_INSTITUTION)
		return CCacheUserAllInfo::instance()->IsBelongAgent(userIDTmp, institutionID);
	else if(usrIn.m_nUserType == UsersType::USER_MANAGER ||
			usrIn.m_nUserType == UsersType::USER_TRADER ||
			usrIn.m_nUserType == UsersType::USER_RISK)
		return CCacheUserAllInfo::instance()->IsBelongAgent(ship.sInstitutionID, institutionID);

	
	return false;
}

bool CAuthrityControl::IsChildAccIDConnectNormal(const std::string& childAccID, const std::string& sessionID)
{
	userRelationShip shipInfo;
	if (!CCacheUserAllInfo::instance()->selectUsersOne(childAccID, shipInfo))
		return false;

	return IsAgentIDConnectNormal(shipInfo.sInstitutionID, sessionID);
}

bool CAuthrityControl::IsUserOnline(std::string& userId)
{
	//由登录模块反馈

	return false;
}
