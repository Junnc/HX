#include "WSServerConfigInfo.h"
#include "INIReader.h"

int CWSServerConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	ip = reader.Get("WSServerInfo", "ip", "");
	port = reader.GetInteger("WSServerInfo", "port", 0);
	threadNum = reader.GetInteger("WSServerInfo", "threadNum", 5);

	return 0;
}
