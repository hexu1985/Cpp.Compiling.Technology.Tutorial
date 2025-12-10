### 示例项目分析：第1阶段（初始版本）

在理解了基本实现要素（版本脚本和`/`或`.symver`汇编指令）的工作原理后，现在可以更深入地考察实际案例。
为阐明关键要点，让我们回到最初用于演示链接器版本脚本的示例（即包含三个函数的libsimple.so库，其中前两个函数将应用符号版本控制）。
为使演示更具说服力，我们会在原始代码中添加一些printf语句

file: simple.h
```c
#pragma once
int first_function(int x);
int second_function(int x);
int third_function(int x);
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
```

file: simpleVersionScript

```
LIBSIMPLE_1.0 {
    global:
         first_function; second_function;
     
    local:
         *;
};
```

file: build.sh

```bash
gcc -Wall -g -O0 -fPIC -c simple.c
gcc -shared simple.o -Wl,--version-script,simpleVersionScript -o libsimple.so
```

既然库文件已构建完成，让我们进一步探究ELF格式是如何支持符号版本控制这一概念的。

**ELF格式支持机制**

对库文件的节区分析显示，存在三个名称高度相似的节区专门用于承载版本信息，如下所示：

```bash
$ readelf -S libsimple.so
There are 37 section headers, starting at offset 0x3b20:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .note.gnu.pr[...] NOTE             00000000000002a8  000002a8
       0000000000000020  0000000000000000   A       0     0     8
  [ 2] .note.gnu.bu[...] NOTE             00000000000002c8  000002c8
       0000000000000024  0000000000000000   A       0     0     4
  [ 3] .gnu.hash         GNU_HASH         00000000000002f0  000002f0
       0000000000000030  0000000000000000   A       4     0     8
  [ 4] .dynsym           DYNSYM           0000000000000320  00000320
       00000000000000d8  0000000000000018   A       5     1     8
  [ 5] .dynstr           STRTAB           00000000000003f8  000003f8
       00000000000000b2  0000000000000000   A       0     0     1
  [ 6] .gnu.version      VERSYM           00000000000004aa  000004aa
       0000000000000012  0000000000000002   A       4     0     2
  [ 7] .gnu.version_d    VERDEF           00000000000004c0  000004c0
       0000000000000038  0000000000000000   A       5     2     8
  [ 8] .gnu.version_r    VERNEED          00000000000004f8  000004f8
       0000000000000020  0000000000000000   A       5     1     8
...
```

通过使用-V命令行参数调用readelf工具，可以非常清晰地展示这些节区的内容详情，如下所示：

```bash
$ readelf -V libsimple.so

Version symbols section '.gnu.version' contains 9 entries:
 Addr: 0x00000000000004aa  Offset: 0x000004aa  Link: 4 (.dynsym)
  000:   0 (*local*)       1 (*global*)      3 (GLIBC_2.2.5)   1 (*global*)
  004:   1 (*global*)      3 (GLIBC_2.2.5)   2 (LIBSIMPLE_1.0)   2 (LIBSIMPLE_1.0)
  008:   2 (LIBSIMPLE_1.0)

Version definition section '.gnu.version_d' contains 2 entries:
 Addr: 0x00000000000004c0  Offset: 0x000004c0  Link: 5 (.dynstr)
  000000: Rev: 1  Flags: BASE  Index: 1  Cnt: 1  Name: libsimple.so
  0x001c: Rev: 1  Flags: none  Index: 2  Cnt: 1  Name: LIBSIMPLE_1.0

Version needs section '.gnu.version_r' contains 1 entry:
 Addr: 0x00000000000004f8  Offset: 0x000004f8  Link: 5 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 1
  0x0010:   Name: GLIBC_2.2.5  Flags: none  Version: 3
```

显而易见：

- `.gnu.version_d` 节段记录了该特定库内定义的版本信息（节段名称中的“_d”后缀即源于此）。
- `.gnu.version_r` 节段描述了该库所引用的其他库的版本信息（节段名称中的“_r”后缀即源于此）。
- `.gnu_version` 节段则汇总了与该库相关的所有版本信息列表。

此时值得关注的是，需要验证版本信息是否已与版本脚本中指定的符号正确关联。

在用于查看二进制文件符号的所有可用方法（nm、objdump、readelf）中，readelf工具再次以最优形式给出了答案。
如下所示，符号与指定版本信息的关联关系通过该工具得以清晰展现。

```bash
$ readelf --wide --symbols libsimple.so | grep function
     7: 000000000000114e    53 FUNC    GLOBAL DEFAULT   15 second_function@@LIBSIMPLE_1.0
     8: 0000000000001119    53 FUNC    GLOBAL DEFAULT   15 first_function@@LIBSIMPLE_1.0
    17: 0000000000001183    53 FUNC    LOCAL  DEFAULT   15 third_function
    28: 0000000000001119    53 FUNC    GLOBAL DEFAULT   15 first_function
    29: 000000000000114e    53 FUNC    GLOBAL DEFAULT   15 second_function
$
$ readelf --wide --dyn-syms libsimple.so | grep function
     7: 000000000000114e    53 FUNC    GLOBAL DEFAULT   15 second_function@@LIBSIMPLE_1.0
     8: 0000000000001119    53 FUNC    GLOBAL DEFAULT   15 first_function@@LIBSIMPLE_1.0
```

显然，版本脚本中指定并传递给链接器的版本信息已成功嵌入二进制文件，并确实成为需要版本控制的符号属性。

值得玩味的是，对二进制文件的反汇编却显示：并不存在所谓的first_function@@LIBVERSIONDEMO_1.0这类实体。
实际能查找到的只有真实函数first_function的符号。运行时通过gdb进行反汇编也呈现相同结果。

由此可见，带有符号版本信息修饰的导出符号实质上是一种（虽有用但终究属于）虚构的概念，
而最终真正发挥作用的，始终是实际存在的函数本身的符号。


**版本符号信息向客户端二进制文件的传递**

当检查链接到您已添加符号版本控制的动态库的客户端二进制文件时，又会有一轮有趣的发现。
为了深入探索符号版本控制在这一特定方向上的作用，我们创建一个引用带版本符号的简单演示应用程序，如下代码所示。

file: main.c
```c
#include <stdio.h>
#include "simple.h"

int main(int argc, char* argv[])
{
    int nFirst  = first_function(1);
    int nSecond = second_function(2);
    int nRetValue = nFirst + nSecond;
    printf("first(1) + second(2) = %d\n", nRetValue);
    return nRetValue;
}
```

file: build.sh
```bash
gcc -g -O0 -c -I../sharedLib main.c
gcc main.o -Wl,-L../sharedLib -lsimple \
           -Wl,-R../sharedLib -o firstDemoApp
```

请注意，为了纯粹验证符号版本控制机制，我们在此有意省略了对库文件soname的指定。

不出所料，作为ELF格式二进制文件的演示应用同样包含了版本相关的段：

```bash
$ readelf -S ./firstDemoApp
There are 37 section headers, starting at offset 0x3ba0:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.gnu.pr[...] NOTE             0000000000000338  00000338
       0000000000000030  0000000000000000   A       0     0     8
  [ 3] .note.gnu.bu[...] NOTE             0000000000000368  00000368
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .note.ABI-tag     NOTE             000000000000038c  0000038c
       0000000000000020  0000000000000000   A       0     0     4
  [ 5] .gnu.hash         GNU_HASH         00000000000003b0  000003b0
       0000000000000024  0000000000000000   A       6     0     8
  [ 6] .dynsym           DYNSYM           00000000000003d8  000003d8
       00000000000000d8  0000000000000018   A       7     1     8
  [ 7] .dynstr           STRTAB           00000000000004b0  000004b0
       00000000000000d6  0000000000000000   A       0     0     1
  [ 8] .gnu.version      VERSYM           0000000000000586  00000586
       0000000000000012  0000000000000002   A       6     0     2
  [ 9] .gnu.version_r    VERNEED          0000000000000598  00000598
       0000000000000050  0000000000000000   A       7     2     8
```

更重要的是，演示动态库的符号版本信息已通过链接过程被客户端二进制文件吸收，如下：

```bash
$ readelf -V ./firstDemoApp

Version symbols section '.gnu.version' contains 9 entries:
 Addr: 0x0000000000000586  Offset: 0x00000586  Link: 6 (.dynsym)
  000:   0 (*local*)       2 (GLIBC_2.34)    1 (*global*)      3 (LIBSIMPLE_1.0)
  004:   3 (LIBSIMPLE_1.0)   4 (GLIBC_2.2.5)   1 (*global*)      1 (*global*)
  008:   4 (GLIBC_2.2.5)

Version needs section '.gnu.version_r' contains 2 entries:
 Addr: 0x0000000000000598  Offset: 0x00000598  Link: 7 (.dynstr)
  000000: Version: 1  File: libsimple.so  Cnt: 1
  0x0010:   Name: LIBSIMPLE_1.0  Flags: none  Version: 3
  0x0020: Version: 1  File: libc.so.6  Cnt: 2
  0x0030:   Name: GLIBC_2.2.5  Flags: none  Version: 4
  0x0040:   Name: GLIBC_2.34  Flags: none  Version: 2
```

正如先前描述的基于soname的版本控制场景那样，符号版本控制机制同样会从动态库传递给其客户端二进制文件。
如此一来，客户端二进制文件与动态库版本控制之间就建立了一种契约关系。

这为何如此重要？因为从客户端二进制文件与动态库链接完成的那一刻起，动态库的代码可能会经历大量变更，
并相应地衍生出多个次要版本和主要版本。

无论动态库如何变化，其客户端二进制文件都会继续携带着链接时存在的版本信息。
如果运行时恰好缺少那个特定版本（当然，也就缺少了与该特定版本相关的确切功能），系统就会明确提示向后兼容性已被破坏。

在继续深入之前，让我们先确保你的版本控制方案不会阻碍应用程序的运行。

```bash
$ ./firstDemoApp
 lib: first_function
 lib: second_function
first(1) + second(2) = 6
```

#### 参考资料:
《高级C/C++编译技术》: 10.2.2 基于符号的版本控制方案


