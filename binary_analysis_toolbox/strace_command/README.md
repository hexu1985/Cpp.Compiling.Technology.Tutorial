### strace命令

strace命令行实用程序能够追踪进程执行的系统调用以及进程接收到的信号。
它有助于查明运行时的依赖关系（而不仅仅是 ldd 命令所适用的加载时依赖关系）。

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


#### 参考资料:
《高级C/C++编译技术》: 12.4.1 strace
