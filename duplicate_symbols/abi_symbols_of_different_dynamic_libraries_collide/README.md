### 不同动态库的ABI符号冲突

为演示此特定场景，我们创建了以下示例项目。
该项目包含两个共享库（均具有重复的ABI符号），客户端应用程序对这两个动态库进行静态链接。
需要补充几个重要细节：其中一个共享库的ABI函数内部会调用重复的ABI函数。

**Shared Library libfirst.so:**

file: shlibFirst/shlibfirstexports.h
```c
#pragma once

int shlib_function(void); // duplicate ABI function
int shlibfirst_function(void);
```

file: shlibFirst/shlib.c
```c
#include <stdio.h>

int shlib_function(void)
{
	printf("shlibFirst: %s\n", __FUNCTION__);
    return 0;
}

int shlibfirst_function(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}
```

file: shlibFirst/build.sh
```bash
gcc -Wall -g -O0 -c shlib.c 
gcc -shared shlib.o -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -s libfirst.so.1 libfirst.so
```

**Shared Library libsecond.so:**

file: shlibSecond/shlibsecondexports.h
```c
#pragma once

int shlib_function(void);
int shlibsecond_function(void);
int shlibsecond_another_function(void);
```

file: shlibSecond/shlib.c
```c
#include <stdio.h>

int shlib_function(void)
{
	printf("shlibSecond: %s\n", __FUNCTION__);
    return 0;
}

int shlibsecond_function(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int shlibsecond_another_function(void)
{
	printf("%s\n", __FUNCTION__);
	shlib_function();       // internal call to the duplicate ABI function
	return 0;
}
```

file: shlibSecond/build.sh
```bash
gcc -Wall -g -O0 -c shlib.c 
gcc -shared shlib.o -Wl,-soname,libsecond.so.1 -o libsecond.so.1.0.0
ldconfig -n .
ln -s libsecond.so.1 libsecond.so
```

**ClientApplication:**

file: clientApp/main.c
```c
#include <stdio.h>
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"

int main(int argc, char* argv[])
{
    shlib_function();    // duplicate ABI function
    shlibfirst_function();
    shlibsecond_function();
    shlibsecond_another_function(); // this one internally calls shlib_function()
    return 0;
}
```

file: clientApp/build.sh
```bash
gcc -Wall -g -O0 -I../shlibFirst -I../shlibSecond -c main.c
gcc main.o -Wl,-L../shlibFirst -lfirst   \
           -Wl,-L../shlibSecond -lsecond \
           -Wl,-R../shlibFirst           \
           -Wl,-R../shlibSecond          \
           -o clientApp
```

尽管两个共享库存在重复符号，且其中一个重复符号（shlib_duplicate_function）并非本地函数，但客户端应用程序仍能成功完成构建。
运行该客户端应用程序会产生以下输出：

```bash
$ ./clientApp
shlibFirst: shlib_function
shlibfirst_function
shlibsecond_function
shlibsecond_another_function
shlibFirst: shlib_function
```

显然，链接器选择了shlibFirst中的重复符号版本来唯一表示该重复符号名称。
此外，尽管shlibsecond_another_function()内部调用了重复的shlib_function()，但这并不影响链接阶段的最终结果。
作为ABI符号（.dynsym节的一部分），重复的函数符号始终以相同方式解析，即便它与其余ABI函数位于同一源文件这一事实也不会改变解析方式。

**1. 不同函数调用顺序的影响分析**

作为研究的一部分，我们还测试了调换函数调用顺序的影响。

file: clientApp/main_differentOrderOfCalls.c
```c
#include <stdio.h>
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"

int main(int argc, char* argv[])
{
	// Reverse order of calls - first shlibsecond methods
	// get called, followed by the shlibfirst methods
    shlibsecond_function();
    shlibsecond_another_function();
    shlib_function();    // duplicate ABI function
    shlibfirst_function();
    return 0;
}
```

file: clientApp/buildDifferentOrderOfCalls.sh
```bash
gcc -Wall -g -O0 -I../shlibFirst -I../shlibSecond -c main_differentOrderOfCalls.c
gcc main_differentOrderOfCalls.o         \
           -Wl,-L../shlibFirst  -lfirst  \
           -Wl,-L../shlibSecond -lsecond \
           -Wl,-R../shlibFirst           \
           -Wl,-R../shlibSecond          \
           -o clientAppDifferentOrderOfCalls
```

编译并运行该客户端应用程序会产生以下输出：
```bash
$ ./clientAppDifferentOrderOfCalls
shlibsecond_function
shlibsecond_another_function
shlibFirst: shlib_function
shlibFirst: shlib_function
shlibfirst_function
```

这一特定更改未对最终结果产生任何影响。
显然，深刻影响重复符号解析过程的链接阶段关键环节发生在更早期的链接阶段。(即连接器的链接阶段，而非装载器阶段)。

**2. 不同的链接顺序产生的影响**

然而以不同的链接顺序构建应用程序会产生不同的结果：

file: clientApp/buildDifferentLinkingOrder.sh
```bash
gcc -Wall -g -O0 -I../shlibFirst -I../shlibSecond -c main.c
gcc main.o -Wl,-L../shlibSecond -lsecond \
           -Wl,-L../shlibFirst  -lfirst  \
           -Wl,-R../shlibFirst           \
           -Wl,-R../shlibSecond          \
           -o clientAppDifferentLinkingOrder
```

编译并运行该客户端应用程序会产生以下输出：

```bash
$ ./clientAppDifferentLinkingOrder
shlibSecond: shlib_function
shlibfirst_function
shlibsecond_function
shlibsecond_another_function
shlibSecond: shlib_function
```

显然，指定相反的链接顺序影响了链接器的决策。现在选择的是shlibSecond中的重复shlib_function版本来代表该重复符号。


#### 参考资料:
- 《高级C/C++编译技术》: 9.4.2 案例2：不同动态库的ABI符号冲突
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/03_sharedLibsDuplicateEachOthersSymbols/01_duplicateABISymbol/01_plainAndSimple

