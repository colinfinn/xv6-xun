/*
 * @Author: xiangxun
 * @Date: 2023-12-27 21:17:52
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-27 22:53:11
 * @FilePath: /xv6-labs-2023/user/primes.c
 * @Description: 素数筛选器
 */


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void usePipe(int fd)
{
    int n;
    // 从管道中读取第一个数字并打印,这里读取4个字节的整型
    read(fd, &n, 4);
    printf("prime %d\n", n);
    int p[2];
    pipe(p); // 建立新管道，用于向子进程传递数据
    // 读取其余数字
    int temp;
    int flag = 1; // 标志位，当读取不到数字的时候应当返回
    while (read(fd, &temp, 4) != 0)
    {
        // 将后面的数字是n的倍数的消去
        if(temp % n != 0)
        {
            flag = 0;
            write(p[1], &temp, 4);
        }
    }
    if(flag)
    {
        close(fd);
        close(p[0]);
        close(p[1]);
        return;
    }

    int pid = fork();
    if(pid == 0)
    {
        close(p[1]);
        close(fd);
        usePipe(p[0]);
        close(p[0]);
    }
    else // 父进程需要等待子进程结束
    {
        close(fd);
        close(p[0]);
        close(p[1]);
        wait(0);
    }
}

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    for(int i = 2; i <= 35; i++)
    {
        //写入管道
        write(p[1], &i, 4);
    }
    close(p[1]);
    usePipe(p[0]);
    close(p[0]);
    exit(0);
}
