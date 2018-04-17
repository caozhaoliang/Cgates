#include <utility>
#include <vector>
#include <string>
#include <stdio.h>
#include "sys_infor.h"
#include <cstring>
#include <stdlib.h>

using namespace std;



CSystemInfor::CSystemInfor()
{

}

CSystemInfor::~CSystemInfor()
{

}

bool CSystemInfor::getCpuUse(long int & iAll, long int & iIdle)
{
    FILE* fp = NULL;
    char buf[128];
    char cpu[5];
    long int user, nice, sys, idle, iowait, irq, softirq;
    
    memset(buf, 0x00, sizeof(buf));
    memset(cpu, 0x00, sizeof(cpu));

   
    fp = fopen("/proc/stat","r");
    if(fp == NULL)
    {
        return false;
    }

    fgets(buf, sizeof(buf), fp);
    sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld",
        cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);

    iAll  = user + nice + sys + idle + iowait + irq + softirq;
    iIdle = idle;
    fclose(fp);
    return true;
}

float CSystemInfor::calcCpuUse(long int & old_all, 
                               long int & old_idle, 
                               long int & new_all, 
                               long int & new_idle)
{
    return (float)(new_all - old_all - (new_idle - old_idle)) / (new_all - old_all) * 100;
}
