#pragma once
#include "UserTableMsgStruct.h"
#include "DBConnPool.h"
#include <mutex>
#include <map>

class CTableCertificationRegRecord
{
public:
	bool addCertificationRegRecord(const certificationRegisterRecordInfo& cerRegRecInfo, DB::ConnectInfo& dbconInfo);


	bool queryCertificationRegRecordAll(std::map<int, certificationRegRecordInfoPtr>& cerMap, DB::ConnectInfo& dbconInfo);
	
	bool updateCertifitionRegState(int id, int state, std::string apprReson, std::string apprID, DB::ConnectInfo& dbconInfo);

	bool selectDB(int id, certificationRegRecordInfoPtr& cerPtr, DB::ConnectInfo& dbconInfo);
private:
	std::mutex mutex;
};


