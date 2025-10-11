### 确定动态库入口点

在查找动态库的入口点时，分析过程并不简单。虽然可以使用"确定可执行文件入口点"中提到的方法，
但获得的信息（通常是一个低位十六进制数值，例如0x390）实际参考价值有限。
由于动态库会被映射到客户端二进制进程的内存空间中，其真正的入口点只能在运行时才能确定。

最简便的方法可能是在GNU调试器中运行加载该动态库的可执行文件。
若设置了LD_DEBUG环境变量，调试器将打印出已加载库的相关信息。
此时只需在main()函数处设置断点——无论该可执行文件是否针对调试编译，这个符号都很可能存在。

当动态库以静态方式链接时，程序执行到断点处时，库的加载过程其实已经完成。

若是运行时动态加载的情况，最便捷的方式或许是将终端的大量输出内容重定向至文件，以便后续查看。

下面展示了基于LD_DEBUG变量的检测方法：

```bash
$ LD_DEBUG=files gdb -q ./FactoryMethod
     55974:	
     55974:	file=libreadline.so.8 [0];  needed by gdb [0]
     55974:	file=libreadline.so.8 [0];  generating link map
     55974:	  dynamic: 0x00007065deb84640  base: 0x00007065deb38000   size: 0x0000000000053dc0
     55974:	    entry: 0x00007065deb38000  phdr: 0x00007065deb38040  phnum:                 11
     55974:	
     55974:	
     55974:	file=libz.so.1 [0];  needed by gdb [0]
     55974:	file=libz.so.1 [0];  generating link map
     55974:	  dynamic: 0x00007065deb36df0  base: 0x00007065deb1c000   size: 0x000000000001b0b8
     55974:	    entry: 0x00007065deb1c000  phdr: 0x00007065deb1c040  phnum:                 11
                                .
                                .
                                .
     55974:	calling init: /lib/x86_64-linux-gnu/libreadline.so.8
     55974:	
     55974:	
     55974:	initialize program: gdb
     55974:	
     55974:	
     55974:	transferring control: gdb
     55974:	
Reading symbols from ./FactoryMethod...
(No debugging symbols found in ./FactoryMethod)
(gdb) start
Temporary breakpoint 1 at 0x23f1
Starting program: /home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/nm_command/cxx/build/FactoryMethod 
     55984:	
     55984:	file=libtinfo.so.6 [0];  needed by /bin/bash [0]
     55984:	file=libtinfo.so.6 [0];  generating link map
     55984:	  dynamic: 0x00007ffff7f9bb18  base: 0x00007ffff7f6b000   size: 0x0000000000031920
     55984:	    entry: 0x00007ffff7f6b000  phdr: 0x00007ffff7f6b040  phnum:                 11
     55984:	
     55984:	
     55984:	file=libc.so.6 [0];  needed by /bin/bash [0]
     55984:	file=libc.so.6 [0];  generating link map
     55984:	  dynamic: 0x00007ffff7e19bc0  base: 0x00007ffff7c00000   size: 0x0000000000228e50
     55984:	    entry: 0x00007ffff7c29f50  phdr: 0x00007ffff7c00040  phnum:                 14
                                .
                                .
                                .
     55984:	
     55984:	file=libidcard.so [0];  needed by /home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/nm_command/cxx/build/FactoryMethod [0]
     55984:	file=libidcard.so [0];  generating link map
     55984:	  dynamic: 0x00007ffff7fb9dc0  base: 0x00007ffff7fb2000   size: 0x0000000000008278
     55984:	    entry: 0x00007ffff7fb2000  phdr: 0x00007ffff7fb2040  phnum:                 11
     55984:	
     55984:	
     55984:	file=libframework.so [0];  needed by /home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/nm_command/cxx/build/FactoryMethod [0]
     55984:	file=libframework.so [0];  generating link map
     55984:	  dynamic: 0x00007ffff7fb0e00  base: 0x00007ffff7fad000   size: 0x0000000000004040
     55984:	    entry: 0x00007ffff7fad000  phdr: 0x00007ffff7fad040  phnum:                 11
     55984:	
```

#### 参考资料:
《高级C/C++编译技术》: 13.3.2 确定动态库入口点
