# Lab2实验报告

## Using gdb

### 实验目的
gdb是一个强大的调试工具，可以帮助我们在开发过程中定位和解决问题。在xv6中，我们可以使用gdb来调试内核代码和用户程序。本实验的目的是学习如何使用gdb调试xv6内核，并通过分析`panic`位置的上下文来找出问题的根本原因。

### 使用方法

**启动gdb并连接到qemu**

在一个窗口使用以下指令来启动qemu并等待gdb连接：
```
make qemu-gdb
```

在另外一个窗口使用以下指令来开启gdb并连接到qemu：
```
gdb-multiarch
...

(gdb) target remote localhost:1234
```

现在两个窗口已经连接成功

**加载文件并设置断点**

在gdb中加载内核映像文件：
```
(gdb) file /path/to/xv6/kernel/kernel
```

设置函数或地址断点：
```
(gdb) b sys_call
(gdb) b *0x12345678
```

继续运行：
```
(gdb) c
```

因为我们在sys_call函数上设置了断点，所以当程序执行到sys_call时会暂停，这样我们就可以检查程序的状态，查看寄存器和内存的内容，从而帮助我们定位问题。而在系统启动时就会通过`exec`系统调用来加载用户程序，所以执行完毕上述指令后`sys_call`函数上的断点就会被触发。

**查看断点处的代码并单步调试**

在gdb中，当程序在断点处暂停时，我们可以使用以下命令来查看断点处的代码或汇编代码：
```
(gdb) layout src
(gdb) layout asm
```

使用以下命令单步调试：
```
(gdb) step
```
或
```
(gdb) next
(gdb) n
```

使用以下指令打印变量值或寄存器值：
```
(gdb) print var_name
(gdb) p var_name
(gdb) p $reg_name
```

使用以下指令查看调用栈：
```
(gdb) backtrace
(gdb) bt
```

### 实验过程

1. 启动qemu并连接gdb
2. 加载内核映像文件并设置断点
3. 继续运行并查看断点处的代码
4. 单步调试并查看变量值
5. 查看调用栈
6. 修改内核代码触发`panic`
7. 使用gdb定位`panic`位置
8. 分析`panic`位置的上下文，查找问题原因

### 实验结果

![实验结果](/procedure/gdb.png)

### 实验结论

通过本次实验，我们成功地使用gdb对xv6内核进行了调试，掌握了gdb的基本使用方法，包括启动gdb、设置断点、单步调试、查看变量和调用栈等。通过分析`panic`位置的上下文，我们找到了问题的根本原因，并提出了相应的解决方案。这为我们后续的内核开发和调试提供了一种重要的调试手段。

## system call tracing

### 实验目的

实现系统调用的跟踪功能，能够记录每个系统调用及其返回值，为后续实验提供一个新的调试手段。

### 实验过程

1. 在Makefile中添加$U/_trace到UPROGS。
2. 在user/user.h中添加trace的原型，在user/usys.pl中添加存根，在kernel/syscall.h中添加系统调用号。
3. 在kernel/sysproc.c中添加sys_trace()函数，实现新的系统调用。
4. 修改fork()，将跟踪掩码从父进程复制到子进程。
5. 修改kernel/syscall.c中的syscall()函数，并添加系统调用的名称数组，打印跟踪输出。

### 实验结果

运行trace命令后能正确的跟踪所有系统调用及其返回值
```
$ trace 2147483647 grep hello README
4: syscall trace -> 0
4: syscall exec -> 3
4: syscall open -> 3
4: syscall read -> 1023
4: syscall read -> 991
4: syscall read -> 324
4: syscall read -> 0
4: syscall close -> 0
```

### 实验结论

通过本次实验，我们成功地实现了系统调用的跟踪功能，能够准确地记录每个系统调用及其返回值。这为我们后续的系统调用分析和调试提供了重要的支持。

## Attack Xv6

### 实验目的

本实验旨在通过利用xv6内核中的内存清零漏洞，突破进程间的隔离，获取其他进程的敏感信息。通过实际攻击演示，理解内核安全漏洞的危害及其利用方式。

### 实验过程

1. 阅读`user/secret.c`和`user/attacktest.c`，了解攻击目标和流程。
2. 分析漏洞：由于`memset`被省略，释放后的物理页内容未被清零，后续分配时可被新进程读取。
3. 修改`user/attack.c`，分配一块新内存并读取其内容，尝试获取前一个进程（secret.c）写入的8字节secret。
4. 将读取到的8字节内容写到文件描述符2（标准错误），供attacktest验证。
5. 在xv6 shell中运行`attacktest`，观察输出结果。

### 实验结果

成功利用漏洞，`attacktest`输出如下，证明攻击成功获取了secret：
```
$ attacktest
OK: secret is .aebf./
```

### 实验结论

本实验通过实际攻击演示了内核内存管理中的安全隐患。由于缺乏内存清零，攻击者可读取到其他进程遗留的敏感数据，严重威胁系统安全。内核开发需严格保证内存分配与释放的安全性，防止类似漏洞的产生。

## Grade

![grade-lab2](/grades/lab2.png)