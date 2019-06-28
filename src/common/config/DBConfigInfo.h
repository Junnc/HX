#pragma once
#include <string>

class CDBConfigInfo
{
public:
	// 读取文件信息
	int Read(const std::string& filePath);

public:
	std::string ip;
	int port;
	std::string loginName;
	std::string pwd;
	std::string dbName;
	std::string settleTime;
	std::string tradeTime;
	int maxConn;
	int minConn;
	int systemType;
};