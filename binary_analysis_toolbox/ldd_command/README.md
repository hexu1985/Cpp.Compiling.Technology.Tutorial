### ldd命令

ldd是一款极其实用的工具，它能显示客户端二进制文件启动时需要静态加载的动态库的完整列表（即加载时依赖项）。

在分析加载时依赖关系时，ldd首先会检查二进制文件，
尝试定位由链接器（根据构建过程中的链接器命令行）嵌入的ELF格式字段，该字段记录了最直接依赖项的列表。

对于每一个嵌入在客户二进制文件中的动态库名称，ldd会按照运行时库位置搜索规则尝试定位其实际二进制文件。
一旦找到最直接依赖项的二进制文件，ldd就会运行其递归过程的下一阶段，尝试查找这些依赖项自身的依赖关系。
针对每个间接依赖项，ldd会进行新一轮的调查，如此循环往复。

当上述递归搜索完成后，ldd会收集所有报告的依赖项，剔除重复项，并最终输出结果。

```bash
$ ldd /usr/bin/gst-inspect-1.0
	linux-vdso.so.1 (0x00007ffded3f0000)
	libgstreamer-1.0.so.0 => /lib/x86_64-linux-gnu/libgstreamer-1.0.so.0 (0x000075b7282ee000)
	libglib-2.0.so.0 => /lib/x86_64-linux-gnu/libglib-2.0.so.0 (0x000075b7281b4000)
	libgobject-2.0.so.0 => /lib/x86_64-linux-gnu/libgobject-2.0.so.0 (0x000075b728154000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000075b727e00000)
	libgmodule-2.0.so.0 => /lib/x86_64-linux-gnu/libgmodule-2.0.so.0 (0x000075b72814d000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x000075b728066000)
	libunwind.so.8 => /lib/x86_64-linux-gnu/libunwind.so.8 (0x000075b728049000)
	libdw.so.1 => /lib/x86_64-linux-gnu/libdw.so.1 (0x000075b727d54000)
	libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x000075b727cde000)
	libffi.so.8 => /lib/x86_64-linux-gnu/libffi.so.8 (0x000075b72803c000)
	/lib64/ld-linux-x86-64.so.2 (0x000075b728470000)
	liblzma.so.5 => /lib/x86_64-linux-gnu/liblzma.so.5 (0x000075b727cb3000)
	libelf.so.1 => /lib/x86_64-linux-gnu/libelf.so.1 (0x000075b727c95000)
	libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x000075b727c79000)
	libbz2.so.1.0 => /lib/x86_64-linux-gnu/libbz2.so.1.0 (0x000075b727c66000)
```

在使用ldd工具前，必须了解其局限性：
- ldd无法识别通过调用dlopen()函数在运行时动态加载的库。要获取此类信息，需采用其他方法。
- 根据其手册页说明，运行某些版本的ldd可能构成安全威胁。

更安全的ldd替代方案

如手册页所述：

请注意，在某些情况下，某些版本的ldd可能会尝试通过直接执行程序来获取依赖信息。
因此，切勿对不可信的二进制文件使用ldd，因为这可能导致任意代码的执行。

处理不可信二进制文件时，更安全的替代方案如下：

`objdump -p /path/to/program | grep NEEDED`

```bash
$ objdump -p /usr/bin/gst-inspect-1.0 | grep NEEDED
  NEEDED               libgstreamer-1.0.so.0
  NEEDED               libglib-2.0.so.0
  NEEDED               libgobject-2.0.so.0
  NEEDED               libc.so.6
```

使用 readelf 工具也可以达到相同的效果。

`readelf -d /path/to/program | grep NEEDED`

```bash
$ readelf -d /usr/bin/gst-inspect-1.0 | grep NEEDED
 0x0000000000000001 (NEEDED)             共享库：[libgstreamer-1.0.so.0]
 0x0000000000000001 (NEEDED)             共享库：[libglib-2.0.so.0]
 0x0000000000000001 (NEEDED)             共享库：[libgobject-2.0.so.0]
 0x0000000000000001 (NEEDED)             共享库：[libc.so.6]
```

显然，在分析依赖关系时，这两种工具都仅限于从二进制文件中读取最直接的依赖项列表。
从安全角度来看，这无疑是更安全的查询方法。

然而，这种方法提供的列表远不如ldd通常生成的列表那样完整详尽。
若要达到同等的完整度，您可能需要自行进行递归搜索。


#### 参考资料:
《高级C/C++编译技术》: 12.2.1 ldd
