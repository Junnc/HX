#pragma once
#include <string>
#include <memory>
#include <map>
#include <mutex>

#define USERMANAGE_API  __declspec(dllexport)
typedef std::unique_lock<std::mutex>		ReadLock;
typedef std::unique_lock<std::mutex>		WriteLock;

using namespace std;
enum UsersType
{
	USER_SUPER,
	USER_TRADER=1,
	USER_RISK,
	USER_MANAGER,
	USER_INSTITUTION,
	USER_MONEYACC
};

// 层级
enum  LevelType
{
	LType_Institution = 0x1,			// 机构
	LType_AgentOne = 0x2,				// 一级代理
	LType_AgentTwo = 0x3,				// 二级代理
	LType_AgentThree = 0x4,				// 三级代理
};

//操作日志查询类型
enum OperatorLogQuery
{
	OLQ_OneManger = 0x0,				// 具体的管理员
	OLQ_OneRisker = 0x1,				// 具体的风控员
	OLQ_Keyword = 0x2,					// 关键字
	OLQ_Agen = 0x3,						// 代理商
	OLQ_Manager = 0x4,					// 管理员
	OLQ_Risker = 0x5,					// 风控员
	OLQ_Child = 0x6,					// 子账号
	OLQ_MarginTemplet = 0x7,			// 保证金模板
	OLQ_FeeTemplet = 0x8,				// 手续费模板
	OLQ_RiskTemplet = 0x9,				// 风控模板
	OLQ_OutInMoney = 0xA,				// 出入金
	OLQ_ExchangeRate = 0xB,				// 汇率
};

// 操作日志对象类型
enum OperatorObjType
{
	OOT_MAIN_ACC = 1,					// 主账户
	OOT_CHILD_ACC = 2,				    // 子账户
	OOT_MANAGER_ACC = 3,				// 管理员
	OOT_RISK_ACC = 4,				    // 风控员
	OOT_CHILD_AGENT = 5,			    // 下级代理
	OOT_AGETOPENMODULE = 6,             // 代理开户模板
	OOT_MARGINMODULE = 7,				// 保证金模板
	OOT_CHILD_FEEMODULE = 8,			// 子账户手续费
	OOT_RISKMOUDLE = 9,                 // 风控模板
	OOT_AGENT_FEEMODULE = 10,			// 代理手续费
	OOT_AUTHRITYMODULE = 11,			// 权限模板
	OOT_BUSINESS_VALUE = 12,			// 业务参数

	OOT_ACCOUNT = 13,					// 账户	
	OOT_CONDITIONORDERS = 14,			// 条件单
	OOT_STOPPROFITLOSSORDERS = 15,	    // 止盈止损单
	OOT_ORDERINFO = 16,                 // 下单

};

enum SysMoudle
{
	Sys_ManagerCenter,                 //管理模块
	Sys_TradeCenter,                   //交易模块
	Sys_RiskCenter,                    //风控模块
	Sys_YunCenter,                     //云条件单模块
};

enum BussinessType
{
	BUSSINESS_SROCK,
	BUSSINESS_FUTRUE
};

typedef struct userInfos_
{
	std::string  m_sUserID;

	//用户类型 1=交易员 2=风控员 3=管理员 4=机构 5=资金账户
	int		m_nUserType;

	//所属机构层次 1=super 2=一级代理 3=二级代理...
	int		m_nLevel;		

	std::string  m_sLoginName;
	
	std::string  m_sAccountName;
	
	std::string  m_sPassword;
	
	std::string  m_sPhone;
	
	std::string  m_sPoularizeLink;
	
	std::string  m_sAddress;
	
	//是否逻辑删除 0=正常 1=删除
	int		m_nIsLogicDel;		

	int		m_nRegisterDate;
	
	int     m_nRegisterTime;
	
	//主账户个数
	int     m_nMainIDNum;			
	
	//子账户个数
	int		m_nSumIDNum;			
	
	//柜台类型1=ctp 2=esunny 3=ib,4=sp 5=sub 6=cms 7=zd
	int		m_nCounterType;		

	//用户金融类型 1=股票，2=期货，3=股票&&期货
	int     m_nFinanceType;

	double  m_dTotalMoney;

	double  m_dFutureMoney;

	double  m_dStockMoney;

	userInfos_() :
		m_nUserType(0),
		m_nLevel(0),
		m_nIsLogicDel(0),
		m_nRegisterDate(0),
		m_nRegisterTime(0),
		m_nMainIDNum(0),
		m_nSumIDNum(0),
		m_nCounterType(0),
		m_nFinanceType(0),
		m_dTotalMoney(0.0),
		m_dFutureMoney(0.0),
		m_dStockMoney(0.0)
	{}
}userInfos;

typedef std::shared_ptr<userInfos>  userInfosPtr;

typedef struct userRelationShip_
{
	//用户ID
	std::string sUserID;

	//机构
	std::string sInstitutionID;

	//机构名称
	std::string sInstitutionName;

	//风控员
	std::string sMonitorID;

	//管理员
	std::string sManagerID;

	//主账户/实盘账户
	std::string sMainID;

	//保证金模板
	std::string sMarginModuleID;

	//手续费模板
	std::string sFeemoduleID;

	//风控模板
	std::string sRiskModuleID;

	//权限模板
	std::string sAuthrityModuleID;

	//机构风控模板权限
	std::string sRiskModuleAuthrityID;
}userRelationShip;

typedef std::shared_ptr<userRelationShip> userRelationShipPtr;

//定义存放users表  user_relation_ship表的map
typedef std::map<userInfosPtr, userRelationShipPtr>		UserAndRelationShipMap;  

typedef struct userIdentify_
{
	std::string m_sUserID;
	
	std::string m_sIDCard;
	
	std::string m_sBankName;
	
	std::string m_sBranchBank;

	std::string m_sBankCardNo;
	//真实姓名
	std::string m_sSurName;

	//是否实名认证 0=未认证  1=认证
	int	   m_nIsDentify;	

	userIdentify_() :
		m_nIsDentify(0) {}
}userIdentify;

typedef std::shared_ptr<userIdentify> userIdentifyPtr;

typedef struct userMoneyInfo_
{
	// 账户唯一标识
	std::string m_sUserID;

	// 用户保证金
	double m_dUserDeposit;

	// 配置额度
	double m_dEquipment;

	// 静态权益
	double m_dPreBalance;

	// 当前资金结余
	double m_dCurrentTotal;

	// 当日平仓盈亏
	double m_dTodayCloseProfit;

	// 当日手续费
	double m_dTodayFee;

	// 当日入金
	double m_dTodayInMoney;

	// 当日出金
	double m_dTodayOutMoney;

	// 历史盈亏总和
	double m_dHistoryProfit;

	// 历史手续费总和
	double m_dHistoryFee;

	// 历史出金总和
	double m_dHistoryOutMoney;

	// 历史入金总和
	double m_dHistoryInMoney;

	// 委托保证金，冻结保证金， 内部缓存用
	double m_dFrozenMargin;

	// 持仓保证金，占用保证金， 内部缓存用
	double m_dHoleMargin;

	// 浮动盈亏 ，内部缓存用
	double m_dFloatGainLoss;

	// 盯市盈亏 ，内部缓存用
	double m_dSettleGainLoss;

	// 动态权益 ，内部缓存用
	double m_dDynamic;

	// 自有资金 ，内部缓存用
	double m_dSelfMoney;

	// 可用资金 ，内部缓存用
	double m_dAvailableMoney;

	// 风险度 ，内部缓存用
	double m_dRiskDegree;

	// 冻结资金
	double m_dFrozenOutMoney;

	userMoneyInfo_()
		: m_dUserDeposit(0.0)
		, m_dEquipment(0.0)
		, m_dPreBalance(0.0)
		, m_dCurrentTotal(0.0)
		, m_dTodayCloseProfit(0.0)
		, m_dTodayFee(0.0)
		, m_dTodayInMoney(0.0)
		, m_dTodayOutMoney(0.0)
		, m_dHistoryProfit(0.0)
		, m_dHistoryFee(0.0)
		, m_dHistoryOutMoney(0.0)
		, m_dHistoryInMoney(0.0)
		, m_dFrozenMargin(0.0)
		, m_dHoleMargin(0.0)
		, m_dFloatGainLoss(0.0)
		, m_dSettleGainLoss(0.0)
		, m_dDynamic(0.0)
		, m_dSelfMoney(0.0)
		, m_dAvailableMoney(0.0)
		, m_dRiskDegree(0.0)
		, m_sUserID("")
		, m_dFrozenOutMoney(0.0)
	{}
}userMoneyInfo;

typedef std::shared_ptr<userMoneyInfo> userMoneyInfoPtr;


typedef struct certificationRegisterRecordInfo_ 
{
	int m_id;

	std::string m_sUserId;

	std::string m_sLoginName;

	std::string m_sAccountName;

	std::string m_sSurName;

	std::string m_sIDCard;

	std::string m_sPostTime;
	
	std::string m_sApprovalTime;

	std::string m_sApprovalID;

	int m_nIsApproval;

	std::string m_sApprovalReason;

}certificationRegisterRecordInfo;

typedef std::shared_ptr<certificationRegisterRecordInfo> certificationRegRecordInfoPtr;

typedef struct InstitutionMainidMap_
{
	// 主键
	std::string m_id;

	//	代理机构id
	std::string m_institutionID;

	// 主账户
	std::string m_mainID;

}InstitutionMainidMap;

typedef std::shared_ptr<InstitutionMainidMap> InstitutionMainidMapPtr;

typedef struct SystemSet_
{
	// 主键
	std::string m_sKey;

	//	
	std::string m_sValue;

	// 
	std::string m_sNote;

}SystemSet;

typedef std::shared_ptr<SystemSet> SystemSetPtr;

typedef struct LogRecords_
{
	// 主键
	int m_logID;

	// 操作者账户编号
	std::string m_userID;

	// 操作者账户名称
	std::string m_userName;

	// 操作对象账户编号
	std::string m_operatorID;

	// 操作对象账户名称
	std::string m_operatorName;

	// 创建日期
	int m_createDate;

	// 创建时间
	int m_createTime;

	// 
	std::string m_newContent;

	std::string m_oldContent;

	int m_sysModule;

	std::string m_mac;

	std::string m_ip;

	std::string m_sysModuleName;

	// 操作对象类型
	int m_type;

	LogRecords_()
		: m_logID(0)
		, m_sysModule(0)
		, m_type(0)
		, m_createDate(0)
		, m_createTime(0)
	{}

}LogRecords;

typedef std::shared_ptr<LogRecords> LogRecordsPtr;