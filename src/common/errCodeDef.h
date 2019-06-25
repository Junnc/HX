/*
* Date  :
* Desc  : 全局错误码定义,系统中所有错误码应在此定义
* Desc  : 错码应该按功能进行分类，每一个类别应该有255个(从00-FF)
*/
#ifndef ERR_CODE_DEF_H_
#define ERR_CODE_DEF_H_
#define RISK_MSG_LEN   256

// 没有错误
#define ERR_NOERROR								0x0000

/***********************①数据库模块相关错误 [0x10100-0x101FF]**************/
#define ERR_DB					                0x10100
// 初始化数据连接错误
#define ERR_DB_INITCONNFAIL					    ERR_DB + 0x1
// 建立数据库连接错误
#define ERR_DB_CREATECONNFAIL					ERR_DB + 0x2
// 设置数据库连接字符集错误
#define ERR_DB_SETCHASETFAIL					ERR_DB + 0x3
// 数据库连接错误
#define ERR_DB_CONNFAIL							ERR_DB + 0x4
// 操作数据库失败
#define ERR_DB_OPERATOR							ERR_DB + 0x5

/***********************②网络模块发送相关错误 [0x10200-0x102FF]*************/
#define ERR_NET							        0x10200
// 网络连接失败
#define ERR_NET_FAIL							ERR_NET + 0x1
// 网络连接被关闭
#define ERR_NET_CLOSE							ERR_NET + 0x2

/***********************③合约、品种相关错误 [0x10300-0x103FF] *************/
#define ERR_CP							        0x10300
// 合约不存在
#define ERR_CP_CONTRACT_NOTEXIST			    ERR_CP + 0x1
// 合约已存在
#define ERR_CP_CONTRACT_ALREADYEXIST			ERR_CP + 0x2
// 合约处于关市状态
#define ERR_CP_CONTRACT_NOTRADETIME			    ERR_CP + 0x3
// 合约到达或超过最后交割日，禁止下单
#define ERR_CP_CONTRACT_DEADLINE			    ERR_CP + 0x4
// 品种信息有误
#define ERR_PRODUCT_INFO			            ERR_CP + 0x5
// 品种不存在
#define ERR_PRODUCT_NOTEXIST			        ERR_CP + 0x6
// 品种已存在 
#define ERR_PRODUCT_ALREADYEXIST			    ERR_CP + 0x7
// 品种所允许交易的合约数超限
#define ERR_FORCE_CLOSETIME_FORBID_ORDER        ERR_CP + 0x8
// 超过当日可交易品种数
#define ERR_PRODUCT_NUM_LIMIT                   ERR_CP + 0x9
// 品种单次开仓手数限制
#define ERR_PRODUCT_SINGLE_OPEN_LIMIT           ERR_CP + 0xA
// 品种单日开仓手数限制
#define ERR_PRODUCT_OPEN_LIMIT                  ERR_CP + 0xB
// 品种总持仓手数限制
#define ERR_PRODUCT_POSITION_LIMIT              ERR_CP + 0xC
// 品种净持仓手数限制
#define ERR_PRODUCT_NET_POSITION_LIMIT          ERR_CP + 0xD
// 该品种到达强平时间，禁止开仓
#define ERR_PRODUCT_FORCE_TRADE_TIME            ERR_CP + 0xE
// 该品种无交易权限
#define ERR_PRODUCT_CANNOT_TRADE				ERR_CP + 0xF
// 该品种不在交易时间内
#define ERR_PRODUCT_NOTIME_TRADED				ERR_CP + 0x10
// 该品种在交易所处于节假日休市中，无交易权限
#define ERR_PRODUCT_HOLIDAY_LIMIT				ERR_CP + 0x11
// 该合约无交易权限
#define ERR_CONTRACT_CANNOT_TRADE				ERR_CP + 0x12

/***********************④行情相关错误  [0x10400-0x104FF]*******************/
#define ERR_QUOT 						        0x10400

/***********************⑤账号与权限等相关错误 [0x10500-0x105FF]************/
#define ERR_USER								0x10500
// 无权限
#define ERR_USER_NOPERMISSION                   ERR_USER + 0x1
// 不存在
#define ERR_USER_NOEXIST                        ERR_USER + 0x2
// 没有登录密码
#define ERR_NO_LOGIN_PASSWORD                   ERR_USER + 0x3
// 账户名已存在
#define ERR_ACCOUNT_ALREADY_EXIST               ERR_USER + 0x4
// 未登录
#define ERR_UN_LOGIN                            ERR_USER + 0x5
// 账号类型有误
#define ERR_ACCOUNT_TYPE                        ERR_USER + 0x6
// 账户名不能为中文
#define ERR_ACCOUNT_CHINESE                     ERR_USER + 0x7
// 存在下级代理
#define ERR_CHILDAGENT_EXIST					ERR_USER + 0x8
// 存在子账户
#define ERR_CHILDAACC_EXIST						ERR_USER + 0x9
// 绑定代理商
#define ERR_BINDAGENT                           ERR_USER + 0x10
// 旧密码错误
#define ERR_OLDPASSWROD                         ERR_USER + 0x11
// 代理商增加已达最大等级
#define ERR_AGENTADD_MAXLEVEL                   ERR_USER + 0x12
// 账户或者密码错误
#define ERR_LOGINNAME_PWD                       ERR_USER + 0x13
// 子账户存在持仓
#define ERR_CHILDPOSITION_EXIST                 ERR_USER + 0x14
// 子账户存在未生效的委托
#define ERR_CHILDORDER_EXIST                    ERR_USER + 0x15
// 主账户存在绑定的子账户
#define ERR_MAINIDTOCHILDACC_EXIST              ERR_USER + 0x16
// 子账户手续模板下已绑定子账号
#define ERR_FEEMODULE_BIND_CHILDACC             ERR_USER + 0x17
// 添加子账户已达最大值
#define ERR_ADDCHILDACC_MAX                     ERR_USER + 0x18
// 添加主账户已达最大值
#define ERR_ADDMAINACC_MAX                      ERR_USER + 0x19
// 模板已被使用
#define ERR_MARGINMODULE_USED                   ERR_USER + 0x20
// 机构下子账户不存在
#define ERR_INS_NOCHILDACC                      ERR_USER + 0x21
// 账户在线
#define ERR_ACC_ONLINE                          ERR_USER + 0x22
// 模板设置数值过大
#define ERR_MODULEVALUE_OVER                    ERR_USER + 0x23
// 子账户存在持仓
#define ERR_CHILDACC_POSITION_EXIST             ERR_USER + 0x24
// 子账户层级ID无效
#define ERR_CHILDACC_LEVEL_ID_NO_VAILD          ERR_USER + 0x25
// 请求参数有数，不是有效的账户ID
#define ERR_PARA_USER_ID_NO_VAILD               ERR_USER + 0x26
// md5校验失败
#define ERR_MD5CHECK_FAIL				        ERR_USER + 0x27
// 代理开户模板不存在
#define ERR_AGENTMODULE_NO_EXIST                ERR_USER + 0x28
// 已登录
#define ERR_ALREADY_LOGIN                       ERR_USER + 0x29
// 手机号与账户名不是绑定关系                   
#define ERR_TELNO_LOGINNAME_NOTBIND             ERR_USER + 0x30

/***********************⑥资金相关错误 [0x10600-0x106FF]*********************/
#define ERR_MONEY								0x10600
// 获取账户资金信息数据失败
#define ERR_MONEY_QRY_FAIL                      ERR_MONEY + 0x1
// 劣后资金不足
#define ERR_POSTINFFUND_LESS                    ERR_MONEY + 0x2
// 配置额度不足
#define ERR_ALLOCATIONFUND_LESS                 ERR_MONEY + 0x3
// 资金不足
#define ERR_LEFTMONEY_LESS                      ERR_MONEY + 0x4
// 自动审核参数不存在
#define AUTO_APPROVAL_VAL_NOEXIST               ERR_MONEY + 0x5
// 系统不审核
#define NOT_AUTO_APPROVAL                       ERR_MONEY + 0x6
// 入金订单不存在
#define INMONEY_ORDER_NOT_EXIST                 ERR_MONEY + 0x7
// 已经审核
#define INMONEY_ORDER_APPROVALED                ERR_MONEY + 0x8
// 未支付成功
#define NOT_PAY_SUCCESS                         ERR_MONEY + 0x9
// 资金为负数
#define MONEY_IS_MINUS                         ERR_MONEY + 0x10

/***********************⑦交易模块相关错误 [0x10700-0x107FF]***************/
#define ERR_TRADE							  0x10700
// 账号下单的委托参数错误
#define ERR_TRADE_ORDER_ARGERROR              ERR_TRADE + 0x1
// 账号的委托不存在
#define ERR_TRADE_ORDER_NOEXIST               ERR_TRADE + 0x2
// 可平手数不足
#define  ERR_TRADE_VOLUME_NOT_ENOUGH		  ERR_TRADE + 0x3
// 获取不到最新行情
#define  ERR_TRADE_NOT_LASTPRICE			  ERR_TRADE + 0x4
// 获取不到汇率
#define  ERR_TRADE_NOT_EXCHANGE_RATE		  ERR_TRADE + 0X5
// 可用资金不足
#define  ERR_TRADE_NOT_ENOUGH_MONEY			  ERR_TRADE + 0X6
// 未指派资金账号
#define  ERR_TRADE_NOT_MAIN_ACCOUNT			  ERR_TRADE + 0X7
// 发送到实盘失败
#define  ERR_TRADE_SEND_EXCHANGE_ERR		  ERR_TRADE + 0x8
// 撤单委托编号不存在
#define  ERR_TRADE_ORDER_DONOT_EXIST		  ERR_TRADE + 0x9
// 委托状态不可撤
#define  ERR_TRADE_CANNOT_BE_CANCELED		  ERR_TRADE + 0x10
// 平指定持仓错误
#define  ERR_TRADE_CLOSE_POSITION			  ERR_TRADE + 0x11

/***********************⑧风控模块相关错误 [0x10800-0x108FF] **************/
#define ERR_RISK									  0x10800
//已达到行情涨跌幅,允许开仓，仓位不调整
#define ERR_RISK_UPDOWN_OPEN						  ERR_RISK + 0x1
//已达到行情涨跌幅,禁止开仓
#define ERR_RISK_UPDOWN_LIMIT						  ERR_RISK + 0x2
//已达到行情涨跌幅,禁止开仓，清空仓位
#define ERR_RISK_UPDOWN_CLOSE_LIMIT					  ERR_RISK + 0x3
//已达到行情涨跌幅,禁止反向开仓，仓位不调整
#define ERR_RISK_UPDOWN_OPP_LIMIT					  ERR_RISK + 0x4
//已达到行情涨跌幅,禁止反向开仓，清空仓位
#define ERR_RISK_UPDOWN_OPP_CLOSE_LIMIT				  ERR_RISK + 0x5
//已达到单笔手数上限,开仓受限
#define ERR_RISK_SINGLE_VALUE_LIMIT					  ERR_RISK + 0x6
//已达到总持仓手数上限,开仓受限
#define ERR_RISK_TOTAL_VALUE_LIMIT					  ERR_RISK + 0x7
//已达到净持仓手数上限,开仓受限
#define ERR_RISK_NET_VALUE_LIMIT					  ERR_RISK + 0x8
//品种定时强平已触发
#define ERR_RISK_GLOBAL_PRODUCT_TRIGGER				  ERR_RISK + 0x9
//品种定时强平全局风控已解除
#define ERR_RISK_GLOBAL_PRODUCT_RELIEVE				  ERR_RISK + 0xA
//品种隔夜强平已触发
#define ERR_RISK_OVER_NIGHT_PRODUCT_TRIGGER			  ERR_RISK + 0xB
//品种隔夜强平全局风控已解除
#define ERR_RISK_OVER_NIGHT_PRODUCT_RELIEVE			  ERR_RISK + 0xC
//已达到账号品种单笔下单手数限制
#define ERR_RISK_POSITION_SINGLE_VALUE_LIMIT          ERR_RISK + 0xD
//已解除账号品种单笔下单手数限制
#define ERR_RISK_POSITION_SINGLE_VALUE_TRIGGER        ERR_RISK + 0xE
//已达到账号品种净持仓手数限制
#define ERR_RISK_NET_POSITION_VALUE_LIMIT		      ERR_RISK + 0xF
//已解除账号品种净持仓手数限制
#define ERR_RISK_NET_PRODUCT_POSITION_TRIGGER	      ERR_RISK + 0x10
//已达到账号品种总持仓手数限制
#define ERR_RISK_TOTAL_POSITION_LIMIT                 ERR_RISK + 0x11
//已解除账号品种总持仓手数限制
#define ERR_RISK_TOTAL_POSITION_TRIGGER               ERR_RISK + 0x12
//[资金风控指标][按优先资金]风控警告线已触发
#define ERR_RISK_MONEY_PRIORITY_WARNING				  ERR_RISK + 0x13
//[资金风控指标][按优先资金]风控警告线已解除
#define ERR_RISK_MONEY_PRIORITY_WARNING_RELIEVE		  ERR_RISK + 0x14
//[资金风控指标][按优先资金]风控禁开线已触发
#define ERR_RISK_MONEY_PRIORITY_FORBID				  ERR_RISK + 0x15
//[资金风控指标][按优先资金]风控禁开线已解除
#define ERR_RISK_MONEY_PRIORITY_FORBID_RELIEVE		  ERR_RISK + 0x16
//[资金风控指标][按优先资金]风控强平线已触发
#define ERR_RISK_MONEY_PRIORITY_CLOSE				  ERR_RISK + 0x17
//[资金风控指标][按优先资金]风控强平线已解除
#define ERR_RISK_MONEY_PRIORITY_CLOSE_RELIEVE		  ERR_RISK + 0x18
//[资金风控指标][按劣后资金]风控警告线已触发
#define ERR_RISK_MONEY_INFERIOR_WARNING				  ERR_RISK + 0x19
//[资金风控指标][按劣后资金]风控警告线已解除
#define ERR_RISK_MONEY_INFERIOR_WARNING_RELIEVE		  ERR_RISK + 0x1A
//[资金风控指标][按劣后资金]风控禁开线已触发
#define ERR_RISK_MONEY_INFERIOR_FORBID				  ERR_RISK + 0x1B
//[资金风控指标][按劣后资金]风控禁开线已解除
#define ERR_RISK_MONEY_INFERIOR_FORBID_RELIEVE		  ERR_RISK + 0x1C
//[资金风控指标][按劣后资金]风控强平线已触发
#define ERR_RISK_MONEY_INFERIOR_CLOSE				  ERR_RISK + 0x1D
//[资金风控指标][按劣后资金]风控强平线已解除
#define ERR_RISK_MONEY_INFERIOR_CLOSE_RELIEVE		  ERR_RISK + 0x1E
//[资金风控指标][按风险度]风控警告线已触发
#define ERR_RISK_MONEY_DEGREE_WARNING				  ERR_RISK + 0x1F
//[资金风控指标][按风险度]风控警告线已解除
#define ERR_RISK_MONEY_DEGREE_WARNING_RELIEVE		  ERR_RISK + 0x20
//[资金风控指标][按风险度]风控禁开线已触发
#define ERR_RISK_MONEY_DEGREE_FORBID				  ERR_RISK + 0x21
//[资金风控指标][按风险度]风控禁开线已解除
#define ERR_RISK_MONEY_DEGREE_FORBID_RELIEVE		  ERR_RISK + 0x22
//[资金风控指标][按风险度]风控强平线已触发
#define ERR_RISK_MONEY_DEGREE_CLOSE					  ERR_RISK + 0x23
//[资金风控指标][按风险度]风控强平线已解除
#define ERR_RISK_MONEY_DEGREE_CLOSE_RELIEVE		      ERR_RISK + 0x24
//[资金风控指标][按当日亏损]风控警告线已触发
#define ERR_RISK_MONEY_LOSS_WARNING				      ERR_RISK + 0x25
//[资金风控指标][按当日亏损]风控警告线已解除
#define ERR_RISK_MONEY_LOSS_WARNING_RELIEVE		      ERR_RISK + 0x26
//[资金风控指标][按当日亏损]风控禁开线已触发
#define ERR_RISK_MONEY_LOSS_FORBID				      ERR_RISK + 0x27
//[资金风控指标][按当日亏损]风控禁开线已解除
#define ERR_RISK_MONEY_LOSS_FORBID_RELIEVE		      ERR_RISK + 0x28
//[资金风控指标][按当日亏损]风控强平线已触发
#define ERR_RISK_MONEY_LOSS_CLOSE					  ERR_RISK + 0x29
//[资金风控指标][按当日亏损]风控强平线已解除
#define ERR_RISK_MONEY_LOSS_CLOSE_RELIEVE		      ERR_RISK + 0x2A
//[资金风控指标][按动态权益]风控警告线已触发
#define ERR_RISK_MONEY_DYNAMIC_WARNING				  ERR_RISK + 0x2B
//[资金风控指标][按动态权益]风控警告线已解除
#define ERR_RISK_MONEY_DYNAMIC_WARNING_RELIEVE		  ERR_RISK + 0x2C
//[资金风控指标][按动态权益]风控禁开线已触发
#define ERR_RISK_MONEY_DYNAMIC_FORBID				  ERR_RISK + 0x2D
//[资金风控指标][按动态权益]风控禁开线已解除
#define ERR_RISK_MONEY_DYNAMIC_FORBID_RELIEVE		  ERR_RISK + 0x2E
//[资金风控指标][按动态权益]风控强平线已触发
#define ERR_RISK_MONEY_DYNAMIC_CLOSE				  ERR_RISK + 0x2F
//[资金风控指标][按动态权益]风控强平线已解除
#define ERR_RISK_MONEY_DYNAMIC_CLOSE_RELIEVE		  ERR_RISK + 0x30
//请求参数有误，机构ID为空或不存在
#define ERR_RISK_INSTRUMENT_ID_NOEXIT	              ERR_RISK + 0x31
//风控模板名称已存在,请重新创建风控模板
#define ERR_RISK_MOUDLE_NAME_REPEAT	                  ERR_RISK + 0x32
//风控模板ID已存在,请重新创建风控模板
#define ERR_RISK_MOUDLE_ID_REPEAT	                  ERR_RISK + 0x33
//风控模板参数有误，该风控模板ID不存在
#define ERR_RISK_MOUDLE_ID_NOEXIT	                  ERR_RISK + 0x34
//风控模板下已绑定子账号，无法删除！
#define ERR_RISK_MOUDLE_ID_BIND_EXIT	              ERR_RISK + 0x35
//新创建的风控资金指标类型已存在,不能添加相同类型的风控资金指标
#define ERR_RISK_MONEY_INDEX_REPEAT	                  ERR_RISK + 0x36
//风控资金指标参数有误，该风控模板的风控资金指标类型不存在
#define ERR_RISK_MONEY_INDEX_NOEXIT	                  ERR_RISK + 0x37
//资金指标警告线风控值不能小于0
#define ERR_RISK_MONEY_INDEX_WARN_ZERO	              ERR_RISK + 0x38
//资金指标禁开线风控值不能小于0
#define ERR_RISK_MONEY_INDEX_FORBID_ZERO	          ERR_RISK + 0x39
//资金指标强平线风控值不能小于0
#define ERR_RISK_MONEY_INDEX_CLOSE_ZERO	              ERR_RISK + 0x3A
//请求参数有误,该风控模板下该品种已存在,不能重复添加该品种
#define ERR_RISK_PRODUCT_CODE_REPEAT	              ERR_RISK + 0x3B
//请求参数有误,该风控模板下该品种不存在
#define ERR_RISK_PRODUCT_CODE_NOEXIT	              ERR_RISK + 0x3C
//请求参数有误, 单笔最大下单手数不能小于0
#define ERR_RISK_OPEN_SINGLE_VOLUME_ZERO	          ERR_RISK + 0x3D
//请求参数有误, 最大总持仓手数不能小于0
#define ERR_RISK_TOTAL_VOLUME_ZERO	                  ERR_RISK + 0x3E
//请求参数有误, 最大净持仓手数不能小于0
#define ERR_RISK_NET_VOLUME_ZERO	                  ERR_RISK + 0x3F
//请求参数有误, 涨跌幅类型值不正确
#define ERR_RISK_NO_UPDOWN_TYPE	                      ERR_RISK + 0x40
//请求参数有误, 开仓权限、仓位调整的设置不合理,不存在此情况
#define ERR_RISK_UPDOWN_LIMIT_TYPE_ONE                ERR_RISK + 0x41
//请求参数有误, 涨跌幅值不能小于0
#define ERR_RISK_UPDOWN_NUM_ZERO                      ERR_RISK + 0x42
//请求参数有误, 强平时间的时间值无效
#define ERR_RISK_PRODUCT_TIME_NULL                    ERR_RISK + 0x43
//品种定时强平时间一与时间二的设置时间不能相同
#define ERR_RISK_PRODUCT_TIME_SAME                    ERR_RISK + 0x44
//请求参数有误,品种隔夜强平风险度指标值不能小于0
#define ERR_RISK_PRODUCT_NIGHT_TIME_ZERO              ERR_RISK + 0x45
//系统内部参数有误,未获取到风控模块的ptr
#define ERR_RISK_CENTER_NULL_PTR					  ERR_RISK + 0x46
//系统管理后台未给账户设置风控模板
#define ERR_RISK_MOUDLE_NOEXIT_BY_USER			      ERR_RISK + 0x47
//[资金风控指标][按自有资金(基础风控)]风控强平已触发
#define ERR_BASE_RISK_SELF_MONEY_CLOSE				  ERR_RISK + 0x48

/***********************⑨云条件单模块相关错误 [0x10900-0x109FF] **************/
#define ERR_YUN								          0x10900
//条件单信息不存在
#define ERR_CONDITION_NOEXIST						ERR_YUN +  0x1
//条件单信息已存在
#define ERR_CONDITION_ALREADYEXIST					ERR_YUN +  0x2
//止盈止损信息不存在
#define ERR_STOP_PROFIT_NOEXIST						ERR_YUN +  0x3
//止盈止损信息已存在
#define ERR_STOP_PROFIT_ALREADYEXIST				ERR_YUN +  0x4

#endif ///ERR_CODE_DEF_H_