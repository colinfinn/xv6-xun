<!--
 * @Author: xiangxun
 * @Date: 2023-12-26 16:55:56
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-27 09:00:10
 * @FilePath: /xv6-riscv-xun/readme.md
 * @Description: 
-->
# 课程设计

## 实验网站

> https://pdos.csail.mit.edu/6.828/2020/schedule.html

## 用到的命令

```bash
Arch 安装编译环境
sudo pacman -S riscv64-linux-gnu-binutils riscv64-linux-gnu-gcc riscv64-linux-gnu-gdb qemu-arch-extra


```

## git

```
git init //初始化git
git add README.md //添加文件
git commit -m "first commit"
git branch  分支名   //创建分支
git branch -M main //移动到分支

git remote add origin https://github.com/colinfinn/os_design.git
git remote add sb git@github.com:colinfinn/os_design.git
git checkout main //切换分支

ssh-keygen -t rsa -C "806181859@qq.com" 创建ssh密钥
ssh -T git@github.com //使用本地ssh密钥
git remote set-url origin ....... //修改地址

git push -u origin main
git push -u sb main
git pull -u sb main
```

## xv6
> ctrl + p 打印进程

> Ctrl-a x 结束
### Lab: Xv6 and Unix utilities
#### sleep
```
Implement a user-level sleep program for xv6, along the lines of the UNIX sleep command. Your sleep should pause for a user-specified number of ticks. A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip. Your solution should be in the file user/sleep.c.
实现一个用户级的睡眠程序，类似于unix的睡眠命令，由用户指定睡眠的tick数，一个tick是在xv6内核中定义的时间概念，即定时器芯片两次中断间隔的时间，解决方案应当在user/sleep.c
```
一些提示：
1. Before you start coding, read Chapter 1 of the xv6 book.在编码前，读取第一章
2. Put your code in user/sleep.c. Look at some of the other programs in user/ (e.g., user/echo.c, user/grep.c, and user/rm.c) to see how command-line arguments are passed to a program.
查看user下其他的c文件中（rm,grep,echo）中命令行的参数如何传递
3. Add your sleep program to UPROGS in Makefile; once you've done that, make qemu will compile your program and you'll be able to run it from the xv6 shell.添加程序到Makefile中的UPROGS
4. If the user forgets to pass an argument, sleep should print an error message.
The command-line argument is passed as a string; you can convert it to an integer using atoi (see user/ulib.c).如果用户忘记传递参数，打印错误信息。
命令行参数通常是字符串，可以用atoi来变成整型
5. Use the system call sleep.
使用sleep的系统调用
6. See kernel/sysproc.c for the xv6 kernel code that implements the sleep system call (look for sys_sleep), user/user.h for the C definition of sleep callable from a user program, and user/usys.S for the assembler code that jumps from user code into the kernel for sleep.
查看内核下的sysproc的sleep的系统调用的实现，
7. sleep's main should call exit(0) when it is done.完成退出为exit(0)
8. Look at Kernighan and Ritchie's book The C programming language (second edition) (K&R) to learn about C.多看书

```
解决方案：
user/sleep.c编写sleep, 使用系统调用
在Makefile的UPROGS里添加$U/_sleep\
测试程序：
Run make grade to see if you indeed pass the sleep tests.

Note that make grade runs all tests, including the ones for the assignments below. If you want to run the grade tests for one assignment, type:

     $ ./grade-lab-util sleep
   
This will run the grade tests that match "sleep". Or, you can type:
     $ make GRADEFLAGS=sleep grade
   
```

