#ifndef __NET_SOCK_H__
#define __NET_SOCK_H__
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "mytime.h"
using std::cout;
using std::endl;
class NetSock
{
    private:
        int _port;
        int _sockfd;
        struct sockaddr_in _sockaddr;
        struct sockaddr_in _sockclient;
        socklen_t _len_client;
        char buff[INET_ADDRSTRLEN];
        void* (*_Func)(void *);
    public:
        NetSock(int port,void* (*Func)(void * arg))
        {
            _port = port; 
            _Func = Func;
            InitSock();
            Startlisten();
        }
        bool InitSock()
        {
            int tmp;
            _sockaddr.sin_family = AF_INET;
            _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            _sockaddr.sin_port = htons(_port);
            
            _sockfd = socket(AF_INET,SOCK_STREAM,0);
            if (_sockfd < 0)
            {
                cout <<GetTime()<< "Error socket()" << endl;
                return false;
            }
            tmp = bind(_sockfd,(struct sockaddr*)&_sockaddr,sizeof(_sockaddr));
            if (tmp < 0)
            {
                cout <<GetTime()<< "Error bind()" << endl;
                return false;
            }
        }
        int Startlisten()
        {    
            int tmp;
            int newfd;
            pthread_t th;
            listen(_sockfd,10);
            while(1)
            {
                newfd = accept(_sockfd,(struct sockaddr *)&_sockclient,&_len_client);
                if(newfd > 0)
                {
                    cout<<GetTime() <<"Connect From" <<inet_ntop(AF_INET,&_sockclient.sin_addr,buff,sizeof(buff))<<"Port"<<ntohs(_sockclient.sin_port)<<endl;
                    tmp = pthread_create(&th,NULL,_Func,(void*)&newfd);
                    if(tmp != 0)
                    {
                        cout<<GetTime() << "    Error Pthread_Create" <<endl;
                    }
                    else
                    {
                        pthread_detach(th);
                    }
                }
            }
        }


};




#endif
