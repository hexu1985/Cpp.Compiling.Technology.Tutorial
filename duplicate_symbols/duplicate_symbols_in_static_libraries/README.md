### 静态库中的重复符号

**重复符号的默认处理方式**

在将多个目标文件或静态库链接生成最终二进制文件时，链接器对重复符号采取零容忍策略。
当检测到重复符号时，链接器会输出错误信息，明确指出重复符号所在的文件及代码行号，并宣告链接失败。
这意味着开发人员必须重新检查并解决问题，通常需要对代码进行重新编译。

以下示例展示了当尝试将两个包含重复符号的静态库链接到同一个客户端二进制文件时发生的情况。
该项目包含两个非常简单的静态库（均存在重复符号）以及一个试图同时链接这两个库的客户端应用程序：

**Static Library libfirst.a:**

file: plain_and_simple/c/libFirst/staticlibfirstexports.h
```c
#pragma once

int staticlibfirst_function(int x);
int staticlib_duplicate_function(int x);
```

file: plain_and_simple/c/libFirst/staticlib.c
```c
#include <stdio.h>

int staticlibfirst_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+1);
}

int staticlib_duplicate_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+2);
}
```

file: plain_and_simple/c/libFirst/build.sh
```bash
gcc -Wall -g -O0 -c staticlib.c
ar -rcs libfirst.a staticlib.o
```

**Static Library libsecond.a:**

file: plain_and_simple/c/libFirst/staticlibsecondexports.h
```c
#pragma once

int staticlibsecond_function(int x);
int staticlib_duplicate_function(int x);
```

file: plain_and_simple/c/libSecond/staticlib.c
```c
#include <stdio.h>

int staticlibsecond_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+1);
}

int staticlib_duplicate_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+2);
}
```

file: plain_and_simple/c/libSecond/build.sh
```bash
gcc -Wall -g -O0 -c staticlib.c
ar -rcs libsecond.a staticlib.o
```

**ClientApplication:**

file: plain_and_simple/c/clientApp/main.c

```c
#include <stdio.h>
#include "staticlibfirstexports.h"
#include "staticlibsecondexports.h"

int main(int argc, char* argv[])
{
    int nRetValue = 0;
    nRetValue += staticlibfirst_function(1);
    nRetValue += staticlibsecond_function(2);
    nRetValue += staticlib_duplicate_function(3);
    printf("nRetValue = %d\n", nRetValue);
    return nRetValue;
}
```

file: plain_and_simple/c/clientApp/build.sh
```bash
gcc -Wall -g -O0 -I../libFirst -I../libSecond -c main.c
gcc main.o -L../libFirst -lfirst -L../libSecond -lsecond -o clientApp
```

由于两个静态库中都存在重复符号，尝试构建客户端应用程序会导致链接器报错：

```bash
/usr/bin/ld: ../libSecond/libsecond.a(staticlib.o): in function `staticlib_duplicate_function':
/home/hexu/git/Cpp.Compiling.Technology.Tutorial/duplicate_symbols/duplicates_in_two_static_libs/plain_and_simple/c/libSecond/staticlib.c:10: multiple definition of `staticlib_duplicate_function'; ../libFirst/libfirst.a(staticlib.o):/home/hexu/git/Cpp.Compiling.Technology.Tutorial/duplicate_symbols/duplicates_in_two_static_libs/plain_and_simple/c/libFirst/staticlib.c:10: first defined here
collect2: error: ld returned 1 exit status
```

注释掉对重复函数的调用并不能避免链接失败。显然，链接器会首先尝试整合所有来自输入静态库和独立目标文件（main.c）的内容。
如果在链接过程的早期阶段就出现重复符号，链接器会直接宣告失败——即使实际上并没有代码引用这些重复符号。

**局部符号可以重复**

有趣的是，用C语言static关键字声明的局部函数（即其作用域仅限于同一源文件中的函数）不会被识别为重复符号。
请使用以下代码修改示例中静态库的源文件：

file: static_functions_are_not_duplicates/c/libFirst/staticlib.c
```c
#include <stdio.h>

static int local_staticlib_duplicate_function(int x)
{
    printf("libfirst: %s\n", __FUNCTION__);
    return 0;	
}

int staticlibfirst_function(int x)
{
    printf("%s\n", __FUNCTION__);
    local_staticlib_duplicate_function(x);
    return (x+1);
}
```

file: static_functions_are_not_duplicates/c/libSecond/staticlib.c
```c
#include <stdio.h>

static int local_staticlib_duplicate_function(int x)
{
    printf("libsecond: %s\n", __FUNCTION__);
    return 0;	
}

int staticlibsecond_function(int x)
{
    printf("%s\n", __FUNCTION__);
    local_staticlib_duplicate_function(x);
    return (x+1);
}
```

**ClientApplication:**

file: static_functions_are_not_duplicates/c/clientApp/main.c

```c
#include <stdio.h>
#include "staticlibfirstexports.h"
#include "staticlibsecondexports.h"

int main(int argc, char* argv[])
{
    staticlibfirst_function(1);
    staticlibsecond_function(2);
    return 0;
}
```

客户端应用程序现在将成功构建并产生以下输出：

```bash
staticlibfirst_function
libfirst: local_staticlib_duplicate_function
staticlibsecond_function
libsecond: local_staticlib_duplicate_function
```

显然，链接器会隔离这些局部函数。即使这些函数的符号名称完全相同，也不会发生冲突。


#### 参考资料:
- 《高级C/C++编译技术》: 9.2 重复符号的默认处理
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/01_duplicateSymbolsCriteria/02_duplicatesInTwoStaticLibs
