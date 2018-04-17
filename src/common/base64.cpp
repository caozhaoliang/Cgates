#include "base64.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char base64_code[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char Base64::base2Chr(unsigned char n)
{
	n &= 0x3F;
	if( n < 26 ) {
		return (char)(n+'A');
	}else if( n < 52 ) {
		return (char)(n -26 +'a');
	}else if(n < 62 ){
		return (char)(n -52 +'0');
	}else if( n == 62 ){
		return '+';
	}
	return '/';
}
unsigned char Base64::chr2Base(char c){
	if( c >= 'A' && c <= 'Z' ){
		return (unsigned char)(c - 'A');
	}else if( c >= 'a' && c <= 'z' ) {
		return (unsigned char)(c - 'a' + 26);
	}else if( c >= '0' && c <= '9' ) {
		return (unsigned char)(c - '0' + 52);
	}else if( c == '+'){
		return (unsigned char)62;
	}else if(c == '/'){
		return (unsigned char)63;
	}else{
		return (unsigned char)64;
	}
}

size_t Base64::encode(char* str,const void* data,int size )
{
	assert((0 != str)&&(0 != data)&&(0 <= size));
	char* s,*p;
	int c;
	const unsigned char* q;
	p = s = str;
	q = (const unsigned char*)data;

	for(long i = 0; i < size; ) {
		c = q[i++];
		c *= 256;
		if(i < size){
			c += q[i];
		}
		i++;
		c *= 256;
		if(i < size){
			c += q[i];
		}
		i++;
		p[0] = base64_code[(c&0x00fc0000) >> 18];
		p[1] = base64_code[(c&0x0003f000) >> 12];
		p[2] = base64_code[(c&0x00000fc0) >>  6];
		p[3] = base64_code[(c&0x0000003f) >>  0];
		if( i > size) {
			p[3] = '=';
		}
		if( i> size +1) {
			p[2] = '=';
		}
		p += 4;
	}
	*p = 0;
	return strlen(str);
}

size_t Base64::decode(unsigned char* const p_szDest,
						const char* p_szSrc)
{
	assert((0 != p_szDest)&&(0 != p_szSrc)&&
			((const char*)p_szDest != p_szSrc));
	unsigned char* 	p = p_szDest;
	size_t 			n = strlen( p_szSrc );
	unsigned char 	c, t = 0;
	for(size_t i = 0; i < n; i++){
		if( *p_szSrc == '=' ) {
			break;
		}
		do{
			if( *p_szSrc ) {
				c = chr2Base(*p_szSrc++);
			}else{
				c = (unsigned char)65;
			}
		}while(c==(unsigned char)64);
		if((unsigned char)65 == c ) {
			break;
		}
		switch( i % 4 ){
			case 0:
				t = (unsigned char)(c << 2);
				break;
			case 1:
				*p++ = (unsigned char)(t | (c >> 4) );
				t = (unsigned char)(c << 4 );
				break;
			case 2:
				*p++ = (unsigned char)(t | (c >> 2) );
				t = (unsigned char)(c << 6 );
				break;
			case 3:
				*p++ = (unsigned char)(t |c);
				break;
			default:
				break;
		}
	}
	return (p - p_szDest);
}






