#ifndef __PROCESS_POOL_H__
#define __PROCESS_POOL_H__
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

class CProcess{
public:
	CProcess():_pid(-1),_index(-1){
		_socketpair[0] = -1;
		_socketpair[1] = -1;
	}
	~CProcess(){
		if(_socketpair[0] > 0)
			close(_socketpair[0]);
		if(_socketpair[1] > 0) 
			close(_socketpair[1]);
	}

public:
	int 		_index;
	pid_t		_pid;
	int 		_socketpair[2];
};

class ProcessPool{
public:
	ProcessPool(int nProcessNum );
	~ProcessPool();
	inline ProcessPool(const ProcessPool& p){}
	inline ProcessPool& operator=(const ProcessPool& p){}

	void run();

	int index(){
		return _index;
	}

	int process_count()const {
		return _process_num;
	}
	vector<CProcess*>& process_array() {
		return _process_array;
	}
	map<int,int>& pid2fdinparent(){
		return _pid2fd_inparent;
	}
private:
	void init();
	void init_parent();
	void init_child();
	void run_parent();
	void run_child();

private:
	int 				_process_num;
	int 				_index;
	vector<CProcess*> 	_process_array;
	map<int,int>		_pid2fd_inparent;

};


#endif