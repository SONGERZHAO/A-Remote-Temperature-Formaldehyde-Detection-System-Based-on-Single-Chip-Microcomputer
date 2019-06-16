#include <iostream>
#include <string>
#include <assert.h>
#include <wait.h>
#include "net_sock.h"
#include "mytime.h"
#define LINE 24
using std::cout;
using std::endl;
using std::string;



void * ThreadFunc(void *arg)
{
    
    int sockfd = *(int*)arg;
    char buff[LINE] ={};
    int i;
    recv(sockfd,buff,LINE,0);
    for(i=0; i< buff[0]-'0'; i++)
    {
        if(buff[i] == 0)
        {
            buff[i] = ~buff[i];
        }
    }
    close(sockfd);
    pid_t pid;
    int tmp;
    pid = fork();
    if(pid < 0)
    {
        cout <<GetTime()<< "   Error" <<endl;
        assert(0);
    }
    else if(pid > 0)
    {
        wait(NULL);
        pthread_exit(0);
    }
    else
    {
        string str = "/home/sez/MyWork/API/a.out";
        tmp = execl(str.c_str(),buff,NULL);
        if(tmp != 0)
        {
            cout <<GetTime()<< "   Error execv"<<endl;
        }
    }
}
int main (void)
{
    
    NetSock netsock(8080,ThreadFunc);

