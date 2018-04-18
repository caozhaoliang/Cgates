#ifndef _EPOLLER_H_
#define _EPOLLER_H_
#include <iostream>
#include <map>
#include <sys/epoll.h>
#define NET_ERRMSG_SIZE 	1024
#define EPOLL_FD_MAX		64

using namespace std;


class CEpoller
{
public:
	CEpoller();
	~CEpoller();
	int create(int maxfd );
	int addEpollIO(int fd, unsigned int flag);
	int modEpollIO(int fd, unsigned int flag);
	int setEpollIO(int fd, unsigned int flag);
	int delEpollIO(int fd );
	int waitForEvent(int timeout);

	inline char* getErrMsg(){
		return _err_msg;
	}


protected:
	char 				_err_msg[NET_ERRMSG_SIZE];
	int 				_epoll_fd;
	epoll_event			_events[EPOLL_FD_MAX];
	int 				_maxfd;
	std::map<int,void*> _mp2fd;
};



#endif
