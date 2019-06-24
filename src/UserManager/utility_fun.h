#pragma once
#include <string>

namespace UtilityFun
{
	extern	int getLocalDateInt();
	extern	int getLocalTimeInt();
	extern	int  ThreeToOneInt(int n1, int n2, int n3);

	extern std::string getDateTimeString();

	extern bool isChineseString(const std::string& sztext);

	

}

namespace UUID
{
	extern std::string getUUid();

	char *random_uuid(char buf[37]);
}
