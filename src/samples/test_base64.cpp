#include <iostream>
#include "base64.h"
#include <string.h>

using namespace std;


int main2()
{
	const char* src = "中国海军出海演戏abcdedf./=";
	char* p = new char[1024];
	Base64* b = new Base64();
	b->encode(p,(const void*)src,strlen(src));
	cout <<p<<endl;

	char* pp = new char[1024];
	b->decode((unsigned char* const)pp,(const char*)p);
	cout <<pp <<endl;
	return 0;
}