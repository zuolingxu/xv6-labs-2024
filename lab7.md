# Lab7实验报告

## Memory allocator

### 实验目的

通过重构xv6物理内存分配器，减少多核环境下的锁竞争，提高分配/释放性能，理解多核操作系统中锁粒度和数据结构设计对并行性的影响。

### 实验过程

1. 阅读kalloc.c和相关章节，分析单锁单链表带来的争用瓶颈。
2. 设计每CPU一个freelist和锁，初始化时将所有空闲页分配给当前CPU。
3. 修改kalloc/kfree，优先操作本地CPU的freelist，空时尝试“偷取”其他CPU的页。
4. 所有kmem相关锁命名以"kmem"开头，保证统计输出正确。
5. 运行`kalloctest`，观察锁竞争次数显著下降。
6. 运行`sbrkmuch`和`usertests -q`，确保分配器功能正确。

### 实验结果

kalloctest输出如下：
```
$ kalloctest
start test1
test1 results:
--- lock kmem/bcache stats
lock: kmem: #test-and-set 0 #acquire() 94703
lock: kmem: #test-and-set 0 #acquire() 173699
lock: kmem: #test-and-set 0 #acquire() 164725
lock: bcache: #test-and-set 0 #acquire() 32
...输出省略...
tot= 0
test1 OK
...
test3 OK
```
sbrkmuch和usertests全部通过。

### 实验结论

通过每CPU freelist和锁设计，极大减少了锁争用，提高了分配器的并行性能。掌握了多核环境下数据结构和锁粒度优化的基本方法。

## Buffer cache

### 实验目的

重构xv6块缓存（bcache），减少多进程/多核文件系统操作时的锁竞争，理解哈希表分桶和细粒度锁在共享缓存中的应用。

### 实验过程

1. 阅读bio.c和相关章节，分析bcache.lock争用原因。
2. 设计哈希表分桶，每个桶一个锁，所有锁命名以"bcache"开头。
3. 修改bget/brelse，查找和释放时只需持有相关桶锁，移除全局LRU链表和锁。
4. 缓存miss时，序列化选择空闲buf，必要时移动buf到新桶。
5. 运行`bcachetest`，观察bcache相关锁争用次数显著下降。
6. 运行`usertests -q`，确保文件系统功能正确。

### 实验结果

bcachetest输出如下：
```
$ bcachetest
start test0
test0 results:
--- lock kmem/bcache stats
lock: kmem: #test-and-set 0 #acquire() 33030
lock: bcache: #test-and-set 0 #acquire() 96
lock: bcache.bucket: #test-and-set 0 #acquire() 6229
lock: bcache.bucket: #test-and-set 0 #acquire() 6204
...输出省略...
tot= 0
test0: OK
...
test3 OK
```
usertests全部通过。

### 实验结论

通过哈希分桶和细粒度锁，显著降低了块缓存的锁争用，提升了文件系统并发性能。掌握了共享缓存并发访问的基本优化方法。

## Grade

![grade-lab7](/grades/lab7.png)
