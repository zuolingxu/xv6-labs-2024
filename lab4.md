# Lab4实验报告

## Backtrace

### 实验目的

实现内核backtrace功能，辅助调试，理解内核栈帧结构。

### 实验过程

1. 在kernel/printf.c实现backtrace()，利用s0寄存器遍历栈帧，打印返回地址。
2. 在sys_sleep和panic中调用backtrace，观察输出。
3. 使用addr2line工具将地址转换为源码位置。

### 实验结果

backtrack函数的输出如下：
```
0x0000000080001e5c
0x0000000080001d34
0x0000000080001ab6
```

addr2line的输出如下：
```
.../xv6-labs-2024/kernel/sysproc.c:68
.../xv6-labs-2024/kernel/syscall.c:141 (discriminator 1)
.../xv6-labs-2024/kernel/trap.c:76
```

### 实验结论

硬件在函数调用的过程中通过保存返回地址和栈帧信息，能够快速定位内核错误发生的调用链，提升调试效率。

## Alarm

### 实验目的

实现用户态定时信号机制，支持用户进程周期性执行自定义处理函数。

### 实验过程

1. 新增sigalarm和sigreturn系统调用，修改相关头文件和Makefile。
2. 在proc结构体中添加alarm相关字段，管理定时器和处理函数指针，还有trapframe备份指针。
3. 修改trap.c，在时钟中断时判断并触发用户处理函数，保存和恢复用户上下文。
4. 防止处理函数重入，确保用户态能正确恢复。
5. 运行alarmtest和usertests，验证功能正确性。

### 实验结果

运行alarmtest的输出如下：
```
$ alarmtest
test0 start
...............................................................alarm!
test0 passed
test1 start
........alarm!
.......alarm!
........alarm!
.......alarm!
........alarm!
.......alarm!
........alarm!
........alarm!
..........alarm!
........alarm!
test1 passed
test2 start
.......................................................................................alarm!
test2 passed
test3 start
test3 passed
```

### 实验结论

通过实现alarm机制，掌握了用户级trap处理的基本原理，为更复杂的用户级异常处理（如页错误）奠定基础。

## Grade

![Grade](/grades/lab4.png)
