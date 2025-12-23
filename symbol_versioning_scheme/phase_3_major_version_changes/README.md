### 示例项目分析：第3阶段（主版本变更）

在先前分析的案例中，我探讨了新代码变更通常不影响客户端使用现有代码库的情况。这类变更被合理地归类为次版本迭代。

而本次我将聚焦于更为显著的变更场景--当代码修改严重影响了客户端原有的使用方式时，这类变更明确属于主版本升级范畴。

**ABI 函数行为变更的案例分析**

假设演示动态库的导出头文件完全没有改动，因此函数原型保持不变。但根据最新的设计要求，从今往后，first_function() 需要返回与以往不同的值。

```c
int first_function(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return 1000*(x+1);
}
```

不用说，这种改动注定会对现有客户端二进制文件造成严重破坏。现有的代码框架根本无法预料到这种数量级的值。
这种数值越界很可能会导致数组访问异常，在图表绘制场景中，数值会完全超出合理范围等。

因此现在你需要一种机制来确保：老客户仍能获得原有的处理方式（即现有客户端二进制文件调用first_function()时仍返回原值），
而新客户则可以享受全新设计带来的优势。

唯一的问题在于你必须解决这个冲突--同一个函数名需要在两种截然不同的场景中使用。
幸运的是，符号版本管理机制已被证明能够处理这类问题。

第一步，你需要修改版本脚本来表明对新主版本的支持，如下所示：

file: simpleVersionScript
```
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

LIBSIMPLE_2.0 {
    global:
         first_function;
    local:
         *;
};
```

接下来，你将应用基于.symver汇编指令的解决方案，具体代码如下所示。

```c
#include <stdio.h>
#include "simple.h"

__asm__(".symver first_function_1_0,first_function@LIBSIMPLE_1.0");
int first_function_1_0(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return (x+1);
}

__asm__(".symver first_function_2_0,first_function@@LIBSIMPLE_2.0");
int first_function_2_0(int x)
{
    printf(" lib: %s\n", __FUNCTION__);
    return 1000*(x+1);
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

如下所示，动态链接库现在新增了一项版本信息。

```bash
$ readelf -V libsimple.so

Version symbols section '.gnu.version' contains 13 entries:
 Addr: 0x0000000000000540  Offset: 0x00000540  Link: 4 (.dynsym)
  000:   0 (*local*)       1 (*global*)      5 (GLIBC_2.2.5)   1 (*global*)
  004:   1 (*global*)      5 (GLIBC_2.2.5)   3 (LIBSIMPLE_1.1)   2 (LIBSIMPLE_1.0)
  008:   4 (LIBSIMPLE_2.0)   2 (LIBSIMPLE_1.0)   4 (LIBSIMPLE_2.0)   3 (LIBSIMPLE_1.1)
  00c:   2h(LIBSIMPLE_1.0)

Version definition section '.gnu.version_d' contains 4 entries:
 Addr: 0x0000000000000560  Offset: 0x00000560  Link: 5 (.dynstr)
  000000: Rev: 1  Flags: BASE  Index: 1  Cnt: 1  Name: libsimple.so
  0x001c: Rev: 1  Flags: none  Index: 2  Cnt: 1  Name: LIBSIMPLE_1.0
  0x0038: Rev: 1  Flags: none  Index: 3  Cnt: 1  Name: LIBSIMPLE_1.1
  0x0054: Rev: 1  Flags: none  Index: 4  Cnt: 1  Name: LIBSIMPLE_2.0

Version needs section '.gnu.version_r' contains 1 entry:
 Addr: 0x00000000000005d0  Offset: 0x000005d0  Link: 5 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 1
  0x0010:   Name: GLIBC_2.2.5  Flags: none  Version: 5
```

有意思的是，如下所示，.symver指令看起来确实发挥了它的魔力。

```bash
$ readelf --wide --dyn-syms libsimple.so

Symbol table '.dynsym' contains 13 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTable
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5 (5)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (5)
     6: 00000000000011f3    53 FUNC    GLOBAL DEFAULT   15 fourth_function@@LIBSIMPLE_1.1
     7: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS LIBSIMPLE_1.0
     8: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS LIBSIMPLE_2.0
     9: 0000000000001189    53 FUNC    GLOBAL DEFAULT   15 second_function@@LIBSIMPLE_1.0
    10: 000000000000114e    59 FUNC    GLOBAL DEFAULT   15 first_function@@LIBSIMPLE_2.0
    11: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS LIBSIMPLE_1.1
    12: 0000000000001119    53 FUNC    GLOBAL DEFAULT   15 first_function@LIBSIMPLE_1.0
```

整个.symver方案的最终效果，在于神奇地导出了first_function()符号的两个版本——尽管实际上名为first_function()的函数已不复存在，
因为它已被first_function_1_0()和first_function_2_0()所取代。

为了清晰地展示实现差异，你将创建一个新应用程序，其源代码与之前版本并无不同

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
