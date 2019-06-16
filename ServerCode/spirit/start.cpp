#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

using std::cout;
using std::endl;
void daemon(char* path,char * logpath)
{
    umask(0);
    pid_t pid;
    int logfd;
    struct sigaction sa;
    pid = fork();
    if(pid < 0)
    {
        cout << "fork error" <<endl;
        return;
    }
    else if(pid > 0)
    {
        return;
    }
    setsid();//创建一个新会话
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGCHLD,&sa,NULL) < 0)
    {
        return;
    }
    if(chdir("/")<0)
    {
        cout<< "error chir" << endl;
        return;
    }
    close(0);
    logfd = open(logpath,O_RDWR);
    if(logfd < 0)
    {
        cout << "error open" << endl;
        return;
    }

    dup2(logfd,1);
    dup2(logfd,2);
    execl(path,NULL);
}

int main (int argc,char** argv)
{
    if(argc != 3)
    {
        cout << "error in main argc" <<endl;
        return 0;
    }
    daemon(argv[1],argv[2]);
}
