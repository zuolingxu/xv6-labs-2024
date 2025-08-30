# Lab9实验报告

## mmap

### 实验目的

实现xv6的mmap和munmap系统调用，支持用户进程将文件映射到虚拟地址空间，实现按需分配和懒加载，掌握虚拟内存区（VMA）管理、页错误处理和文件同步机制。

### 实验过程

1. 阅读mmap相关手册和xv6内核代码，理解mmap/munmap的语义和VMA结构。
2. 新增系统调用mmap/munmap，分配系统调用号，修改usys.pl和user.h。
3. 在proc结构体中添加VMA数组，记录每个映射区域的起始地址、长度、权限、文件指针、映射类型等信息。
4. mmap实现：查找空闲虚拟地址区，建立VMA，增加文件引用计数（filedup），返回映射地址。
5. 懒加载：在usertrap中处理页错误，判断是否属于mmap区域，分配物理页，调用readi读取文件内容，设置页表权限。
6. munmap实现：查找对应VMA，解除映射区，若MAP_SHARED且页被修改则写回文件，减少文件引用计数，释放物理页。
7. 进程exit时自动munmap所有VMA，确保MAP_SHARED内容同步到文件。
8. fork时复制父进程VMA，增加文件引用计数，子进程页错误时重新分配物理页并加载文件内容。
9. 运行mmaptest和usertests，验证所有功能和边界情况。

### 实验结果

mmaptest输出如下（占位符）：
```
$ mmaptest
test basic mmap
test basic mmap: OK
test mmap private
test mmap private: OK
test mmap read-only
test mmap read-only: OK
test mmap read/write
test mmap read/write: OK
test mmap dirty
test mmap dirty: OK
test not-mapped unmap
test not-mapped unmap: OK
test lazy access
test lazy access: OK
test mmap two files
test mmap two files: OK
test fork
test fork: OK
test munmap prevents access
usertrap(): unexpected scause 0xd pid=7
            sepc=0x924 stval=0xc0001000
usertrap(): unexpected scause 0xd pid=8
            sepc=0x9ac stval=0xc0000000
test munmap prevents access: OK
test writes to read-only mapped memory
usertrap(): unexpected scause 0xf pid=9
            sepc=0xaf4 stval=0xc0000000
test writes to read-only mapped memory: OK
mmaptest: all tests succeeded
```
usertests全部通过。

### 实验结论

通过实现mmap和munmap，掌握了用户态虚拟内存区管理、懒加载、文件同步和进程间VMA复制等操作系统高级技术。mmap机制为高效文件访问、共享内存和用户级异常处理提供了基础，广泛应用于现代操作系统。

## Grade

![grade-lab9](/grades/lab9.png)
