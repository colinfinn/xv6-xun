/*
 * @Author: xiangxun
 * @Date: 2023-12-27 23:02:17
 * @LastEditors: xiangxun
 * @LastEditTime: 2023-12-28 10:42:09
 * @FilePath: /xv6-labs-2023/user/find.c
 * @Description: find命令，能够查找用户指定的文件名所在的全部路径
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


void find(char *path, char *str)
{
    char buf[512];
    char *p;
    int fd;
    struct dirent de;
    struct stat st;

    fd = open(path, O_RDONLY);
    fstat(fd, &st);

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      stat(buf, &st);
      switch (st.type)
      {
        case T_FILE:
            if(strcmp(str, de.name) == 0)
            {
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            if(strcmp(".", de.name) != 0 && strcmp("..", de.name) != 0)
            {
                // 开始递归
                find(buf,str);
            }
            break;
        default:
            break;
      }
    }
  close(fd);
}


int
main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(2, "Usage: find [path] [filename]\n");
        exit(1);
        // 
    }
    else if(argc == 2)
    {
        find(".", argv[1]);
    }
    find(argv[1], argv[2]);
    exit(0);
}


