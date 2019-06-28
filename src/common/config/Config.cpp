#include "Config.h"
#include <fstream>

bool CConfig::IsFileExist(const std::string& filePath)
{
	std::fstream fs;
	fs.open(filePath, std::ios::in);
	if (!fs)
		return false;
	return true;
}

int CConfig::Read(const std::string& filePath)
{
	m_dbInfo.Read(filePath);
	m_WSServerInfo.Read(filePath);
	m_apiServerInfo.Read(filePath);
	m_quotationServer.Read(filePath);
	m_populinkConfigInfo.Read(filePath);
	m_httpServer.Read(filePath);
	m_threadInfo.Read(filePath);
	return 0;
}

