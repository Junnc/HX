#pragma once

#include <string>
#include <memory>

namespace DB {
	class CDBConnect;

	// 数据库连接信息
	typedef struct DBInfo_
	{
		std::string ip;
		int port;
		std::string userName;
		std::string pwd;
		std::string dbName;

		DBInfo_() :
			port(0)
		{}
	}DBInfo, *PDBInfo;

	// 数据库执行错误信息
	typedef struct DBErrorInfo_
	{
		int type;
		std::string errorInfo;

		DBErrorInfo_() :
			type(0)
		{}

	}DBErrorInfo, *PDBErrorInfo;

	typedef std::shared_ptr<CDBConnect> CDBConnectPtr;


}