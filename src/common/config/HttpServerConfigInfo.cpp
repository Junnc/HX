#include "HttpServerConfigInfo.h"
#include "INIReader.h"

int CHttpServerConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	ip = reader.Get("HttpServerInfo", "ip", "");
	port = reader.GetInteger("HttpServerInfo", "port", 0);

	return 0;
}
