/*
 * @Author: xiangxun
 * @Date: 2023-12-28 10:46:04
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-28 16:46:22
 * @FilePath: /xv6-labs-2023/user/xargs.c
 * @Description: 
 */


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
    // int p[2];
    char buf[32];
    char c;
    int j = 0;

    char *argvMore[MAXARG];
    for (int i = 1; i < argc; i++, j++)
    {
        argvMore[j] = malloc(strlen(argv[i]) + 1);
        memcpy(argvMore[j], argv[i], strlen(argv[i]) + 1);
    }
    int n = 0;
    while(read(0, &c, 1))
    {
        if(c == '\n')
        {
            n = 0;
            argvMore[j] = malloc(strlen(buf) + 1);
            memcpy(argvMore[j], buf, strlen(buf) + 1);
            int pid = fork();
            if(pid == 0)
            {
                exec(argv[1], argvMore);
            }
            else
            {
                wait(0);
            }
        }
        else
        {
            buf[n++] = c;
        }
    }
    exit(0);
}
