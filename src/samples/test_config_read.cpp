#include <iostream>
#include <string>
#include "config_read.h"

using namespace std;


int main2(int argc, char const *argv[])
{
	CConfigRead *read = new CConfigRead("./config.conf");
	string value = read->ReadAsString("key1","szdefault");
	cout <<value <<endl;
	int iValue = read->ReadAsInt("key2",10);
	cout <<"key2:"<<iValue<<endl;
	int iValue2 = read->ReadAsInt("key3_t",1000);
	cout<< "key3_t:"<<iValue2<<endl;

	
	return 0;
}
