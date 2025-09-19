### 动态库ABI符号和另一个动态库局部符号冲突

为演示此特定场景，我们创建了以下示例项目。
该项目包含两个共享库（均具有重复的ABI符号），客户端应用程序对这两个动态库进行静态链接。

**Shared Library libfirst.so:**

file: shlibFirst/shlibfirstexports.h
```c
#pragma once

int shlib_function(void);
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

int shlibsecond_function(void);
```

file: shlibSecond/shlib.c
```c
#include <stdio.h>

static int shlib_function(void)
{
	printf("shlibSecond: %s\n", __FUNCTION__);
	return 0;
}

int shlibsecond_function(void)
{
	printf("%s\n", __FUNCTION__);
	shlib_function();
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
    shlib_function();
    shlibsecond_function();
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

客户端应用程序构建成功，并产生以下输出：

```bash
$ ./clientApp
shlibFirst: shlib_function
shlibsecond_function
shlibSecond: shlib_function
```

此处我们遇到一个有趣的情况。
首先，当客户端二进制文件调用重名函数shlib_function时，链接器毫无疑问会选择shlibFirst库中的版本来代表该符号，
这仅仅是因为它位于更高优先级的代码区域。客户端应用程序输出的第一行正印证了这一事实。

然而，在链接器进行决策之前，在动态库本身的构建阶段，
shlibsecond_function()对其本地shlib_function()的内部调用早已完成解析——这仅仅是因为这两个符号在彼此本地可见。
这就是为什么一个shlibSecond函数对另一个shlibSecond函数的内部调用不会受到客户端二进制文件构建过程影响的原因。

正如预期的那样，当链接器的决策由代码区域优先级差异决定时，改变链接顺序不会对最终结果产生任何影响。


#### 参考资料:
- 《高级C/C++编译技术》: 9.4.3 案例3：动态库ABI符号和另一个动态库局部符号冲突
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/03_sharedLibsDuplicateEachOthersSymbols/02_duplicateABIwithVisibleSymbol/01_plainAndSimple/


