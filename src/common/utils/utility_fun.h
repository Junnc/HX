/*
 * Purpose: 为程序提供公共函数
 */
#ifndef __UTILITY_FUN_H__
#define __UTILITY_FUN_H__

#include <string>

namespace UtilityFun{
#define HX_DOUBLE_PRECISE           1e-8  //  double型数据精度
#define HX_FOREIGN_TIME             60000 //  时间6:00:00
#define HX_INNER_STIME              60000  // 时间6:00:00
#define HX_INNER_ETIME              90000  // 时间9:00:00
	// mixSpace: 最小变动单位
	extern bool compareDouble(double left, double right, double mixSpace = HX_DOUBLE_PRECISE);

	// 获取128位GUID,ASCII表示时为32个字符加4个分隔符
	extern std::string createGUID();

	// 获取当前年份,格式:YYYY
	extern int getCurrentYear();
	// 获取当前日期,格式:YYYY-MM-DD
	extern std::string getCurrentDate();
	// 获取当前时间,格式:HH:MM:SS
	extern std::string getCurrentTime();
	// 获取当前日期时间,格式:YYYY-MM-DD HH:MM:SS
	extern std::string getCurrentDateTime();
	// 获取当前日期+漂移天数,格式:YYYY-MM-DD
	extern std::string getAddDate(int days);
	extern std::string getAddDate(const std::string& d1, int days);
	// 获取当前日期+漂移秒数,格式:YYYY-MM-DD HH:MM:SS
	extern std::string getAddTime(int secs);
	// 获取两个日期之间相差时间间隔天数,余数不取
	extern int getDateSpace(const std::string& d1, const std::string& d2);
	extern int getDateTimeSpace(const std::string& dt1, const std::string& dt2);
	extern int getTimeSpace(const std::string& dt1, const std::string& dt2);

	// 获取当前日期,格式:YYYYMMDD
	extern int getCurrentDateInt();

	extern const size_t get_cpu_count(void);

	//  判断实数是否相等
	extern bool IsEqual(double left, double right);
	//  四舍五入 其中 base > 0
	extern double Round(double src, double base);
	//  成否被整除
	extern bool CanBeDivided(double src, double base);

	//获取当前 int date & int time
	extern void GetCurrentIntdateAndIntTime(int& date, int& time);

	extern int GetDaysOfMonth(int nYear, int nMonth);

	//比较int date int time时间新旧
	extern bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2);
	//获取时间
	extern int GetPreWorkDay(int dt);
	extern void GetPreWorkDayToSelf(int& outYear, int& outMon, int& outDay);
	extern void GetPreWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
	extern void GetPreDay(int year, int month, int day, int& outYear, int& outMonth, int& outDay);
	extern int GetPreDay(int inDay);
	extern void GetPreDayToSelf(int& outYear, int& outMonth, int& outDay);
	extern bool isLeapYear(int year);
	extern int GetDaysOfYear(int year);
	extern int GetDayOfWeek(int y, int m, int d);
	extern int GetDayOfWeek(int date);
	extern int GetNextWorkDay(int dt);
	extern void GetNextWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
	extern void GetNextDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
	extern int GetNextDay(int date);
	extern void GetNextDayToSelf(int& outYear, int& outMonth, int& outDay);
	extern void GetNextWorkDayToSelf(int& outYear, int& outMonth, int& outDay);

	extern bool TodayIsWeekDayByForeign();
	extern bool TodayIsWeekDayByForeignLimit(int tradetime = HX_FOREIGN_TIME);
	extern bool TodayIsWeekDayByInner();
	extern bool TodayIsWeekDayByInnerLimit(int stime = HX_INNER_STIME, int etime = HX_INNER_ETIME);
	// 获取指定时间返回string类型拼接
	extern  std::string  TranslateDateTime(int date, int time);
	// 获取时间 string 转 int
	extern  std::string  TranslateTimeString(int time);
	extern  std::string  TranslateDoubleToString(double price);

	// 获取指定时间返回string类型 格式:HH:MM:SS
	extern  std::string  TranslateTime(int time);
	// 获取指定日期返回string类型 格式:YYYY-MM-DD
	extern  std::string  TranslateDate(int date);

	// 获取当前时间string 类型
	extern std::string GetCurrentTimeString();

	// 获取指定string 类型时间 2018-01-24 15:34:31  返回 日期和时间int类型 20180124 153431   成功返回true,失败 false
	extern bool GetDateAndTimeInt(std::string  dateTime, int&  date, int& time);

	// 获取指定String 时间2018-01-24 ，返回时间int类型 20180124 成功返回true,失败 false
	extern bool GetTimeInt(std::string  time,  int& tTime);
	// 获取指定String 时间15:34:31，返回日期int类型 153431 成功返回true,失败 false
	extern bool GetDateInt(std::string  date, int& tDate);

	extern	int getLocalDateInt();
	extern	int getLocalTimeInt();
	extern	int ThreeToOneInt(int n1, int n2, int n3);

	extern std::string getDateTimeString();

	extern bool isChineseString(const std::string& sztext);
}

namespace UUID
{
	extern std::string getUUid();

	char *random_uuid(char buf[37]);
}

#endif
