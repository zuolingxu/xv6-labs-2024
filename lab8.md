# Lab8实验报告

## Large files 

### 实验目的

扩展xv6文件系统，支持最大文件长度从268块提升到65803块，实现双重间接块结构，掌握文件系统索引结构设计与实现。

### 实验过程

1. 阅读fs.h和fs.c，理解inode结构和bmap()逻辑。
2. 修改NDIRECT为11，新增双重间接块（第13项），调整inode和dinode结构。
3. 在bmap()中实现双重间接块索引，逻辑块号映射到双重间接块、单重间接块和数据块。
4. 修改itrunc，确保释放所有直接、单重间接和双重间接块。
5. 重新生成fs.img，运行bigfile和usertests，验证大文件写入和系统功能正确。

### 实验结果

bigfile输出如下：
```
$ bigfile
...........................................................................................................
wrote 65803 blocks
done; ok
```
usertests全部通过。

### 实验结论

通过双重间接块设计，显著提升了文件系统最大文件容量，掌握了多级索引块的实现方法，为更复杂的文件系统结构打下基础。

---

## Symbolic links

### 实验目的

实现xv6文件系统的符号链接（symlink），支持路径级别的文件引用，理解文件系统路径解析和递归查找机制。

### 实验过程

1. 新增系统调用symlink，分配系统调用号，修改usys.pl和user.h。
2. 在stat.h中新增T_SYMLINK类型，在fcntl.h中新增O_NOFOLLOW标志。
3. 实现sys_symlink，在inode数据块中存储目标路径，允许目标不存在。
4. 修改open系统调用，支持递归解析符号链接，遇到O_NOFOLLOW时直接打开链接本身，循环深度超过阈值报错。
5. 其他系统调用（如link/unlink）不跟随符号链接。
6. 运行symlinktest和usertests，验证符号链接功能和并发正确性。

### 实验结果

symlinktest输出如下：
```
$ symlinktest
Start: test symlinks
test symlinks: ok
Start: test concurrent symlinks
test concurrent symlinks: ok
```
usertests全部通过。

### 实验结论

通过实现符号链接，掌握了文件系统路径解析、递归查找和类型区分等核心技术。符号链接为用户提供了灵活的文件引用机制，广泛应用于现代操作系统。


## Grade

![grade-lab8](/grades/lab8.png)
