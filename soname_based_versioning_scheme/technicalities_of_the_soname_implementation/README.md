### SONAME实现的技术细节

尽管基于SONAME的方案在理论上非常稳固，但若其实现缺少一个关键环节，实际效力将大打折扣。
具体而言，SONAME会被嵌入到二进制文件中。ELF格式在动态段保留了专用字段，这些字段会根据用途承载SONAME信息。
在链接阶段，链接器会提取指定的SONAME字符串并将其插入到ELF格式的对应字段中。

SONAME的"隐秘使命"始于链接器将其嵌入动态库之时，其目的在于声明库的主版本号。然而这并非终点。
当客户端二进制文件链接动态库时，链接器会提取动态库的SONAME，并将其同样插入客户端二进制文件中——尽管此次目的略有不同：
用于声明客户端二进制文件的版本依赖要求。

**嵌入动态库文件的soname**

在构建动态库时，可通过专用链接器标志指定库的soname：

```bash
$ gcc -shared <链接器输入文件列表> -Wl,-soname,<soname> -o <库文件名>
```

链接器会将指定的soname字符串嵌入二进制文件的DT_SONAME字段中。如下所示：

```bash
$ ls -alg
total 20
drwxrwxr-x 2 hexu 4096 Nov  6 16:56 .
drwxrwxr-x 4 hexu 4096 Oct 22 17:26 ..
-rw-rw-r-- 1 hexu  172 Nov  6 16:55 build.sh
-rw-rw-r-- 1 hexu  120 Oct 22 17:26 shlibdemo.c
-rw-rw-r-- 1 hexu   46 Oct 22 17:26 shlibdemo.h
$ gcc -fPIC -c shlibdemo.c -o shlibdemo.o
$ gcc -shared shlibdemo.o -Wl,-soname,libshlibdemo.so.1 -o libshlibdemo.so.1.0.0
$ ls -alg
total 40
drwxrwxr-x 2 hexu  4096 Nov  6 17:09 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   172 Nov  6 17:02 build.sh
-rwxrwxr-x 1 hexu 15608 Nov  6 17:09 libshlibdemo.so.1.0.0
-rw-rw-r-- 1 hexu   124 Nov  6 17:08 shlibdemo.c
-rw-rw-r-- 1 hexu    46 Nov  6 17:02 shlibdemo.h
-rw-rw-r-- 1 hexu  1632 Nov  6 17:08 shlibdemo.o
$ readelf -d libshlibdemo.so.1.0.0

Dynamic section at offset 0x2df8 contains 25 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000e (SONAME)             Library soname: [libshlibdemo.so.1]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x1150
 0x0000000000000019 (INIT_ARRAY)         0x3de8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3df0
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x2f0
 0x0000000000000005 (STRTAB)             0x3c0
 0x0000000000000006 (SYMTAB)             0x318
 0x000000000000000a (STRSZ)              152 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000003 (PLTGOT)             0x3fe8
 0x0000000000000002 (PLTRELSZ)           24 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x530
 0x0000000000000007 (RELA)               0x488
 0x0000000000000008 (RELASZ)             168 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x468
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x458
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0
 ```

 **嵌入客户端二进制文件的soname**

当客户端二进制文件与动态库链接时（直接链接或通过软链接），链接器会获取动态库的soname并将其插入客户端二进制文件的DT_NEEDED字段中。如下所示：

```bash
$ ln -s libshlibdemo.so.1.0.0 libshlibdemo.so.1
$ ln -s libshlibdemo.so.1 libshlibdemo.so
$ ls -alg
total 40
drwxrwxr-x 2 hexu  4096 Nov  6 17:26 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   172 Nov  6 17:02 build.sh
lrwxrwxrwx 1 hexu    17 Nov  6 17:26 libshlibdemo.so -> libshlibdemo.so.1
lrwxrwxrwx 1 hexu    21 Nov  6 17:25 libshlibdemo.so.1 -> libshlibdemo.so.1.0.0
-rwxrwxr-x 1 hexu 15608 Nov  6 17:11 libshlibdemo.so.1.0.0
-rw-rw-r-- 1 hexu   124 Nov  6 17:08 shlibdemo.c
-rw-rw-r-- 1 hexu    46 Nov  6 17:02 shlibdemo.h
-rw-rw-r-- 1 hexu  1632 Nov  6 17:11 shlibdemo.o
$ cd ../driverApp/
$ ls -alg
total 16
drwxrwxr-x 2 hexu 4096 Nov  6 17:02 .
drwxrwxr-x 4 hexu 4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu  165 Nov  6 17:02 build.sh
-rw-rw-r-- 1 hexu  105 Nov  6 17:02 main.c
$ gcc -I../sharedLib -c main.c -o main.o
$ gcc main.o -Wl,-L../sharedLib -lshlibdemo -o demo
$ ls -alg
total 36
drwxrwxr-x 2 hexu  4096 Nov  6 17:58 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   165 Nov  6 17:02 build.sh
-rwxrwxr-x 1 hexu 15960 Nov  6 17:58 demo
-rw-rw-r-- 1 hexu   105 Nov  6 17:02 main.c
-rw-rw-r-- 1 hexu  1384 Nov  6 17:58 main.o
$ readelf -d demo

Dynamic section at offset 0x2db8 contains 28 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libshlibdemo.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x1168
 0x0000000000000019 (INIT_ARRAY)         0x3da8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3db0
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x3b0
 0x0000000000000005 (STRTAB)             0x480
 0x0000000000000006 (SYMTAB)             0x3d8
 0x000000000000000a (STRSZ)              174 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x3fb8
 0x0000000000000002 (PLTRELSZ)           24 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x630
 0x0000000000000007 (RELA)               0x570
 0x0000000000000008 (RELASZ)             192 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000000000001e (FLAGS)              BIND_NOW
 0x000000006ffffffb (FLAGS_1)            Flags: NOW PIE
 0x000000006ffffffe (VERNEED)            0x540
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x52e
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0
```

通过这种方式，soname承载的版本信息得以持续传递，从而在所有相关方（链接器、动态库文件、客户端二进制文件和加载器）之间建立起严格的版本规则。

与可被轻易修改的库文件名不同（从好奇心过剩的初学者到恶意黑客都可能随意更改），修改soname值既非易事也不切实际。
因为这不仅需要修改二进制文件，还要求操作者深入了解ELF格式规范。


**其他实用工具对SONAME的支持***

除了动态链接场景中的所有必要组件（链接器、二进制文件、加载器）外，其他工具也普遍支持SONAME概念。
其中，ldconfig实用程序就是典型代表。除了其原始职责范围外，该工具还具备一项"瑞士军刀"式的附加功能。

当传入`-n <目录>`命令行参数时，ldconfig会打开所有符合库命名规范的动态库文件，提取它们的SONAME，并为每个库创建名称与提取的SONAME相同的软链接。

而`-l <特定库文件>`选项则更加灵活，因为此时动态库文件名可以是任何合法的文件名。
无论文件名如何变化（无论是包含完整版本信息的原始库名，还是经过大幅修改的文件名），
ldconfig都能从指定文件中提取嵌入的SONAME，并正确创建明确指向该库文件的软链接。

为验证此功能，我们进行了一个小实验：故意修改原始库名称后，ldconfig依然成功创建了正确的软链接。如下所示：

```bash
$ ls -alg
total 40
drwxrwxr-x 2 hexu  4096 Nov  6 18:21 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   172 Nov  6 17:02 build.sh
-rwxrwxr-x 1 hexu 15608 Nov  6 17:11 libshlibdemo.so.1.0.0
-rw-rw-r-- 1 hexu   124 Nov  6 17:08 shlibdemo.c
-rw-rw-r-- 1 hexu    46 Nov  6 17:02 shlibdemo.h
-rw-rw-r-- 1 hexu  1632 Nov  6 17:11 shlibdemo.o
$ mv libshlibdemo.so.1.0.0 purposefullyChangedName
$ ls -alg
total 40
drwxrwxr-x 2 hexu  4096 Nov  6 18:22 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   172 Nov  6 17:02 build.sh
-rwxrwxr-x 1 hexu 15608 Nov  6 17:11 purposefullyChangedName
-rw-rw-r-- 1 hexu   124 Nov  6 17:08 shlibdemo.c
-rw-rw-r-- 1 hexu    46 Nov  6 17:02 shlibdemo.h
-rw-rw-r-- 1 hexu  1632 Nov  6 17:11 shlibdemo.o
$ ldconfig -l purposefullyChangedName
$ ls -alg
total 40
drwxrwxr-x 2 hexu  4096 Nov  6 18:22 .
drwxrwxr-x 4 hexu  4096 Nov  6 17:02 ..
-rw-rw-r-- 1 hexu   172 Nov  6 17:02 build.sh
lrwxrwxrwx 1 hexu    23 Nov  6 18:22 libshlibdemo.so.1 -> purposefullyChangedName
-rwxrwxr-x 1 hexu 15608 Nov  6 17:11 purposefullyChangedName
-rw-rw-r-- 1 hexu   124 Nov  6 17:08 shlibdemo.c
-rw-rw-r-- 1 hexu    46 Nov  6 17:02 shlibdemo.h
-rw-rw-r-- 1 hexu  1632 Nov  6 17:11 shlibdemo.o
```


#### 参考资料:
《高级C/C++编译技术》: 10.2.1 基于soname的版本控制方案

