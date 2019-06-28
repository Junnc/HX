#pragma once
#include <string>

class CThreadInfoConfigInfo
{
public:
	int Read(const std::string& filePath);

public:
	int managerThread;
	int riskThread;
	int yunCenterThread;
	int tradeThread;

};