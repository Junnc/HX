#include "DBConnect.h"
#include <mysql/mysql.h>
#include <string>

//NG_LOGGER(logger, "CDBConnect");

namespace DB {

#define ERR_DB_NOERR 0
	// Message: Lost connection to MySQL server during query
#define CR_SERVER_LOST 2013    
// Message: MySQL server has gone away
#define CR_SERVER_GONE_ERROR 2006    

// 连接状态
#define CONNECTED 0
// 断开状态
#define DISCONNECTED 1

	CDBConnect::CDBConnect(const DBInfo& dbInfo) : m_charSet("gbk"), m_dbInfo(dbInfo), m_connectState(DISCONNECTED)
	{

	}

	CDBConnect::~CDBConnect()
	{

	}

	int CDBConnect::Connect()
	{
		if (!(m_pDBConnect = mysql_init(NULL)))
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_init failed,reason:" + m_errorInfo.errorInfo;
			return -1;
		}

		if (mysql_real_connect(m_pDBConnect, m_dbInfo.ip.c_str(), m_dbInfo.userName.c_str()
			, m_dbInfo.pwd.c_str(), m_dbInfo.dbName.c_str(), m_dbInfo.port, NULL, 0) == NULL)
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_real_connect failed,reason:" + m_errorInfo.errorInfo;
			return -2;
		}

		if (mysql_set_character_set(m_pDBConnect, m_charSet.c_str()) != 0)
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_set_character_set failed,reason:" + m_errorInfo.errorInfo;
			return -3;
		}

		m_connectState = CONNECTED;
		return 0;
	}

	int CDBConnect::Select(const std::string& sql, CDBRecordSet& dbRecordSet, bool quick_mode/* = false*/)
	{
		int ret = 0;
		if ((ret = mysql_query(m_pDBConnect, sql.c_str())) != 0)
		{
			ret = mysql_errno(m_pDBConnect);

			if (ret == CR_SERVER_LOST || ret == CR_SERVER_GONE_ERROR)
			{
				mysql_close(m_pDBConnect);
				ret = Connect();

				if (ret == 0)
				{
					if ((ret = mysql_query(m_pDBConnect, sql.c_str())) != 0)
					{
						m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
						m_errorInfo.errorInfo = "mysql_query Select failed,sql:" + sql + ",reason:" + m_errorInfo.errorInfo;
						//LOG4CXX_ERROR(logger, LOG_VAR(m_errorInfo.errorInfo));
						return -1;
					}
				}
				else
				{
					m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
					m_errorInfo.errorInfo = "mysql_query Select failed,sql:" + sql + ",reason:" + m_errorInfo.errorInfo;
					//LOG4CXX_ERROR(logger, LOG_VAR(m_errorInfo.errorInfo));
					return ret;
				}
			}
			else
			{
				m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
				m_errorInfo.errorInfo = "mysql_query Select failed,sql:" + sql + ",reason:" + m_errorInfo.errorInfo;
				//LOG4CXX_ERROR(logger, LOG_VAR(m_errorInfo.errorInfo));
				return -1;
			}
		}

		if (quick_mode)
			dbRecordSet.SetSqlRes(mysql_use_result(m_pDBConnect));
		else
			dbRecordSet.SetSqlRes(mysql_store_result(m_pDBConnect));

		return ERR_DB_NOERR;
	}

	int CDBConnect::Execute(const std::string& sql)
	{
		int ret = 0;
		if ((ret = mysql_query(m_pDBConnect, sql.c_str())) != 0)
		{
			ret = mysql_errno(m_pDBConnect);

			if (ret == CR_SERVER_LOST || ret == CR_SERVER_GONE_ERROR)
			{
				mysql_close(m_pDBConnect);
				ret = Connect();
				if (ret == ERR_DB_NOERR)
				{
					if ((ret = mysql_query(m_pDBConnect, sql.c_str())) != 0)
					{
						m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
						m_errorInfo.errorInfo = "mysql_query Execute failed,sql:" + sql + ",renson:" + m_errorInfo.errorInfo;
						//LOG4CXX_ERROR(logger, LOG_VAR(m_errorInfo.errorInfo));
						return -1;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
				m_errorInfo.errorInfo = "mysql_query Execute failed,sql:" + sql + ",renson:" + m_errorInfo.errorInfo;
				//LOG4CXX_ERROR(logger, LOG_VAR(m_errorInfo.errorInfo));
				return -1;
			}

		}

		return 0;
	}

	bool CDBConnect::BeginTransaction()
	{
		if (mysql_query(m_pDBConnect, "START TRANSACTION") != 0)
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_query START TRANSACTION failed,reason:" + m_errorInfo.errorInfo;
			return false;
		}
		return true;
	}

	bool CDBConnect::Commit()
	{
		if (mysql_query(m_pDBConnect, "COMMIT") != 0)
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_query Commit failed,reason:" + m_errorInfo.errorInfo;
			return false;
		}
		return true;
	}

	bool CDBConnect::RollBack()
	{
		if (mysql_query(m_pDBConnect, "ROLLBACK") != 0)
		{
			m_errorInfo.errorInfo = mysql_error(m_pDBConnect);
			m_errorInfo.errorInfo = "mysql_query ROLLBACK failed,reason:" + m_errorInfo.errorInfo;
			return false;
		}
		return true;
	}

	bool CDBConnect::ModCharSet(const std::string& charSet)
	{
		m_charSet = charSet;
		return true;
	}

	DBErrorInfo CDBConnect::GetLastError()
	{
		return m_errorInfo;
	}

	void CDBConnect::Close()
	{
		if (nullptr != m_pDBConnect)
			mysql_close(m_pDBConnect);
	}

	void CDBConnect::setConnectID(size_t connectID)
	{
		m_connectID = connectID;
	}

	size_t CDBConnect::getConnectID()
	{
		return m_connectID;
	}

	CDBRecordSet::CDBRecordSet() : m_sqlRes(nullptr)
	{

	}

	CDBRecordSet::~CDBRecordSet()
	{
		if (nullptr != m_sqlRes)
		{
			// 不为空，释放内存
			mysql_free_result(m_sqlRes);
		}
	}

	bool CDBRecordSet::GetNextRow()
	{
		while (m_resRow = (mysql_fetch_row((MYSQL_RES *)m_sqlRes)))
		{
			return true;
		}

		return false;
	}

	size_t CDBRecordSet::Count()
	{
		return m_sqlRes->row_count;
	}

	bool CDBRecordSet::isEof()
	{
		return (bool)mysql_eof(m_sqlRes);
	}

	int CDBRecordSet::GetInt(int valueKey)
	{
		char* pChar = ((MYSQL_ROW)m_resRow)[valueKey];
		if (nullptr == pChar)
			return 0;
		return atoi(pChar);
	}

	double CDBRecordSet::GetDouble(int valueKey)
	{
		char* pChar = ((MYSQL_ROW)m_resRow)[valueKey];
		if (nullptr == pChar)
			return 0.0;
		return atof(pChar);
	}

	std::string CDBRecordSet::GetString(int valueKey)
	{
		char* pChar = (((MYSQL_ROW)m_resRow)[valueKey]);
		if (nullptr == pChar)
			return "";
		return std::string(pChar);
	}

	void CDBRecordSet::SetSqlRes(MYSQL_RES* sqlRes)
	{
		m_sqlRes = sqlRes;
	}

	CAtomTransaction::CAtomTransaction(CDBConnectPtr pDBConnect)
	{
		m_pDBConnect = pDBConnect;
		m_pDBConnect->BeginTransaction();
	}

	CAtomTransaction::~CAtomTransaction()
	{
		if (!m_isCommit)
			m_pDBConnect->RollBack();
	}

	void CAtomTransaction::SetCommit()
	{
		m_pDBConnect->Commit();
		m_isCommit = true;
	}
}
