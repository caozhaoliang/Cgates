#include <iostream>
#include <string.h>
#include <stdio.h>
#include "../version.h"
#include "./common/config_read.h"
#include <signal.h>
#include <unistd.h>

#include "processpool.h"



using namespace std;

int main(int argc, char const *argv[])
{
	if(argc > 1){
		if(string(argv[1]) == "-v" || (string(argv[1]) == "-V")){
			string szVersion = MINOR_VERSION_STRING;
			if(szVersion.empty() || szVersion.length()==0){
				printf("warning!!! this project without version control\n");
				return 0;
			}
			printf("%s v%s 版(%s,%s)\n",MAIN_VERSION_STRING,
							MINOR_VERSION_STRING,__DATE__,__TIME__ );
		}
	}

	//daemon(1,0);	//程序目录为当前目录，不输出到终端

	//load tempconfig 
	CConfigRead cfgRead("../etc/tmp.conf");
	int iProcessNum = cfgRead.ReadAsUint("subProcessNum",3);
	if(iProcessNum <=0 || iProcessNum >=50 ) {
		iProcessNum = 3;
	}
	ProcessPool* pPool = new ProcessPool(iProcessNum);
	pPool->run();

	while(1)
	{
		printf("-------------\n");
		sleep(1);
	}



	
	return 0;
}