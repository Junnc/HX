#ifndef COMMOM_GLOBAL_ENUM_H
#define COMMOM_GLOBAL_ENUM_H

///////////////////////////////////////////////////风控相关/////////////////////////////////////////////////////////
//行情涨跌幅
enum RiskUpDownOperatorType
{
	R_QuotationUpDown = 0x1,        // 涨跌幅
};

enum RiskUpDownOrderLimitType
{
	R_OrderOpenEnable = 0x0,        //允许开仓
	R_OrderOpenProhibit = 0x1,      //禁止开仓
};

enum RiskUpDownPositionAdjustType
{
	R_PositionNoAdjust = 0x0,       //不调整
	R_PositionFullClose = 0x1,      //全部清仓
};

enum RiskModuleType
{
	R_SetMoneyIndex = 0x1,          //资金指标设置
	R_SetTimingClose = 0x2,         //定时强平设置
	R_SetOverNightClose = 0x3,      //隔夜强平设置
	R_SetTradeProdouctClose = 0x4,  //交易品种及数量设置
};

//资金指标
enum RiskMoneyIndexType
{
	R_PriorityMoneyIndex = 0x1,        // 按优先资金(<)
	R_InferiorMoneyIndex = 0x2,        // 按劣后资金(<)
	R_RiskDegreeIndex = 0x3,           // 按风险度(>)
	R_TodayLossIndex = 0x4,            // 按当日亏损(>)
	R_DynamicEquityIndex = 0x5,        // 按动态权益(>)
	R_InferiorRiskDegreeIndex = 0x6,   // 按劣后风险度(>)
	R_SelfMoneyIndex = 0x7,            // 按自有资金(<)
};

//解除风控状态变更参数类型
enum RiskParaChangeType
{
	R_ParaByInOutMoney = 0x1,          // 子账号资金（出入金）变更,解除风控状态
	R_ParaByUserModuleChange = 0x2,    // 子账号切换风控模板,解除风控状态
	R_ParaByModuleSetChange = 0x3,     // 风控模板设置参数变更,解除风控状态
	R_ParaRiskDegreeIndex = 0x4,       // 风险度逐笔强平后，解除强平状态
};

//风控记录----触发风控类型
enum RiskMsgType
{
	R_GlobalUpDown = 0x1,             // 行情涨跌幅全局风控(系统级别)
	R_ProductTiming = 0x2,            // 品种定时强平风控(系统级别)
	R_ProductOverNightSys = 0x3,      // 品种隔夜强平风控(系统级别)
	R_ProductOverNightUser = 0x4,     // 品种隔夜强平风控(账号级别)
	R_ProductNumLimitSys = 0x5,       // 交易品种与数量限制风控(系统级别)
	R_ProductNumLimitUser = 0x6,      // 交易品种与数量限制风控(账号级别)
	R_MoneyIndexSys = 0x7,            // 资金指标风控(系统级别)
	R_MoneyIndexUser = 0x8,           // 资金指标风控(账号级别)
};

//触发风控类型
enum RiskTriggerType
{
	R_Warn = 0x1,                  // 预警
	R_Prohibit = 0x2,              // 禁开
	R_Close = 0x3,                 // 强平
};

///风控触发平仓处理类型
enum RiskTriggerCloseType
{
	RTCT_Normal = 0x0,                //正常单:(默认)初始状态
	RTCT_CommonTrigger = 0x1,		  //共通的：风控触发后撤单/平仓处理中
	RTCT_MoneyDegreeTrigger = 0x2,    //风控特例:资金风险度指标逐笔撤单/平仓处理中
	RTCT_NightDegreeTrigger = 0x3,    //风控特例:隔夜强平劣后风险度触发逐笔撤单/平仓处理中
};

// 账号属性
enum E_ACCOUNT_PROP
{
	EAP_Root = 0x0, 					// 根账号
	EAP_Trader = 0x1,					// 交易账号
	EAP_Risker = 0x2,					// 风控账号
	EAP_Manager = 0x3,					// 管理账号
	EAP_Agency = 0x4,					// 机构账号
	EAP_Funder = 0x5,					// 资金账号
};
// 账号状态
enum E_ACCOUNT_STATUS
{
	EAS_LOGIN = 0x0,					// 登录
	EAS_UNLOGIN = 0x1,					// 未登录
};
// 账号类型
enum E_ACCOUNT_TYPE
{
	EAT_Simulation = 0x0,				// 模拟账号
	EAT_Real = 0x1,						// 实盘账号
	EAT_SimuReal = 0x2,					// 模拟或实盘账号
};
//下单类型
enum OrderStyle
{
	LASTPRICE = 0x0,				    // 最新价
	BUYONEPRICE = 0x1,				    // 买一价
	SELLONEPRICE = 0x2,				    // 卖一价
	MARKETPRICE = 0x3,                  // 市价
	LIMITEPRICE = 0x4,                  // 限价
};
//条件单触发类型
enum YunTrrigerStyle
{
	Y_LASTPRICE = 0x0,				   // 最新价
	Y_BUYONEPRICE = 0x1,			   // 买一价
	Y_SELLONEPRICE = 0x2,			   // 卖一价
};
//开平类型
enum  OffsetType 
{
	OFFSET_OPEN = 0x1,					 // 开仓
	OFFSET_COVER = 0x2,				     // 平仓
	OFFSET_COVER_TODAY = 0x3,			 // 平今
};
//委托状态类型
enum  OrderStateType 
{
	ORDER_STATE_FAIL = 0x0,				    // 指令失败
	ORDER_STATE_ACCEPT = 0x1,				// 已受理,加入至服务器队列
	ORDER_STATE_QUEUED = 0x2,				// 已排队,加入至竞价/交易队列/提交至交易所
	ORDER_STATE_SUPPENDING = 0x3,			// 提交中
	ORDER_STATE_SUPPENDED = 0x4,			// 已挂起
	ORDER_STATE_FINISHED = 0x5,				// 完全成交
	ORDER_STATE_PARTFINISHED = 0x6,			// 部分成交
	ORDER_STATE_DELETEING = 0x7,			// 待撤消
	ORDER_STATE_PARTDELETED = 0x8,			// 部分撤单
	ORDER_STATE_DELETED = 0x9,				// 完全撤单
	
};
//触发类型
enum YunTriggerType
{
	Y_GREATEREQUAL = 0x0,				  //  大于等于
	Y_LESSEREQUAL = 0x1,				  //  小于等于
};
// 时间类型
enum TimeType
{
	T_CurrentDay = 0x0,                         // 当日有效
	T_PromptDay = 0x1,                          // 交割日钱有效
};
//条件单触发类型
enum  YunConditonOrderType
{
	Y_GREATEREQUALLASTPRICE = 0x0,           // 最新价 大于等于
	Y_LESSEQUALLASTPRICE = 0x1,              // 最新价 小于等于
	Y_GREATEREQUALBUYONEPRICE = 0x2,         // 买一价 大于等于
	Y_LESSEQUALBUYONEPRICE = 0x3,            // 买一价 小于等于
	Y_GREATEREQUALSELLONEPRICE = 0x4,	    //  卖一价 大于等于
	Y_LESSEQUALSELLONEPRICE = 0x5,		    //  卖一价 小于等于
};
//操作类型
enum YunOperatorType
{
	Y_ADDOPERATOR = 0x0,                   // 增加
	Y_UPDATEOPERATOR = 0x1,                // 修改
	Y_DELETEOPERATOR = 0x2,                // 删除
};
//条件单类型
enum YunConditionType
{
	Y_PRICE =0X0,                         //价格
	Y_TIME  =0X1,                         //时间
	Y_TIMEPRICE =0X2,                     //时间价格
};

// 条件单状态
enum ConditionStateType
{
	CONDITION_STATE_WORKING = 0x0,          // 新建(工作中)
	CONDITION_STATE_HADTRRIGER = 0x1,       // 已触发
	CONDITION_STATE_FAIL = 0x2,             // 失败
	CONDITION_STATE_DELETE = 0x3,           // 删除
	CONDITION_STATE_SETTLEDELETE = 0x4,     // 结算删除

};
//操作员类型
enum  OperatorTradeType 
{
	OPERATOR_TRADE_PC = 0x0,              // PC端客户自发起
	OPERATOR_TRADE_APP = 0x1,             // APP端客户自发起
	OPERATOR_TRADE_MC = 0x2,              // 后台监控端发起
	OPERATOR_TRADE_RC = 0x3,              // 后台风控端发起
	OPERATOR_CONDITION_TC = 0x4,          // 条件单模块发起
	OPERATOR_STOP_PROFIT_TC = 0x5,	      // 止盈止损端发起
	OPERATOR_RISK = 0x6,			      // 风控模块发起
	OPERATOR_POSTIONT = 0x7,			  // 修正持仓
	OPERATOR_ROUTINE_LIST = 0x8,          // 程序单
	OPERATOR_MODIFY_STATE = 0x9,          // 修正状态
	OPERATOR_AUTO_STOP_PC = 0xA,		  // PC端自动止盈止损发起
};
// 出入金方式
enum OIMM_Change_Type
{
	OIMM_In_WithCapotal = 0x0,				// 配资入金
	OIMM_Out_Withdrawals = 0x1,				// 出金提现
};

// 出入金变更方式
enum OIMM_MoneyChange_Type
{
	OIMM_Type_Invalid = 0,
	OIMM_Out_PostInferiorFunds,		// 减劣后资金
	OIMM_Out_AllocationFunds,		// 减配资额度
	OIMM_Out_RedReverse,		    // 红冲
	OIMM_In_PostInferiorFunds,      // 加劣后资金
	OIMM_In_AllocationFunds,        // 加配资额度
	OIMM_In_BluePatch,              // 蓝补
};

// 资金审核状态
enum E_APPLY_MONEY_STATUS
{
	EAMS_Check_Create = 0x0,				// 创建申请审核中
	EAMS_Check_Unpass = 0x1,				// 审核拒绝
	EAMS_Using = 0x2,						// 通过审核
};
// 资金变动方式
enum Money_Change_Type
{
	MC_In_Equipment = 0x1,                  // 加优先资金
	MC_EquipmentADD = 0x2,                  // 加配资额度
	MC_Out_RedSub = 0x3,		            // 资金红冲	
	MC_In_BlueAdd = 0x4,		            // 资金蓝补
	MC_Fee_Change = 0x5,                    // 变更手续费
	MC_Colse_Position = 0x6,                // 平仓盈亏
	MC_Settle_Profit = 0x7,                 // 结算亏损
	
		
};
//接口类型类型
enum  ApiTypeType 
{
	APIType_TYPE_CTP = 0x0,
	APIType_TYPE_ESUNNY = 0x1,
	APIType_TYPE_IB = 0x2,
	APIType_TYPE_SP = 0x3,
};
// 层级
enum  LevelType
{
	LType_Institution = 0x1,			// 机构
	LType_AgentOne = 0x2,				// 一级代理
	LType_AgentTwo = 0x3,				// 二级代理
	LType_AgentThree = 0x4,				// 三级代理
};
// 手续费计算方式
enum  FeeCalcType
{
	FCT_Fixed = 0x0,					// 固定
	FCT_Ratio = 0x1,					// 比例
};

//保证金计算方式
enum  MarginCalcType
{
	MCT_Fixed = 0x0,					// 固定
	MCT_Ratio = 0x1,					// 比例
};
//浮动止损标志
enum FloatLossFlag
{
	FLF_FloatLoss = 0x0,				// 浮动止损
	FLF_NoFloatLoss = 0x1,				// 无浮动止损
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
	OOT_CONDITIONORDERS =14,			// 条件单
	OOT_STOPPROFITLOSSORDERS = 15,	    // 止盈止损单
	OOT_ORDERINFO = 16,                 // 下单

};

///系统结算类型
enum SysSettleType
{
	Sys_SettleDate = 0x0,             //日结算
	Sys_SettleMonth = 0x1,            //月结算
	Sys_SettleByRange = 0x2,          //按时间段
};

///系统模块id
enum SysMoudle
{
	Sys_ManagerCenter,                 //管理模块
	Sys_TradeCenter,                   //交易模块
	Sys_RiskCenter,                    //风控模块
	Sys_YunCenter,                     //云条件单模块
};
#endif //COMMOM_GLOBAL_ENUM_H
