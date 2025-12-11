### 查看运行时动态链接的库文件

当运行时动态库加载发生时，二进制文件分析工具在运行时几乎无用武之地。诸如ldd之类的工具无法涵盖通过调用dlopen()函数在运行时加载的动态库。

以下方法将提供已加载动态库的完整列表。该列表既包括静态感知的动态链接库，也包括在运行时动态链接的库

**strace 工具**

通过执行 `strace <程序命令行>` 可以有效追踪系统调用的执行序列，其中对我们最具价值的是 open() 和 mmap() 调用。
这种方法能完整呈现已加载的共享库列表。当出现共享库相关调用时，通常在 mmap() 调用之后的几行输出中会显示其加载地址。

```bash
$ strace ./test
execve("./test", ["./test"], 0x7ffd45f647f0 /* 31 vars */) = 0
brk(NULL)                               = 0x564086dfb000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x79a03e850000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=84867, ...}) = 0
mmap(NULL, 84867, PROT_READ, MAP_PRIVATE, 3, 0) = 0x79a03e83b000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=2592224, ...}) = 0
mmap(NULL, 2609472, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a03e400000
mmap(0x79a03e49d000, 1343488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9d000) = 0x79a03e49d000
mmap(0x79a03e5e5000, 552960, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e5000) = 0x79a03e5e5000
mmap(0x79a03e66c000, 57344, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26b000) = 0x79a03e66c000
mmap(0x79a03e67a000, 12608, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x79a03e67a000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a03e000000
mmap(0x79a03e028000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x79a03e028000
mmap(0x79a03e1b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x79a03e1b0000
mmap(0x79a03e1ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x79a03e1ff000
mmap(0x79a03e205000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x79a03e205000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=952616, ...}) = 0
mmap(NULL, 950296, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a03e752000
mmap(0x79a03e762000, 520192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x10000) = 0x79a03e762000
mmap(0x79a03e7e1000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8f000) = 0x79a03e7e1000
mmap(0x79a03e839000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe7000) = 0x79a03e839000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=183024, ...}) = 0
mmap(NULL, 185256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a03e724000
mmap(0x79a03e728000, 147456, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x79a03e728000
mmap(0x79a03e74c000, 16384, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x79a03e74c000
mmap(0x79a03e750000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2b000) = 0x79a03e750000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x79a03e722000
arch_prctl(ARCH_SET_FS, 0x79a03e723500) = 0
set_tid_address(0x79a03e7237d0)         = 340812
set_robust_list(0x79a03e7237e0, 24)     = 0
rseq(0x79a03e723e20, 0x20, 0, 0x53053053) = 0
mprotect(0x79a03e1ff000, 16384, PROT_READ) = 0
mprotect(0x79a03e750000, 4096, PROT_READ) = 0
mprotect(0x79a03e839000, 4096, PROT_READ) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x79a03e720000
mprotect(0x79a03e66c000, 45056, PROT_READ) = 0
mprotect(0x56407ae1f000, 4096, PROT_READ) = 0
mprotect(0x79a03e88e000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x79a03e83b000, 84867)           = 0
futex(0x79a03e67a7bc, FUTEX_WAKE_PRIVATE, 2147483647) = 0
getrandom("\x15\xf6\x5f\x2e\xdf\x14\xaa\x31", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x564086dfb000
brk(0x564086e1c000)                     = 0x564086e1c000
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, {tv_sec=0, tv_nsec=4914098}) = 0
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, {tv_sec=0, tv_nsec=902305808}) = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x3), ...}) = 0
write(1, "Time: 0.90 sec\n", 15Time: 0.90 sec
)        = 15
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x3), ...}) = 0
read(0,
"\n", 1024)                     = 1
exit_group(0)                           = ?
+++ exited with 0 +++
```

**LD_DEBUG 环境变量**

该工具凭借其灵活性和多样化的选项，始终位列链接/加载过程排查工具清单。
针对动态库追踪这一特定场景，使用 LD_DEBUG=files 选项能够输出大量详细信息，完整展示运行时动态加载的库文件（包括库名称、运行时路径、入口点地址等核心数据）。

```bash
$ LD_DEBUG=libs ./test 
    340958:     find library=libstdc++.so.6 [0]; searching
    340958:      search cache=/etc/ld.so.cache
    340958:       trying file=/lib/x86_64-linux-gnu/libstdc++.so.6
    340958:
    340958:     find library=libc.so.6 [0]; searching
    340958:      search cache=/etc/ld.so.cache
    340958:       trying file=/lib/x86_64-linux-gnu/libc.so.6
    340958:
    340958:     find library=libm.so.6 [0]; searching
    340958:      search cache=/etc/ld.so.cache
    340958:       trying file=/lib/x86_64-linux-gnu/libm.so.6
    340958:
    340958:     find library=libgcc_s.so.1 [0]; searching
    340958:      search cache=/etc/ld.so.cache
    340958:       trying file=/lib/x86_64-linux-gnu/libgcc_s.so.1
    340958:
    340958:
    340958:     calling init: /lib64/ld-linux-x86-64.so.2
    340958:
    340958:
    340958:     calling init: /lib/x86_64-linux-gnu/libc.so.6
    340958:
    340958:
    340958:     calling init: /lib/x86_64-linux-gnu/libgcc_s.so.1
    340958:
    340958:
    340958:     calling init: /lib/x86_64-linux-gnu/libm.so.6
    340958:
    340958:
    340958:     calling init: /lib/x86_64-linux-gnu/libstdc++.so.6
    340958:
    340958:
    340958:     initialize program: ./test
    340958:
    340958:
    340958:     transferring control: ./test
    340958:

Time: 0.97 sec
    340958:
    340958:     calling fini:  [0]
    340958:
    340958:
    340958:     calling fini: /lib/x86_64-linux-gnu/libstdc++.so.6 [0]
    340958:
    340958:
    340958:     calling fini: /lib/x86_64-linux-gnu/libm.so.6 [0]
    340958:
    340958:
    340958:     calling fini: /lib/x86_64-linux-gnu/libgcc_s.so.1 [0]
    340958:
    340958:
    340958:     calling fini: /lib/x86_64-linux-gnu/libc.so.6 [0]
    340958:
    340958:
    340958:     calling fini: /lib64/ld-linux-x86-64.so.2 [0]
    340958:
```

**/proc/<ID>/maps 文件**

当进程运行时，Linux操作系统会在 `/proc` 目录下维护一组文件，用于记录与进程相关的重要信息。
特别地，对于进程ID为 NNNN 的进程，其 `/proc/<NNNN>/maps` 文件包含了已加载库及其各自加载地址的完整列表。

例如，下面展示了该方法为test生成的报告内容。

在一个终端上执行：
```bash
$ ./test 
Time: 0.89 sec
```

在另外一个终端上执行：
```bash
$ ps -eaf | grep test
kernoops    1448       1  0 Dec06 ?        00:00:00 /usr/sbin/kerneloops --test
hexu      341102  339248  1 10:19 pts/3    00:00:00 ./test
hexu      341131  340565  0 10:20 pts/5    00:00:00 grep --color=auto test
$ cat /proc/341102/maps 
57c6bafb5000-57c6bafb6000 r--p 00000000 08:02 2889995                    /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/listing_dynamically_linked_libraries/cxx/test
57c6bafb6000-57c6bafb7000 r-xp 00001000 08:02 2889995                    /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/listing_dynamically_linked_libraries/cxx/test
57c6bafb7000-57c6bafb8000 r--p 00002000 08:02 2889995                    /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/listing_dynamically_linked_libraries/cxx/test
57c6bafb8000-57c6bafb9000 r--p 00002000 08:02 2889995                    /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/listing_dynamically_linked_libraries/cxx/test
57c6bafb9000-57c6bafba000 rw-p 00003000 08:02 2889995                    /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/listing_dynamically_linked_libraries/cxx/test
57c6f184b000-57c6f186c000 rw-p 00000000 00:00 0                          [heap]
718f33c00000-718f33c28000 r--p 00000000 08:02 3410336                    /usr/lib/x86_64-linux-gnu/libc.so.6
718f33c28000-718f33db0000 r-xp 00028000 08:02 3410336                    /usr/lib/x86_64-linux-gnu/libc.so.6
718f33db0000-718f33dff000 r--p 001b0000 08:02 3410336                    /usr/lib/x86_64-linux-gnu/libc.so.6
718f33dff000-718f33e03000 r--p 001fe000 08:02 3410336                    /usr/lib/x86_64-linux-gnu/libc.so.6
718f33e03000-718f33e05000 rw-p 00202000 08:02 3410336                    /usr/lib/x86_64-linux-gnu/libc.so.6
718f33e05000-718f33e12000 rw-p 00000000 00:00 0 
718f34000000-718f3409d000 r--p 00000000 08:02 3419893                    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
718f3409d000-718f341e5000 r-xp 0009d000 08:02 3419893                    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
718f341e5000-718f3426c000 r--p 001e5000 08:02 3419893                    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
718f3426c000-718f34277000 r--p 0026b000 08:02 3419893                    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
718f34277000-718f3427a000 rw-p 00276000 08:02 3419893                    /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
718f3427a000-718f3427e000 rw-p 00000000 00:00 0 
718f342ec000-718f342f0000 rw-p 00000000 00:00 0 
718f342f0000-718f342f4000 r--p 00000000 08:02 3419500                    /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
718f342f4000-718f34318000 r-xp 00004000 08:02 3419500                    /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
718f34318000-718f3431c000 r--p 00028000 08:02 3419500                    /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
718f3431c000-718f3431d000 r--p 0002b000 08:02 3419500                    /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
718f3431d000-718f3431e000 rw-p 0002c000 08:02 3419500                    /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
718f3431e000-718f3432e000 r--p 00000000 08:02 3410339                    /usr/lib/x86_64-linux-gnu/libm.so.6
718f3432e000-718f343ad000 r-xp 00010000 08:02 3410339                    /usr/lib/x86_64-linux-gnu/libm.so.6
718f343ad000-718f34405000 r--p 0008f000 08:02 3410339                    /usr/lib/x86_64-linux-gnu/libm.so.6
718f34405000-718f34406000 r--p 000e7000 08:02 3410339                    /usr/lib/x86_64-linux-gnu/libm.so.6
718f34406000-718f34407000 rw-p 000e8000 08:02 3410339                    /usr/lib/x86_64-linux-gnu/libm.so.6
718f3441c000-718f3441e000 rw-p 00000000 00:00 0 
718f3441e000-718f34420000 r--p 00000000 00:00 0                          [vvar]
718f34420000-718f34422000 r--p 00000000 00:00 0                          [vvar_vclock]
718f34422000-718f34424000 r-xp 00000000 00:00 0                          [vdso]
718f34424000-718f34425000 r--p 00000000 08:02 3410333                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
718f34425000-718f34450000 r-xp 00001000 08:02 3410333                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
718f34450000-718f3445a000 r--p 0002c000 08:02 3410333                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
718f3445a000-718f3445c000 r--p 00036000 08:02 3410333                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
718f3445c000-718f3445e000 rw-p 00038000 08:02 3410333                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffc525ec000-7ffc5260d000 rw-p 00000000 00:00 0                          [stack]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

备注1：
某些应用程序可能执行速度过快，导致没有足够时间检查进程内存映射。
此时最简单快捷的解决方案是通过gdb调试器启动进程，并在main函数处设置断点。当程序执行在断点处暂停时，您将有充足的时间检查进程内存映射。


备注2：
如果确认当前系统中只有一个该程序的实例在运行，可以结合使用pgrep（进程查找）命令来避免手动查找进程ID的步骤。以Firefox浏览器为例，只需执行：

```bash
$ cat /proc/`pgrep test`/maps
```

**lsof 工具**

lsof 实用程序可分析运行中的进程，并在标准输出流中打印进程打开的所有文件列表。
打开的文件可以是常规文件、目录、块特殊文件、字符特殊文件、执行文本引用、库文件、流或网络文件（互联网套接字、NFS 文件或 UNIX 域套接字）。

在它报告的各种已打开文件类型中，还会包含由进程加载的动态库列表，无论这些库是通过静态链接还是动态加载（在运行时通过 dlopen 调用）方式载入的。

以下代码片段演示了如何获取 test 浏览器打开的所有共享库列表：

在一个终端上执行：
```bash
$ ./test 
Time: 0.89 sec
```

在另外一个终端上执行：
```bash
$ ps -eaf | grep test
kernoops    1448       1  0 Dec06 ?        00:00:00 /usr/sbin/kerneloops --test
hexu      341102  339248  1 10:19 pts/3    00:00:00 ./test
hexu      341131  340565  0 10:20 pts/5    00:00:00 grep --color=auto test
$ lsof -p 341102 | grep '.so'
$ lsof -p 341102 | grep '.so'
lsof: WARNING: can't stat() tracefs file system /sys/kernel/debug/tracing
      Output information may be incomplete.
test    341102 hexu  mem    REG    8,2  2125328 3410336 /usr/lib/x86_64-linux-gnu/libc.so.6
test    341102 hexu  mem    REG    8,2  2592224 3419893 /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
test    341102 hexu  mem    REG    8,2   183024 3419500 /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
test    341102 hexu  mem    REG    8,2   952616 3410339 /usr/lib/x86_64-linux-gnu/libm.so.6
test    341102 hexu  mem    REG    8,2   236616 3410333 /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
```

备注：
如果确认当前系统中只有一个该程序的实例在运行，可以结合使用pgrep（进程查找）命令来避免手动查找进程ID的步骤。以Firefox浏览器为例，只需执行：

```bash
$ lsof -p `pgrep test`
```

请注意，lsof 提供了定期检查进程的命令行选项。通过设定检测周期，您可能捕捉到运行时动态加载和卸载发生的瞬间。

使用 `-r` 选项运行 lsof 时，周期性的进程检查会无限循环执行，需要用户按下 `Ctrl-C` 才能终止。
而使用 `+r` 选项运行 lsof 时，当检测不到任何已打开文件后，lsof 将自动终止运行。


**编程化方法**

同样可以通过编写代码来输出进程加载的库信息。
当应用程序代码中集成对 dl_iterate_phdr() 函数的调用时，其运行时打印的信息可帮助您确定加载的共享库完整列表，
以及每个库相关的附加数据（例如已加载库的起始地址）。

为演示这一概念，我们创建了包含驱动程序和两个简单动态库的示例代码。以下示例展示了应用程序的源文件内容。
其中一个动态库采用静态链接方式动态集成，而另一个库则通过调用 dlopen() 函数实现动态加载：

```c
#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <dlfcn.h>
#include "sharedLib1Functions.h"
#include "sharedLib2Functions.h"

static const char* segment_type_to_string(uint32_t type)
{
	switch(type)
	{
	case PT_NULL:         // 0
		return "Unused";
		break;
	case PT_LOAD:         // 1
		return "Loadable Program Segment";
		break;
	case PT_DYNAMIC:      //2
		return "Dynamic linking information";
		break;
	case PT_INTERP:       // 3
		return "Program interpreter";
		break;
	case PT_NOTE:         // 4
		return "Auxiliary information";
		break;
	case PT_SHLIB:        // 5
		return "Reserved";
		break;
	case PT_PHDR:         // 6
		return "Entry for header table itself";
		break;
	case PT_TLS:          // 7
		return "Thread-local storage segment";
		break;
//	case PT_NUM:          // 8		/* Number of defined types */
	case PT_LOOS:         // 0x60000000	
		return "Start of OS-specific";
		break;
	case PT_GNU_EH_FRAME: // 0x6474e550	
		return "GCC .eh_frame_hdr segment";
		break;
	case PT_GNU_STACK:    // 0x6474e551	
		return "Indicates stack executability";
		break;
	case PT_GNU_RELRO:    // 0x6474e552	
		return "Read-only after relocation";
		break;
//	case PT_LOSUNW:       // 0x6ffffffa
	case PT_SUNWBSS:      // 0x6ffffffa	
		return "Sun Specific segment";
		break;
	case PT_SUNWSTACK:    // 0x6ffffffb	
		return "Sun Stack segment";
		break;
//	case PT_HISUNW:       // 0x6fffffff
//	case PT_HIOS:         // 0x6fffffff	/* End of OS-specific */
//	case PT_LOPROC:       // 0x70000000	/* Start of processor-specific */
//	case PT_HIPROC:       // 0x7fffffff	/* End of processor-specific */	
	default:
		return "???";
	}
}

static const char* flags_to_string(uint32_t flags)
{
	switch(flags)
	{
	case 1:
		return "--x";
		break;
	case 2:
		return "-w-";
		break;
	case 3:
		return "-wx";
		break;
	case 4:
		return "r--";
		break;
	case 5:
		return "r-x";
		break;
	case 6:
		return "rw-";
		break;
	case 7:
		return "rwx";
		break;
	default:
		return "???";
		break;
	}
}

static int header_handler(struct dl_phdr_info* info, size_t size, void* data)
{
	int j;
    printf("name=%s (%d segments) address=%p\n",
            info->dlpi_name, info->dlpi_phnum, (void*)info->dlpi_addr);
    for (j = 0; j < info->dlpi_phnum; j++) {
         printf("\t\t header %2d: address=%10p\n", j,
             (void*) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
         printf("\t\t\t type=0x%X (%s),\n\t\t\t flags=0x%X (%s)\n",
                 info->dlpi_phdr[j].p_type, 
                 segment_type_to_string(info->dlpi_phdr[j].p_type),
                 info->dlpi_phdr[j].p_flags,
                 flags_to_string(info->dlpi_phdr[j].p_flags));
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
	// function from statically aware loaded library
	sharedLib1Function(argc);
	
	// function from run-time dynamically loaded library
    void* pLibHandle = dlopen("libdemo2.so", RTLD_GLOBAL | RTLD_NOW);
    if(NULL == pLibHandle)
    {
		printf("Failed loading libdemo2.so, error = %s\n", dlerror());
		return -1;
	}	
	PFUNC pFunc = (PFUNC)dlsym(pLibHandle, "sharedLib2Function");
	
	if(NULL == pFunc)
	{
		printf("Failed identifying the symbol \"sharedLib2Function\"\n");
		dlclose(pLibHandle);
		pLibHandle = NULL;
		return -1;
	}
	
	pFunc(argc);
	if(2 == argc)
		getchar();
		
	if(3 == argc)
		dl_iterate_phdr(header_handler, NULL);
		
	return 0;
}
```

此代码示例的核心在于对 dl_iterate_phdr() 函数的调用。
该函数会在运行时提取相关的进程映射信息，并将其传递给调用者。
调用方需要负责提供回调函数（本例中为 header_handler()）的自定义实现。

下面展示了程序运行后可能产生的屏幕输出示例。

```bash
$ ./driverApp 1 2 | grep -A 20 libdemo
name=../sharedLib1/libdemo1.so (11 segments) address=0x750332487000
                 header  0: address=0x750332487000
                         type=0x1 (Loadable Program Segment),
                         flags=0x4 (r--)
                 header  1: address=0x750332488000
                         type=0x1 (Loadable Program Segment),
                         flags=0x5 (r-x)
                 header  2: address=0x750332489000
                         type=0x1 (Loadable Program Segment),
                         flags=0x4 (r--)
                 header  3: address=0x75033248adf8
                         type=0x1 (Loadable Program Segment),
                         flags=0x6 (rw-)
                 header  4: address=0x75033248ae08
                         type=0x2 (Dynamic linking information),
                         flags=0x6 (rw-)
                 header  5: address=0x7503324872a8
                         type=0x4 (Auxiliary information),
                         flags=0x4 (r--)
                 header  6: address=0x7503324872c8
                         type=0x4 (Auxiliary information),
--
name=../sharedLib2/libdemo2.so (11 segments) address=0x750332482000
                 header  0: address=0x750332482000
                         type=0x1 (Loadable Program Segment),
                         flags=0x4 (r--)
                 header  1: address=0x750332483000
                         type=0x1 (Loadable Program Segment),
                         flags=0x5 (r-x)
                 header  2: address=0x750332484000
                         type=0x1 (Loadable Program Segment),
                         flags=0x4 (r--)
                 header  3: address=0x750332485df8
                         type=0x1 (Loadable Program Segment),
                         flags=0x6 (rw-)
                 header  4: address=0x750332485e08
                         type=0x2 (Dynamic linking information),
                         flags=0x6 (rw-)
                 header  5: address=0x7503324822a8
                         type=0x4 (Auxiliary information),
                         flags=0x4 (r--)
                 header  6: address=0x7503324822c8
                         type=0x4 (Auxiliary information),
```


#### 参考资料:
《高级C/C++编译技术》: 13.11 查看运行时动态链接的文件

