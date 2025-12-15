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
