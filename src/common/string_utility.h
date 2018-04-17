#ifndef     __STRING_UTILITY_H__
#define     __STRING_UTILITY_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>

// ²»·Ö´óÐ¡Ð´µÄ×Ö·û´®±È½Ïº¯Êý
#ifdef _WIN32
#ifndef STRNCASECMP
#define STRNCASECMP			_strnicmp
#endif
#ifndef STRCASECMP
#define STRCASECMP			_stricmp
#endif
#define snprintf            _snprintf
#else
#ifndef STRNCASECMP
#define STRNCASECMP			strncasecmp
#endif
#ifndef STRCASECMP
#define STRCASECMP			strcasecmp
#endif
#endif

#ifdef _WIN32
#define END_LINE "\r\n"
#else
#define END_LINE "\n"
#endif

#ifndef ISALPHA_DIGIT_SPACE

#define ISALPHA_DIGIT_SPACE
#define ISALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define ISDIGIT(c) (c >= '0' && c <= '9')
#define ISSPACE(c) (c == ' ' || c == '\t' || c == '\r' || c == '\n')
#endif

#ifdef __GNUC__
#define SU_DEPRECATED_BY(New)  __attribute__((deprecated))
#else
#ifdef _MSC_VER
#if _MSC_VER >= 1400
#define SU_DEPRECATED_BY(New) __declspec(deprecated(#New))
#else
#define SU_DEPRECATED_BY(New) __declspec(deprecated)
#endif
#endif //_MSC_VER
#endif

class StringUtility
{
public:
    static std::string TrimLeft(const std::string& strValue, const std::string& strTarget);
    static std::string TrimLeft(const std::string& strValue);

    static std::string TrimRight(const std::string& strValue, const std::string& strTarget);
    static std::string TrimRight(const std::string& strValue);

    static std::string Trim(const std::string& strValue, const std::string& strTarget);
    static std::string Trim(const std::string& strValue);

    SU_DEPRECATED_BY(Trim) static std::string TrimBothSides(const std::string& strValue, const std::string& strTarget = "\r\n \t")
    {
        return Trim(strValue, strTarget);
    }

    static void InplaceTrimLeft(std::string& strValue, const std::string& strTarget);
    static void InplaceTrimRight(std::string& strValue, const std::string& strTarget);
    static void InplaceTrim(std::string& strValue, const std::string& strTarget);
    static void InplaceTrimLeft(std::string& strValue);
    static void InplaceTrimRight(std::string& strValue);
    static void InplaceTrim(std::string& strValue);

    static bool TestTrimLeft(const std::string& strValue);
    static bool TestTrimRight(const std::string& strValue);
    static bool TestTrim(const std::string& strValue);
    static bool TestTrimLeft(const std::string& strValue, const std::string& strTarget);
    static bool TestTrimRight(const std::string& strValue, const std::string& strTarget);
    static bool TestTrim(const std::string& strValue, const std::string& strTarget);

    static std::string TrimChineseSpace(const std::string& strValue);

    static std::string TrimBothChEnSpace(const std::string& strValue);

    static void Split(const std::string& strMain,
                      char chSpliter,
                      std::vector<std::string>& strList,
                      bool bReserveNullString = false);
    static void Split(const std::string& strMain,
                      const std::string& strSpliter,
                      std::vector<std::string>& strList,
                      bool bReserveNullString = false);

    SU_DEPRECATED_BY(Split) static void SplitString(
        const std::string& strMain,
        const std::string& strSpliter,
        std::vector<std::string>& strList,
        bool bReserveNullString = false)
    {
        Split(strMain, strSpliter, strList, bReserveNullString);
    }

    static void SplitString(const std::string& strMain,
                            std::vector<std::string>& strList);

    static std::string ReplaceStr(const std::string& strValue,
                                  const std::string& oldStr,
                                  const std::string& newStr);

  
    static std::string ReplaceCharSet(const std::string& strOld,
                                      std::string strFromSet,
                                      std::string strToSet);

    static std::string ReplaceStrSet(const std::string& strRawData,
                                     std::map<std::string, std::string>& mSet);

    static std::string RemoveChar(std::string& strRawData, char ch);

    static std::string RemoveStr(std::string& strRawData, std::string strSubStr, bool bNeedSeparator = false);

    static std::string RemoveStrSet(const std::string& strRawData,
                                    std::set<std::string>& sStrSet, bool bNeedSeparator = false);

    static std::string DeleteSubstr(const std::string& strRawData, std::string strBegin, std::string strEnd);

    static std::string ExtractSubstr(const std::string& strInput, std::string& strPattern);

    static std::string QuoteWild(const char* strRaw);
    static std::string QuoteWild(const char* strRaw, size_t size);
    static std::string QuoteWild(const std::string& strRaw);
    static std::string AbstractString(std::string& strOldStr, int dwLen, std::string& strLeftStr);

    static bool CmpNoCase(char c1, char c2);
    
    static char * FindNoCaseEnStrWithLength(const char * pcBegin,const char * pcEnd,const char * pcSubStr);
    
    static std::string::size_type FindNoCase(const std::string& strMain, const std::string& strSub, size_t dwFrom = 0);

    static std::string::size_type RFindNoCase(const std::string& strMain, const std::string& strSub, size_t dwFrom);

    static char* WStrChr(const char* pcMain, const char* pcWChar);

    static char* RWStrChr(const char* pcMain, const char* pcWChar);

    static std::string::size_type RWStrChr(const std::string& strMain, const std::string& strWChar);

    static char* WFind(const char* pcMain, const char* pcSub);

    static int GetCharCount(const std::string& strWord);

    static int GetCharCount(const std::string& strWord, char c);

    static int StatStr(const std::string& strWord, int& dwAlpha, int& dwDigit);

    static int GetSubStrCnt(const std::string& strMain, const std::string& strSubStr, bool bNoCase = true);

    static int GetChineseCharCount(const std::string& strWord);

    static std::string GetNextChar(const std::string& str, size_t dwCurPos);

    static char* GetNextValidEndPos(char* pcCurPos, char* pcEnd, char cEndSign = '>');

    static bool IsSubStrContained(const std::string& strRawData, const std::set<std::string>& sSubStr);

    static bool IsDigitIp(const std::string& strIp);

    static bool IsWhiteString(char const *pStr);

    static bool IsEnglishString(const char* pStr, bool bLowLineAsAlpha = false);

    static bool IsDigitString(const char* pStr);

    static bool IsHexDigitString(const char* pStr);

    static int GetGB2312HanziIndex(const std::string& str);

    static bool IsGB2312Hanzi(const std::string& str);

    static bool IsOnlyComposedOfGB2312Hanzi(const std::string& strWord);

    static bool IsSpace(char c);

    static bool IsAlnum(char c);

    static bool IsDigit(char c);

    static bool IsAlpha(char c);

    static bool IsSeparator(char c);

    static bool IsValidUrl(char* pcUrl);

    static char CharToLower(char c);

    static char CharToUpper(char c);

    static std::string ToLower(const char *pszValue);

    static std::string ToUpper(const char *pszValue);
    static std::string Int2Str(int dwValue);

    static std::string Int2Str(unsigned int  dwValue);

    /** °Ñ×Ö·û´®×ªÎªÕûÐÍÊý */
    static int Str2Int(const std::string& str);

    /** °Ñ×Ö·û´®×ªÎªÎÞ·ûºÅÕûÐÍÊý */
    static unsigned int Str2UInt(const std::string& str);

    /**°Ñ×Ö·û´®×ªÎªlong longÐÍÊý*/
    static long long Str2LongLong(const std::string& str);

    /**°Ñ×Ö·û´®×ªÎªunsigned long longÐÍÊý*/
    static unsigned long long Str2ULongLong(const std::string& str);

    /** °ÑÒ»¸ölong longÖµ×ª»»³ÉÎª×Ö·û´®*/
    static std::string LongLong2Str(long long ddwValue);

    /** °ÑÒ»¸ölong longÖµ×ª»»³ÉÎª×Ö·û´®*/
    static std::string ULongLong2Str(unsigned long long ddwValue);

    /** °Ñ×Ö·û´®×ªÎª¸¡µãÊý */
    static double Str2Double(const std::string& str);

    /** °Ñ¸¡µãÊý×ªÎª×Ö·û´® */
    static std::string Double2Str(double);

    /** °Ñ16½øÖÆµÄ×Ö·û´®×ªÎªÕûÐÍÊý */
    static int HexStr2long(const char* pcHex);

    /** ÒÔÊ®Áù½øÖÆµÄ¸ñÊ½´òÓ¡£¬µ÷ÊÔÊ±ºòÊ¹ÓÃ */
    static void Str2HexStr(char* pcHexStr, unsigned char * p,int len);

    /** °ÑÒ»¸ö×Ö·û×ª»»³É16½øÖÆµÄÐÎÊ½ */
    static std::string Char2Hex(unsigned char ch);

    static void ToHxString(char* pcBinStr, char * title, unsigned char * p,int len);

    /** ÒÔÊ®Áù½øÖÆµÄ¸ñÊ½´òÓ¡£¬µ÷ÊÔÊ±ºòÊ¹ÓÃ */
    static void BinPrint(char * title, unsigned char * p,int len);

    /** ×Ô¶¯ÒÔ¿ÉÏÔÊ¾µÄ¸ñÊ½´òÓ¡£¬µ÷ÊÔÊ±ºòÊ¹ÓÃ */
    static void PrintWithAutoArrange(char* pText, int dwLineWidth = 80);

    /** °ÑÒ»¸ösetÊä³öÎªÒ»¸ö×Ö·û´® */
    static std::string OutputSet(const std::set<std::string>& strSet);

    /** °ÑÒ»¸öVectorÊä³öÎªÒ»¸ö×Ö·û´® */
    static std::string OutputVector(const std::vector<std::string>& strVec);

    /** °ÑÒ»¸ömapÊä³öÎªÒ»¸ö×Ö·û´® */
    static std::string OutputMap(const std::map<std::string, std::string>& strMap);

    /** °ÑÒ»¸ömapÊä³öÎªÒ»¸ö×Ö·û´® */
    static std::string OutputMap(const std::map<std::string, int>& strMap);

    /** °ÑÒ»¸ömultimapÊä³öÎªÒ»¸ö×Ö·û´® */
    static std::string OutputMultiMap(const std::multimap<std::string, std::string>& strMap);

    /** ÅÐ¶ÏÒ»¸ö×Ö·ûÊÇ·ñÔÚÒ»¸ö×Ö·û´®ÖÐ */
    static bool IsCharInStr(unsigned char ch, const std::string& strTarget);

    /** °ÑÒ»¸ö×Ö·û´®ÖÐµÄÁ¬Ðø¿Õ¸ñ×ªÎªµ¥¸ö¿Õ¸ñ */
    static std::string SingleBlank(const std::string& strRaw);

    /** É¾³ýhtml»òxml¸ñÊ½µÄ×¢ÊÍ <!-- -->, µÈ¼ÛÓÚDeleteSubstr(str, "<!--", "-->"), µ«ÊÇÐÔÄÜÒª¸ß */
    static std::string StripComments(const std::string& strRawFile);

    /** ¼ÆËãÒ»¸ö×Ö·û´®µÄhashÖµ */
    static unsigned int GetStrHashValue(const char* pcStr);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ×Ö·û´®Ä£ºýÆ¥ÅäÊµÏÖ£¨¾ÍÊÇ¼òµ¥µÄÕýÔò±í´ïÊ½ÒÔ¼°·¶Î§Æ¥Åä¹¦ÄÜ£©

    /** ¼ì²éÒ»¸ö×Ö·û´®ÊÇ·ñÄÜÆ¥Åäµ½Ò»¸öÍ¨Åä·ûºÅ
     *  MatchWildcard("he*o","hello"): true
     *  MatchWildcard("he*p","hello"): false
     *  MatchWildcard("he??o","hello"): true
     *  MatchWildcard("he?o","hello"): false
     *  MatchWildcard("[a-z][0-9]","h7"): true
     *  MatchWildcard("172.16.*","172.16.68.29"): true
     */
    static bool MatchWildcard(const std::string& strWild, const std::string& strMatch);

    /** ¹¦ÄÜ: ¼ÆËãÁ½¸ö×Ö·û´®µÄÏàËÆ¶È
     *    ÊäÈë²ÎÊý const std::string& strA      ×Ö·û´®1
     *    ÊäÈë²ÎÊý const  std::string& strB     ×Ö·û´®2
     */
    static int CalcSimilar(const std::string& strA, const std::string& strB);
    static int CalcSimilarEx(const char* pcStrA, int dwLenA, const char* pcStrB, int dwLenB);

    // Éú³ÉCRC-16-CCITTËã·¨Ç©Ãû
    static unsigned short crc16_ccitt(const char *ucbuf, int iLen);

    // °Ñ16½øÖÆ×Ö·û´®»¹Ô­³ÉÔ­Ê¼µÄ×Ö·û´®
    static std::string HexDigit2String(const char* pStr);

	//»ñÈ¡±àÒëÊ±¼ä	
	static std::string GetBuildTime();

private:

    static bool _MatchSet(const std::string& strPattern, char strMatch);

    static bool _MatchRemainder(const std::string& strWild,
                                std::string::const_iterator itWild,
                                const std::string& strMatch,
                                std::string::const_iterator itMatch);

};

#undef SU_DEPRECATED_BY

#endif

