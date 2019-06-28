#pragma once
#include <string>

#include "DBConfigInfo.h"
#include "WSServerConfigInfo.h"
#include "ApiServerConfigInfo.h"
#include "QuotationServerConfigInfo.h"
#include "PopulinkConfigInfo.h"
#include "HttpServerConfigInfo.h"
#include "ThreadInfoConfigInfo.h"
#include "../instance_shared_from_this.h"

class CConfig : public CommonTools::instance_shared_from_this<CConfig>
{
public:
	// 文件是否存在
	bool IsFileExist(const std::string& filePath);

	// 读取文件信息
	int Read(const std::string& filePath);

public:
	CDBConfigInfo m_dbInfo;
	CWSServerConfigInfo m_WSServerInfo;
	CApiServerConfigInfo m_apiServerInfo;
	CQuotationServerConfigInfo m_quotationServer;
	CPopulinkConfigInfo m_populinkConfigInfo;
	CHttpServerConfigInfo m_httpServer;
	CThreadInfoConfigInfo m_threadInfo;

};
