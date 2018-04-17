#ifndef _CONFIG_READ_H_
#define _CONFIG_READ_H_
#include <string>
#include <map>
#include <vector>

using namespace std;


class CConfigRead{
public:
	CConfigRead(const char* szFile);
	const char* ReadAsString(const char* szKey,char const* szDefault="");
	const char* ReadAsString(int index,const char* szKey,char const* szDefault="");
	int ReadAsInt(const char* szKey,int iDefault = 0);
	int ReadAsInt(int index,const char* szKey,int iDefault=0);
	unsigned int ReadAsUint(const char* szKey,unsigned int iDefault=0);
	double ReadAsDouble(const char* szKey,double dDefault=0.0);
	bool ReadAsHexBuf(const char* szKey,vector<unsigned char>& oBuf);
private:
	int Load(const char* szFile);
	void ParseItem(const char* szItem);
	static unsigned int Hex2Int(char c);
private:
	std::map<string,string> m_oData;
};



#endif