# Lab6实验报告

## Part One: NIC

### 实验目的

实现xv6的E1000网卡驱动，掌握DMA、环形缓冲区、设备寄存器操作等底层网络设备驱动技术。理解网卡收发包的基本流程，为后续协议栈实现打下基础。

### 实验过程

1. 阅读E1000芯片手册，理解DMA收发机制、寄存器含义、描述符结构。
2. 完善`e1000_transmit()`，实现发送环形队列管理，填充描述符，通知网卡发送数据，处理资源释放。
3. 完善`e1000_recv()`，实现接收环形队列扫描，检测新包，调用`net_rx()`交给协议栈，分配新缓冲区，更新描述符和寄存器。
4. 处理并发访问，添加锁保护关键区，保证多核/中断安全。
5. 运行`nettest txone`和`nettest rxone`，通过单包收发测试，使用`tcpdump`分析`packets.pcap`包内容。

### 实验结果

收发包测试输出如下：
```
$ nettest txone
txone: sending one packet
...输出省略...
$ nettest rxone
arp_rx: received an ARP packet
ip_rx: received an IP packet
...输出省略...
```
`tcpdump -XXnr packets.pcap`显示ARP和UDP包内容。

### 实验结论

通过实现E1000网卡驱动，掌握了DMA收发、环形缓冲区、设备寄存器操作等底层驱动技术。理解了网卡与操作系统的交互流程，为协议栈开发提供了坚实基础。

## Part Two: UDP Receive

### 实验目的

实现UDP协议的接收处理，支持用户进程通过系统调用接收UDP包，掌握协议解析、端口绑定、包队列管理、进程同步等操作系统网络核心技术。

### 实验过程

1. 设计端口绑定和包队列结构，支持每个端口最多缓存16个包。
2. 完善`ip_rx()`，解析IP/UDP头，判断目标端口是否已绑定，入队或丢弃包。
3. 实现`sys_bind()`，支持用户进程绑定端口，初始化队列。
4. 实现`sys_recv()`，支持用户进程阻塞等待包到达，唤醒机制，拷贝包内容到用户空间，返回源IP/端口等信息。
5. 注意字节序转换，正确解析协议头部。
6. 运行`nettest grade`，通过ping和DNS等多种UDP收发测试。

### 实验结果

UDP协议栈测试输出如下：
```
$ nettest grade
txone: sending one packet
arp_rx: received an ARP packet
ip_rx: received an IP packet
ping0: starting
ping0: OK
ping1: starting
ping1: OK
dns: starting
DNS arecord for pdos.csail.mit.edu. is 128.52.129.126
dns: OK
...输出省略...
```

### 实验结论

通过实现UDP协议栈的接收部分，掌握了协议解析、端口管理、包队列、进程同步等操作系统网络核心技术。能够支持用户进程高效、可靠地收发UDP数据包，为更复杂的网络协议实现奠定基础。

## Grade

![grade-lab6](/grades/lab6.png)
