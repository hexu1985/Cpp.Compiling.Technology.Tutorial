### size命令

size命令可用于快速获取 ELF 各分段字节长度的直观信息。

```bash
$ size /usr/bin/gst-inspect-1.0
   text	   data	    bss	    dec	    hex	filename
  53121	   2188	     40	  55349	   d835	/usr/bin/gst-inspect-1.0
$
$ size /lib/x86_64-linux-gnu/libc.so.6
   text	   data	    bss	    dec	    hex	filename
2177222	  20328	  54832	2252382	 225e5e	/lib/x86_64-linux-gnu/libc.so.6
$
$ size idcard/libidcard.a
   text	   data	    bss	    dec	    hex	filename
   1028	     80	      1	   1109	    455	IDCard.cpp.o (ex idcard/libidcard.a)
   5681	     80	      0	   5761	   1681	IDCardFactory.cpp.o (ex idcard/libidcard.a)
```


#### 参考资料:
《高级C/C++编译技术》: 12.1.2 size实用程序
