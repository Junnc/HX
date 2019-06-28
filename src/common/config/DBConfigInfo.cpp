#include "DBConfigInfo.h"
#include "INIReader.h"

int CDBConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	// 读取数据库连接信息
	ip = reader.Get("DBInfo", "ip", "");
	port = reader.GetInteger("DBInfo", "port", 0);
	
	loginName = reader.Get("DBInfo", "loginName", "");
	pwd = reader.Get("DBInfo", "pwd", "");

	dbName = reader.Get("DBInfo", "dbName", "");
	maxConn = reader.GetInteger("DBInfo", "maxConn", 0);
	minConn = reader.GetInteger("DBInfo", "minConn", 0);

	settleTime = reader.Get("DBInfo", "settleTime", "05:30:00");
	tradeTime = reader.Get("DBInfo", "tradeTime", "6:00:00");

	//默认0是外盘，设置1是内盘
	systemType = reader.GetInteger("DBInfo", "systemType", 0);

	return 0;
}
