### 查看运行时动态链接的库文件

当运行时动态库加载发生时，二进制文件分析工具在运行时几乎无用武之地。诸如ldd之类的工具无法涵盖通过调用dlopen()函数在运行时加载的动态库。

以下方法将提供已加载动态库的完整列表。该列表既包括静态感知的动态链接库，也包括在运行时动态链接的库

**strace 工具**

通过执行 `strace <程序命令行>` 可以有效追踪系统调用的执行序列，其中对我们最具价值的是 open() 和 mmap() 调用。
这种方法能完整呈现已加载的共享库列表。当出现共享库相关调用时，通常在 mmap() 调用之后的几行输出中会显示其加载地址。

```bash
$ strace ./driverApp
execve("./driverApp", ["./driverApp"], 0x7fffbdbd8ed0 /* 52 vars */) = 0
brk(NULL)                               = 0x5644b8cd7000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffce38bd700) = -1 EINVAL (无效的参数)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7b874948f000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v3/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v2/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/x86_64/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/x86_64/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/x86_64/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/x86_64/libdemo1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/libdemo1.so", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0775, st_size=16896, ...}, AT_EMPTY_PATH) = 0
getcwd("/home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/objdump_command/c/driverApp", 128) = 91
mmap(NULL, 16432, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7b874948a000
mmap(0x7b874948b000, 4096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1000) = 0x7b874948b000
mmap(0x7b874948c000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7b874948c000
mmap(0x7b874948d000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7b874948d000
close(3)                                = 0
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v3/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v2/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/glibc-hwcaps/x86-64-v3/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/glibc-hwcaps/x86-64-v2/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/haswell/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/haswell/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/haswell/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/haswell/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=119472, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 119472, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7b874946c000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\325\31p\226\367\t\200\30)\261\30\257\33|\366c"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7b8749200000
mprotect(0x7b8749228000, 2023424, PROT_NONE) = 0
mmap(0x7b8749228000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7b8749228000
mmap(0x7b87493bd000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7b87493bd000
mmap(0x7b8749416000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x7b8749416000
mmap(0x7b874941c000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7b874941c000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7b8749469000
arch_prctl(ARCH_SET_FS, 0x7b8749469740) = 0
set_tid_address(0x7b8749469a10)         = 19026
set_robust_list(0x7b8749469a20, 24)     = 0
rseq(0x7b874946a0e0, 0x20, 0, 0x53053053) = 0
mprotect(0x7b8749416000, 16384, PROT_READ) = 0
mprotect(0x7b874948d000, 4096, PROT_READ) = 0
mprotect(0x56448d512000, 4096, PROT_READ) = 0
mprotect(0x7b87494c9000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7b874946c000, 119472)          = 0
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x1), ...}, AT_EMPTY_PATH) = 0
getrandom("\x40\x11\xdc\xa9\xc9\x15\xf3\x66", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x5644b8cd7000
brk(0x5644b8cf8000)                     = 0x5644b8cf8000
write(1, "sharedLib1Function(1) is called\n", 32sharedLib1Function(1) is called
) = 32
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v3/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/glibc-hwcaps/x86-64-v2/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/haswell/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/tls/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/haswell/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib1/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/glibc-hwcaps/x86-64-v3/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/glibc-hwcaps/x86-64-v2/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/haswell/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/haswell/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/tls/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/haswell/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/haswell/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/x86_64/libdemo2.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (没有那个文件或目录)
openat(AT_FDCWD, "../sharedLib2/libdemo2.so", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0775, st_size=16896, ...}, AT_EMPTY_PATH) = 0
getcwd("/home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/objdump_command/c/driverApp", 128) = 91
mmap(NULL, 16432, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7b8749485000
mmap(0x7b8749486000, 4096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1000) = 0x7b8749486000
mmap(0x7b8749487000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7b8749487000
mmap(0x7b8749488000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7b8749488000
close(3)                                = 0
mprotect(0x7b8749488000, 4096, PROT_READ) = 0
write(1, "sharedLib2Function(1) is called\n", 32sharedLib2Function(1) is called
) = 32
exit_group(0)                           = ?
+++ exited with 0 +++
```

**LD_DEBUG 环境变量**

该工具凭借其灵活性和多样化的选项，始终位列链接/加载过程排查工具清单。
针对动态库追踪这一特定场景，使用 LD_DEBUG=files 选项能够输出大量详细信息，完整展示运行时动态加载的库文件（包括库名称、运行时路径、入口点地址等核心数据）。

```bash
$ LD_DEBUG=libs ./FactoryMethod
     26612:	find library=libidcard.so [0]; searching
     26612:	 search path=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/glibc-hwcaps/x86-64-v3:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/glibc-hwcaps/x86-64-v2:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v3:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v2:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework		(RUNPATH from file ./FactoryMethod)
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/glibc-hwcaps/x86-64-v3/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/glibc-hwcaps/x86-64-v2/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/haswell/x86_64/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/haswell/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/x86_64/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/tls/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/haswell/x86_64/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/haswell/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/x86_64/libidcard.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libidcard.so
     26612:
     26612:	find library=libframework.so [0]; searching
     26612:	 search path=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v3:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v2:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/x86_64:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework		(RUNPATH from file ./FactoryMethod)
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v3/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/glibc-hwcaps/x86-64-v2/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell/x86_64/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/haswell/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/x86_64/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/tls/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell/x86_64/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/haswell/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/x86_64/libframework.so
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libframework.so
     26612:
     26612:	find library=libstdc++.so.6 [0]; searching
     26612:	 search path=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework		(RUNPATH from file ./FactoryMethod)
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libstdc++.so.6
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libstdc++.so.6
     26612:	 search cache=/etc/ld.so.cache
     26612:	  trying file=/lib/x86_64-linux-gnu/libstdc++.so.6
     26612:
     26612:	find library=libgcc_s.so.1 [0]; searching
     26612:	 search path=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework		(RUNPATH from file ./FactoryMethod)
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libgcc_s.so.1
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libgcc_s.so.1
     26612:	 search cache=/etc/ld.so.cache
     26612:	  trying file=/lib/x86_64-linux-gnu/libgcc_s.so.1
     26612:
     26612:	find library=libc.so.6 [0]; searching
     26612:	 search path=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework		(RUNPATH from file ./FactoryMethod)
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libc.so.6
     26612:	  trying file=/home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libc.so.6
     26612:	 search cache=/etc/ld.so.cache
     26612:	  trying file=/lib/x86_64-linux-gnu/libc.so.6
     26612:
     26612:	find library=libm.so.6 [0]; searching
     26612:	 search cache=/etc/ld.so.cache
     26612:	  trying file=/lib/x86_64-linux-gnu/libm.so.6
     26612:
     26612:
     26612:	calling init: /lib64/ld-linux-x86-64.so.2
     26612:
     26612:
     26612:	calling init: /lib/x86_64-linux-gnu/libc.so.6
     26612:
     26612:
     26612:	calling init: /lib/x86_64-linux-gnu/libm.so.6
     26612:
     26612:
     26612:	calling init: /lib/x86_64-linux-gnu/libgcc_s.so.1
     26612:
     26612:
     26612:	calling init: /lib/x86_64-linux-gnu/libstdc++.so.6
     26612:
     26612:
     26612:	calling init: /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libframework.so
     26612:
     26612:
     26612:	calling init: /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libidcard.so
     26612:
     26612:
     26612:	initialize program: ./FactoryMethod
     26612:
     26612:
     26612:	transferring control: ./FactoryMethod
     26612:
制作小明的ID卡。
制作小红的ID卡。
制作小刚的ID卡。
使用小明的ID卡。
使用小红的ID卡。
使用小刚的ID卡。
     26612:
     26612:	calling fini: ./FactoryMethod [0]
     26612:
     26612:
     26612:	calling fini: /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/idcard/libidcard.so [0]
     26612:
     26612:
     26612:	calling fini: /home/hexu/git/Cpp.Compiling.Technology.Tutorial/binary_analysis/debugging_the_linking/cxx/build/framework/libframework.so [0]
     26612:
     26612:
     26612:	calling fini: /lib/x86_64-linux-gnu/libstdc++.so.6 [0]
     26612:
     26612:
     26612:	calling fini: /lib/x86_64-linux-gnu/libgcc_s.so.1 [0]
     26612:
     26612:
     26612:	calling fini: /lib/x86_64-linux-gnu/libm.so.6 [0]
     26612:
```

**/proc/<ID>/maps 文件**

当进程运行时，Linux操作系统会在 `/proc` 目录下维护一组文件，用于记录与进程相关的重要信息。
特别地，对于进程ID为 NNNN 的进程，其 `/proc/<NNNN>/maps` 文件包含了已加载库及其各自加载地址的完整列表。

例如，下面展示了该方法为Firefox浏览器生成的报告内容。

```bash
$ ps -ef | grep firefox
hexu        5953    2503 50 16:34 ?        00:00:02 /snap/firefox/7177/usr/lib/firefox/firefox
$ cat /proc/5953/maps
823d00000-823e00000 rw-p 00000000 00:00 0                                [anon:js-gc-heap]
120ad500000-120ad600000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
409bf700000-409bf800000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
5b9e5500000-5b9e5600000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
74d5f900000-74d5fa00000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
82222500000-82222600000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
96ee7a00000-96ee7b00000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
b38bee00000-b38bef00000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
f0410600000-f0410700000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
fae18900000-fae18a00000 rw-p 00000000 00:00 0                            [anon:js-gc-heap]
110082900000-110082a00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
11bb93a00000-11bb93b00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
13913a300000-13913a400000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
15bec3b00000-15bec3c00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
197dd4d00000-197dd4e00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
1b5781b00000-1b5781c00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
223dd7100000-223dd7200000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
271094f00000-271095000000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
2817fdd00000-2817fde00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
2abecea00000-2abeceb00000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
2bf305f00000-2bf306000000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
2d665d300000-2d665d400000 rw-p 00000000 00:00 0                          [anon:js-gc-heap]
2e7fc24c7000-2e7fc24d5000 r-xp 00000000 00:00 0                          [anon:js-executable-memory]
...
712d68284000-712d6831e000 r--p 00000000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d6831e000-712d6842f000 r-xp 0009a000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d6842f000-712d6849e000 r--p 001ab000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d6849e000-712d6849f000 ---p 0021a000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d6849f000-712d684aa000 r--p 0021a000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d684aa000-712d684ad000 rw-p 00225000 07:09 11130                      /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
712d684ad000-712d684b0000 rw-p 00000000 00:00 0
712d684b0000-712d684b1000 r--p 00000000 07:09 300                        /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so
712d684b1000-712d684b2000 r-xp 00001000 07:09 300                        /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so
712d684b2000-712d684b3000 r--p 00002000 07:09 300                        /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so
712d684b3000-712d684b4000 r--p 00002000 07:09 300                        /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so
712d684b4000-712d684b5000 rw-p 00003000 07:09 300                        /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so
712d684b5000-712d684b7000 rw-p 00000000 00:00 0
712d684b7000-712d684b9000 r--p 00000000 00:00 0                          [vvar]
712d684b9000-712d684bb000 r--p 00000000 00:00 0                          [vvar_vclock]
712d684bb000-712d684bd000 r-xp 00000000 00:00 0                          [vdso]
712d684bd000-712d684bf000 r--p 00000000 07:02 7482                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
712d684bf000-712d684e9000 r-xp 00002000 07:02 7482                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
712d684e9000-712d684f4000 r--p 0002c000 07:02 7482                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
712d684f4000-712d684f5000 r--p 00000000 07:02 2090                       /usr/lib/locale/C.utf8/LC_IDENTIFICATION
712d684f5000-712d684f7000 r--p 00037000 07:02 7482                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
712d684f7000-712d684f9000 rw-p 00039000 07:02 7482                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffd3741b000-7ffd37441000 rw-p 00000000 00:00 0                          [stack]
7ffd37441000-7ffd37443000 rw-p 00000000 00:00 0
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

备注1：
某些应用程序可能执行速度过快，导致没有足够时间检查进程内存映射。
此时最简单快捷的解决方案是通过gdb调试器启动进程，并在main函数处设置断点。当程序执行在断点处暂停时，您将有充足的时间检查进程内存映射。


备注2：
如果确认当前系统中只有一个该程序的实例在运行，可以结合使用pgrep（进程查找）命令来避免手动查找进程ID的步骤。以Firefox浏览器为例，只需执行：

```bash
$ cat /proc/`pgrep firefox`/maps
```

**lsof 工具**

lsof 实用程序可分析运行中的进程，并在标准输出流中打印进程打开的所有文件列表。
打开的文件可以是常规文件、目录、块特殊文件、字符特殊文件、执行文本引用、库文件、流或网络文件（互联网套接字、NFS 文件或 UNIX 域套接字）。

在它报告的各种已打开文件类型中，还会包含由进程加载的动态库列表，无论这些库是通过静态链接还是动态加载（在运行时通过 dlopen 调用）方式载入的。

以下代码片段演示了如何获取 Firefox 浏览器打开的所有共享库列表：

```bash
$ lsof -p 5953 | grep '.so'
firefox 5953 hexu  mem       REG                7,9             10834 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libicudata.so.70.1 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             10849 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libicuuc.so.70.1 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             11311 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libxml2.so.2.9.13 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9               870 /snap/firefox/7177/gnome-platform/usr/lib/librsvg-2.so.2.48.0 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9              9678 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.so (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             11289 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libxcb-randr.so.0.1.0 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             11257 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libwayland-server.so.0.22.0 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,4    378952     326 /snap/firefox/7177/usr/lib/x86_64-linux-gnu/libopus.so.0.8.0
firefox 5953 hexu  mem       REG                7,9             11233 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libvorbisenc.so.2.0.12 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             11231 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libvorbis.so.0.4.9 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             10297 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libFLAC.so.8.3.0 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9             11111 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libsndfile.so.1.0.31 (stat: No such file or directory)firefox 5953 hexu  mem       REG                7,9             11818 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/pulseaudio/libpulsecommon-15.99.so (stat: No such file or directory)
...
firefox 5953 hexu  mem       REG                7,4    409200     289 /snap/firefox/7177/usr/lib/firefox/libssl3.so
firefox 5953 hexu  mem       REG                7,4   1449136     280 /snap/firefox/7177/usr/lib/firefox/libmozsqlite3.so
firefox 5953 hexu  mem       REG                7,4    169096     287 /snap/firefox/7177/usr/lib/firefox/libsmime3.so
firefox 5953 hexu  mem       REG                7,4    739152     283 /snap/firefox/7177/usr/lib/firefox/libnss3.so
firefox 5953 hexu  mem       REG                7,4    184712     284 /snap/firefox/7177/usr/lib/firefox/libnssutil3.so
firefox 5953 hexu  mem       REG                7,4    179200     274 /snap/firefox/7177/usr/lib/firefox/liblgpllibs.so
firefox 5953 hexu  mem       REG                7,4   8539912     273 /snap/firefox/7177/usr/lib/firefox/libgkcodecs.so
firefox 5953 hexu  mem       REG                7,4    172704     279 /snap/firefox/7177/usr/lib/firefox/libmozsandbox.so
firefox 5953 hexu  mem       REG                7,4    210000     282 /snap/firefox/7177/usr/lib/firefox/libnspr4.so
firefox 5953 hexu  mem       REG                7,2              7511 /usr/lib/x86_64-linux-gnu/libc.so.6 (path dev=8,2, inode=3410336)
firefox 5953 hexu  mem       REG                7,2              7561 /usr/lib/x86_64-linux-gnu/libgcc_s.so.1 (path dev=8,2, inode=3419500)
firefox 5953 hexu  mem       REG                7,2              7612 /usr/lib/x86_64-linux-gnu/libm.so.6 (path dev=8,2, inode=3410339)
firefox 5953 hexu  mem       REG                7,4      4112     277 /snap/firefox/7177/usr/lib/firefox/libmozgtk.so
firefox 5953 hexu  mem       REG                7,4     12048     286 /snap/firefox/7177/usr/lib/firefox/libplds4.so
firefox 5953 hexu  mem       REG                7,4     16232     285 /snap/firefox/7177/usr/lib/firefox/libplc4.so
firefox 5953 hexu  mem       REG                7,9             11130 /snap/firefox/7177/gnome-platform/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30 (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,9               300 /snap/firefox/7177/gnome-platform/lib/x86_64-linux-gnu/bindtextdomain.so (stat: No such file or directory)
firefox 5953 hexu  mem       REG                7,2              7482 /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 (path dev=8,2, inode=3410333)
```

备注：
如果确认当前系统中只有一个该程序的实例在运行，可以结合使用pgrep（进程查找）命令来避免手动查找进程ID的步骤。以Firefox浏览器为例，只需执行：

```bash
$ lsof -p `pgrep firefox`
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

