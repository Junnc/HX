#pragma once

//#include <boost\shared_ptr.hpp>
#include "DBConnect.h"
//#include <Windows.h>

namespace DB {
	typedef struct ConnectInfo_
	{
		// ���ݿ�����
		CDBConnectPtr pDBConnect;

		// ���ӱ��
		//size_t connectID;

		// �Ƿ����
		bool isFree;

		ConnectInfo_() :
			pDBConnect(nullptr),
			//connectID(-1),
			isFree(true)
		{}

	}ConnectInfo, *PConnectInfo;
}
