### 基本实现要素

符号版本控制方案通过链接器版本脚本与`.symver`汇编指令结合实现，接下来将对两者进行详细阐述。

**链接器版本脚本**

符号可见性控制机制最基础的实现方式，依赖于GNU链接器读取以版本脚本文本文件形式提供的符号版本信息。

我们从一个简单动态库（libsimple.so）的示例开始演示，该库包含三个函数。

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

现在假设你需要为前两个库函数（而非第三个！）添加版本信息。
指定符号版本的方法是通过创建一个相当简单的版本脚本文件，其内容可能类似如下代码。

file: simpleVersionScript
```
LIBSIMPLE_1.0 {
    global:
         first_function; second_function;
     
    local:
         *;
};
```

最后，现在让我们来构建这个动态库。可以通过专门的链接器参数，将版本脚本文件名传递给链接器，具体操作如下：

```bash
gcc -Wall -fPIC -c simple.c
gcc -shared simple.o -Wl,--version-script,simpleVersionScript -o libsimple.so.1.0.0
```

链接器会从脚本文件中提取信息，并将其嵌入到专用于版本控制的特定ELF格式节区中。
关于符号版本信息如何嵌入ELF二进制文件的更多细节，将在稍后展开说明。


**汇编指令.symver的作用**

与版本脚本文件作为符号版本控制概念“核心基础”（适用于所有阶段和场景）不同，
符号版本控制模式还依赖另一要素--`.symver`汇编指令——来解决棘手的边缘情况。

假设存在主版本变更的场景：函数签名在版本间未发生变化，但其底层功能已发生重大改动。
例如，某个函数原本返回链表元素数量，而在最新版本中被重新设计为返回链表所占用的总字节数（或反之）。
具体示例下：

```c
// VERSION 1.0:
unsigned long list_occupancy(struct List* pStart)
{
    // here we scan the list, and return the number of elements
    return nElements;
}
// VERSION 2.0:
unsigned long list_occupancy(struct List* pStart)
{
    // here we scan the list, but now return the total number of bytes
    return nElements*sizeof(struct List);
}
```


显然，使用该库第一版本的客户端将面临问题，因为函数返回的值不再符合预期。

如前所述，这种版本控制技术的核心原则是在同一二进制文件中提供同一符号的不同版本。
说起来容易，但如何实现呢？尝试同时构建两个函数版本会导致链接器报告符号重复。
幸运的是，GCC 编译器支持自定义的 `.symver` 汇编指令，这有助于缓解此问题

```c
__asm__(".symver list_occupancy_1_0, list_occupancy@MYLIBVERSION_1.0");
unsigned long list_occupancy_1_0(struct List* pStart)
{
    // here we scan the list, and return the number of elements
    return nElements;
}
                                    // default symbol version indicated by the additional "@"
                                    //                  |
                                    //                  v
__asm__(".symver list_occupancy_2_0, list_occupancy@@MYLIBVERSION_2.0");
unsigned long list_occupancy_2_0(struct List* pStart)
{
// here we scan the list, but now return the total number of bytes
return nElements*sizeof(struct List);
}
```

**该方案如何运作？**
为避免链接器遭遇符号重复问题，可以为同一函数的不同版本创建仅内部使用的专用名称（即不对外导出）。
例如本例中的 `list_occupancy_1_0` 和 `list_occupancy_2_0`。

但从外部视角看，链接器会生成带有预期函数名称（即 `list_occupancy()`）的符号，并附加对应的符号版本信息，
最终呈现为两个不同版本：`list_occupancy@MYLIBVERSION_1.0` 和 `list_occupancy@MYLIBVERSION_2.0`。

如此一来，新旧客户端二进制文件都能识别到它们期望的符号。旧版客户端会确认符号 `list_occupancy@MYLIBVERSION_1.0` 存在，
其对此中介函数符号的调用将在内部路由至正确的目标--即实际的动态库函数 `list_occupancy_1_0()`。

而全新的客户端二进制文件（无需关注先前版本历史）将选择默认符号--通过名称中额外的 `@` 字符标识
（本例中为 `list_occupancy@MYLIBVERSION_2.0`）。


#### 参考资料:
《高级C/C++编译技术》: 10.2.2 基于符号的版本控制方案

