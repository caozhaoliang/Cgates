#include "processpool.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "global.h"


/*
_process_num;
	int 				_index;
	vector<CProcess*> 	_process_array;
	map<int,int>		_pid2fd_inparent;
*/
ProcessPool::ProcessPool(int nProcessNum){
	_process_num = nProcessNum;
	_pid2fd_inparent.clear();
	_index = -1;
	init();
}
ProcessPool::~ProcessPool(){

}

void ProcessPool::init()
{
	for (int i = 0; i < _process_num; ++i){
		_process_array.push_back(new CProcess() );
	}
	for(int i=0; i <_process_num;++i){
		if(-1 == _index ) {
			int nRet = socketpair(PF_UNIX,SOCK_STREAM,0,_process_array[i]->_socketpair);
			if(nRet == 0 ) {
				_process_array[i]->_pid = fork();
				if(_process_array[i]->_pid > 0 ) {
					close(_process_array[i]->_socketpair[1]);
					_process_array[i]->_socketpair[1] = -1;
					_process_array[i]->_index = i;
					_pid2fd_inparent.insert(make_pair(_process_array[i]->_pid,
											_process_array[i]->_socketpair[0]));
					if(i+1 == _process_num ) {
						init_parent();
					}
					continue;
				}else if(_process_array[i]->_pid == 0) {
					//子进程中...
					close(_process_array[i]->_socketpair[0]);
					_process_array[i]->_socketpair[0] = -1;
					_index = i;
					init_child();
					break;
				}else{
					exit(-1);
				}
			}
		}
	}
}

void ProcessPool::init_parent()
{
	dealSig();
	//TODO: some others init
}

void ProcessPool::init_child()
{
	map<int,int>::iterator it = _pid2fd_inparent.begin();
	for(;it != _pid2fd_inparent.end(); ++it){
		close(it->second);
	}
	_pid2fd_inparent.clear();
	for(int i = 0; i < _process_num; ++i){
		if(_process_array[i]->_pid >= 0) {
			close(_process_array[i]->_socketpair[0]);
		}
	}
	//TODO: some other init for child process
	dealSig();
}	

void ProcessPool::run()
{
	if(_index == -1){
		run_parent();
		return;
	}else{
		run_child();
		return;
	}
}

void ProcessPool::run_parent()
{
	//parent process working
	Application* app = new Application();
	app->Start();
}

void ProcessPool::run_child()
{
	//child process working
}









