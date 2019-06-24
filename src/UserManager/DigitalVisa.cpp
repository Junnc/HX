#include "DigitalVisa.h"
#include <cstdlib>
#include <sstream>
#include <time.h>


using namespace std;

string CDigitalVisa::CreatPopularizeLink()
{
	stringstream ssTemp;

	std::string chars("abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"1234567890");

	srand(time(0));
	for (int i = 0; i < 4; ++i)
	{
		int num = rand() % chars.size();
		ssTemp << chars[num];
	}

	return ssTemp.str();
}
