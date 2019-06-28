#include "QuotationServerConfigInfo.h"
#include "INIReader.h"

int CQuotationServerConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	ip = reader.Get("QuotationServerInfo", "ip", "");
	port = reader.Get("QuotationServerInfo", "port", "");

	return 0;
}
