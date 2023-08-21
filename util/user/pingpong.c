#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char **argv)
{
    int ptoc[2];//parent write && child read
    int ctop[2];//child write && parent read
    pipe(ptoc);
    pipe(ctop);
    if(fork()!=0)
    {
        //parent
        char parent_msg[50];
        close(ptoc[0]);
        //parent send a byte to child by ptoc
        char* ping="a";
        write(ptoc[1],ping,1);
        close(ptoc[1]);
        if(read(ctop[0],parent_msg,1)!=0)
        {
            printf("%d: received pong\n",getpid());
        }
        exit(0);
    }
    else
    {
        //child
        char child_msg[50];
        close(ptoc[1]);
        //child receive byte
        if(read(ptoc[0],child_msg,1)!=0)
        {
            printf("%d: received ping\n",getpid());
        }
        close(ctop[0]);
        //child send a byte
        write(ctop[1],child_msg,1);
        exit(0);
    }
}
