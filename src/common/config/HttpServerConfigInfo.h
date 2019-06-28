#pragma once
#include <string>

class CHttpServerConfigInfo
{
public:
	// 读取文件信息
	int Read(const std::string& filePath);

public:
	std::string ip;
	int port;

};