#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
void sig_usr1_handler(int sig)
{
	printf("get signal user1\n");
}

void dealSig()
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGHUP , SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	struct sigaction act,oact;
	act.sa_handler = sig_usr1_handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGUSR1);
	if(sigaction(SIGUSR1,&act,&oact) < 0){
		printf("sigaction(SIGUSR1,&act,&oact) err.\n");
		return ;
	}
}



#endif