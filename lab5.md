# Lab5实验报告

## Copy-on-Write Fork

### 实验目的

实现xv6内核的写时复制（Copy-on-Write, COW）fork机制，提升fork效率，减少物理内存和拷贝开销，理解虚拟内存的间接性和异常处理机制。

### 实验过程

1. 修改`uvmcopy()`，将父进程的物理页直接映射到子进程，所有可写用户页PTE去掉PTE_W，并设置COW标记（利用PTE_RSW位）。
2. 父子进程共享物理页，维护物理页引用计数。kalloc.c中增加计数数组，kalloc分配时初始化为1，fork共享时递增，kfree释放时递减，计数为0才真正释放物理页。
3. 修改`usertrap()`，在写页异常时检测COW页，分配新物理页，拷贝原内容，更新PTE为可写并去除COW标记。若原本是只读页（如代码段），则直接kill进程。
4. 修改`copyout()`，遇到COW页时也触发写时复制逻辑。
5. 运行`cowtest`和`usertests -q`，确保所有测试通过。

### 实验结果

运行cowtest输出如下：
```
$ cowtest
simple: ok
simple: ok
three: ok
three: ok
three: ok
file: ok
forkfork: ok
ALL COW TESTS PASSED
```
运行usertests -q全部通过。

### 实验结论

通过COW fork机制，显著减少了fork时的物理内存分配和数据拷贝，提升了系统性能。掌握了虚拟内存异常处理、物理页共享与引用计数等操作系统核心技术。COW机制广泛应用于现代操作系统，适用于高效进程创建和资源管理。

## Grade

![Grade](/grades/lab5.png)
