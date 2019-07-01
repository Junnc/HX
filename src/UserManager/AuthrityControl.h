#pragma once
//#include "instance.h"
#include "instance_shared_from_this.h"
#include "UserManagerSPI.h"
#include <map>


class CAuthrityControl : public CommonTools::instance_shared_from_this<CAuthrityControl>
{
public:
	int Init();

	////////////////////// 账户对应连接是否合法//////////////////////
	// 账户编号是否是连接本身
	bool IsUserIDConnectNormal(const std::string& userID, const std::string& sessionID);
	// 账户名称是否是连接本身
	bool IsLoginNameConnectNormal(const std::string& loginNames, const std::string& sessionID);
	// 代理账户是否是所属代理连接
	bool IsAgentIDConnectNormal(const std::string& institutionID, const std::string& sessionID, PUserManagerSPI pSPI);
	// 代理账户是否是所属代理连接
	bool IsAgentNameConnectNormal(const std::string& loginNames, const std::string& sessionID);
	// 非代理账户是否是所属代理连接
	bool IsChildAccIDConnectNormal(const std::string& childAccID, const std::string& sessionID, PUserManagerSPI pSPI);
	// 代理手续费模板所属代理连接
	bool IsAgentFeeIDConnectNormal(const std::string& feeMudoleID, const std::string& sessionID);
	// 权限模板所属代理连接
	bool IsAuthrityRoleIDConnectNormal(const std::string& rolesID, const std::string& sessionID);
	// 佣金审核所属连接
	bool IsCommissionApprovalConnectNormal(int serialNumber, const std::string& sessionID);
	// 是否为超级代理连接
	bool IsSuperConnect(const std::string& sessionID);
	// 自选合约所属连接
	bool IsOptionContractConnectNormal(const std::string& serialNumber, const std::string& sessionID);
	// 是否为本级以及下级机构的风控员操作子账户
	bool IsRiskConnectNormal(const std::string& userID, const std::string& sessionID);

	// 账户权限是否存在
	bool IsAuthrityExist(const std::string& userID, int cmdCode);

	/*bool IsUserOnline(std::string& userId);*/

private:
	std::map<int, int> m_cmdCodeTofunIDMap;

};
