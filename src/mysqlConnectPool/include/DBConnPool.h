#pragma once

#include "DBConnectPoolHelper.h"
#include <list>
#include "cmutex.h"

using namespace std;

namespace DB {

	/*******************************************
	����:���ݿ����ӳ�
	����:���𴴽�����ȡ��ά�����������ݿ�����
	********************************************/
	class CDBConnPool
	{
	public:
		CDBConnPool(const DBInfo& dbInfo);
		~CDBConnPool();

	public:
		/*************************************************
		Description: ����һ������
		Return     : ��������ָ��
		*************************************************/
		CDBConnectPtr CreateConnection();

		/*************************************************
		Description: ��ʼ�����ݿ����ӳ�
		int minSize: ��С������
		int maxSize: ���������
		Return     : �ɹ���������
		*************************************************/
		size_t InitConnection(int minSize, int maxSize);

		/*************************************************
		Description: �������ݿ����Ӷ���
		Return     : ���ٽ��
		*************************************************/
		int DestoryConnection();

		/*************************************************
		Description: ������ݿ�����
		ConnectInfo& connectInfo : ���ݿ�������Ϣ
		Return     : ���ػ�ȡ��� true �ɹ���false ʧ��
		*************************************************/
		bool GetConnection(ConnectInfo& connectInfo);

		/*************************************************
		Description: �����ݿ����ӷŻص����ӳص�������
		connectId : ���ݿ����ӱ��
		Return     : ��
		*************************************************/
		void ReleaseConnection(size_t connectId);

	public:
		size_t GetFreeNum();

		size_t GetBusyNum();

	private:
		// ��ʱ����
		void ReleaseConnection(ConnectInfo& connectInfo);

		CDBConnPool();

	private:
		// ���ݿ������б�
		std::list<ConnectInfo> m_dbConnList;

		// ���ݿ�������Ϣ
		DBInfo m_dbInfo;

		// ��С������
		int m_minSize;

		// ���������
		int m_maxSize;

		// �ٽ���
		Mutex m_mutex;

		// ���ݿ����������
		size_t m_maxConnectID;

	};

	typedef std::shared_ptr<CDBConnPool> CDBConnPoolPtr;
}