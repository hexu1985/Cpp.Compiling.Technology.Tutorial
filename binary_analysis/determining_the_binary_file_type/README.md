### 判断二进制文件类型

以下是几种简单的二进制文件类型判断方法：

1. file工具能够识别多种文件类型，可能是最简洁、快速且高效的二进制文件性质判断方式。

```bash
$ file /usr/bin/gst-inspect-1.0
/usr/bin/gst-inspect-1.0: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=a92c6092ee0fba68dfe54e5c22c3f3ff6e7b58f1, for GNU/Linux 3.2.0, stripped
$
$ file /usr/lib/x86_64-linux-gnu/libpthread.a 
/usr/lib/x86_64-linux-gnu/libpthread.a: current ar archive
$
$ file /lib/x86_64-linux-gnu/libc.so.6 
/lib/x86_64-linux-gnu/libc.so.6: ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=d5197096f709801829b118af1b7cf6631efa2dcd, for GNU/Linux 3.2.0, stripped
```

2. readelf工具通过分析ELF头信息可获取二进制文件类型等详细信息。执行命令：

```
$ readelf -h <二进制文件路径> | grep Type
```

将显示以下类型之一：
- EXEC（可执行文件）
- DYN（共享对象文件）
- REL（可重定位文件）
对于静态库文件，该命令会为库中包含的每个目标文件分别显示REL输出。

```bash
$ readelf -h driverApp
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (Position-Independent Executable file)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x1180
  程序头起点：          64 (bytes into file)
  Start of section headers:          17672 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 36
```

```bash
$ readelf -h libdemo1.so
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (共享目标文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          64 (bytes into file)
  Start of section headers:          14592 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         11
  Size of section headers:           64 (bytes)
  Number of section headers:         36
  Section header string table index: 35
```

```bash
$ readelf -h sharedLib1Functions.o
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              REL (可重定位文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          0 (bytes into file)
  Start of section headers:          2488 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         23
  Section header string table index: 22
```

3. objdump工具同样支持ELF头分析，但报告内容相对简略。执行命令：

```
$ objdump -f <二进制文件路径>
```

输出结果中将包含以下取值之一：
- EXEC_P（可执行文件）
- DYNAMIC（共享对象文件）
- 对于目标文件则不会显示类型标识
在处理静态库时，该命令会为库中每个目标文件分别显示对应信息。

```bash
$ objdump -f driverApp

driverApp：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000150：
HAS_SYMS, DYNAMIC, D_PAGED
起始地址 0x0000000000001180
$
$ objdump -f libdemo1.so

libdemo1.so：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000150：
HAS_SYMS, DYNAMIC, D_PAGED
起始地址 0x0000000000000000
$
$ objdump -f sharedLib1Functions.o

sharedLib1Functions.o：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000011：
HAS_RELOC, HAS_SYMS
起始地址 0x0000000000000000
```

#### 参考资料:
《高级C/C++编译技术》: 13.2 确定二进制文件类型
