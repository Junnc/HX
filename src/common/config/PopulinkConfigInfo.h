#pragma once
#include <string>

class CPopulinkConfigInfo
{
public:
	int Read(const std::string& filePath);

public:
	std::string addr;
};
