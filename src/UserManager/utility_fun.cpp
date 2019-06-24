#include "utility_fun.h"
#include <time.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

namespace UtilityFun
{
	extern	int getLocalDateInt()
	{
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t = localtime(&tt);
		int nDate = ThreeToOneInt(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
						
		return nDate;
	}

	extern	int getLocalTimeInt()
	{
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t = localtime(&tt);

		int nTime = ThreeToOneInt(t->tm_hour, t->tm_min, t->tm_sec);

		return nTime;
	}

	extern	int  ThreeToOneInt(int n1, int n2, int n3)
	{
		int time;
		time = n1 * 10000 + n2 * 100 + n3;
		return time;
	}

	extern std::string getDateTimeString()
	{
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t = localtime(&tt);

		char buffer[200] = { 0 };

		strftime(buffer, sizeof(buffer) - 1, "%Y-%m-%d %H:%M:%S", t);
		//sprintf_s(buffer, sizeof(buffer) - 1, "%04d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	
		return buffer;
	}

	bool isChineseString(const std::string& sztext)
	{
		if (sztext.empty())
			return true;

		char c = 0;
		char szchinese[3] = { 0 };
		int i = 0;
		for (; i < sztext.size(); i++)
		{
			//不是全角字符？
			if (sztext[i] >= 0 && sztext[i] <= 127)
			{
				c = sztext[i];
			}
			else
			{
				//中文是2个字节,所以i++
				szchinese[0] = sztext[i],
				szchinese[1] = sztext[i + 1],
				i++;
				return true;
			}
		}

		return false;
	}
}

namespace UUID
{
	extern std::string getUUid()
	{
		char guid[37];
		random_uuid(guid);

		return guid;
	}

	char *random_uuid(char buf[37])
	{
		srand(time(0));
		const char *c = "89ab";
		char *p = buf;
		int n;
		for (n = 0; n < 16; ++n)
		{
			int b = rand() % 255;
			switch (n)
			{
			case 6:
				sprintf(p, "4%x", b % 15);
				break;
			case 8:
				sprintf(p, "%c%x", c[rand() % strlen(c)], b % 15);
				break;
			default:
				sprintf(p, "%02x", b);
				break;
			}

			p += 2;
			switch (n)
			{
			case 3:
			case 5:
			case 7:
			case 9:
				*p++ = '-';
				break;
			}
		}
		*p = 0;
		return buf;
	}
}


