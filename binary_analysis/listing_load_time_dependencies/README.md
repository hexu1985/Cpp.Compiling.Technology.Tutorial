### 列出加载时依赖项

要列出可执行文件（应用程序和/或共享库）在加载时依赖的共享库集合，请仔细阅读关于ldd命令的讨论（其中提到了ldd方法和基于objdump的更安全方法）。

简而言之，运行：

```bash
$ ldd <二进制文件路径>
```

将提供完整的依赖项列表。

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

或者，使用objdump或readelf检查二进制文件的动态段是更安全的选择，但代价是只提供第一层依赖关系：

```bash
$ objdump -p /路径/程序 | grep NEEDED
$ readelf -d /路径/程序 | grep NEEDED
```

```bash
$ objdump -p FactoryMethod | grep NEEDED
  NEEDED               libidcard.so
  NEEDED               libframework.so
  NEEDED               libstdc++.so.6
  NEEDED               libgcc_s.so.1
  NEEDED               libc.so.6
```

```bash
$ readelf -d FactoryMethod | grep NEEDED
 0x0000000000000001 (NEEDED)             Shared library: [libidcard.so]
 0x0000000000000001 (NEEDED)             Shared library: [libframework.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 ```

#### 参考资料:
《高级C/C++编译技术》: 13.9 查看加载时依赖项
