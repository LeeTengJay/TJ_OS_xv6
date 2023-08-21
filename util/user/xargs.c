#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define CMDSTYLE        2

char *cutoffinput(char *buf);
void substring(char s[], char sub[], int pos, int len);

/* get the char * */
void substring(char s[], char *sub, int pos, int len) 
{
   int c = 0;   
   while (c < len) 
   {
      *(sub + c) = s[pos+c];
      c++;
   }
   *(sub + c) = '\0';
}

/* clear '\n' in the end */
char* cutoffinput(char *buf)
{
    if(strlen(buf) > 1 && buf[strlen(buf) - 1] == '\n')
    {
        char *subbuff = (char*)malloc(sizeof(char) * (strlen(buf) - 1));
        substring(buf, subbuff, 0, strlen(buf) - 1);
        return subbuff;
    }
    else
    {
        char *subbuff = (char*)malloc(sizeof(char) * strlen(buf));
        strcpy(subbuff, buf);
        return subbuff;
    }
}

int main(int argc, char *argv[])
{
    /* code */
    int pid;
    char buf[MAXPATH];
    char *args[MAXARG];
    char *cmd;
    /* default cmd is echo */
    if(argc == 1)
    {
        cmd = "echo";
    }
    else
    {
        cmd = argv[1];
    }

    int args_num = 0;
    while (1)
    {
    	//every time clear
        memset(buf, 0, sizeof(buf));
        //get a line
        gets(buf, MAXPATH);
        char *arg = cutoffinput(buf);
        if(strlen(arg) == 0 || args_num >= MAXARG)
	{
            break;
        }
        args[args_num]= arg;
        args_num++;
    }

    
    // argv2exec : store args needed for cmd
    int argstartpos = 1;
    char *argv2exec[MAXARG];
    argv2exec[0] = cmd;
    //the same line with cmd
    for (; argstartpos < argc-1; argstartpos++)
    {
        argv2exec[argstartpos] = argv[argstartpos+1];
    }
    //other lines not in cmd line
    for (int i = 0; i < args_num; i++)
    {
        argv2exec[i + argstartpos] = args[i];
    }
    argv2exec[args_num + argstartpos] = 0;
    
    /* exec cmd */
    if((pid = fork()) == 0)
    {   
        exec(cmd, argv2exec);    
    }  
    else
    {
        /* code */
        wait(0);
    }
    exit(0);
}





