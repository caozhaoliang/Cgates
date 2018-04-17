#include "time_utility.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>

#include <vector>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include "string_utility.h"

using namespace std;

/** »ñµÃµ±Ç°Ê±¼ä */
string TimeUtility::GetCurTime()
{
    return GetStringTime(time(NULL));
}

/** »ñµÃµ±Ç°ÈÕÆÚ£¬²»°üº¬Ê±¼ä */
string TimeUtility::GetCurDate(bool bIsEnglishFormat)
{
    time_t tTime = time (NULL);
    return GetDate(tTime, bIsEnglishFormat);
}

/** »ñµÃµ±Ç°Äê */
int TimeUtility::GetCurYear()
{
    return GetYear(time(NULL));
}

/** »ñµÃµ±Ç°ÔÂ */
int TimeUtility::GetCurMonth()
{
    return GetMonth(time(NULL));
}

/** »ñµÃµ±Ç°Ìì */
int TimeUtility::GetCurDay()
{
    return GetDay(time(NULL));
}

/** »ñµÃµ±Ç°ÊÇÐÇÆÚ¼¸ */
int TimeUtility::GetCurWeek()
{
    return GetWeek(time(NULL));
}

/** »ñµÃµ±Ç°Ð¡Ê± */
int TimeUtility::GetCurHour()
{
    return GetHour(time(NULL));
}

/** »ñµÃµ±Ç°·ÖÖÓ */
int TimeUtility::GetCurMinute()
{
    return GetMinute(time(NULL));
}

/** »ñµÃµ±Ç°Ãë */
int TimeUtility::GetCurSecond()
{
    return GetSecond(time(NULL));
}

/** »ñµÃµ±Ç°ºÁÃë */
unsigned int TimeUtility::GetCurMilliSecond()
{
    time_t dwPreciseTime;
#ifdef _WIN32
    struct _timeb tbNow;
    _ftime(&tbNow);
    dwPreciseTime = tbNow.millitm;
#else
    struct timeval tvNow;
    gettimeofday(&tvNow, NULL);
    dwPreciseTime = tvNow.tv_usec / 1000;
#endif
    return (unsigned int)dwPreciseTime;
}

/** »ñµÃµ±Ç°Î¢Ãë */
unsigned long long TimeUtility::GetCurMicroSecond()
{
    unsigned long long dwPreciseTime;
#ifdef _WIN32
    struct _timeb	tbNow;
    _ftime(&tbNow);
    dwPreciseTime = (unsigned long long)tbNow.millitm * 1000;
#else
    struct timeval	tvNow;
    gettimeofday(&tvNow, NULL);
    dwPreciseTime = (unsigned long long)(tvNow.tv_sec*1000 + tvNow.tv_usec/1000);
#endif
    return dwPreciseTime;
}

/** »ñµÃµ±Ç°ÈÕÆÚ£¬²»°üº¬Ê±¼ä */
string TimeUtility::GetDate(time_t tTime, bool bIsEnglishFormat)
{
    struct tm	*lptmNow;
    char szBuf[32];
#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    // linuxÏÂÃ»ÓÐÖ±½Ó»ñµÃÈÕÆÚµÄº¯Êý
    struct tm	tmNow;
    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    if (bIsEnglishFormat)
    {
        snprintf(szBuf, sizeof(szBuf), "%04d-%02d-%02d",
                 lptmNow->tm_year + 1900,
                 lptmNow->tm_mon + 1,
                 lptmNow->tm_mday);
    }
    else
    {
        snprintf(szBuf, sizeof(szBuf), "%04dÄê%02dÔÂ%02dÈÕ",
                 lptmNow->tm_year + 1900,
                 lptmNow->tm_mon + 1,
                 lptmNow->tm_mday);
    }
    return string(szBuf);
}

/** »ñµÃÄê */
int TimeUtility::GetYear(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return 1900+lptmNow->tm_year;
}

/** »ñµÃÔÂ */
int TimeUtility::GetMonth(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_mon+1;
}

/** »ñµÃÌì */
int TimeUtility::GetDay(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_mday;
}

/** »ñµÃÐÇÆÚ¼¸ */
int TimeUtility::GetWeek(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_wday;
}


/** »ñµÃÐ¡Ê± */
int TimeUtility::GetHour(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_hour;
}


/** »ñµÃ·ÖÖÓ */
int TimeUtility::GetMinute(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_min;
}

/** »ñµÃµ±Ç°Ãë */
int TimeUtility::GetSecond(const time_t tTime)
{
    struct tm	*lptmNow;

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif
    return lptmNow->tm_sec;
}

/** °ÑÕûÊýÊ±¼ä×ªÎª×Ö·û´®Ê±¼ä */
string TimeUtility::GetStringTime(const time_t tTime)
{
    if (tTime < 0)
        return GetCurTime();

    struct tm	*lptmNow;
    char		sTime[sizeof("2009-12-03 11:09:56")];

#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;

    lptmNow = localtime_r(&tTime, &tmNow);
#endif

    memset(sTime, 0, sizeof(sTime));
    size_t length = strftime(sTime, sizeof(sTime), "%F %T", lptmNow);
    return string(sTime, length);
}

/** »ñµÃµ±Ç°Ê±¼ä£¬¾«È·µ½Î¢Ãë */
string TimeUtility::GetCurPreciseTime()
{
    struct tm	*lptmNow;
    time_t		nTime;
    int nPreciseTime;
    char		sTime[256];

#ifdef _WIN32
    struct _timeb	tbNow;

    _ftime(&tbNow);
    nTime = tbNow.time;
    nPreciseTime = tbNow.millitm;
#else
    struct timeval	tvNow;

    gettimeofday(&tvNow, NULL);
    nTime = tvNow.tv_sec;
    nPreciseTime = tvNow.tv_usec;
#endif

    memset(sTime, 0, sizeof(sTime));
#ifdef _WIN32
    lptmNow = localtime((const time_t *)&nTime);
    sprintf(sTime, "%04d-%02d-%02d %02d:%02d:%02d:%03d",
            1900+lptmNow->tm_year, lptmNow->tm_mon+1, lptmNow->tm_mday,
            lptmNow->tm_hour, lptmNow->tm_min, lptmNow->tm_sec, nPreciseTime);
#else
    struct tm	tmNow;
    lptmNow = localtime_r((const time_t *)&nTime, &tmNow);
    sprintf(sTime, "%04d-%02d-%02d %02d:%02d:%02d:%06d",
            1900+lptmNow->tm_year, lptmNow->tm_mon+1, lptmNow->tm_mday,
            lptmNow->tm_hour, lptmNow->tm_min, lptmNow->tm_sec, nPreciseTime);

#endif

    return string(sTime);
}

bool TimeUtility::IsLeapYear(const int dwYear)
{
    if((dwYear % 100) == 0)
    {
        if((dwYear % 400) == 0)
            return false;
        else
            return true;
    }
    if((dwYear % 4) == 0)
        return false;
    return true;
}

/** Ëæ»úÊý³õÊ¼»¯ */
void TimeUtility::InitRand()
{
    int	dwSecond;
    int dwUSecond;
#ifdef _WIN32
    struct _timeb	tbNow;

    _ftime(&tbNow);
    dwSecond = (int)tbNow.time;
    dwUSecond = tbNow.millitm;
#else
    struct timeval	tvNow;

    gettimeofday(&tvNow, NULL);
    dwSecond = tvNow.tv_sec;
    dwUSecond = tvNow.tv_usec;
#endif

    srand(dwSecond * dwUSecond);
}

/** ²úÉúÒ»¸öËæ»úÕûÊý */
int TimeUtility::GetRandInt(int dwMin, int dwMax)
{
    return dwMin + (int) ((dwMax - dwMin)*1.0*rand()/(RAND_MAX+1.0));
}

/** Ïß³ÌË¯Ãß£¬µ¥Î»ÊÇÎ¢Ãë */
void TimeUtility::USleep(unsigned long dwUSeconds)
{
#ifdef _WIN32
    Sleep(dwUSeconds / 1000);
#else
    struct timeval oDelay;
    oDelay.tv_sec = (unsigned long)dwUSeconds / 1000000;
    oDelay.tv_usec = (unsigned long)dwUSeconds % 1000000;
    select(0, 0, 0, 0, &oDelay);
#endif
}

/**************** ÏÂÃæÊµÏÖ×Ô¶¯Ê¶±ðÊ±¼ä¸ñÊ½µÄ·½·¨ *************/

/** ×Ô¶¯µÄ°ÑÊ±¼ä×ªÎªtime_tÀàÐÍµÄ, Êä³öµÄ×Ö·û´®Ó¦¸ÃÊÇ¾­¹ý´¦ÀíµÄ */
/** Ä¿Ç°²»ÄÜ´¦ÀíÕâÑùµÄ: Sat, 05 Jan 2008 15:35:21 GMT+8 */
time_t TimeUtility::NormalizeTime(const std::string& strRawTime)
{
    string strDate;
    string strTime;
    struct tm oTime = {};

    // ÕâÀïÏàµ±ÊÇÈ±Ê¡Öµ
    oTime.tm_year = GetCurYear();
    oTime.tm_hour = 0;//GetCurHour();
    oTime.tm_min  = 0;//GetCurMinute();
    oTime.tm_sec  = 0;//GetCurSecond();

    string::size_type dwPos = strRawTime.find(" ");

    // Ã»ÓÐÕÒµ½¿Õ¸ñËµÃ÷Ö»ÓÐÈÕÆÚÃ»ÓÐÊ±¼ä
    if (string::npos == dwPos)
    {
        strDate = strRawTime;
    }
    else
    {
        strDate = strRawTime.substr(0, dwPos);
        strTime = strRawTime.substr(dwPos+1);
    }

    vector<string> vDate;
    string         strTmp;
    for (size_t i = 0 ; i < strDate.size(); i++)
    {
        if (strDate[i] >= '0' && strDate[i] <= '9')
        {
            strTmp += strDate[i];
        }
        else
        {
            if (!strTmp.empty())
            {
                vDate.push_back(strTmp);
                strTmp = "";
            }
        }
    }
    if (!strTmp.empty())
    {
        vDate.push_back(strTmp);
        strTmp = "";
    }

    // ÈÕÆÚÍêÕûµÄÇé¿ö
    if (3 == vDate.size())
    {
        // 2006-4-30 »ò 2006/4/30 µÄÇé¿ö
        if (vDate[0].size() == 4)
        {
            oTime.tm_year = StringUtility::Str2Int(vDate[0]);
            oTime.tm_mon = StringUtility::Str2Int(vDate[1]);
            oTime.tm_mday = StringUtility::Str2Int(vDate[2]);
        }
        // 30/4/2006 µÄÇé¿ö
        else if (vDate[2].size() == 4)
        {
            oTime.tm_year = StringUtility::Str2Int(vDate[2]);
            oTime.tm_mon = StringUtility::Str2Int(vDate[1]);
            oTime.tm_mday = StringUtility::Str2Int(vDate[0]);
        }
        // 30/4/06»ò06/4/30 µÄÇé¿ö£¬ Õâ¸ö·Ç³£²»ºÃÅÐ¶ÏÄêÔÂÈÕµÄË³Ðò
        else
        {
            int  dwYear = GetCurYear() - 2000;
            int  dwTmp0 = StringUtility::Str2Int(vDate[0]);
            int  dwTmp1 = StringUtility::Str2Int(vDate[1]);
            int  dwTmp2 = StringUtility::Str2Int(vDate[2]);
            bool bIsYMDOrder;
            if(dwTmp0 == dwYear)
                bIsYMDOrder = true;
            else if(dwTmp2 == dwYear)
                bIsYMDOrder = false;
            else if(abs(dwYear - dwTmp0) <= 2)
                bIsYMDOrder = true;
            else if(abs(dwYear - dwTmp2) <= 2)
                bIsYMDOrder = false;
            else
                bIsYMDOrder = true;

            if (bIsYMDOrder)
            {
                oTime.tm_year = dwTmp0 + 2000;
                oTime.tm_mon  = dwTmp1;
                oTime.tm_mday = dwTmp2;
            }
            else
            {
                oTime.tm_year = dwTmp2 + 2000;
                oTime.tm_mon  = dwTmp1;
                oTime.tm_mday = dwTmp0;
            }
        }
    }
    // Ö»ÓÐÔÂºÍÌìµÄÇé¿ö
    else if (2 == vDate.size())
    {
        oTime.tm_mon = StringUtility::Str2Int(vDate[0]);
        oTime.tm_mday = StringUtility::Str2Int(vDate[1]);
    }

    // Èç¹ûÓÐÊ±¼ä
    if (!strTime.empty())
    {
        vector<string> vTime;
        bool bIsPM = false; // ÊÇ·ñÊÇÏÂÎç

        for (size_t i = 0 ; i < strTime.size(); i++)
        {
            if ((strTime[i] >= '0') && (strTime[i] <= '9'))
            {
                strTmp += strTime[i];
            }
            else if ((strTime[i] == ' ') || (strTime[i] == ':') || (strTime[i] == '/')
                     || (strTime[i] == '-') || (strTime[i] == '.'))
            {
                if (!strTmp.empty())
                {
                    vTime.push_back(strTmp);
                    strTmp = "";
                }
            }
            else if ((0 == strTime.compare(i, 2, "PM")) || (0 == strTime.compare(i, 2, "pm")))
            {
                bIsPM = true;
            }
            else
            {
                break;
            }
        }
        if (!strTmp.empty())
        {
            vTime.push_back(strTmp);
            strTmp = "";
        }

        // Ê±¼äÍêÕûµÄÇé¿ö
        if (3 == vTime.size())
        {
            oTime.tm_hour = StringUtility::Str2Int(vTime[0]);
            oTime.tm_min  = StringUtility::Str2Int(vTime[1]);
            oTime.tm_sec  = StringUtility::Str2Int(vTime[2]);
        }
        // Ö»ÓÐÐ¡Ê±ºÍ·ÖµÄÇé¿ö
        else if (2 == vTime.size())
        {
            oTime.tm_hour = StringUtility::Str2Int(vTime[0]);
            oTime.tm_min  = StringUtility::Str2Int(vTime[1]);
        }

        // Èç¹ûÊÇÏÂÎç
        if (bIsPM)
            oTime.tm_hour += 12;
    }
    oTime.tm_year -= 1900;
    oTime.tm_mon  -= 1;
    return mktime(&oTime);
}

string TimeUtility::NormalizeTimeAsString(const std::string& strRawTime)
{
    time_t t = NormalizeTime(strRawTime);
    string strRet;
    strRet.assign(ctime(&t));
    return strRet;
}

time_t TimeUtility::NormalizeChineseTime(const std::string& strDateTime, std::string& strRawTime)
{
    string::size_type dwYearPos;
    string::size_type dwMonthPos;
    string::size_type dwDayPos;
    struct tm oTime = {};

    // ÈÏÎªÖÐÎÄÊ±¼ä¸ñÊ½ÊÇ:"yyyyÄêMMÔÂDDÈÕhh:mm"»ò"yyyyÄêMMÔÂDDÈÕhh:mm:ss"
    // "yyyyÄêMMÔÂDDÈÕhhÊ±mm·Ö"
    dwYearPos = strDateTime.find("年");
    dwMonthPos = strDateTime.find("月");
    dwDayPos = strDateTime.find("日");

    if(string::npos == dwYearPos || string::npos == dwMonthPos || string::npos == dwDayPos)
    {
        return 0;
    }
    else
    {
        string strYear = strDateTime.substr(0, dwYearPos);
        string strMonth = strDateTime.substr(dwYearPos+2, dwMonthPos-dwYearPos-2);
        string strDay = strDateTime.substr(dwMonthPos+2, dwDayPos-dwMonthPos-2);
        string strTime = strDateTime.substr(dwDayPos+2);

        size_t dwBeginPos, dwEndPos = strYear.size()-1;
        while (dwEndPos > 0 && (strYear[dwEndPos] == ' '))
            dwEndPos--;
        dwBeginPos = dwEndPos;
        while (dwBeginPos > 0 && StringUtility::IsDigit(strYear[dwBeginPos]))
            dwBeginPos--;
        strYear = strYear.substr(dwBeginPos+1, dwEndPos - dwBeginPos+1);

        oTime.tm_year = StringUtility::Str2Int(strYear) - 1900;
        oTime.tm_mon = StringUtility::Str2Int(strMonth) - 1;
        oTime.tm_mday = StringUtility::Str2Int(strDay);
        oTime.tm_hour = 0;
        oTime.tm_min  = 0;
        oTime.tm_sec  = 0;

        strTime = StringUtility::TrimLeft(strTime, " \t");

        string::size_type dwHourPos;
        string::size_type dwMinutePos;

        dwHourPos = strTime.find("时");
        dwMinutePos = strTime.find("分");
        if(string::npos != dwHourPos && string::npos != dwMinutePos)
        {
            string strHour   = strTime.substr(0, dwHourPos);
            string strMinute = strTime.substr(dwHourPos+2, dwMinutePos-dwHourPos-2);
            oTime.tm_hour    = StringUtility::Str2Int(strHour);
            oTime.tm_min     = StringUtility::Str2Int(strMinute);
        }
        else
        {
            dwEndPos = 0;

            while ((dwEndPos < strTime.size() && (strTime[dwEndPos] == ':')) || StringUtility::IsDigit(strTime[dwEndPos]))
                dwEndPos++;
            strTime = strTime.substr(0, dwEndPos);

            string::size_type dwRawTimeBeginPos = strDateTime.find(strYear);
            string::size_type dwRawTimeEndPos;
            if (!strTime.empty())
                dwRawTimeEndPos = strDateTime.find(strTime);
            else
                dwRawTimeEndPos = strDateTime.find("日");
            if (string::npos != dwRawTimeBeginPos && string::npos != dwRawTimeEndPos)
            {
                if (!strTime.empty())
                    strRawTime = strDateTime.substr(dwRawTimeBeginPos, dwRawTimeEndPos-dwRawTimeBeginPos+strTime.size());
                else
                    strRawTime = strDateTime.substr(dwRawTimeBeginPos, dwRawTimeEndPos-dwRawTimeBeginPos+2);
            }

            if (!strTime.empty())
            {
                vector<string> vTime;
                StringUtility::Split(strTime, ":", vTime);
                for (size_t i = 0; i < vTime.size() && i < 3; i++)
                {
                    if (0 == i)
                        oTime.tm_hour =  StringUtility::Str2Int(vTime[i]);
                    else if (1 == i)
                        oTime.tm_min =  StringUtility::Str2Int(vTime[i]);
                    else
                        oTime.tm_sec =  StringUtility::Str2Int(vTime[i]);
                } // end for
            } // end if
        }
    }

    time_t t = mktime(&oTime);
    return t;
}

time_t TimeUtility::NormalizeChineseTime(const std::string& strDateTime)
{
    std::string strRaw;
    return TimeUtility::NormalizeChineseTime(strDateTime, strRaw);
}

time_t TimeUtility::ParseDateTime(const char* str)
{
    struct tm tm = {};

#ifdef _XOPEN_SOURCE
    const char* end = strptime(str, "%F %T", &tm);
    if (end && end - str >= int(sizeof("2009-03-24 00:00:00") - 1)) 
        return mktime(&tm);
#else
    if (sscanf(str,
               "%u-%u-%u %u:%u:%u",
               &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
               &tm.tm_hour, &tm.tm_min, &tm.tm_sec
              ) == 6)
    {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        return mktime(&tm);
    }
#endif

    return time_t(-1);
}

int TimeUtility::GetNowTime(const time_t tTime)
{
    time_t t = tTime;
    struct tm mt = {0};
    localtime_r(&t, &mt);
    int time = mt.tm_hour * 10000 + mt.tm_min * 100 + mt.tm_sec;
    return time;
}

int TimeUtility::GetNowDate(const time_t tTime)
{
    struct tm	*lptmNow;
    char szBuf[32];
#ifdef _WIN32
    lptmNow = localtime(&tTime);
#else
    struct tm	tmNow;
    lptmNow = localtime_r(&tTime, &tmNow);
#endif

   int date = ((lptmNow->tm_year + 1900) * 10000) 
       + ((lptmNow->tm_mon + 1) * 100) 
       + lptmNow->tm_mday;

    return date;
}


