#ifndef  _SYSTEM_INFOR_H_
#define  _SYSTEM_INFOR_H_

using namespace std;

class CSystemInfor
{
public:
    CSystemInfor();
    ~CSystemInfor();

public:
    static bool getCpuUse(long int & iAll, long int & iIdle);

    static float calcCpuUse(long int & old_all, 
                            long int & old_idle, 
                            long int & new_all, 
                            long int & new_idle);
};

#endif