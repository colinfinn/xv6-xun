/*
 * @Author: xiangxun
 * @Date: 2023-12-26 22:39:34
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-27 08:56:57
 * @FilePath: /xv6-riscv-xun/user/sleep.c
 * @Description: 实现睡眠程序
 */
 // 定义一些类型，如uint，uint8等
#include "kernel/types.h"
// 文件信息的结构体，在系统调用中部分函数使用到了该
//程序
#include "kernel/stat.h"
// 系统调用的头文件
#include "user/user.h"
// // 类似的C库函数，有strcpy,atoi等函数
// #include "user/ulib.c"

int
main(int argc, char *argv[])
{
    // 未传递参数
    if(argc < 2)
    {
        fprintf(2, "no input ticks!!!, Usage: sleep [ticks]\n");
        exit(1);
    }
    // 获取指定的tick数
    char * tickArg = argv[1];
    // 转成整型
    int tickNum = atoi(tickArg);
    sleep(tickNum);
    exit(0);

}