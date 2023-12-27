/*
 * @Author: xiangxun
 * @Date: 2023-12-27 09:40:43
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-27 20:57:07
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

        read(p[0], buf, 32);
        printf("%d: received %s\n", getpid(), buf);
        //关闭读端
        close(p[0]);
        write(p[1], "pong", 32);//向管道写pong，父进程来读取
    }
    else //父进程
    {

        write(p[1], "ping", 32);
        close(p[1]);
        wait(0); // 等待子进程写数据
        read(p[0], buf, 32); // 从p[0]中读取子进程发送的pong
        printf("%d: received %s\n", getpid(), buf);
	    close(p[0]);
    }


    exit(0);

}