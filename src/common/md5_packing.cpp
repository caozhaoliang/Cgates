#include "md5_packing.h"
#include <string.h>
#include <stdio.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace
{

typedef struct {
	ULONG i[2];
	ULONG buf[4];
	unsigned char in[64];
	unsigned char digest[16];
} MD5_CTX;

void MD5Digest(const void *data, size_t size, void *digest)
{
	static HMODULE hDLL = LoadLibraryA("advapi32.dll");
	static void (WINAPI* MD5Init)(MD5_CTX* context) = (void (WINAPI* )(MD5_CTX* context))GetProcAddress(hDLL,"MD5Init");
	static void (WINAPI* MD5Update)(MD5_CTX* context, const unsigned char* input, unsigned int inlen) =
		(void (WINAPI* )(MD5_CTX* context, const unsigned char* input, unsigned int inlen))GetProcAddress(hDLL,"MD5Update");
	static void (WINAPI* MD5Final)(MD5_CTX* context) = (void (WINAPI*)(MD5_CTX* context))GetProcAddress(hDLL,"MD5Final");

	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, (const unsigned char*)data, (unsigned int)size);
	MD5Final(&md5);
	memcpy(digest, md5.digest, sizeof(md5.digest));
}

}

#else

//#include <openssl/md5.h>
#include "md5.h"
namespace
{
inline void MD5Digest(const void* data, size_t size, void* digest)
{
	struct MD5Context ctx;
	MD5Init(&ctx);
	MD5Update(&ctx, (unsigned char *)data, size);
	MD5Final((unsigned char*)digest, &ctx);
}
}

#endif
void MD5::encode(unsigned char* pcDest, const char* pcSrc)
{
    MD5Digest((void *)pcSrc, ::strlen(pcSrc), pcDest);
}

void MD5::Hash64(const char* pcSrc, char* pcHashValue)
{
	unsigned long long digest;
	Hash64(pcSrc, digest);
    sprintf(pcHashValue, "%llu", digest);
}

void MD5::Hash64(const char* pcSrc, long long& ddwHashValue)
{
	Hash64(pcSrc, strlen(pcSrc), ddwHashValue);
}

void MD5::Hash64(const char* pcSrc, unsigned long long& ddwHashValue)
{
	Hash64(pcSrc, strlen(pcSrc), ddwHashValue);
}

void MD5::Encode(const void* pcSrc, size_t dwSrcLen, unsigned char* pcDest)
{
	MD5Digest((void *)pcSrc, dwSrcLen, pcDest);
}

void MD5::Hash64(const void* pcSrc, size_t dwSrcLen, char* pcHashValue)
{
	unsigned long long digest;
	Hash64(pcSrc, dwSrcLen, digest);
    sprintf(pcHashValue, "%llu", digest);
}

void MD5::Hash64(const void* pcSrc, size_t dwSrcLen, long long& ddwHashValue)
{
    long long digest[DigestLength / sizeof(ddwHashValue)];
    MD5Digest((void *)pcSrc, dwSrcLen, (unsigned char*)digest);
    ddwHashValue = digest[0];
}

void MD5::Hash64(const void* pcSrc, size_t dwSrcLen, unsigned long long& ddwHashValue)
{
    unsigned long long digest[DigestLength / sizeof(ddwHashValue)];
    MD5Digest((void *)pcSrc, dwSrcLen, (unsigned char*)digest);
    ddwHashValue = digest[0];
}

unsigned long long MD5::GetHash64(const char* pcSrc)
{
	unsigned long long result;
	Hash64(pcSrc, result);
	return result;
}

unsigned long long MD5::GetHash64(const void* pcSrc, size_t dwsrclen)
{
	unsigned long long result;
	Hash64(pcSrc, dwsrclen, result);
	return result;
}

#ifdef _LP64
void MD5::Hash64(const char* pcSrc, unsigned long & dwHashValue)
{
	Hash64(pcSrc, strlen(pcSrc), dwHashValue);
}

void MD5::Hash64(const void* pcSrc, size_t dwSrcLen, unsigned long& dwHashValue)
{
    unsigned long digest[DigestLength / sizeof(dwHashValue)];
    MD5Digest((void *)pcSrc, dwSrcLen, (unsigned char*)digest);
    dwHashValue = digest[0];
}
#endif

int MD5::Encode32(unsigned char* input, unsigned int len, string &outstring)
{
	struct MD5Context context;
	unsigned char output[16];
	bzero(output, sizeof(output));
	MD5Init(&context);
	MD5Update(&context, input, len);
	MD5Final(output, &context);

	int ret = 0;
	char key[33];
	bzero(key, sizeof(key));
	for (int i=0; i<16; i++)
	{
		ret += sprintf(key + ret, "%02x", output[i]);
	}
	outstring = string(key);
	return 0;
}

