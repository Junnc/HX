#pragma once

#include "DBConnectHelper.h"
#include <mysql/mysql.h>

/**********************************************
类名:数据库记录集游标管理器
功能:负责对数据库记录集游标进行管理，读取查询内容
************************************************/
namespace DB{
	class CDBRecordSet
	{	
	public:
		CDBRecordSet();
		~CDBRecordSet();

	public:
		// 读取行
		bool GetNextRow(); 

		// 返回行数
		size_t Count();

		// 是否能是最后一行,此功能mysql可能弃用
		bool isEof();

		// 读取不同数据类型
		int GetInt(int valueKey);

		double GetDouble(int valueKey);

		std::string GetString(int valueKey);

	public:
		// 注入内容
		void SetSqlRes(MYSQL_RES* sqlRes);

	private:
		MYSQL_RES *m_sqlRes;

		MYSQL_ROW m_resRow;

	};

	/**********************************************
	类名:数据库连接
	功能:负责对数据库进行查找、修改、删除和事务等操作
	************************************************/
	class CDBConnect
	{
	public:
		CDBConnect(const DBInfo& dbInfo);
		~CDBConnect();

	public:
		// 连接
		int Connect();

		// 查询
		int Select(const std::string& sql, CDBRecordSet& dbRecordSet, bool quick_mode = false);

		// 增删改
		int Execute(const std::string& sql);

		// 开始事务
		bool BeginTransaction();

		// 提交事务
		bool Commit();

		// 事务回滚
		bool RollBack();

		// 修改字符集
		bool ModCharSet(const std::string& charSet);

		// 获取错误信息
		DBErrorInfo GetLastError();

		// 释放
		void Close();

	public:
		void setConnectID(size_t connectID);

		size_t getConnectID();

	private:
		// 数据库连接
		MYSQL* m_pDBConnect;

		// 数据库连接状态
		int m_connectState;

		// 数据库连接信息
		DBInfo m_dbInfo;

		// 字符集
		std::string m_charSet;

		// 错误信息
		DBErrorInfo m_errorInfo;

		// 连接编号
		size_t m_connectID;

	};

	/**********************************************
	类名:原子事务类
	功能:负责事务的原子性操作
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
