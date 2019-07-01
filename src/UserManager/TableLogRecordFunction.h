#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableLogRecordFunction
{
public:

	bool queryLogRecordAll(std::map<int, LogRecordsPtr>& logMap, DB::ConnectInfo& dbconInfo);

	bool addLogRecord(LogRecords& logRec, DB::ConnectInfo& dbconInfo);

private:
	std::mutex mutex;
};
