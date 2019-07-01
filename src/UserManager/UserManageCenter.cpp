#include "UserManageCenter.h"
#include <iostream>
#include "CacheUserAllInfo.h"
#include "UserAccountDeal.h"
#include "log4cxx/hx_log4cxx.h"

NG_LOGGER(logger,"UserManageCerter");

bool CUserManageCenter::init()
{
	//1.初始化数据库连接池    后面改成低配置
	DB::DBInfo dbinfo;
	dbinfo.ip = "192.168.2.84";
	dbinfo.port = 3306;
	dbinfo.userName = "root";
	dbinfo.pwd = "root";
	dbinfo.dbName = "tcversion1";

	int nMaxSize(20), nMinSize(10);

	if (!CDBOpeartor::instance()->init(dbinfo, nMaxSize, nMinSize))
	{
		std::cout << "init DBPool fail" << endl;
		NG_LOG4CXX_ERROR(logger,"init DBPool fail");
		return false;
	}

	//2.初始化缓存
	if (!CCacheUserAllInfo::instance()->init())
	{
		std::cout << "init cache fail" << endl;
		NG_LOG4CXX_ERROR(logger, "init cache fail");
		return false;
	}


	if (!CCommandParseAndDeal::instance()->init(5))
	{
		std::cout << "init Task threadpool fail" << endl;
		NG_LOG4CXX_ERROR(logger, "init Task threadpool fail");
		return false;
	}

	std::cout << "init Success" << endl;
	NG_LOG4CXX_INFO(logger, "init Success");
	return true;
}


