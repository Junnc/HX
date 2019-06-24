#pragma once

#include "DBConnectPoolHelper.h"
#include <list>
#include "cmutex.h"

using namespace std;

namespace DB {

	/*******************************************
	类名:数据库连接池
	功能:负责创建、获取、维护和销毁数据库连接
	********************************************/
	class CDBConnPool
	{
	public:
		CDBConnPool(const DBInfo& dbInfo);
		~CDBConnPool();

	public:
		/*************************************************
		Description: 创建一个连接
		Return     : 返回连接指针
		*************************************************/
		CDBConnectPtr CreateConnection();

		/*************************************************
		Description: 初始化数据库连接池
		int minSize: 最小连接数
		int maxSize: 最大连接数
		Return     : 成功连接数量
		*************************************************/
		size_t InitConnection(int minSize, int maxSize);

		/*************************************************
		Description: 销毁数据库连接对象
		Return     : 销毁结果
		*************************************************/
		int DestoryConnection();

		/*************************************************
		Description: 获得数据库连接
		ConnectInfo& connectInfo : 数据库连接信息
		Return     : 返回获取结果 true 成功、false 失败
		*************************************************/
		bool GetConnection(ConnectInfo& connectInfo);

		/*************************************************
		Description: 将数据库连接放回到连接池的容器中
		connectId : 数据库连接编号
		Return     : 空
		*************************************************/
		void ReleaseConnection(size_t connectId);

	public:
		size_t GetFreeNum();

		size_t GetBusyNum();

	private:
		// 暂时隐藏
		void ReleaseConnection(ConnectInfo& connectInfo);

		CDBConnPool();

	private:
		// 数据库连接列表
		std::list<ConnectInfo> m_dbConnList;

		// 数据库连接信息
		DBInfo m_dbInfo;

		// 最小连接数
		int m_minSize;

		// 最大连接数
		int m_maxSize;

		// 临界区
		Mutex m_mutex;

		// 数据库连接最大编号
		size_t m_maxConnectID;

	};

	typedef std::shared_ptr<CDBConnPool> CDBConnPoolPtr;
}