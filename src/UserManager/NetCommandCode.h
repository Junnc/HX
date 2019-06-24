#ifndef NET_COMMAND_CODE_H
#define NET_COMMAND_CODE_H

enum  E_CMD_MSG_TYPE :int
{
	ECMD_INIT_NULL = -1,                           // 无效

	//////////////////////////////登录相关/////////////////////////////////////////////////////
	LOGINCENTER = 1000,                            // 登录模块	
	LOGINOUT = 1001,                                 	

	///////////////////////////// 管理模块////////////////////////////////////////////////////////////
	MANAGERCENTER = 2000,                           // 管理模块
	CHILD_ACCOUNT_QUERY_REQ = 2001,				    // 子账户查询请求 
	CHILD_ACCOUNT_QUERY_RSP = 2002,					// 子账户查询应答 
	CHILD_ACCOUNT_ADD_REQ = 2003,					// 子账户增加请求 
	CHILD_ACCOUNT_ADD_RSP = 2004,					// 子账户增加应答 
	CHILD_ACCOUNT_UPDATE_REQ = 2005,				// 子账户更新请求 
	CHILD_ACCOUNT_UPDATE_RSP = 2006,				// 子账户更新应答 
	CHILD_ACCOUNT_DELETE_REQ = 2007,			    // 子账户删除请求 
	CHILD_ACCOUNT_DELETE_RSP = 2008,				// 子账户删除应答 
	MAIN_ACCOUNT_QUERY_REQ = 2009,					// 主账户查询请求 
	MAIN_ACCOUNT_QUERY_RSP = 2010,					// 主账户查询应答 
	MAIN_ACCOUNT_ADD_REQ = 2011,					// 主账户增加请求 
	MAIN_ACCOUNT_ADD_RSP = 2012,					// 主账户增加应答 
	MAIN_ACCOUNT_UPDATE_REQ = 2013,					// 主账户更新请求 
	MAIN_ACCOUNT_UPDATE_RSP = 2014,					// 主账户更新应答 
	MAIN_ACCOUNT_DELETE_REQ = 2015,					// 主账户删除请求 
	MAIN_ACCOUNT_DELETE_RSP = 2016,					// 主账户删除请求 
	MONITOR_QUERY_REQ = 2017,						// 风控员查询请求 
	MONITOR_QUERY_RSP = 2018,						// 风控员查询应答 
	MONITOR_ADD_REQ = 2019,						    // 风控员增加请求 
	MONITOR_ADD_RSP = 2020,						    // 风控员增加应答 
	MONITOR_UPDATE_REQ = 2021,					    // 风控员更新请求 
	MONITOR_UPDATE_RSP = 2022,					    // 风控员更新应答 
	MONITOR_DELETE_REQ = 2023,                      // 风控员删除请求 
	MONITOR_DELETE_RSP = 2024,                      // 风控员删除应答 
	MANAGER_QUERY_REQ = 2025,					    // 管理员查询请求 
	MANAGER_QUERY_RSP = 2026,					    // 管理员查询应答 
	MANAGER_ADD_REQ = 2027,						    // 管理员增加请求 
	MANAGER_ADD_RSP = 2028,						    // 管理员增加应答 
	MANAGER_UPDATE_REQ = 2029,					    // 管理员更新请求 
	MANAGER_UPDATE_RSP = 2030,					    // 管理员更新应答 
	MANAGER_DELETE_REQ = 2031,                      // 管理员删除请求 
	MANAGER_DELETE_RSP = 2032,                      // 管理员删除应答 
	LOWER_AGENT_QUERY_REQ = 2033,					// 代理商查询请求 
	LOWER_AGENT_QUERY_RSP = 2034,					// 代理商查询应答 
	LOWER_AGENT_ADD_REQ = 2035,						// 代理商增加请求 
	LOWER_AGENT_ADD_RSP = 2036,						// 代理商增加应答 
	LOWER_AGENT_UPDATE_REQ = 2037,					// 代理商更新请求 
	LOWER_AGENT_UPDATE_RSP = 2038,					// 代理商更新应答 
	LOWER_AGENT_DELETE_REQ = 2039,					// 代理商删除请求 
	LOWER_AGENT_DELETE_RSP = 2040,					// 代理商删除应答 
	ALLAGENTBYINSTID_QUERY_REQ = 2041,              // 机构的代理商查询请求 
	ALLAGENTBYINSTID_QUERY_RSP = 2042,              // 机构的代理商查询应答 
	ALLCHILDBYAGTID_QUERY_REQ = 2043,               // 代理商下所有子账户查询请求 
	ALLCHILDBYAGTID_QUERY_RSP = 2044,               // 代理商所有子账户查询应答 
	ALLMAINACTBYAGTID_QUERY_REQ = 2045,             // 代理商所有主账户查询请求 
	ALLMAINACTBYAGTID_QUERY_RSP = 2046,             // 代理商所有主账户查询应答 
	ALLMANAGERACTBYAGTID_QUERY_REQ = 2047,          // 代理商所有管理员查询请求 
	ALLMANAGERACTBYAGTID_QUERY_RSP = 2048,          // 代理商所有管理员查询应答 
	ALLRISKACTBYAGTID_QUERY_REQ = 2049,             // 代理商所有风控员查询请求 
	ALLRISKACTBYAGTID_QUERY_RSP = 2050,             // 代理商所有风控员查询应答 
	ALLAGENTBYAGTID_QUERY_REQ = 2051,               // 查询代理商所有下级代理商请求
	ALLAGENTBYAGTID_QUERY_RSP = 2052,               // 查询代理商所有下级代理商应答
	AGENT_TEMPLET_QUERY_REQ = 2053,					// 代理开户模板查询请求  (在线用户)
	AGENT_TEMPLET_QUERY_RSP = 2054,					// 代理开户模板查询应答 
	AGENT_TEMPLET_ADD_REQ = 2055,				    // 代理开户模板增加请求 
	AGENT_TEMPLET_ADD_RSP = 2056,					// 代理开户模板增加应答
	AGENT_TEMPLET_UPDATE_REQ = 2057,			    // 代理开户模板更新请求 
	AGENT_TEMPLET_UPDATE_RSP = 2058,			    // 代理开户模板更新应答 
	AGENT_TEMPLET_DELETE_REQ = 2059,				// 代理开户模板删除请求 
	AGENT_TEMPLET_DELETE_RSP = 2060,				// 代理开户模板删除应答 
	MARGIN_MDNAME_QUERY_REQ = 2061,					// 保证金模板名称查询请求 
	MARGIN_MDNAME_QUERY_RSP = 2062,					// 保证金模板名称查询应答 
	MARGIN_MDNAME_ADD_REQ = 2063,					// 保证金模板名称增加请求 
	MARGIN_MDNAME_ADD_RSP = 2064,					// 保证金模板名称应答
	MARGIN_MDNAME_UPDATE_REQ = 2065,				// 保证金模板名称更新请求 
	MARGIN_MDNAME_UPDATE_RSP = 2066,				// 保证金模板名称更新应答 
	MARGIN_MDNAME_DELETE_REQ = 2067,				// 保证金模板名称删除请求 
	MARGIN_MDNAME_DELETE_RSP = 2068,				// 保证金模板名称删除应答 
	MARGIN_TEMPLET_QUERY_REQ = 2069,				// 保证金模板信息查询请求 
	MARGIN_TEMPLET_QUERY_RSP = 2070,				// 保证金模板信息查询应答 
	MARGIN_TEMPLET_ADD_REQ = 2071,					// 保证金模板信息设置请求 
	MARGIN_TEMPLET_ADD_RSP = 2072,					// 保证金模板信息设置应答 
	MARGIN_TEMPLET_DELETE_REQ = 2073,				// 保证金模板信息删除请求 
	MARGIN_TEMPLET_DELETE_RSP = 2074,				// 保证金模板信息删除应答 
	CHILDFEE_MDNAME_QUERY_REQ = 2075,				// 子账户手续费模板名称查询请求 
	CHILDFEE_MDNAME_QUERY_RSP = 2076,				// 子账户手续费模板名称查询应答 
	CHILDFEE_MDNAME_ADD_REQ = 2077,					// 子账户手续费模板名称增加请求 
	CHILDFEE_MDNAME_ADD_RSP = 2078,					// 子账户手续费模板名称增加应答 
	CHILDFEE_MDNAME_UPDATE_REQ = 2079,				// 子账户手续费模板名称更新请求 
	CHILDFEE_MDNAME_UPDATE_RSP = 2080,				// 子账户手续费模板名称更新应答 
	CHILDFEE_MDNAME_DELETE_REQ = 2081,				// 子账户手续费模板名称删除请求 
	CHILDFEE_MDNAME_DELETE_RSP = 2082,				// 子账户手续费模板名称删除应答 
	CHILDFEE_TEMPLET_QUERY_REQ = 2083,				// 子账户手续费模板信息查询请求 
	CHILDFEE_TEMPLET_QUERY_RSP = 2084,				// 子账户手续费模板信息查询应答 
	CHILDFEE_TEMPLET_ADD_REQ = 2085,				// 子账户手续费模板设置请求 
	CHILDFEE_TEMPLET_ADD_RSP = 2086,				// 子账户手续费模板设置应答 
	CHILDFEE_TEMPLET_DELETE_REQ = 2087,			    // 子账户手续费模板信息删除请求  
	CHILDFEE_TEMPLET_DELETE_RSP = 2088,			    // 子账户手续费模板信息删除应答 
	AGENTFEE_MDNAME_QUERY_REQ = 2089,				// 代理手续费模板名称查询请求 
	AGENTFEE_MDNAME_QUERY_RSP = 2090,				// 代理手续费模板名称查询应答 
	AGENTFEE_MDNAME_ADD_REQ = 2091,					// 代理手续费模板名称增加请求 
	AGENTFEE_MDNAME_ADD_RSP = 2092,					// 代理手续费模板名称增加应答 
	AGENTFEE_MDNAME_UPDATE_REQ = 2093,				// 代理手续费模板名称修改请求 
	AGENTFEE_MDNAME_UPDATE_RSP = 2094,				// 代理手续费模板名称修改应答 
	AGENTFEE_MDNAME_DELETE_REQ = 2095,				// 代理手续费模板名称删除请求 
	AGENTFEE_MDNAME_DELETE_RSP = 2096,				// 代理手续费模板名称删除应答 
	AGENTFEE_TEMPLET_QUERY_REQ = 2097,				// 代理手续费模板信息查询请求 
	AGENTFEE_TEMPLET_QUERY_RSP = 2098,				// 代理手续费模板信息查询应答 
	AGENTFEE_TEMPLET_ADD_REQ = 2099,				// 代理手续费模板信息设置请求 
	AGENTFEE_TEMPLET_ADD_RSP = 2100,				// 代理手续费模板信息设置应答 
	AGENTFEE_TEMPLET_DELETE_REQ = 2101,			    // 代理手续费模板信息删除请求 
	AGENTFEE_TEMPLET_DELETE_RSP = 2102,			    // 代理手续费模板信息删除应答 
	AUTHORITY_MDNAME_QUERY_REQ = 2103,				// 权限模板名称查询请求 
	AUTHORITY_MDNAME_QUERY_RSP = 2104,				// 权限模板名称查询应答 
	AUTHORITY_MDNAME_ADD_REQ = 2105,				// 权限模板名称增加请求 
	AUTHORITY_MDNAME_ADD_RSP = 2106,				// 权限模板名称增加应答 
	AUTHORITY_MDNAME_UPDATE_REQ = 2107,				// 权限模板名称更新请求 
	AUTHORITY_MDNAME_UPDATE_RSP = 2108,				// 权限模板名称更新应答 
	AUTHORITY_MDNAME_DELETE_REQ = 2109,			    // 权限模板名称删除请求 
	AUTHORITY_MDNAME_DELETE_RSP = 2110,			    // 权限模板名称删除应答 
	AUTHORITY_TEMPLET_QUERY_REQ = 2111,				// 权限模板查询请求 
	AUTHORITY_TEMPLET_QUERY_RSP = 2112,				// 权限模板查询应答 
	AUTHORITY_TEMPLET_ADD_REQ = 2113,				// 权限模板增加应答 
	AUTHORITY_TEMPLET_ADD_RSP = 2114,				// 权限模板增加请求 
	AUTHORITY_TEMPLET_UPDATE_REQ = 2115,			// 权限模板更新应答 
	AUTHORITY_TEMPLET_UPDATE_RSP = 2116,			// 权限模板更新请求 
	AUTHORITY_TEMPLET_DELETE_REQ = 2117,			// 权限模板删除请求 
	AUTHORITY_TEMPLET_DELETE_RSP = 2118,			// 权限模板删除应答 
	RISK_MDNAME_QUERY_REQ = 2119,					// 风控模板名称查询请求
	RISK_MDNAME_QUERY_RSP = 2120,					// 风控模板名称查询应答 
	RISK_MDNAME_ADD_REQ = 2121,						// 风控模板名称增加请求
	RISK_MDNAME_ADD_RSP = 2122,						// 风控模板名称增加应答 
	RISK_MDNAME_UPDATE_REQ = 2123,					// 风控模板名称更新请求
	RISK_MDNAME_UPDATE_RSP = 2124,					// 风控模板名称更新应答 
	RISK_MDNAME_DELETE_REQ = 2125,					// 风控模板名称删除请求
	RISK_MDNAME_DELETE_RSP = 2126,					// 风控模板名称删除应答 
	RISK_TEMPLET_PRODUCT_QUERY_REQ = 2127,			// 风控交易品种以及数量查询请求 
	RISK_TEMPLET_PRODUCT_QUERY_RSP = 2128,			// 风控交易品种以及数量查询应答 
	RISK_TEMPLET_PRODUCT_ADD_REQ = 2129,			// 风控交易品种以及数量增加请求 
	RISK_TEMPLET_PRODUCT_ADD_RSP = 2130,			// 风控交易品种以及数量增加应答 
	RISK_TEMPLET_PRODUCT_UPDATE_REQ = 2131,			// 风控交易品种以及数量更新请求 
	RISK_TEMPLET_PRODUCT_UPDATE_RSP = 2132,			// 风控交易品种以及数量更新应答 
	RISK_TEMPLET_PRODUCT_DELETE_REQ = 2133,		    // 风控交易品种以及数量删除请求 
	RISK_TEMPLET_PRODUCT_DELETE_RSP = 2134,		    // 风控交易品种以及数量删除应答 
	RISK_TEMPLET_OVERNIGHT_QUERY_REQ = 2135,		// 风控隔夜强平设置查询请求 
	RISK_TEMPLET_OVERNIGHT_QUERY_RSP = 2136,		// 风控隔夜强平设置查询应答 
	RISK_TEMPLET_OVERNIGHT_ADD_REQ = 2137,			// 风控隔夜强平设置增加请求 
	RISK_TEMPLET_OVERNIGHT_ADD_RSP = 2138,			// 风控隔夜强平设置增加应答 
	RISK_TEMPLET_OVERNIGHT_UPDATE_REQ = 2139,		// 风控隔夜强平设置更新请求 
	RISK_TEMPLET_OVERNIGHT_UPDATE_RSP = 2140,		// 风控隔夜强平设置更新应答 
	RISK_TEMPLET_OVERNIGHT_DELETE_REQ = 2141,		// 风控隔夜强平设置删除请求 
	RISK_TEMPLET_OVERNIGHT_DELETE_RSP = 2142,		// 风控隔夜强平设置删除应答 
	RISK_TEMPLET_MONEYINDEX_QUERY_REQ = 2143,		// 风控资金指标信息查询请求 
	RISK_TEMPLET_MONEYINDEX_QUERY_RSP = 2144,		// 风控资金指标信息查询应答 
	RISK_TEMPLET_MONEYINDEX_ADD_REQ = 2145,			// 风控资金指标信息增加请求 
	RISK_TEMPLET_MONEYINDEX_ADD_RSP = 2146,			// 风控资金指标信息增加应答 
	RISK_TEMPLET_MONEYINDEX_UPDATE_REQ = 2147,		// 风控资金指标信息更新请求 
	RISK_TEMPLET_MONEYINDEX_UPDATE_RSP = 2148,		// 风控资金指标信息更新应答 
	RISK_TEMPLET_MONEYINDEX_DELETE_REQ = 2149,		// 风控资金指标信息删除请求 
	RISK_TEMPLET_MONEYINDEX_DELETE_RSP = 2150,		// 风控资金指标信息删除应答 
	RISK_TEMPLET_FORCECLOSE_QUERY_REQ = 2151,		// 风控定时强平信息查询请求 
	RISK_TEMPLET_FORCECLOSE_QUERY_RSP = 2152,		// 风控定时强平信息查询应答 
	RISK_TEMPLET_FORCECLOSE_ADD_REQ = 2153,			// 风控定时强平信息增加请求 
	RISK_TEMPLET_FORCECLOSE_ADD_RSP = 2154,			// 风控定时强平信息增加应答 
	RISK_TEMPLET_FORCECLOSE_UPDATE_REQ = 2155,		// 风控定时强平信息更新请求 
	RISK_TEMPLET_FORCECLOSE_UPDATE_RSP = 2156,		// 风控定时强平信息更新应答 
	RISK_TEMPLET_FORCECLOSE_DELETE_REQ = 2157,		// 风控定时强平信息删除请求 
	RISK_TEMPLET_FORCECLOSE_DELETE_RSP = 2158,		// 风控定时强平信息删除应答 
	RISK_RECORD_QUERY_REQ = 2159,                   // 风控记录查询请求 
	RISK_RECORD_QUERY_RSP = 2160,                   // 风控记录查询应答 
	CHILDUSER_INOUTMONE_QUERY_REQ = 2161,			// 子账户出入金查询请求 
	CHILDUSER_INOUTMONE_QUERY_RSP = 2162,			// 子账户出入金查询应答 
	CHILDUSER_INOUTMONEY_ADD_REQ = 2163,			// 子账户出入金增加请求 
	CHILDUSER_INOUTMONEY_ADD_RSP = 2164,			// 子账户出入金增加应答 
	CHILD_OUTMONEY_QUERY_REQ = 2165,				// 子账户（线上）入金审核查询请求 
	CHILD_OUTMONEY_QUERY_RSP = 2166,				// 子账户（线上）入金审核查询应答 
	CHILD_INTOMONEY_QUERY_REQ = 2167,				// 子账户出金审核查询请求 
	CHILD_INTOMONEY_QUERY_RSP = 2168,				// 子账户出金审核查询应答 
	CHILDUSER_INMONEY_APPROVAL_REQ = 2169,			// 子账户（线上）入金审核请求 
	CHILDUSER_INMONEY_APPROVAL_RSP = 2170,			// 子账户（线上）入金审核应答 
	CHILDUSER_OUTMONEY_APPROVAL_REQ = 2171,			// 子账户出金审核请求 
	CHILDUSER_OUTMONEY_APPROVAL_RSP = 2172,			// 子账户出金审核应答 
	OUTINMONEY_QUERY_REQ = 2173,		            // 出入金审核查询请求 
	OUTINMONEY_QUERY_RSP = 2174,		            // 出入金审核查询应答 
	COMMISSION_QUERY_REQ = 2175,					// 佣金查询请求 
	COMMISSION_QUERY_RSP = 2176,					// 佣金查询应答 
	COMMISSION_DETAIL_REQ = 2177,					// 佣金明细查询请求 
	COMMISSION_DETAIL_RSP = 2178,					// 佣金明细查询应答 
	ONLINE_USERE_QUERY_REQ = 2179,					// 在线用户查询请求 
	ONLINE_USERE_QUERY_RSP = 2180,					// 在线用户应答 
	OPERATOR_LOGE_QUERY_REQ = 2181,					// 操作日志查询请求 
	OPERATOR_LOGE_QUERY_RSP = 2182,					// 操作日志应答 
	OPERATOR_LOGE_ADD_REQ = 2183,					// 操作日志增加查询请求 
	OPERATOR_LOGE_ADD_RSP = 2184,					// 操作日志增加应答 
	QUOTATION_RISEUPE_QUERY_REQ = 2185,				// 行情涨幅查询请求 
	QUOTATION_RISEUPE_QUERY_RSP = 2186,				// 行情涨幅查询应答 
	QUOTATION_RISEUPE_ADD_REQ = 2187,				// 行情涨幅增加请求（预留：未使用） 
	QUOTATION_RISEUPE_ADD_RSP = 2188,				// 行情涨幅增加应答（预留：未使用） 
	QUOTATION_RISEUPE_UPDATE_REQ = 2189,			// 行情涨幅修改请求 
	QUOTATION_RISEUPE_UPDATE_RSP = 2190,			// 行情涨幅修改应答 
	EXCHANGERATE_QUERY_REQ = 2191,					// 汇率查询请求 
	EXCHANGERATE_QUERY_RSP = 2192,					// 汇率查询应答 
	EXCHANGERATE_ADD_REQ = 2193,					// 汇率增加请求 （预留：未使用） 
	EXCHANGERATE_ADD_RSP = 2194,					// 汇率增加应答 （预留：未使用） 
	EXCHANGERATE_UPDATE_REQ = 2195,				    // 汇率更新请求 
	EXCHANGERATE_UPDATE_RSP = 2196,				    // 汇率更新应答 
	CALCPARAMS_QUERY_REQ = 2197,					// 计算参数查询请求 
	CALCPARAMS_QUERY_RSP = 2198,					// 计算参数查询应答 
	CALCPARAMS_ADD_REQ = 2199,						// 计算参数增加请求 （预留：未使用） 
	CALCPARAMS_ADD_RSP = 2200,						// 计算参数增加应答 （预留：未使用） 
	CALCPARAMS_UPDATE_REQ = 2201,					// 计算参数更新请求 
	CALCPARAMS_UPDATE_RSP = 2202,					// 计算参数更新应答 
	BUSSNESS_QUERY_REQ = 2203,						// （权限模板）所有业务查询请求 
	BUSSNESS_QUERY_RSP = 2204,						// （权限模板）所有业务查询请求应答 
	SELFFUNCTION_QUERY_REQ = 2205,					// 自身功能查询请求 
	SELFFUNCTION_QUERY_RSP = 2206,					// 自身功能查询请求应答 
	PASSWORD_CHANGE_REQ = 2207,				        // 密码修改请求 
	PASSWORD_CHANGE_RSP = 2208,				        // 密码修改应答 
	POSITION_QUERY_REQ = 2209,					    // 子账户当前持仓查询请求 
	POSITION_QUERY_RSP = 2210,					    // 子账户当前持仓查询应答 
	POSITION_DETAIL_QUERY_REQ = 2211,				// 子账户当前持仓明细查询请求 
	POSITION_DETAIL_QUERY_RSP = 2212,				// 子账户当前持仓明细查询应答
	TODAYENTRUST_QUERY_REQ = 2213,					// 当日委托查询请求 
	TODAYENTRUST_QUERY_RSP = 2214,					// 当日委托查询应答 
	HISTORYENTRUST_QUERY_REQ = 2215,				// 历史委托查询请求 
	HISTORYENTRUST_QUERY_RSP = 2216,				// 历史委托查询应答 
	TRADE_QUERY_REQ = 2217,							// 当日成交查询请求 
	TRADE_QUERY_RSP = 2218,							// 当日成交查询应答 
	HISTORYTRADE_QUERY_REQ = 2219,					// 历史成交查询请求 
	HISTORYTRADE_QUERY_RSP = 2220,					// 历史成交查询应答  
	HISTORYPOSITION_QUERY_REQ = 2221,               // 历史持仓查询请求 
	HISTORYPOSITION_QUERY_RSP = 2222,               // 历史持仓查询应答 
	SETTLE_FUND_QUERY_REQ = 2223,					// 结算资金查询请求 
	SETTLE_FUND_QUERY_RSP = 2224,					// 结算资金查询应答 
	SETTLE_RECORD_QUERY_REQ = 2225,			        // 结算信息查询请求 
	SETTLE_RECORD_QUERY_RSP = 2226,			        // 结算信息查询应答 
	SETTLE_TRADE_RECORD_QUERY_REQ = 2227,			// 结算成交记录查询请求 （业务暂不单独提供） 
	SETTLE_TRADE_RECORD_QUERY_RSP = 2228,			// 结算成交记录查询应答 （业务暂不单独提供） 
	SETTLE_CLOSEP_DETAIL_QUERY_REQ = 2229,			// 结算平仓明细查询请求 （业务暂不单独提供） 
	SETTLE_CLOSEP_DETAIL_QUERY_RSP = 2230,			// 结算平仓明细查询应答 （业务暂不单独提供） 
	SETTLE_HOLDP_DETAIL_QUERY_REQ = 2231,			// 结算持仓明细查询请求 （业务暂不单独提供） 
	SETTLE_HOLDP_DETAIL_QUERY_RSP = 2232,			// 结算持仓明细查询应答 （业务暂不单独提供） 
	SETTLE_HOLD_POSITON_QUERY_REQ = 2233,			// 结算持仓汇总查询请求 （业务暂不单独提供） 
	SETTLE_HOLD_POSITION_QUERY_RSP = 2234,			// 结算持仓汇总查询应答 （业务暂不单独提供） 
	LOGIN_TRADE_REQ = 2235,							// 登录请求	
	LOGIN_TRADE_RSP = 2236,							// 登录回调	
	LOGIN_OUT_REQ_ = 2237,							// 登出请求
	EXCHANGE_QUERY_REQ = 2238,                      // 交易所查询请求
	EXCHANGE_QUERY_RSP = 2239,                      // 交易所查询应答
	PRODUCTINFO_QUERY_REQ = 2240,                   // 品种信息查询请求
	PRODUCTINFO_QUERY_RSP = 2241,                   // 品种信息查询应答
	CONTRACTINFO_QUERY_REQ = 2242,                  // 合约信息查询请求
	CONTRACTINFO_QUERY_RSP = 2243,                  // 合约信息查询应答
	CUSTOMCONTRACT_REQ = 2244,						// 自选合约查询请求	
	CUSTOMCONTRACT_RSP = 2245,						// 自选合约查询应答	
	CUSTOMCONTRACT_ADD_REQ = 2246,					// 自选合约新增请求
	CUSTOMCONTRACT_ADD_RSP = 2247,					// 自选合约新增应答
	CUSTOMCONTRACT_DEL_REQ = 2248,					// 自选合约删除请求	
	CUSTOMCONTRACT_DEL_RSP = 2249,					// 自选合约删除应答	
	ASSIGNMAINID_REQ = 2250,						// 指派主账号请求
	ASSIGNMAINID_RSP = 2251,						// 指派主账号应答
	CHILDINFOSENT_MSG = 2252,                       // 子账户信息推送
	MAINUSERINFOSENT_MSG = 2253,                    // 主账户信息推送
	APP_CUSTOMCONTRACT_DEL_REQ = 2254,				// app自选合约删除请求	
	APP_CUSTOMCONTRACT_DEL_RSP = 2255,				// app自选合约删除应答	
	LOGIN_OUT_REQ = 2256,							// 登出请求
	LOGIN_OUT_RSP = 2257,							// 登出回调
	FEEMODULEFILTER_REQ = 2258,					    // 手续费模板过滤请求
	FEEMODULEFILTER_RSP = 2259,						// 手续费模板过滤响应
	CHILDACC_MARGINDETAIL_QUERY_REQ = 2260,         // 子账户保证金详细信息请求
	CHILDACC_MARGINDETAIL_QUERY_RSP = 2261,         // 子账户保证金详细信息响应
	MARGINDETAIL_UPDATE_PUSH = 2262,                // 保证金详细信息更新推送
	ONLINE_REGISTER_ACC_REQ = 2263,					// 在线开户请求
	ONLINE_REGISTER_ACC_RSP = 2264,					// 在线开户响应
	ALL_MANAGER_QRY_REQ = 2265,					    // 所有管理员查询请求
	ALL_MANAGER_QRY_RSP = 2266,					    // 所有管理员查询响应
	FUND_NOW_QUERY_REQ = 2267,						// 账户当前资金查询请求 
	FUND_NOW_QUERY_RSP = 2268,						// 账户当前资金查询应答 
	AGENT_POPULARIZE_LINK_REQ = 2269,               // 代理推广请求
	AGENT_POPULARIZE_LINK_RSP = 2270,               // 代理推广响应
	EFFECTIVE_CONDITIONORDER_REQ = 2271,            // 有效条件单请求
	EFFECTIVE_CONDITIONORDER_RSP = 2272,            // 有效条件单响应
    HIS_CONDITIONORDER_REQ = 2273,                  // 历史条件单请求
	HIS_CONDITIONORDER_RSP = 2274,                  // 历史条件单响应
	EFFECTIVE_STOPLOSEORDER_REQ = 2275,             // 有效止盈止损单请求
	EFFECTIVE_STOPLOSEORDER_RSP = 2276,             // 有效止盈止损单响应
	HIS_STOPLOSEORDER_REQ = 2277,                   // 历史止盈止损单请求
	HIS_STOPLOSEORDER_RSP = 2278,                   // 历史止盈止损单响应
	RC_ALL_CHILDBYAGTID_QUERY_REQ = 2279,           // 风控代理下所有子账户查询请求 
	RC_ALL_CHILDBYAGTID_QUERY_RSP = 2280,           // 风控代理下所有子账户查询应答 
	PC_USER_SET_MONEY_INDEX_QRY_REQ = 2281,         // 子账户查询风控模板资金指标请求 
	PC_USER_SET_MONEY_INDEX_QRY_RSP = 2282,         // 子账户查询风控模板资金指标应答
    USER_SET_MONEY_INDEX_CHANGE_PUSH = 2283,        // 风控模板资金指标(按风险度、按劣后资金)变更主动推送客户端
	CONTRACT_WHITE_LIST_QRY_REQ = 2284,             // 合约白名单查询请求
	CONTRACT_WHITE_LIST_QRY_RSP = 2285,             // 合约白名单查询响应
	CONTRACT_WHITE_LIST_UPDATE_REQ = 2286,          // 合约白名单修改请求
	CONTRACT_WHITE_LIST_UPDATE_RSP = 2287,          // 合约白名单修改响应
	CHILDACCCONFIRM = 2288,                         // 账户密码校验
	CHILDACCCONFIRM_RSP = 2289,                     // 账户密码校验响应
	AGENTALLCHILDACC_REQ = 2290,					// 机构所有子账户查询请求（包括下下级）
	AGENTALLCHILDACC_RSP = 2291,					// 机构所有子账户查询响应（包括下下级）
	ORDER_DOWNLOAD_REQ = 2292,                      // 历史委托信息下载请求
	ORDER_DOWNLOAD_RSP = 2293,                      // 历史委托信息下载响应
	TRADE_DOWNLOAD_REQ = 2294,                      // 历史成交信息下载请求
	TRADE_DOWNLOAD_RSP = 2295,                      // 历史成交信息下载响应
	POSITION_DOWNLOAD_REQ = 2296,                   // 历史持仓信息下载请求
	POSITION_DOWNLOAD_RSP = 2297,                   // 历史持仓信息下载响应
	MONEY_DOWNLOAD_REQ = 2298,                      // 资金信息下载请求
	MONEY_DOWNLOAD_RSP = 2299,                      // 资金信息下载响应
	INOUTMONEY_DOWNLOAD_REQ = 2300,                 // 出入金信息下载请求
	INOUTMONEY_DOWNLOAD_RSP = 2301,                 // 出入金信息下载响应
	COMMISSION_DOWNLOAD_REQ = 2302,                 // 佣金信息下载请求
	COMMISSION_DOWNLOAD_RSP = 2303,                 // 佣金信息下载响应
	COMMISSIONDETAIL_DOWNLOAD_REQ = 2304,           // 佣金明细信息下载请求
	COMMISSIONDETAIL_DOWNLOAD_RSP = 2305,           // 佣金明细信息下载响应
	EFFCONDITIONORDER_DOWNLOAD_REQ = 2306,          // 有效条件单信息下载请求
	EFFCONDITIONORDER_DOWNLOAD_RSP = 2307,          // 有效条件单信息下载响应
	HISCONDITIONORDER_DOWNLOAD_REQ = 2308,          // 历史条件单信息下载请求
	HISCONDITIONORDER_DOWNLOAD_RSP = 2309,          // 历史条件单信息下载响应
	EFFSTOPLOSSORDER_DOWNLOAD_REQ = 2310,           // 有效止盈止损单信息下载请求
	EFFSTOPLOSSORDER_DOWNLOAD_RSP = 2311,           // 有效止盈止损单信息下载响应
	HISSTOPLOSSORDER_DOWNLOAD_REQ = 2312,           // 历史止盈止损单信息下载请求
	HISSTOPLOSSORDER_DOWNLOAD_RSP = 2313,           // 历史止盈止损单信息下载响应
	CHILD_INMONEY_ADD_REQ = 2314,					// 入金审核添加请求
	CHILD_INMONEY_ADD_RSP = 2315,					// 入金审核添加响应
	CHILD_OUTMONEY_ADD_REQ = 2316,					// 出金审核添加请求
	CHILD_OUTMONEY_ADD_RSP = 2317,					// 出金审核添加响应
	HTTP_SYS_EXCHANGERATE_QRY_REQ = 2318,			// http系统汇率查询请求
	HTTP_SYS_EXCHANGERATE_QRY_RSP = 2319,			// http系统汇率查询响应
	SYS_SETTLE_PRICE_QRY_REQ = 2320,				// 合约结算价查询请求
	SYS_SETTLE_PRICE_QRY_RSP = 2321,				// 合约结算价查询响应
	SYS_SETTLE_PRICE_QRESERVED_REQ = 2322,			// 合约结算价保存请求
	SYS_SETTLE_PRICE_QRESERVED_RSP = 2323,			// 合约结算价保存响应
	SYS_SETTLE_START_REQ = 2324,					// 开始结算请求
	SYS_SETTLE_START_RSP = 2325,					// 开始结算响应
	AUTO_APPROVAL_REQ = 2326,						// 自动审核请求
	AUTO_APPROVAL_RSP = 2327,						// 自动审核响应
	SYS_FINISH_SETTLE_RSP = 2328,					// 系统结算完状态推送
	CHILD_INMONEY_PROMPT_PUSH = 2329,				// 入金提示推送
	CHILD_OUTMONEY_PROMPT_PUSH = 2330,				// 出金提示推送
	SYS_RISK_TRIGGER_PUSH_RSP = 2331,				// 风控触发主动推送
	INS_ALL_ACCOUNT_QRY_REQ = 2332,				    // 机构所有账户查询请求
	INS_ALL_ACCOUNT_QRY_RSP = 2333,				    // 机构所有账户查询响应
    MAINUSERSTATUSSENT_MSG = 2334,                  // 主账户状态推送
	OPERATOR_ALL_QRY_REQ = 2335,				    // 所有操作对象查询请求
	OPERATOR_ALL_QRY_RSP = 2336,				    // 所有操作对象查询响应
	IN_MONEY_QRY_REQ = 2337,				        // 入金信息查询请求
	IN_MONEY_QRY_RSP = 2338,				        // 入金信息查询响应
	OUT_MONEY_QRY_REQ = 2339,				        // 出金信息查询请求
	OUT_MONEY_QRY_RSP = 2340,				        // 出金信息查询响应
	SWITCH_OWN_AGENT_REQ = 2341,				    // 子账户切换所属代理请求
	SWITCH_OWN_AGENT_RSP = 2342,				    // 子账户切换所属代理响应
	IN_MONEY_DOWNLOAD_REQ = 2343,				    // 入金信息下载请求
	IN_MONEY_DOWNLOAD_RSP = 2344,				    // 入金信息下载响应
	OUT_MONEY_DOWNLOAD_REQ = 2345,				    // 出金信息下载请求
	OUT_MONEY_DOWNLOAD_RSP = 2346,				    // 出金信息下载响应
	SWITCH_OWN_AGENT_PUSH = 2347,				    // 子账户切换所属代理推送
	HOME_PAGE_INFO_REQ = 2348,                      // 首页信息请求
	HOME_PAGE_INFO_RSP = 2349,                      // 首页信息响应
	BANK_CARD_BIND_REQ = 2350,                      // 银行卡绑定请求
	BANK_CARD_BIND_RSP = 2351,                      // 银行卡绑定响应
	REAL_NAME_IDENTIFY_REQ = 2352,                  // 实名认证请求
	REAL_NAME_IDENTIFY_RSP = 2353,                  // 实名认证响应
	COMMISSION_MONEY_INFO_REQ = 2354,               // 佣金金额信息查询请求
	COMMISSION_MONEY_INFO_RSP = 2355,               // 佣金金额信息查询响应
	COMMISSION_MONEY_CASH_REQ = 2356,               // 佣金提现申请请求
	COMMISSION_MONEY_CASH_RSP = 2357,               // 佣金提现申请响应
	DAILY_COMMISSION_MONEY_INFO_REQ = 2358,         // 每日佣金统计请求
	DAILY_COMMISSION_MONEY_INFO_RSP = 2359,         // 每日佣金统计响应
	COMMISSION_SURPLUS_QRY_REQ = 2360,              // 佣金结余查询请求
	COMMISSION_SURPLUS_QRY_RSP = 2361,              // 佣金结余查询响应
	COMMISSION_MONEY_CASH_INFO_REQ = 2362,          // 提现记录查询请求
	COMMISSION_MONEY_CASH_INFO_RSP = 2363,          // 提现记录查询响应
	COMMISSION_APPROVAL_QRY_REQ = 2364,             // 佣金审核查询请求
	COMMISSION_APPROVAL_QRY_RSP = 2365,             // 佣金审核查询响应
	COMMISSION_APPROVAL_HANDLE_REQ = 2366,          // 佣金审核处理请求
	COMMISSION_APPROVAL_HANDLE_RSP = 2367,          // 佣金审核处理响应
	CERTIFICATION_APPROVAL_QRY_REQ = 2368,          // 实名认证查询请求
	CERTIFICATION_APPROVAL_QRY_RSP = 2369,          // 实名认证查询响应
	CERTIFICATION_APPROVAL_HANDLE_REQ = 2370,       // 实名认证审核处理请求
	CERTIFICATION_APPROVAL_HANDLE_RSP = 2371,       // 实名认证审核处理响应
	COMMISSION_SURPLUS_DOWNLOAD_REQ = 2372,         // 佣金结余下载请求
	COMMISSION_SURPLUS_DOWNLOAD_RSP = 2373,         // 佣金结余下载响应
	COMMISSION__CASH_DOWNLOAD_REQ = 2374,           // 提现记录下载请求
	COMMISSION__CASH_DOWNLOAD_RSP = 2375,           // 提现记录下载响应 
	DAILY_COMMISSION_MONEY_DOWNLOAD_REQ = 2376,     // 每日佣金下载请求
	DAILY_COMMISSION_MONEY_DOWNLOAD_RSP = 2377,     // 每日佣金下载响应
	CERTIFICATION_APPROVAL_SENT = 2378,             // 实名认证推送
	OFFLINE_INMONEY_APPROVAL_QRY_REQ = 2379,		// 线下入金审核查询请求
	OFFLINE_INMONEY_APPROVAL_QRY_RSP = 2380,		// 线下入金审核查询响应
	OFFLINE_INMONEY_APPROVAL_HANDLE_REQ = 2381,		// 线下入金审核处理请求
	OFFLINE_INMONEY_APPROVAL_HANDLE_RSP = 2382,		// 线下入金审核处理响应
	ALL_CHILDUSER_NOW_QUERY_REQ = 2383,			    // 风控代理下所有子账户当前资金查询请求 
	ALL_CHILDUSER_NOW_QUERY_RSP = 2384,			    // 风控代理下所有子账户当前资金查询应答 
	MAINACCOUNT_POSITION_QRY_REQ = 2385,            // 主账户持仓查询请求
	MAINACCOUNT_POSITION_QRY_RSP = 2386,            // 主账户持仓查询响应
	CHILDACC_RESET_PASSWORD_REQ = 2387,             // 子账户重置密码请求
	CHILDACC_RESET_PASSWORD_RSP = 2388,             // 子账户重置密码响应

/////////////////////////////////风控模块 ////////////////////////////////////
    RSIKERCENTER = 3000,                       // 风控模块
   

///////////////////////////// 交易模块 ////////////////////////////////////////////////////////////
	TRADECENTER = 4000,							    // 交易相关 
	OPENCLOSE_REQ = 4001,							// 开平仓请求 
	ORDERINSERT_MSG = 4002,							// 委托提交推送 
	ORDERCHANGE_MSG = 4003,							// 委托改变推送 
	CANCELORDER_REQ = 4004,							// 撤单请求
	ORDERCANCEL_MSG = 4005,							// 委托撤销应答 
	TRADEOVER_MSG = 4006,							// 成交推送
	POSITION_MSG = 4007,							// 持仓推送
	MONEYCHANGE_MSG = 4008,							// 资金推送
	RISKTIGGER_MSG = 4009,							// 风控推送
	CORRECTPOSITION_MSG = 4010,						// 修正持仓-- 推送走原来流程
	CORRECTORDER_STATE = 4011,						// 修改订单状态
	CORRECTORDER_MSG = 4012,						// 修改订单状态返回
	REALACCOUNTFUND_MSG = 4013,						// 实盘资金信息推送

  ///////////////////////////// 条件单模块 ////////////////////////////////////////////////////////////
	YUNCENTER= 5000,                                // 条件单模块
	CONDITIONORDERS_QUERY_REQ = 5001,				// 条件单信息查询请求 
	CONDITIONORDERS_QUERY_RSP = 5002,				// 条件单信息应答 
	CONDITIONORDERS_ADD_REQ = 5003,					// 条件单信息增加请求 
	CONDITIONORDERS_ADD_RSP = 5004,					// 条件单信息增加应答 
	CONDITIONORDERS_UPDATE_REQ = 5005,				// 条件单信息更新请求 
	CONDITIONORDERS_UPDATE_RSP = 5006,				// 条件单信息更新应答 
	CONDITIONORDERS_DELETE_REQ = 5007,				// 条件单删除请求 
	CONDITIONORDERS_DELETE_RSP = 5008,				// 条件单删除应答 
	STOPP_ROFIT_LOSS_QUERY_REQ = 5009,				// 止盈止损单信息查询请求 
	STOPP_ROFIT_LOSS_QUERY_RSP = 5010,				// 止盈止损单信息应答 
	STOPP_ROFIT_LOSS_ADD_REQ = 5011,				// 止盈止损单增加请求 
	STOPP_ROFIT_LOSS_ADD_RSP = 5012,				// 止盈止损单增加应答 
	STOPP_ROFIT_LOSS_UPDATE_REQ = 5013,				// 止盈止损单更新请求 
	STOPP_ROFIT_LOSS_UPDATE_RSP = 5014,				// 止盈止损单更新应答 
	STOPP_ROFIT_LOSS_DELETE_REQ = 5015,				// 止盈止损单信息删除请求 
	STOPP_ROFIT_LOSS_DELETE_RSP = 5016,				// 止盈止损单信息删除应答 
	STOPP_ROFIT_LOSS_PCADD_REQ = 5017,				// 止盈止损单客户端增加请求 
	STOPP_ROFIT_LOSS_PCADD_RSP = 5018,				// 止盈止损单客户端增加应答 
	STOPP_ROFIT_LOSS_PCUPDATE_REQ = 5019,			// 止盈止损单客户端更新请求 
	STOPP_ROFIT_LOSS_PCUPDATE_RSP = 5020,			// 止盈止损单客户端更新应答 
	STOPP_ROFIT_LOSS_PCDELETE_REQ = 5021,			// 止盈止损单信息客户端删除请求 
	STOPP_ROFIT_LOSS_PCDELETE_RSP = 5022,			// 止盈止损单信息客户端删除应答 
	CONDITIONORDERS_STATUS_UPDATE_RSP = 5023,		// 条件单状态改变推送
	STOPP_ROFIT_LOSS_STATUS_UPDATE_RSP = 5024,		// 止盈止损单状态改变推送

	///////////////////////////////// http对外接口模块 ///////////////////////////////
	OPENINTERFACE = 6000,                           // http对外接口模块
	REGISTER_VAL_CONFIRM_REQ = 6001,				// 注册字段验证请求
	REGISTER_VAL_CONFIRM_RSP = 6002,				// 注册字段验证响应
	OFFLINE_INMONEY_APPROVAL_ADD = 6003,            // 线下入金审核添加
};

#endif