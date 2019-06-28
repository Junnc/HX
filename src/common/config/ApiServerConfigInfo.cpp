#include "ApiServerConfigInfo.h"
#include "INIReader.h"

int CApiServerConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       
	//GetPrivateProfileStringA("ApiServerInfo", "ip", "", ipTmp, sizeof(ipTmp), filePath.c_str());
	ip = reader.Get("ApiServerInfo", "ip", "" );
	port = reader.GetInteger("ApiServerInfo", "port", 0);

	return 0;
}
