#define T_DIR     1   // Directory 目录
#define T_FILE    2   // File  文件
#define T_DEVICE  3   // Device

struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number    文件索引好
  short type;  // Type of file   文件的类型
  short nlink; // Number of links to file 文件链接数
  uint64 size; // Size of file in bytes
};
