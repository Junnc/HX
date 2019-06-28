#include "PopulinkConfigInfo.h"
#include "INIReader.h"

int CPopulinkConfigInfo::Read(const std::string& filePath)
{
	// read ini file
	INIReader reader(filePath);
	if (reader.ParseError() < 0) {
		//TODO
		// log error
		return -1;
	}       

	addr = reader.Get("PopulinkAddr", "addr", "");

	return 0;
}
