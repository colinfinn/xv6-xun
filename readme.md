<!--
 * @Author: xiangxun
 * @Date: 2023-12-26 16:55:56
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-28 10:48:14
 * @FilePath: /xv6-labs-2023/readme.md
 * @Description: 
-->
# 课程设计

## 实验网站

> https://pdos.csail.mit.edu/6.828/2020/schedule.html

## 用到的命令

```bash
Arch 安装编译环境
sudo pacman -S riscv64-linux-gnu-binutils riscv64-linux-gnu-gcc riscv64-linux-gnu-gdb qemu-arch-extra
文件注释
"fileheader.customMade": {
        "Author": "git config user.name", // 同时获取用户名与邮箱
        "Date": "Do not edit", // 文件创建时间(不变)
        // LastEditors、LastEditTime、FilePath将会自动更新 如果觉得时间更新的太频繁可以使用throttleTime(默认为1分钟)配置更改更新时间。
        "LastEditors": "git config user.name", // 文件最后编辑者 与Author字段一致
        // 由于编辑文件就会变更最后编辑时间，多人协作中合并的时候会导致merge
        // 可以将时间颗粒度改为周、或者月，这样冲突就减少很多。搜索变更时间格式: dateFormat
        "LastEditTime": "Do not edit", // 文件最后编辑时间
        // 输出相对路径，类似: /文件夹名称/src/index.js
        "FilePath": "Do not edit", // 文件在项目中的相对路径 自动更新
        // 插件会自动将光标移动到Description选项中 方便输入 Description字段可以在specialOptions更改
        "Description": "", 
    }
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

测试结果：
[xiangxun@xiang-mou xv6-labs-2023]$ ./grade-lab-util sleep
make: 'kernel/kernel' is up to date.
== Test sleep, no arguments == sleep, no arguments: OK (1.0s) 
== Test sleep, returns == sleep, returns: OK (0.9s) 
== Test sleep, makes syscall == sleep, makes syscall: OK (1.0s) 

   
This will run the grade tests that match "sleep". Or, you can type:
     $ make GRADEFLAGS=sleep grade
   
```

#### pingpong
任务要求：
```
Write a user-level program that uses xv6 system calls to ''ping-pong'' a byte between two processes over a pair of pipes, one for each direction. The parent should send a byte to the child; the child should print "<pid>: received ping", where <pid> is its process ID, write the byte on the pipe to the parent, and exit; the parent should read the byte from the child, print "<pid>: received pong", and exit. Your solution should be in the file user/pingpong.c.
使用系统调用写一个用户程序，在两个进程间能够通过一对管道来'ping-pong'（像乒乓球一样） 1字节，，每个方向都一字节。
父进程能够发送一个字节给子进程，子进程应该打印<pid>: received ping，pid是进程号，写这个字节到管道传给父进程，并退出，父进程应当读取从子进程传来的字节，并接受pong,

```
提示:
1. Add the program to UPROGS in Makefile.
2. Use pipe to create a pipe.
3. Use fork to create a child.
4. Use read to read from a pipe, and write to write to a pipe.
5. Use getpid to find the process ID of the calling process.
6. User programs on xv6 have a limited set of library functions available to them. You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c, user/printf.c, and user/umalloc.c.

解决方案：
```
// 理解管道
int p[2];
char *argv[2];
argv[0] = "wc";
argv[1] = 0;
pipe(p);
if(fork() == 0) {
	close(0);
	dup(p[0]);
	close(p[0]);
	close(p[1]);
	exec("/bin/wc", argv);
} else {
	write(p[1], "hello world\n", 12);
	close(p[0]);
	close(p[1]);
}
参考管道通信：https://blog.csdn.net/qq_51604330/article/details/126492589

```

#### primes
任务要求
> Write a concurrent prime sieve program for xv6 using pipes and the design illustrated in the picture halfway down this page and the surrounding text. This idea is due to Doug McIlroy, inventor of Unix pipes. Your solution should be in the file user/primes.c.
运用管道写一个并发的素数筛选程序，

提示


解决方案:
```
 The sieve of Eratosthenes can be simulated by a pipeline of processes executing the following pseudocode:
埃拉托色尼筛可以通过执行以下伪代码的进程管道来模拟，
从左邻居读取第一个数字，直接打印（因为其本身就是素数），然后从左邻居接着读数字
，一旦数字能被第一个数字整除，就忽略掉，
相当于依次消除2的倍数，3的倍数，5的倍数，。。
p = get a number from left neighbor
print p
loop:
    n = get a number from left neighbor
    if (p does not divide n)
        send n to right neighbor

```


#### find
任务要求
> Write a simple version of the UNIX find program for xv6: find all the files in a directory tree with a specific name. Your solution should be in the file user/find.c.

提示
```
Look at user/ls.c to see how to read directories.
Use recursion to allow find to descend into sub-directories.
Don't recurse into "." and "..".
Changes to the file system persist across runs of qemu; to get a clean file system run make clean and then make qemu.
You'll need to use C strings. Have a look at K&R (the C book), for example Section 5.5.
Note that == does not compare strings like in Python. Use strcmp() instead.
Add the program to UPROGS in Makefile.
```

#### xargs
任务要求
> Write a simple version of the UNIX xargs program for xv6: its arguments describe a command to run, it reads lines from the standard input, and it runs the command for each line, appending the line to the command's arguments. Your solution should be in the file user/xargs.c.

提示
```
Use fork and exec to invoke the command on each line of input. Use wait in the parent to wait for the child to complete the command.
To read individual lines of input, read a character at a time until a newline ('\n') appears.
kernel/param.h declares MAXARG, which may be useful if you need to declare an argv array.
Add the program to UPROGS in Makefile.
Changes to the file system persist across runs of qemu; to get a clean file system run make clean and then make qemu.

```
