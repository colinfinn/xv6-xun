/*
 * @Author: xiangxun
 * @Date: 2023-12-27 09:40:43
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-27 12:19:55
 * @FilePath: /xv6-labs-2023/user/pingpong.c
 * @Description: 
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int
main(int argc, char *argv[])
{
    int pid;
    int p[2];
    char buf[32];
    
    // 创建子进程
    
    // 创建管道
    pipe(p);
    pid = fork();
    if(pid == 0)
    {
        // 关闭写端
        close(p[1]);
        read(p[0], buf, 32);
        printf("3%saaa\n", buf);
        //关闭读端
        close(p[0]);
    }
    else
    {
        // 关闭读端
        close(p[0]);
        //fprintf(p[1], "x%d: received ping", getpid());
        write(p[1], "xiang", 6);
        printf("1%d: received pong", getpid());
	    close(p[1]);
    }


    exit(0);

}