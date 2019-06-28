#include "ThreadInfoConfigInfo.h"
#include "INIReader.h"

int CThreadInfoConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	managerThread = reader.GetInteger("ThreadInfo", "managerThread", 3);
	riskThread = reader.GetInteger("ThreadInfo", "riskThread", 3);
	yunCenterThread = reader.GetInteger("ThreadInfo", "yunCenterThread", 3);
	tradeThread = reader.GetInteger("ThreadInfo", "tradeThread", 3);

	return 0;
}
