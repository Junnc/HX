#include "DBConnPool.h"

namespace DB {
	CDBConnPool::CDBConnPool(const DBInfo& dbInfo) : m_dbInfo(dbInfo), m_maxConnectID(0)
	{

	}

	CDBConnPool::~CDBConnPool()
	{

	}

	CDBConnectPtr CDBConnPool::CreateConnection()
	{
		CDBConnectPtr dbConnect(new CDBConnect(m_dbInfo));
		if (0 != dbConnect->Connect())
			return NULL;
		++m_maxConnectID;
		return dbConnect;
	}

	size_t CDBConnPool::InitConnection(int minSize, int maxSize)
	{
		m_minSize = minSize;
		m_maxSize = maxSize;
		for (int i = 0; i < minSize; ++i)
		{
			CDBConnectPtr pdbConnect = CreateConnection();
			if (NULL == pdbConnect)
				continue;
			ConnectInfo connectInfo;
			connectInfo.pDBConnect = pdbConnect;
			connectInfo.pDBConnect->setConnectID(m_maxConnectID);
			connectInfo.isFree = true;
			m_dbConnList.push_back(connectInfo);
		}

		return m_dbConnList.size();
	}

	int CDBConnPool::DestoryConnection()
	{
		scoped_lock lock(m_mutex);
		for (std::list<ConnectInfo>::iterator iter = m_dbConnList.begin(); iter != m_dbConnList.end(); ++iter)
		{
			iter->pDBConnect->Close();
			iter->pDBConnect = nullptr;
			m_dbConnList.erase(iter);
		}

		return 0;
	}

	bool CDBConnPool::GetConnection(ConnectInfo& connectInfo)
	{
		scoped_lock lock(m_mutex);

		for (std::list<ConnectInfo>::iterator iter = m_dbConnList.begin(); iter != m_dbConnList.end(); ++iter)
		{
			if (iter->isFree)
			{
				// 设置为不空闲
				iter->isFree = false;
				connectInfo = *iter;
				return true;
			}
		}

		// 连接数超过最大值，直接返回
		if (m_maxSize <= m_dbConnList.size())
			return false;

		// 没有空闲时，创建一个连接并存入列表
		CDBConnectPtr pdbConnect = CreateConnection();
		if (NULL == pdbConnect)
			return false;
		connectInfo.pDBConnect = pdbConnect;
		connectInfo.pDBConnect->setConnectID(m_maxConnectID + 1);
		connectInfo.isFree = false;
		m_dbConnList.push_back(connectInfo);

		return true;
	}

	void CDBConnPool::ReleaseConnection(ConnectInfo& connectInfo)
	{
		scoped_lock lock(m_mutex);
		ReleaseConnection(connectInfo.pDBConnect->getConnectID());
	}

	void CDBConnPool::ReleaseConnection(size_t connectId)
	{
		for (std::list<ConnectInfo>::iterator iter = m_dbConnList.begin(); iter != m_dbConnList.end(); ++iter)
		{
			if (iter->pDBConnect->getConnectID() == connectId && (!iter->isFree))
			{
				// 将连接改为空闲连接
				iter->isFree = true;
			}
		}
	}

	size_t CDBConnPool::GetFreeNum()
	{
		int freeNum = 0;
		for (std::list<ConnectInfo>::iterator iter = m_dbConnList.begin(); iter != m_dbConnList.end(); ++iter)
		{
			if (iter->isFree)
			{
				++freeNum;
			}
		}
		return freeNum;
	}

	size_t CDBConnPool::GetBusyNum()
	{
		int busyNum = 0;
		for (std::list<ConnectInfo>::iterator iter = m_dbConnList.begin(); iter != m_dbConnList.end(); ++iter)
		{
			if (!iter->isFree)
			{
				++busyNum;
			}
		}
		return busyNum;
	}

}
