#include "UserManageCenter.h"
//#include "DBConnPool.h"
#include <iostream>
#include "CacheUserAllInfo.h"
#include "UserAccountDeal.h"
//#include "TaskManager.h"


bool CUserManageCenter::init()
{
	//1.��ʼ�����ݿ����ӳ�    ����ĳɵ�����
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
		return false;
	}
	std::cout << "init DBPool success" << endl;

	//2.��ʼ������
	if (!CCacheUserAllInfo::instance()->init())
	{
		std::cout << "init cache fail" << endl;
		return false;
	}
	std::cout << "init cache success" << endl;

	//3.��ʼ�������
	/*if (!CTaskManager::instance()->init(5))
	{
		std::cout << "init Task threadpool fail" << endl;
		return false;
	}
	std::cout << "init Task threadpool success" << endl;*/

	if (!CCommandParseAndDeal::instance()->init(5))
	{
		std::cout << "init Task threadpool fail" << endl;
		return false;
	}
	std::cout << "init Task threadpool success" << endl;

	return true;
}


