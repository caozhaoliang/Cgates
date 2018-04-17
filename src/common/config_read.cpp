#include "config_read.h"
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


using namespace std;

CConfigRead::CConfigRead(const char* szFile)
{
	Load(szFile);
}
int CConfigRead::Load(const char* szFile)
{
	if(!szFile ) {
		return -1;
	}
	char szItem[2048] = {0};
	ifstream oFile(szFile,ios_base::in);
	while(oFile.getline(szItem,sizeof(szItem)-1))
	{
		if(strlen(szItem) == 0) {
			continue;
		}
		char* pItem = szItem;
		while((*pItem == ' ')||(*pItem == '\t')) {
			++pItem;
		}
		if(*pItem != ';'){
			char* pRemak = strrchr(szItem,';');
			if(pRemak){
				*pRemak = 0;
			}
			ParseItem(szItem);
		}
	}
	return (int)m_oData.size();
}
void CConfigRead::ParseItem(const char* szItem)
{
	const char* p = strchr(szItem,'=');
	if( !p ){
		FILE* wp = fopen("./stderr.txt","a+");
		assert(wp != NULL);
		fwrite("config file is illegal.",30,1,wp);
		fclose(wp);
		exit(-1);
	}
	const char* pFrom = szItem;
	while(*pFrom == ' ' || *pFrom == '\t'){
		++pFrom;
	}
	const char* pTo = p -1;
	while(pTo >= pFrom && (*pTo == ' ' || *pTo == '\t')){
		--pTo;
	}
	if(pTo >= pFrom){
		string strKey(pFrom,pTo + 1);
		pFrom = p +1;
		while(*pFrom == ' ' || *pFrom == '\t' ) {
			++pFrom;
		}
		pTo = szItem +strlen(szItem) -1;
		while(pTo >= pFrom && (*pTo == ' ' || *pTo=='\t')){
			--pTo;
		}
		if(pTo >= pFrom){
			m_oData[strKey] = string(pFrom,pTo+1);
		}
	}
}

const char* CConfigRead::ReadAsString(const char* szKey,char const* szDefault)
{
	map<string,string>::const_iterator it = m_oData.find(szKey);
	if( it != m_oData.end() ) {
		return it->second.c_str();
	}
	return szDefault;
}

int CConfigRead::ReadAsInt(const char* szKey,int iDefault)
{
	std::map<string,string>::const_iterator it = m_oData.find(szKey);
	if(it != m_oData.end() ) {
		return atoi(it->second.c_str());
	}
	return iDefault;
}

unsigned int CConfigRead::ReadAsUint(const char* szKey,unsigned int iDefault)
{
	std::map<string,string>::const_iterator it = m_oData.find(szKey);
	if(it != m_oData.end()){
		return strtoul(it->second.c_str(),0,10);
	}
	return iDefault;
}

double CConfigRead::ReadAsDouble(const char* szKey,double dDefault)
{
	std::map<string,string>::const_iterator it = m_oData.find(szKey);
	if(it != m_oData.end()){
		return atof(it->second.c_str());
	}
	return dDefault;
}	
bool CConfigRead::ReadAsHexBuf(const char* szKey,vector<unsigned char>& oBuf)
{
	std::map<string,string>::const_iterator it = m_oData.find(szKey);
    if (it != m_oData.end())
    {
        oBuf.clear();
        const char * p = it->second.c_str();
        const char * pEnd = p + it->second.length();
        while (p + 1 < pEnd)
        {
            oBuf.push_back((Hex2Int(p[0]) << 4) + Hex2Int(p[1]));
            p += 3;
        }
        return true;
    }
    return false;
}


inline unsigned int CConfigRead::Hex2Int(char c)
{
	if(c >= '0' && c <= '9'){
		return c - '0';
	}else if(c >= 'a' && c <= 'f'){
		return c-'a' +0x0a;
	}else if(c >= 'A' && c <= 'F') {
		return c - 'A' +0x0a;
	}
	return 0;
}