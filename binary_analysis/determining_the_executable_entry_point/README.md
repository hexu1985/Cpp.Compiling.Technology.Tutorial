### 确定可执行文件入口点  
可执行文件的入口点（即程序内存映射中第一条指令的地址）可通过以下两种方式确定：

1. readelf ELF头分析

通过分析ELF头文件可获取二进制文件类型等详细信息。执行命令：  

```bash
$ readelf -h <二进制文件路径> | grep Entry
```  

输出结果格式如下：  

`Entry point address：0x<地址>`

```bash
$ LANG=C readelf -h ./driverApp | grep 'Entry'
  Entry point address:               0x1180
```

2. objdump EFL头分析

该方法可提供类似分析结果，但报告内容相对简略。执行命令：  

```bash
$ objdump -f <二进制文件路径> | grep start
```  

输出结果格式如下：  

`start address 0x<地址>`

```bash
$ LANG=C objdump -f driverApp | grep start
start address 0x0000000000001180
```

#### 参考资料:
《高级C/C++编译技术》: 13.3.1 确定可执行文件入口点
