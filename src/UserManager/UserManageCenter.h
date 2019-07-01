#pragma once
//#include "instance_shared_from_this.h"
#include "DBConnPool.h"
#include "DBOperator.h"
#include "UserAccountDeal.h"

class CUserManageCenter
{
public:

	bool init();

	//PUserManagerSPI getManagerSPI();
	
private:
	//PUserManagerSPI m_pUserManagerSPI;
	std::shared_ptr<CCommandParseAndDeal> m_cmddeal;
};


