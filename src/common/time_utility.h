#ifndef __TIME_UTILITY_H__
#define __TIME_UTILITY_H__

#include <string>

using namespace std ;

class TimeUtility
{
public:

	static std::string GetCurTime();

    static std::string GetCurDate(bool bIsEnglishFormat = true);

	static int GetCurYear();

	static int GetCurMonth();

	static int GetCurDay();

	static int GetCurWeek();

	static int GetCurHour();

	static int GetCurMinute();

	static int GetCurSecond();

    static unsigned int GetCurMilliSecond();

    static unsigned long long GetCurMicroSecond();

    static std::string GetDate(time_t tTime, bool bIsEnglishFormat = true);

	static int GetYear(const time_t tTime);

	static int GetMonth(const time_t tTime);

	static int GetDay(const time_t tTime);

	static int GetWeek(const time_t tTime);

	static int GetHour(const time_t tTime);

	static int GetMinute(const time_t tTime);

	static int GetSecond(const time_t tTime);

	static std::string GetStringTime(const time_t tTime);

	static std::string GetCurPreciseTime();

    static int GetNowTime(const time_t tTime);

    static int GetNowDate(const time_t tTime);

  
    static time_t PadCurHMS(time_t tRawTime);

	static bool IsLeapYear(const int dwYear);

	static void InitRand();

	static int GetRandInt(int dwMin, int dwMax);

	static void USleep(unsigned long dwUSeconds);

public:

	static time_t NormalizeTime(const std::string& strRawTime);

	static std::string NormalizeTimeAsString(const std::string& strRawTime);

	static time_t NormalizeChineseTime(const std::string& strDateTime, std::string& strRawTime);
	static time_t NormalizeChineseTime(const std::string& strDateTime);

	static time_t ParseDateTime(const char* str);
	static inline time_t ParseDateTime(const std::string& str)
	{
		return ParseDateTime(str.c_str());
	}
};

#endif
