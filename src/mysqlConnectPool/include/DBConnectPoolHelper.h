#pragma once

//#include <boost\shared_ptr.hpp>
#include "DBConnect.h"
//#include <Windows.h>

namespace DB {
	typedef struct ConnectInfo_
	{
		// 数据库连接
		CDBConnectPtr pDBConnect;

		// 连接编号
		//size_t connectID;

		// 是否空闲
		bool isFree;

		ConnectInfo_() :
			pDBConnect(nullptr),
			//connectID(-1),
			isFree(true)
		{}

	}ConnectInfo, *PConnectInfo;
}
