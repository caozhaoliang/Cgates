#ifndef _BASE64_H_
#define _BASE64_H_
#include <sys/types.h>
class Base64
{
public:
	Base64(){}
	virtual ~Base64(){}
	/*
	 *用作base64 加密 data为需要加密的参数
	 * str 为加密后出参 size 为入参长度
	 */
	size_t encode(char* str, const void* data, int size);

	/*
	 *用作base64 解密 p_szDest为解密后数据 p_szSrc为需要解密的
	 */
	size_t decode(unsigned char* const p_szDest,const char* p_szSrc);
private:
	char base2Chr(unsigned char n);
	unsigned char chr2Base(char c);
};


#endif