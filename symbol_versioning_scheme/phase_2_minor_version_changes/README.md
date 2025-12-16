### 示例项目分析：第2阶段（增改次版本号）

理解符号版本控制方案的基本运作原理后，即可开始模拟动态库开发过程中进行非破坏性变更（即次版本升级）的场景。
为尽可能贴近真实开发环境，我们将按以下步骤展开：

- 对动态库进行修改，新增若干函数。其中仅有一个新增函数会被导出，同时版本控制脚本将通过新增条目声明LIBSIMPLE_1.1次版本升级。

- 原始客户端二进制文件（即初始简易演示应用程序）将特意保持原状。不重新构建该程序的行为，将精确模拟遗留应用程序的使用场景——该程序是在动态库尚处于1.0初始版本时期构建的。

- 新的客户端二进制文件（另一个简单的演示应用程序）将被创建并链接至更新后的动态库。这种方式下，它将作为一个全新客户端二进制文件的示例——该文件基于最新最优的动态库1.1版本创建，且完全无需适配任何旧版库。

- 为简化演示流程，其代码与原始简易演示应用程序不会有显著差异，最值得注意的区别在于它将调用新增的ABI函数，该函数在最新的1.1版本之前并不存在。


下面代码展示了修改后动态库源文件的内容：


file: simple.h
```c
#pragma once

int first_function(int x);
int second_function(int x);
int third_function(int x);

int fourth_function(int x);
int fifth_function(int x);
```

file: simple.c
```c
#include <stdio.h>
#include "simple.h"

int first_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+1);
}

int second_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+2);
}

int third_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+3);
}

int fourth_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+4);
}

int fifth_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+5);
}
```

下面是版本脚本在修改后的样子：

simpleVersionScript
```bash
LIBSIMPLE_1.0 {
    global:
         first_function; second_function;
     
    local:
         *;
};

LIBSIMPLE_1.1 {
    global:
         fourth_function;
     
    local:
         *;
};
```

新的演示应用程序源代码文件如下：

file: main.c
```c
#include <stdio.h>
#include "simple.h"

int main(int argc, char* argv[])
{
    int nFirst  = first_function(1);
    int nSecond = second_function(2);
    int nFourth  = fourth_function(4);
    int nRetValue = nFirst + nSecond + nFourth;
    printf("first(1) + second(2) + fourth(4) = %d\n", nRetValue);
    return nRetValue;
}
```

现在让我们开始构建它：

```bash
gcc -g -O0 -c -I../sharedLib main.c
gcc main.o -Wl,-L../sharedLib -lsimple \
           -Wl,-R../sharedLib -o newerApp
```

现在，让我们更仔细地审视这次小型版本控制实践的效果，它完美模拟了动态库次版本升级时真实发生的情景。

首先，如下所示，版本信息不仅包含原始版本（1.0），还包含了最新版本（1.1）。

```bash
$ readelf -V libsimple.so

Version symbols section '.gnu.version' contains 11 entries:
 Addr: 0x00000000000004fa  Offset: 0x000004fa  Link: 4 (.dynsym)
  000:   0 (*local*)       1 (*global*)      4 (GLIBC_2.2.5)   1 (*global*)
  004:   1 (*global*)      4 (GLIBC_2.2.5)   3 (LIBSIMPLE_1.1)   2 (LIBSIMPLE_1.0)
  008:   2 (LIBSIMPLE_1.0)   2 (LIBSIMPLE_1.0)   3 (LIBSIMPLE_1.1)

Version definition section '.gnu.version_d' contains 3 entries:
 Addr: 0x0000000000000510  Offset: 0x00000510  Link: 5 (.dynstr)
  000000: Rev: 1  Flags: BASE  Index: 1  Cnt: 1  Name: libsimple.so
  0x001c: Rev: 1  Flags: none  Index: 2  Cnt: 1  Name: LIBSIMPLE_1.0
  0x0038: Rev: 1  Flags: none  Index: 3  Cnt: 1  Name: LIBSIMPLE_1.1

Version needs section '.gnu.version_r' contains 1 entry:
 Addr: 0x0000000000000568  Offset: 0x00000568  Link: 5 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 1
  0x0010:   Name: GLIBC_2.2.5  Flags: none  Version: 4
```

当前导出的符号集合已包含版本1.0和版本1.1的所有符号，如下所示：

```bash
$ readelf --wide --dyn-syms libsimple.so

Symbol table '.dynsym' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTable
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5 (4)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (4)
     6: 00000000000011b8    53 FUNC    GLOBAL DEFAULT   15 fourth_function@@LIBSIMPLE_1.1
     7: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS LIBSIMPLE_1.0
     8: 000000000000114e    53 FUNC    GLOBAL DEFAULT   15 second_function@@LIBSIMPLE_1.0
     9: 0000000000001119    53 FUNC    GLOBAL DEFAULT   15 first_function@@LIBSIMPLE_1.0
    10: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS LIBSIMPLE_1.1
```

现在让我们来看看，在版本1.1发布后首次构建的、更新更现代的客户端二进制文件（newerApp）情况如何。
如下所示，链接器读取了动态库支持的所有版本信息，并将其插入到新应用程序的客户端二进制文件中。

```bash
$ readelf -V ./newerApp

Version symbols section '.gnu.version' contains 10 entries:
 Addr: 0x00000000000005bc  Offset: 0x000005bc  Link: 6 (.dynsym)
  000:   0 (*local*)       2 (GLIBC_2.34)    1 (*global*)      3 (LIBSIMPLE_1.0)
  004:   4 (LIBSIMPLE_1.1)   3 (LIBSIMPLE_1.0)   5 (GLIBC_2.2.5)   1 (*global*)
  008:   1 (*global*)      5 (GLIBC_2.2.5)

Version needs section '.gnu.version_r' contains 2 entries:
 Addr: 0x00000000000005d0  Offset: 0x000005d0  Link: 7 (.dynstr)
  000000: Version: 1  File: libsimple.so  Cnt: 2
  0x0010:   Name: LIBSIMPLE_1.1  Flags: none  Version: 4
  0x0020:   Name: LIBSIMPLE_1.0  Flags: none  Version: 3
  0x0030: Version: 1  File: libc.so.6  Cnt: 2
  0x0040:   Name: GLIBC_2.2.5  Flags: none  Version: 5
  0x0050:   Name: GLIBC_2.34  Flags: none  Version: 2
```


客户端二进制文件在运行时依赖的动态库符号列表，同时包含了两个版本的符号。下面清晰地说明了这一点。

```bash
$ readelf --wide --dyn-syms ./newerApp

Symbol table '.dynsym' contains 10 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.34 (2)
     2: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTable
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND second_function@LIBSIMPLE_1.0 (3)
     4: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND fourth_function@LIBSIMPLE_1.1 (4)
     5: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND first_function@LIBSIMPLE_1.0 (3)
     6: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5 (5)
     7: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     8: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     9: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (5)
```

现在，为了验证新增功能和修改后的版本信息是否按预期工作，你可以尝试同时运行旧版和新版应用程序。
如下所示，运行旧版应用将证明动态库的新次版本并未带来任何意外问题。

```bash
$ ./newerApp 
 lib: first_function
 lib: second_function
 lib: fourth_function
first(1) + second(2) + fourth(4) = 14
$ ./firstDemoApp
 lib: first_function
 lib: second_function
first(1) + second(2) = 6
$
```


#### 参考资料:
《高级C/C++编译技术》: 10.2.2 基于符号的版本控制方案


