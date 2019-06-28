#pragma once
#include <string>

class CWSServerConfigInfo
{
public:
	int Read(const std::string& filePath);

public:
	std::string ip;
	int port;
	int threadNum;

};