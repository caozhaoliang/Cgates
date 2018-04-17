
#ifndef _MD5_H_
#define _MD5_H_

#include <stddef.h>
#include <string>
using namespace std;

class MD5
{
public:
	static const size_t DigestLength = 16;
	
	static void encode(unsigned char* pcDest, const char* pcSrc);

	static void Hash64(const char* pcSrc, char* pcHashValue);

	static void Hash64(const char* pcSrc, long long& ddwHashValue);

	static void Hash64(const char* pcSrc, unsigned long long& ddwHashValue);

	static void Encode(const void* pcSrc, size_t dwSrcLen, unsigned char* pcDest);

	static int Encode32(unsigned char* input, unsigned int len, string &outstring);

	static void Hash64(const void* pcSrc, size_t dwSrcLen, char* pcHashValue);

	static void Hash64(const void* pcsrc, size_t dwsrclen, long long& ddwhashvalue);
	
	static void Hash64(const void* pcSrc, size_t dwsrclen, unsigned long long& ddwHashValue);
#ifdef _LP64 
	
	static void Hash64(const char* pcSrc, unsigned long & ddwHashValue);
	
	static void Hash64(const void* pcSrc, size_t dwsrclen, unsigned long& ddwHashValue);
#endif
    static unsigned long long GetHash64(const char* pcSrc);
    static unsigned long long GetHash64(const void* pcSrc, size_t dwsrclen);
};

#endif//_MD5_H_

