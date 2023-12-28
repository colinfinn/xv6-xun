/*
 * @Author: xiangxun
 * @Date: 2023-12-28 10:46:04
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-28 11:28:41
 * @FilePath: /xv6-labs-2023/user/xargs.c
 * @Description: 
 */


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int
main(int argc, char *argv[])
{
    // int p[2];
    char buf[32];
    // pipe(p);
    // if(fork() == 0) {
    //     // 关闭
    //     close(0);
    //     dup(p[0]);
    //     read(p[0], buf, 32);
    //     printf("%s", buf);
    //     close(p[0]);
    //     close(p[1]);
    //     //exec("/bin/xargs", argv);
    // } else {
    //     write(p[1], argv[1], 12);
    //     wait(0);
    //     close(p[0]);
    //     close(p[1]);
    // }

    read(0, buf, 32);
    printf("234%s", buf);
    exit(0);
}
