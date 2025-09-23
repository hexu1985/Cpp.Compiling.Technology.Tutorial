### file命令

file命令行工具可用于识别各类文件的详细信息。它能快速检测二进制文件的基础属性，因此在日常操作中非常实用。
例如：

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

#### 参考资料:
《高级C/C++编译技术》: 12.1.1 file实用程序
