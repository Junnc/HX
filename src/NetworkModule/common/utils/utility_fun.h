/*
* Purpose: Ϊ�����ṩ��������
*/
#ifndef __UTILITY_FUN_H__
#define __UTILITY_FUN_H__

#include <string>

namespace UtilityFun{
    #define HX_DOUBLE_PRECISE           1e-8  //  double�����ݾ���
    #define HX_FOREIGN_TIME             60000 //  ʱ��6:00:00
    #define HX_INNER_STIME              60000  // ʱ��6:00:00
    #define HX_INNER_ETIME              90000  // ʱ��9:00:00
    // mixSpace: ��С�䶯��λ
    extern bool compareDouble(double left, double right, double mixSpace = HX_DOUBLE_PRECISE);

    // ��ȡ128λGUID,ASCII��ʾʱΪ32���ַ���4���ָ���
    extern std::string createGUID();

	// ��ȡ��ǰ���,��ʽ:YYYY
	extern int getCurrentYear();
    // ��ȡ��ǰ����,��ʽ:YYYY-MM-DD
    extern std::string getCurrentDate();
    // ��ȡ��ǰʱ��,��ʽ:HH:MM:SS
    extern std::string getCurrentTime();
    // ��ȡ��ǰ����ʱ��,��ʽ:YYYY-MM-DD HH:MM:SS
    extern std::string getCurrentDateTime();
    // ��ȡ��ǰ����+Ư������,��ʽ:YYYY-MM-DD
    extern std::string getAddDate(int days);
    extern std::string getAddDate(const std::string& d1, int days);
	// ��ȡ��ǰ����+Ư������,��ʽ:YYYY-MM-DD HH:MM:SS
	extern std::string getAddTime(int secs);
	// ��ȡ��������֮�����ʱ��������,������ȡ
    extern int getDateSpace(const std::string& d1, const std::string& d2);
    extern int getDateTimeSpace(const std::string& dt1, const std::string& dt2);
	extern int getTimeSpace(const std::string& dt1, const std::string& dt2);

	// ��ȡ��ǰ����,��ʽ:YYYYMMDD
	extern int getCurrentDateInt();

    extern const size_t get_cpu_count(void);

    //  �ж�ʵ���Ƿ����
    extern bool IsEqual(double left, double right);
    //  �������� ���� base > 0
    extern double Round(double src, double base);
    //  �ɷ�����
    extern bool CanBeDivided(double src, double base);

    //��ȡ��ǰ int date & int time
    extern void GetCurrentIntdateAndIntTime(int& date, int& time);

    extern int GetDaysOfMonth(int nYear, int nMonth);

    //�Ƚ�int date int timeʱ���¾�
    extern bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2);
    //��ȡʱ��
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
	// ��ȡָ��ʱ�䷵��string����ƴ��
	extern  std::string  TranslateDateTime(int date, int time);
	// ��ȡʱ�� string ת int
	extern  std::string  TranslateTimeString(int time);
	extern  std::string  TranslateDoubleToString(double price);

	// ��ȡָ��ʱ�䷵��string���� ��ʽ:HH:MM:SS
	extern  std::string  TranslateTime(int time);
	// ��ȡָ�����ڷ���string���� ��ʽ:YYYY-MM-DD
	extern  std::string  TranslateDate(int date);

	// ��ȡ��ǰʱ��string ����
	extern std::string GetCurrentTimeString();

	// ��ȡָ��string ����ʱ�� 2018-01-24 15:34:31  ���� ���ں�ʱ��int���� 20180124 153431   �ɹ�����true,ʧ�� false
	extern bool GetDateAndTimeInt(std::string  dateTime, int&  date, int& time);

	// ��ȡָ��String ʱ��2018-01-24 ������ʱ��int���� 20180124 �ɹ�����true,ʧ�� false
	extern bool GetTimeInt(std::string  time,  int& tTime);
	// ��ȡָ��String ʱ��15:34:31����������int���� 153431 �ɹ�����true,ʧ�� false
	extern bool GetDateInt(std::string  date, int& tDate);

}

#endif