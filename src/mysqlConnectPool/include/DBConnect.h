#pragma once

#include "DBConnectHelper.h"
#include <mysql/mysql.h>

/**********************************************
����:���ݿ��¼���α������
����:��������ݿ��¼���α���й�����ȡ��ѯ����
************************************************/
namespace DB{
	class CDBRecordSet
	{	
	public:
		CDBRecordSet();
		~CDBRecordSet();

	public:
		// ��ȡ��
		bool GetNextRow(); 

		// ��������
		size_t Count();

		// �Ƿ��������һ��,�˹���mysql��������
		bool isEof();

		// ��ȡ��ͬ��������
		int GetInt(int valueKey);

		double GetDouble(int valueKey);

		std::string GetString(int valueKey);

	public:
		// ע������
		void SetSqlRes(MYSQL_RES* sqlRes);

	private:
		MYSQL_RES *m_sqlRes;

		MYSQL_ROW m_resRow;

	};

	/**********************************************
	����:���ݿ�����
	����:��������ݿ���в��ҡ��޸ġ�ɾ��������Ȳ���
	************************************************/
	class CDBConnect
	{
	public:
		CDBConnect(const DBInfo& dbInfo);
		~CDBConnect();

	public:
		// ����
		int Connect();

		// ��ѯ
		int Select(const std::string& sql, CDBRecordSet& dbRecordSet, bool quick_mode = false);

		// ��ɾ��
		int Execute(const std::string& sql);

		// ��ʼ����
		bool BeginTransaction();

		// �ύ����
		bool Commit();

		// ����ع�
		bool RollBack();

		// �޸��ַ���
		bool ModCharSet(const std::string& charSet);

		// ��ȡ������Ϣ
		DBErrorInfo GetLastError();

		// �ͷ�
		void Close();

	public:
		void setConnectID(size_t connectID);

		size_t getConnectID();

	private:
		// ���ݿ�����
		MYSQL* m_pDBConnect;

		// ���ݿ�����״̬
		int m_connectState;

		// ���ݿ�������Ϣ
		DBInfo m_dbInfo;

		// �ַ���
		std::string m_charSet;

		// ������Ϣ
		DBErrorInfo m_errorInfo;

		// ���ӱ��
		size_t m_connectID;

	};

	/**********************************************
	����:ԭ��������
	����:���������ԭ���Բ���
	**********************************************/
	class CAtomTransaction
	{
	public:
		CAtomTransaction(CDBConnectPtr pDBConnect);

		~CAtomTransaction();

	public:
		void SetCommit();

	private:
		CDBConnectPtr m_pDBConnect;

		bool m_isCommit;
	};

}
