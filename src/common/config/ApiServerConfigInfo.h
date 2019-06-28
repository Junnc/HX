#pragma once
#include <string>

class CApiServerConfigInfo
{
public:
	int Read(const std::string& filePath);

public:
	std::string ip;
	int port;

};