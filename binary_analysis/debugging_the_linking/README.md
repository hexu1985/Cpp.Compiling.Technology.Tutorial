### 链接过程调试

在调试链接阶段，最强大的辅助工具之一或许是使用 LD_DEBUG 环境变量。
它不仅适用于测试构建过程，也可用于检查运行时的动态库加载情况。

```bash
$ LD_DEBUG=help cat
Valid options for the LD_DEBUG environment variable are:

  libs        display library search paths
  reloc       display relocation processing
  files       display progress for input file
  symbols     display symbol table processing
  bindings    display information about symbol binding
  versions    display version dependencies
  scopes      display scope information
  all         all previous options combined
  statistics  display relocation statistics
  unused      determined unused DSOs
  help        display this help message and exit

To direct the debugging output into a file instead of standard output
a filename can be specified using the LD_DEBUG_OUTPUT environment variable.
```

**查看库依赖关系**

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


#### 参考资料:
《高级C/C++编译技术》: 13.1 链接过程调试

