#pragma once
#include <string>
#include <map>
#include "jsoncpp/json/json.h"
#include <memory>
#include "UserTableMsgStruct.h"
#include <iostream>


class CUserManagerSPI
{
public:
	//===================================  网络模块  ===============================================//
	// 根据sessionID找到userID
	virtual std::string OnGetUseIDBySessionID(const std::string& sessionID) { return ""; }
	// 根据sessionID找到ip
	virtual std::string OnGetIpBySessionID(const std::string& sessionID) { return ""; }
	// 根据sessionID找到mac
	virtual std::string OnGetMacBySessionID(const std::string& sessionID) { return ""; }

	// 增加子账户 
	virtual void OnAddChildAccount(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 子账户推送
	virtual void OnAddChildAccPush(int errorCode, const std::string& errmsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 查询子账户
	virtual void OnQryChildAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 删除子账户
	virtual void OnDelChildAccount(int errorCode, const std::string& errmsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// 修改子账户 
	virtual void OnUpdateChildAccount(int errorCode, const std::string& errmsg, const std::string& oldRiskModuleID, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 查询主账户
	virtual void OnQryMainAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 增加主账户
	virtual void OnAddMainAccount(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 主账户推送
	virtual void OnAddMainAccPush(int errorCode, const std::string& errMsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 修改主账户 
	virtual void OnUpdateMainAccount(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 删除主账户 
	virtual void OnDelMainAccount(int errorCode, const std::string& errMsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// 查询管理员
	virtual void OnQryManagerAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 增加管理员
	virtual void OnAddManagerAccount(int errorCode, const std::string& errmsg, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 修改管理员
	virtual void OnUpdateManagerAccount(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 删除管理员
	virtual void OnDelManagerAccount(int errorCode, const std::string& errmsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// 查询下级代理
	virtual void OnQryChildAgent(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 增加下级代理
	virtual void OnAddChildAgent(int errorCode, const std::string& userID, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 修改下级代理
	virtual void OnUpdateChildAgent(int errorCode, userInfos uInfo, userRelationShip tableInfo, const std::string& sessionID) {}

	// 删除下级代理
	virtual void OnDelChildAgent(int errorCode, const std::string& errMsg, const std::string& userID, const std::string& institutionID, const std::string& sessionID) {}

	// 绑定银行卡
	virtual void OnBankCardBind(int errorCode, const std::string& errMsg, userIdentifyPtr& userIdentifyInfo, const std::string& sessionID) {}

	// 实名认证响应
	virtual void OnRealNameCertification(int errorCode, const std::string& errMsg, certificationRegRecordInfoPtr tableInfo, int isIdentify, const std::string& sessionID) {}

	// 实名认证审核通过推送消息
	virtual void OnRealNameCertificationSent(int errorCode, const std::string& errMsg, certificationRegRecordInfoPtr& tableInfo, const std::string& sessionID) {}

	// 实名认证执行
	virtual void OnRealNameCertificationExe(int errorCode, const std::string& errMsg, int id, int state, const std::string& apprReson, const std::string& apprName, const std::string& sessionID) {}

	// 查询所有代理
	virtual void OnQryAllChildAgent(int errorCode, const std::string& errMsg, UserAndRelationShipMap& institutionID, const std::string& sessionID) {}

	// 查询代理商子账户
	virtual void OnQryAllChildAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 查询代理商主账户
	virtual void OnQryAllMainAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 查询代理商管理员
	virtual void OnQryAllManagerAccount(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	// 查询下级代理
	virtual void OnQryNextAllChildAgent(int errorCode, UserAndRelationShipMap& tableInfos, const std::string& sessionID) {}

	//反馈用户权限
	virtual void OnConnectAhturityLegitimacyInfo(std::string& content, std::string& sessionUserID) { std::cout << content.c_str() << std::endl; }

	//判断用户是否在线
	virtual bool IsUserOnline(std::string& userId) { return false; }

	//通过sessionID得到userID
	virtual std::string GetUserIDBySessionID(const std::string& sessionID) { return "hengbang1"; }

public:
	//=======================================交易模块============================================================//
	//添加一条佣金信息
	virtual bool AddCommissionInfo(std::string userID) { return true; }

	//查询账户是否有持仓
	virtual bool IsHoldPosition(std::string userID) { return false; }

	//查询账户是否有未生效订单
	virtual bool IsTodayNoEffectiveOrder(std::string userID) { return false; }

private:

};

typedef std::shared_ptr<CUserManagerSPI> PUserManagerSPI;
