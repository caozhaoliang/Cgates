#include "epoller.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

CEpoller::CEpoller()
{
	memset(_err_msg,0,sizeof(NET_ERRMSG_SIZE));
	_epoll_fd = 	-1;
	_maxfd = 		-1;
	_mp2fd.clear();
}
CEpoller::~CEpoller()
{
	memset(_err_msg,0,sizeof(NET_ERRMSG_SIZE));
	_epoll_fd = 	-1;
	_maxfd = 		-1;
	_mp2fd.clear();	
}

int CEpoller::create(int maxfd) 
{
	_maxfd = maxfd;
	_epoll_fd = epoll_create(_maxfd);
	if(_epoll_fd <= 0 ) {
		memset(_err_msg,0,NET_ERRMSG_SIZE);
		snprintf(_err_msg,NET_ERRMSG_SIZE,"epoll_create(%d) err:%s\n",_maxfd,strerror(errno));
		return -1;
	}
}

int CEpoller::waitForEvent(int timeout)
{
	int fd,nfds;
	unsigned int ev;
	nfds = epoll_wait(_epoll_fd,_events,EPOLL_FD_MAX,timeout); //timeout ms
	if(nfds < 0 ) {
		snprintf(_err_msg,NET_ERRMSG_SIZE,"epoll_wait ret:%d,error:%s\n",nfds,strerror(errno));
		return -1;
	}else if(nfds == 0) {
		return 0;
	}

	for(int i =0; i < nfds; i++){
		fd = _events[i].data.fd;
		//TODO: 该怎么返回呢？？
	}
}

int CEpoller::addEpollIO(int fd, unsigned int flag)
{
	epoll_event ev;
	ev.data.fd = fd;
	ev.events = flag;
	if(epoll_ctl(_epoll_fd,EPOLL_CTL_ADD,fd,&ev) < 0 ){
		return -1;
	}
	return 0;
}

int CEpoller::modEpollIO(int fd, unsigned int flag)
{
	epoll_event ev;
	ev.data.fd = fd;
	ev.events = flag;
	if(epoll_ctl(_epoll_fd,EPOLL_CTL_MOD,fd,&ev) < 0 ) {
		return -1;
	}
	return 0;
}

int CEpoller::setEpollIO(int fd, unsigned int flag){
	epoll_event ev;
    ev.data.fd = fd;
    ev.events = flag|EPOLLHUP|EPOLLERR;
    if ( epoll_ctl(_epoll_fd, EPOLL_CTL_MOD , fd, &ev) < 0 ) {
        if ( epoll_ctl(_epoll_fd, EPOLL_CTL_ADD , fd, &ev) < 0 ) {
            snprintf(_err_msg,NET_ERRMSG_SIZE,"epoll_ctl fd:%d err:%s\n",fd,strerror(errno));
            return -1;
        }
    }
    return 0;
}

int CEpoller::delEpollIO(int fd )
{
	epoll_event ev;
    ev.data.fd = fd;
    ev.events = 0;
    if ( epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, &ev) < 0 ) {
        return -1;
	}
    return 0;
}













