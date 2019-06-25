#include <sstream>
#include <limits>
#include <cmath>
#include <uuid/uuid.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "utility_fun.h"

namespace UtilityFun {

	bool IsEqual(double left, double right)
	{
		double delta = left - right;
		if (delta > -HX_DOUBLE_PRECISE && delta < HX_DOUBLE_PRECISE)
			return true;

		return false;
	}

	double Round(double src, double base)
	{
		if (base > -HX_DOUBLE_PRECISE && base < HX_DOUBLE_PRECISE)
			return src;

		long long max_value = (std::numeric_limits<long long>::max)() * base;
		if (src > max_value || src < -max_value)
		{
			return src;
		}

		if (src == 0)
			return 0.0;
		if (src > 0)
			return ((long long)((src + base / 2) / base)) * base;
		else
			return ((long long)((src - base / 2) / base)) * base;
	}

	bool CanBeDivided(double src, double base)
	{
		if (base > -HX_DOUBLE_PRECISE && base < HX_DOUBLE_PRECISE)
			return false;

		double theta = src / base;
		double delta = theta - (long long)(theta);
		if ((delta > -HX_DOUBLE_PRECISE && delta < HX_DOUBLE_PRECISE) || (delta - 1 > -HX_DOUBLE_PRECISE) || (delta + 1 < HX_DOUBLE_PRECISE))
			return true;

		return false;
	}

	void GetCurrentIntdateAndIntTime(int& date, int& rtime)
	{
/*
 *                SYSTEMTIME st = { 0 };
 *                GetLocalTime(&st);
 *
 *                date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;
 *                time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
 */
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);
                date = st->tm_year * 10000 + st->tm_mon* 100 + st->tm_mday;
                rtime = st->tm_hour* 10000 + st->tm_min* 100 + st->tm_sec;

	}


	bool isLeapYear(int year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			return true;
		}

		return false;
	}

	int GetDaysOfMonth(int nYear, int nMonth)
	{
		if (nMonth < 1 || nMonth > 12)
		{
			return -1;
		}

		if (nMonth == 2 && isLeapYear(nYear))
			return 29;

		static int month[13];
		month[1] = 31;
		month[2] = 28;
		month[3] = 31;
		month[4] = 30;
		month[5] = 31;
		month[6] = 30;
		month[7] = 31;
		month[8] = 31;
		month[9] = 30;
		month[10] = 31;
		month[11] = 30;
		month[12] = 31;

		return month[nMonth];
	}

	int GetDaysOfYear(int year)
	{
		return isLeapYear(year) ? 366 : 365;
	}

	bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2)
	{
		if (date1 > date2 || (date1 == date2 && time1 > time2))
			return true;

		return false;
	}

	//´«ÈëÊý¾Ý±ØÐëºÏ·¨
	void GetPreDay(int year, int month, int day, int& outYear, int& outMonth, int& outDay)
	{
		if (day > 1)
		{
			outYear = year;
			outMonth = month;
			outDay = day - 1;
			return;
		}

		if (month > 1)
		{
			outYear = year;
			outMonth = month - 1;
			outDay = GetDaysOfMonth(outYear, outMonth);
			return;
		}

		outYear = year - 1;
		outMonth = 12;
		outDay = GetDaysOfMonth(outYear, outMonth);
		return;
	}

	extern int GetPreDay(int day)
	{
		int tyear = day / 10000;
		int tday = day % 100;
		int tmonth = (day % 10000) / 100;

		int outYear(0),outMonth(0),outDay(0);
		GetPreDay(tyear, tmonth, tday, outYear,outMonth,outDay);

		return outYear * 10000 + outMonth * 100 + outDay;
	}

	void GetPreDayToSelf(int& outYear, int& outMonth, int& outDay)
	{
		if (outDay > 1)
		{
			outDay -= 1;
			return;
		}

		if (outMonth > 1)
		{
			outMonth -= 1;
			outDay = GetDaysOfMonth(outYear, outMonth);
			return;
		}

		outYear -= 1;
		outMonth = 12;
		outDay = GetDaysOfMonth(outYear, outMonth);
		return;
	}

	int GetPreWorkDay(int dt)
	{
		int year = dt / 10000;

		int day = dt % 100;
		int mon = (dt % 10000) / 100;
		GetPreWorkDayToSelf(year, mon, day);
		return year * 10000 + mon * 100 + day;
	}

	void GetPreWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
	{
		GetPreDay(year, mon, day, outYear, outMonth, outDay);
		int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
		if (dayOfWeek < 6)
		{
			return;
		}

		for (int i = 5; i < dayOfWeek; ++i)
		{
			GetPreDayToSelf(outYear, outMonth, outDay);
		}
	}

	void GetPreWorkDayToSelf(int& outYear, int& outMon, int& outDay)
	{
		GetPreDayToSelf(outYear, outMon, outDay);
		int dayOfWeek = GetDayOfWeek(outYear, outMon, outDay);
		if (dayOfWeek < 6)
		{
			return;
		}

		for (int i = 5; i < dayOfWeek; ++i)
		{
			GetPreDayToSelf(outYear, outMon, outDay);
		}
	}

	int GetDayOfWeek(int year, int mon, int day)
	{
		// »ùÄ·À­¶ûÉ­¹«Ê½ 0=ÐÇÆÚÌì 
		int m = mon;
		int d = day;
		int y = year;
		if (m == 1) { m = 13; y--; }

		if (m == 2) { m = 14; y--; }

		if ((y < 1752) || ((y == 1752) && (m < 9)) || ((y == 1752) && (m == 9) && (d < 3))) //ÅÐ¶ÏÊÇ·ñÔÚ1752Äê9ÔÂ3ÈÕÖ®Ç°
			return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7; //1752Äê9ÔÂ3ÈÕÖ®Ç°µÄ¹«Ê½

		return 1 + (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7; //1752Äê9ÔÂ3ÈÕÖ®ºóµÄ¹«Ê½
	}

	int GetDayOfWeek(int date)
	{
		int year = date / 10000;
		int day = date % 100;
		int mon = (date % 10000) / 100;
		return GetDayOfWeek(year, mon, day);
	}

	int GetNextWorkDay(int dt)
	{
		int year = dt / 10000;

		int day = dt % 100;
		int mon = (dt % 10000) / 100;
		GetNextWorkDayToSelf(year, mon, day);
		return year * 10000 + mon * 100 + day;
	}

	void GetNextWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
	{
		GetNextDay(year, mon, day, outYear, outMonth, outDay);
		int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
		if (dayOfWeek > 5)
		{
			return;
		}

		for (int i = 5; i < dayOfWeek; ++i)
		{
			GetNextDayToSelf(outYear, outMonth, outDay);
		}
	}

	void GetNextDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
	{
		if (day < GetDaysOfMonth(year, mon))
		{
			outYear = year;
			outMonth = mon;
			outDay = day + 1;
			return;
		}

		outDay = 1;
		if (mon < 12)
		{
			outYear = year;
			outMonth = mon + 1;
			return;
		}

		outYear = year + 1;
		outMonth = 1;
		return;
	}

	extern int GetNextDay(int date)
	{
		int year = date / 10000;
		int month = (date % 10000) / 100;
		int day = date % 100;

		int yearTmp = 0;
		int monthTmp = 0;
		int dayTmp = 0;
		GetNextDay(year, month, day, yearTmp, monthTmp, dayTmp);
		return yearTmp * 10000 + monthTmp * 100 + dayTmp;
	}

	void GetNextDayToSelf(int& outYear, int& outMonth, int& outDay)
	{
		if (outDay < GetDaysOfMonth(outYear, outMonth))
		{
			outDay += 1;
			return;
		}

		outDay = 1;
		if (outMonth < 12)
		{
			outMonth += 1;
			return;
		}

		outYear += 1;
		outMonth = 1;
		return;
	}

	void GetNextWorkDayToSelf(int& outYear, int& outMonth, int& outDay)
	{
		GetNextDayToSelf(outYear, outMonth, outDay);
		int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
		if (dayOfWeek < 6)
		{
			return;
		}

		for (int i = dayOfWeek; i <= 7; ++i)
		{
			GetNextDayToSelf(outYear, outMonth, outDay);
		}
	}

	extern bool TodayIsWeekDayByForeign()
	{
		bool bFlag(false);
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		//注：外盘不考虑周六
		if (st->tm_wday == 0 || st->tm_wday == 6)
			bFlag = true;

		return bFlag;
	}

	extern bool TodayIsWeekDayByForeignLimit(int tradetime)
	{
		bool bFlag(false);
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		int  rtime(-1);
                rtime = st->tm_hour* 10000 + st->tm_min* 100 + st->tm_sec;

		//注：外盘双休日：周六上午endTime开始 ~ 周一上午endTime结束
		if (st->tm_wday == 0 ||  (st->tm_wday == 6 && rtime > tradetime)
			|| (st->tm_wday == 1 && rtime < tradetime))
			bFlag = true;

		return bFlag;
	}

	extern bool TodayIsWeekDayByInner()
	{
		bool bFlag(false);
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		if (st->tm_wday == 0 || st->tm_wday == 1)
			bFlag = true;

		return bFlag;
	}

	extern bool TodayIsWeekDayByInnerLimit(int stime /*= HX_INNER_STIME*/, int etime /*= HX_INNER_ETIME*/)
	{
		bool bFlag(false);
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		int  rtime(-1);
                rtime = st->tm_hour* 10000 + st->tm_min* 100 + st->tm_sec;

		//注：外盘双休日：周六上午stime开始 ~ 周一上午etime结束
		if (st->tm_wday == 0 ||  (st->tm_wday == 6 && rtime > stime)
			|| (st->tm_wday == 1 && rtime < etime))
			bFlag = true;

		return bFlag;
	}

	std::string TranslateDateTime(int date, int time)
	{
		std::ostringstream streamDate;
		if (time < 10)
		{
			streamDate << date << "0" << "0" << "0" << "0" << "0" << time;
		}
		else if (time < 60)
		{
			streamDate << date << "0" << "0" << "0" << "0" << time;
		}
		else if (time < 1000)
		{
			streamDate << date << "0" << "0" << "0" << time;
		}
		else if (time < 6000)
		{
			streamDate << date << "0" << "0" << time;
		}
		else if (time < 100000)
		{
			streamDate << date<<"0"<< time;
		}
		else
		{
			streamDate << date << time;
		}
		std::string streamDateTime = streamDate.str();
		return streamDateTime;
	}

	std::string TranslateTimeString(int time)
	{
		std::ostringstream streamTime;
		streamTime << time;
		std::string streamDateTime = streamTime.str();
		return streamDateTime;
	}

	extern std::string TranslateDoubleToString(double price)
	{
		std::ostringstream streamTime;
		streamTime << price;
		std::string streamDateTime = streamTime.str();
		return streamDateTime;
	}

	std::string TranslateTime(int time)
	{
		int hour = time / 10000;
		int second = time % 100;
		int minute = (time % 10000) / 100;

		char szBuffer[20] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%02d:%02d:%02d", hour, minute, second);
		return szBuffer;
	}

	std::string TranslateDate(int date)
	{
		int year = date / 10000;
		int day = date % 100;
		int mon = (date % 10000) / 100;

		char szBuffer[20] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", year, mon, day);
		return  szBuffer;
	}

	std::string GetCurrentTimeString()
	{
		int date(0), time(0);
		GetCurrentIntdateAndIntTime(date, time);
		std::string  currentTime = TranslateDateTime(date, time);
		return currentTime;
	}

	bool GetDateAndTimeInt(std::string dateTime, int & date, int & time)
	{
		size_t dateIndex(0), timeIndex(0);
		int  tmpDate(0), tmpTime(0);

		while (dateIndex != std::string::npos)
		{
			dateIndex = dateTime.find("-");
			if (dateIndex != std::string::npos)
			{
				dateTime.erase(dateIndex, 1);
				++tmpDate;
			}
		}
		while (timeIndex != std::string::npos)
		{
			timeIndex = dateTime.find(":");
			if (timeIndex != std::string::npos)
			{
				dateTime.erase(timeIndex, 1);
				++tmpTime;
			}
		}

		if (tmpTime == 2 && tmpDate == 2)
		{
			date = atoi(dateTime.substr(0, 8).c_str());
			time = atoi(dateTime.substr(dateTime.size() - 6, dateTime.size()).c_str());

			return true;
		}

		return false;
	}

	bool GetTimeInt(std::string time, int & tTime)
	{
		int  tmpTime(0); 
		size_t timeIndex(0);

		while (timeIndex != std::string::npos)
		{
			timeIndex = time.find(":");
			if (timeIndex != std::string::npos)
			{
				time.erase(timeIndex, 1);
				++tmpTime;
			}
		}

		if (tmpTime == 2)
		{
			tTime = atoi(time.substr(0, 6).c_str());

			return true;
		}

		return false;
	}

	bool GetDateInt(std::string date, int & tDate)
	{
		size_t dateIndex(0); 
		int tmpDate(0);

		while (dateIndex != std::string::npos)
		{
			dateIndex = date.find("-");
			if (dateIndex != std::string::npos)
			{
				date.erase(dateIndex, 1);
				++tmpDate;
			}
		}

		if (tmpDate == 2)
		{
			tDate = atoi(date.substr(0, 8).c_str());
			return true;
		}
		return false;
	}

	bool compareDouble(double left, double right, double mixSpace /*= HX_DOUBLE_PRECISE*/)
	{
		double delta = left - right;
		if (delta > -mixSpace && delta < mixSpace)
			return true;

		return false;
	}

	std::string createGUID()
	{
		char uuid [64];
		uuid_t uu;
		uuid_generate_random(uu);
		uuid_unparse_lower(uu, uuid);

		return std::string(uuid);
	}

	extern int getCurrentYear()
	{
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		return st->tm_year;
	}

	std::string getCurrentDate()
	{
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		char szBuffer[40] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", st->tm_year, st->tm_mon, st->tm_mday);
		return szBuffer;
	}

	std::string getCurrentTime()
	{
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		char szBuffer[40] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%02d:%02d:%02d", st->tm_hour, st->tm_min, st->tm_sec);
		return szBuffer;
	}

	std::string getCurrentDateTime()
	{
		return getCurrentDate() + " " + getCurrentTime();
	}

	std::string getAddDate(int days)
	{
		char szBuffer[40] = { 0 };
		time_t ltime;

		struct tm   tmcur;

		time(&ltime);
		ltime = ltime + days * 60 * 60 * 24;
		localtime_r(&ltime, &tmcur);
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", tmcur.tm_year + 1900, tmcur.tm_mon + 1, tmcur.tm_mday);
		return szBuffer;
	}

	std::string getAddDate(const std::string& d1, int days)
	{
		if (d1.empty())
			return "0000-00-00";

		struct tm tm1;
		sscanf(d1.c_str(), "%04d-%02d-%02d",
			&(tm1.tm_year),
			&(tm1.tm_mon),
			&(tm1.tm_mday));

		tm1.tm_year -= 1900;
		tm1.tm_mon--;
		tm1.tm_hour = 0;
		tm1.tm_min = 0;
		tm1.tm_sec = 0;
		tm1.tm_isdst = -1;

		time_t ltime;
		ltime = mktime(&tm1);
		ltime = ltime + days * 60 * 60 * 24;

		struct tm   tmcur;
		localtime_r(&ltime, &tmcur);
		char szBuffer[40] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", tmcur.tm_year + 1900, tmcur.tm_mon + 1, tmcur.tm_mday);

		return szBuffer;
	}

	std::string getAddTime(int secs)
	{
		char szBuffer[40] = { 0 };
		time_t ltime;

		struct tm   tmcur;

		time(&ltime);
		ltime = ltime + secs;
		localtime_r(&ltime, &tmcur);
		snprintf(szBuffer, sizeof(szBuffer) - 1,
			"%04d-%02d-%02d %02d:%02d:%02d"
			, tmcur.tm_year + 1900, tmcur.tm_mon + 1, tmcur.tm_mday
			, tmcur.tm_hour, tmcur.tm_min, tmcur.tm_sec);
		return szBuffer;
	}

	int getDateSpace(const std::string& d1, const std::string& d2)
	{
		if (d1.empty() || d2.empty())
			return -1;

		struct tm tm1, tm2;
		sscanf(d1.c_str(), "%04d-%02d-%02d",
			&(tm1.tm_year),
			&(tm1.tm_mon),
			&(tm1.tm_mday));

		tm1.tm_year -= 1900;
		tm1.tm_mon--;
		tm1.tm_hour = 0;
		tm1.tm_min = 0;
		tm1.tm_sec = 0;
		tm1.tm_isdst = -1;

		sscanf(d2.c_str(), "%04d-%02d-%02d",
			&(tm2.tm_year),
			&(tm2.tm_mon),
			&(tm2.tm_mday));

		tm2.tm_year -= 1900;
		tm2.tm_mon--;
		tm2.tm_hour = 0;
		tm2.tm_min = 0;
		tm2.tm_sec = 0;
		tm2.tm_isdst = -1;

		time_t time_day1 = mktime(&tm1);
		time_t time_day2 = mktime(&tm2);

		int value = abs(time_day1 - time_day2);
		int  day = value / (60 * 60 * 24);
		return day;
	}

	int getDateTimeSpace(const std::string& dt1, const std::string& dt2)
	{
		if (dt1.empty() || dt2.empty())
			return -1;

		struct tm tm1, tm2;
		sscanf(dt1.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
			&(tm1.tm_year),
			&(tm1.tm_mon),
			&(tm1.tm_mday),
			&(tm1.tm_hour),
			&(tm1.tm_min),
			&(tm1.tm_sec));

		tm1.tm_year -= 1900;
		tm1.tm_mon--;
		tm1.tm_isdst = -1;

		sscanf(dt2.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
			&(tm2.tm_year),
			&(tm2.tm_mon),
			&(tm2.tm_mday),
			&(tm2.tm_hour),
			&(tm2.tm_min),
			&(tm2.tm_sec));

		tm2.tm_year -= 1900;
		tm2.tm_mon--;
		tm2.tm_isdst = -1;

		time_t time_day1 = mktime(&tm1);
		time_t time_day2 = mktime(&tm2);

		long long value = abs(time_day1 - time_day2);
		int day = value / (60 * 60 * 24);
		return day;
	}

	extern int getTimeSpace(const std::string& dt1, const std::string& dt2)
	{
		if (dt1.empty() || dt2.empty())
			return -1;

		struct tm tm1, tm2;
		sscanf(dt1.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
			&(tm1.tm_year),
			&(tm1.tm_mon),
			&(tm1.tm_mday),
			&(tm1.tm_hour),
			&(tm1.tm_min),
			&(tm1.tm_sec));

		tm1.tm_year -= 1900;
		tm1.tm_mon--;
		tm1.tm_isdst = -1;

		sscanf(dt2.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
			&(tm2.tm_year),
			&(tm2.tm_mon),
			&(tm2.tm_mday),
			&(tm2.tm_hour),
			&(tm2.tm_min),
			&(tm2.tm_sec));

		tm2.tm_year -= 1900;
		tm2.tm_mon--;
		tm2.tm_isdst = -1;

		time_t time_day1 = mktime(&tm1);
		time_t time_day2 = mktime(&tm2);

		long long value = abs(time_day1 - time_day2);
		return fabs(value);
	}

	int getCurrentDateInt()
	{
		time_t t;
		struct tm *st;
		time(&t);
		st = localtime(&t);

		char szBuffer[40] = { 0 };
		snprintf(szBuffer, sizeof(szBuffer) - 1, "%04d%02d%02d", st->tm_year, st->tm_mon, st->tm_mday);
		return atoi(szBuffer);
	}

	const size_t get_cpu_count(void)
	{
		//may return 0 when not able to detect
		//return std::thread::hardware_concurrency();
#ifdef WIN32 
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		return sysinfo.dwNumberOfProcessors;
#elif MACOS 
		int nm[2];
		size_t len = 4;
		uint32_t count;

		nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);

		if (count < 1) {
			nm[1] = HW_NCPU;
			sysctl(nm, 2, &count, &len, NULL, 0);
			if (count < 1) { count = 1; }
		}
		return count;
#else 
		return sysconf(_SC_NPROCESSORS_ONLN);
#endif 
	}

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


